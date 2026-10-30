import numpy as np
from opendbc.can import CANPacker
from opendbc.car import Bus, structs
from opendbc.car.common.conversions import Conversions as CV
from opendbc.car.lateral import apply_driver_steer_torque_limits
from opendbc.car.interfaces import CarControllerBase
from opendbc.car.rivian.ext_controller import ExternalController, get_safety_CP  # noqa: F401
from opendbc.car.rivian.riviancan import (create_acm_status, create_adas_status, create_angle_steering,
                                          create_lka_steering, create_longitudinal, create_wheel_touch)
from opendbc.car.rivian.values import CarControllerParams, RivianFlags

GearShifter = structs.CarState.GearShifter
LateralControlMode = structs.CarControl.Actuators.LateralControlMode

ANGLE_SPEED_HYSTERESIS = 1.0 * CV.MPH_TO_MS


def get_longitudinal_accel(requested_accel: float, gas_pressed: bool, long_active: bool = False,
                           v_ego: float = 0.0) -> float:
  # Keep Rivian's command stream continuous when Panda's gas safety check
  # disables longitudinal control before the controls process sees the pedal.
  if gas_pressed:
    return 0.0

  accel = requested_accel
  if long_active:
    accel += float(np.interp(v_ego, CarControllerParams.ACCEL_FF_DRAG_BP, CarControllerParams.ACCEL_FF_DRAG_V))
  return float(np.clip(accel, CarControllerParams.ACCEL_MIN, CarControllerParams.ACCEL_MAX))


class CarController(CarControllerBase):
  def __init__(self, dbc_names, CP):
    super().__init__(dbc_names, CP)
    self.apply_torque_last = 0
    self.packer = CANPacker(dbc_names[Bus.pt])

    self.cancel_frames = 0
    self.base_gen1 = CP.flags == 0
    self.angle_harness = bool(CP.flags & RivianFlags.ANGLE_HARNESS)
    self.longitudinal_harness = bool(CP.flags & RivianFlags.LONGITUDINAL_HARNESS)
    # GEN2 without a harness keeps the upstream torque path verbatim. Base GEN1
    # and Extreme harnesses use the ToI-handshaking external controller.
    self.ext_controller = ExternalController(CP) if (self.base_gen1 or self.angle_harness or self.longitudinal_harness) else None

    # Startup-selected angle preferences (see starpilot.vehicle_preferences).
    self.angle_control = False
    self.angle_speed_control = False
    self.angle_minimum_speed = 0.0
    self.angle_speed_active = False

  def update_live_params(self, roll, angle_offset_deg, stiffness_factor, steer_ratio):
    if self.ext_controller is not None:
      self.ext_controller.roll = roll
      self.ext_controller.angle_offset_deg = angle_offset_deg
      self.ext_controller.VM.update_params(max(stiffness_factor, 0.1), max(steer_ratio, 0.1))

  def _update_angle_request(self, v_ego: float) -> bool:
    if not self.angle_control or not self.angle_speed_control:
      self.angle_speed_active = False
      return self.angle_control

    minimum_speed = max(float(self.angle_minimum_speed), 0.0)
    if self.angle_speed_active:
      self.angle_speed_active = v_ego >= max(minimum_speed - ANGLE_SPEED_HYSTERESIS, 0.0)
    else:
      self.angle_speed_active = v_ego >= minimum_speed
    return self.angle_speed_active

  def _update_upstream_torque(self, CC, CS, steer_max, projection):
    # Preserve current upstream GEN2/unknown-profile behavior verbatim.
    lat_active = torque_request = CC.latActive
    apply_torque = 0
    if lat_active:
      new_torque = int(round(CC.actuators.torque * steer_max))
      if projection is not None:
        projection.input(new_torque, steer_max, self.apply_torque_last, CS.out.steeringTorque, CarControllerParams, limiter='driver')
      apply_torque = apply_driver_steer_torque_limits(new_torque, self.apply_torque_last,
                                                      CS.out.steeringTorque, CarControllerParams, steer_max)
    self.apply_torque_last = apply_torque
    return lat_active, apply_torque, torque_request

  def update(self, CC, CS, now_nanos):
    _projection = self.learning_projection_observer
    if _projection is not None:
      _projection.begin(CC.actuators.torque, self.frame)
    actuators = CC.actuators
    can_sends = []

    steer_max = round(float(np.interp(CS.out.vEgoRaw, CarControllerParams.STEER_MAX_LOOKUP[0],
                                      CarControllerParams.STEER_MAX_LOOKUP[1])))

    if self.ext_controller is None:
      lat_active, apply_torque, torque_request = self._update_upstream_torque(CC, CS, steer_max, _projection)
    else:
      lat_active = CC.latActive and CS.out.gearShifter == GearShifter.drive
      angle_requested = self.angle_harness and self._update_angle_request(CS.out.vEgo)
      self.ext_controller.force_torque = not angle_requested
      self.ext_controller.update(CS, lat_active, actuators, _projection)
      # A failed EPAS overlay recovery is reported as a temporary steering fault on the next CarState.
      CS.toi_recovery_failed = bool(self.ext_controller.toi_controller.recovery_failed)
      apply_torque = self.ext_controller.torque_cmd
      torque_request = self.ext_controller.toi_act_cmd
      self.apply_torque_last = apply_torque

    # send steering command
    can_sends.append(create_lka_steering(self.packer, self.frame, CS.acm_lka_hba_cmd, apply_torque, CC.enabled, torque_request))
    if _projection is not None:
      _projection.emit('rivian.ACM_lkaHbaCmd', apply_torque, torque_request, can_sends[-1])

    if self.angle_harness:
      can_sends.append(create_angle_steering(self.packer, self.frame, self.ext_controller.apply_angle_last,
                                             self.ext_controller.angle_active))
      feature_status = (1 if self.ext_controller.torque_active else 2) if lat_active else 0
      can_sends.append(create_acm_status(self.packer, self.frame, feature_status))

    if self.frame % 5 == 0 and not (self.CP.flags & RivianFlags.GEN2):
      can_sends.append(create_wheel_touch(self.packer, CS.sccm_wheel_touch, lat_active if self.angle_harness else CC.enabled))

    # Longitudinal control
    if self.CP.openpilotLongitudinalControl:
      if self.longitudinal_harness:
        accel = get_longitudinal_accel(actuators.accel, CS.out.gasPressed, CC.longActive, CS.out.vEgo)
        can_sends.append(create_longitudinal(self.packer, self.frame, accel, CC.enabled))

        # Keep the stock ACM from winding up an acceleration request which the
        # disconnected stock controller cannot apply.
        for msg in CS.vdm_adas_status:
          can_sends.append(create_adas_status(self.packer, msg, None, driver_override=0 if CC.enabled else None))
      else:
        if self.base_gen1:
          long_active = CC.enabled and CC.longActive and CS.out.gearShifter == GearShifter.drive
          accel = (float(np.clip(actuators.accel, CarControllerParams.ACCEL_MIN, CarControllerParams.ACCEL_MAX))
                   if long_active and not CS.out.gasPressed else 0.0)
        else:
          long_active = CC.enabled
          accel = float(np.clip(actuators.accel, CarControllerParams.ACCEL_MIN, CarControllerParams.ACCEL_MAX))
        can_sends.append(create_longitudinal(self.packer, self.frame, accel, long_active))
    else:
      interface_status = None
      if CC.cruiseControl.cancel:
        # if there is a noEntry, we need to send a status of "available" before the ACM will accept "unavailable"
        # send "available" right away as the VDM itself takes a few frames to acknowledge
        interface_status = 1 if self.cancel_frames < 5 else 0
        self.cancel_frames += 1
      else:
        self.cancel_frames = 0

      # Base GEN1 forwards the real stock cancel request (UP_1) for the whole
      # cancel; harnesses keep it only alongside the "available" handshake frames.
      cancel = CC.cruiseControl.cancel if self.base_gen1 else interface_status == 1
      for msg in CS.vdm_adas_status:
        can_sends.append(create_adas_status(self.packer, msg, interface_status, cancel=cancel))

    new_actuators = actuators.as_builder()
    new_actuators.torque = apply_torque / steer_max
    new_actuators.torqueOutputCan = apply_torque
    if self.ext_controller is not None:
      new_actuators.steeringAngleDeg = self.ext_controller.apply_angle_last
      if lat_active and self.ext_controller.toi_controller.recovering:
        new_actuators.lateralControlMode = LateralControlMode.torqueRecovering
      elif lat_active and (self.ext_controller.torque_active or self.ext_controller.torque_prearm):
        new_actuators.lateralControlMode = LateralControlMode.torque
      elif lat_active and self.ext_controller.angle_active:
        new_actuators.lateralControlMode = LateralControlMode.angle
      else:
        new_actuators.lateralControlMode = LateralControlMode.inactive

    self.frame += 1
    if _projection is not None:
      _projection.finish(new_actuators.torque)
    return new_actuators, can_sends
