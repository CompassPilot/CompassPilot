import numpy as np

from opendbc.can import CANPacker
from opendbc.car import Bus, structs
from opendbc.car.common.conversions import Conversions as CV
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
    self.angle_harness = bool(CP.flags & RivianFlags.ANGLE_HARNESS)
    self.angle_speed_active = False
    self.ext_controller = ExternalController(CP)
    self.toi_recovery_failed_last = None
    self.toi_recovery_params = None
    try:
      # Keep opendbc importable standalone while exposing controller-only state
      # to selfdrived's existing car-specific warning bridge.
      from openpilot.common.params import Params
      self.toi_recovery_params = Params(memory=True)
    except Exception:
      pass

  def _publish_toi_recovery_failed(self) -> None:
    params = getattr(self, "toi_recovery_params", None)
    if params is None:
      return

    failed = bool(self.ext_controller.toi_controller.recovery_failed)
    if failed != getattr(self, "toi_recovery_failed_last", None):
      put_bool = getattr(params, "put_bool_nonblocking", None) or params.put_bool
      put_bool("RivianToiRecoveryFailed", failed)
      self.toi_recovery_failed_last = failed

  def _update_angle_request(self, starpilot_toggles, v_ego: float) -> bool:
    angle_control = bool(getattr(starpilot_toggles, "rivian_angle_control", False))
    speed_control = bool(getattr(starpilot_toggles, "rivian_angle_speed_control", False))
    if not angle_control or not speed_control:
      self.angle_speed_active = False
      return angle_control

    minimum_speed = max(float(getattr(starpilot_toggles, "rivian_angle_minimum_speed", 0.0)), 0.0)
    if self.angle_speed_active:
      self.angle_speed_active = v_ego >= max(minimum_speed - ANGLE_SPEED_HYSTERESIS, 0.0)
    else:
      self.angle_speed_active = v_ego >= minimum_speed
    return self.angle_speed_active

  def update(self, CC, CS, now_nanos, starpilot_toggles):
    actuators = CC.actuators
    can_sends = []

    lat_active = CC.latActive and CS.out.gearShifter == GearShifter.drive
    steer_max = round(float(np.interp(CS.out.vEgoRaw, CarControllerParams.STEER_MAX_LOOKUP[0],
                                      CarControllerParams.STEER_MAX_LOOKUP[1])))

    angle_requested = self.angle_harness and self._update_angle_request(starpilot_toggles, CS.out.vEgo)
    self.ext_controller.force_torque = not angle_requested
    self.ext_controller.update(CS, lat_active, actuators)
    self._publish_toi_recovery_failed()
    apply_torque = self.ext_controller.torque_cmd
    self.apply_torque_last = apply_torque
    can_sends.append(create_lka_steering(self.packer, self.frame, CS.acm_lka_hba_cmd,
                                         apply_torque, CC.enabled, self.ext_controller.toi_act_cmd))
    if self.angle_harness:
      can_sends.append(create_angle_steering(self.packer, self.frame, self.ext_controller.apply_angle_last,
                                             self.ext_controller.angle_active))
      feature_status = (1 if self.ext_controller.torque_active else 2) if lat_active else 0
      can_sends.append(create_acm_status(self.packer, self.frame, feature_status))

    if self.frame % 5 == 0 and not (self.CP.flags & RivianFlags.GEN2):
      can_sends.append(create_wheel_touch(self.packer, CS.sccm_wheel_touch, lat_active if self.angle_harness else CC.enabled))

    if self.CP.openpilotLongitudinalControl:
      accel = get_longitudinal_accel(actuators.accel, CS.out.gasPressed, CC.longActive, CS.out.vEgo)
      can_sends.append(create_longitudinal(self.packer, self.frame, accel, CC.enabled))

      # Keep the stock ACM from winding up an acceleration request which the
      # disconnected stock controller cannot apply.
      for msg in CS.vdm_adas_status:
        can_sends.append(create_adas_status(self.packer, msg, None, 0 if CC.enabled else None))
    else:
      interface_status = None
      if CC.cruiseControl.cancel:
        # The ACM accepts unavailable only after first seeing available.
        interface_status = 1 if self.cancel_frames < 5 else 0
        self.cancel_frames += 1
      else:
        self.cancel_frames = 0

      for msg in CS.vdm_adas_status:
        can_sends.append(create_adas_status(self.packer, msg, interface_status))

    new_actuators = actuators.as_builder()
    new_actuators.torque = apply_torque / steer_max
    new_actuators.torqueOutputCan = apply_torque
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
    return new_actuators, can_sends
