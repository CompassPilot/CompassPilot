import numpy as np
from opendbc.can import CANPacker
from opendbc.car import Bus, structs
from opendbc.car.lateral import apply_driver_steer_torque_limits, common_fault_avoidance
from opendbc.car.interfaces import CarControllerBase
from opendbc.car.rivian.riviancan import create_adas_status, create_lka_steering, create_longitudinal, create_wheel_touch
from opendbc.car.rivian.values import CarControllerParams

GearShifter = structs.CarState.GearShifter
TOI_MAX_ANGLE_DEG = 90
TOI_MAX_ANGLE_FRAMES = 89
TOI_BLIP_FRAMES = 2
HIGH_ANGLE_TORQUE_CAP = 0.95


def get_longitudinal_accel(requested_accel: float, gas_pressed: bool) -> float:
  # Keep Rivian's command stream continuous when Panda's gas safety check becomes active.
  if gas_pressed:
    return 0.0
  return float(np.clip(requested_accel, CarControllerParams.ACCEL_MIN, CarControllerParams.ACCEL_MAX))


class CarController(CarControllerBase):
  def __init__(self, dbc_names, CP):
    super().__init__(dbc_names, CP)
    self.apply_torque_last = 0
    self.packer = CANPacker(dbc_names[Bus.pt])

    self.cancel_frames = 0
    self.toi_angle_limit_counter = 0

  def update(self, CC, CS, now_nanos, starpilot_toggles):
    actuators = CC.actuators
    can_sends = []

    lat_active = CC.latActive and CS.out.gearShifter == GearShifter.drive
    apply_torque = 0
    steer_max = round(float(np.interp(CS.out.vEgoRaw, CarControllerParams.STEER_MAX_LOOKUP[0],
                                      CarControllerParams.STEER_MAX_LOOKUP[1])))
    if lat_active:
      new_torque = int(round(CC.actuators.torque * steer_max))
      apply_torque = apply_driver_steer_torque_limits(new_torque, self.apply_torque_last,
                                                      CS.out.steeringTorque, CarControllerParams, steer_max)
      if abs(CS.out.steeringAngleDeg) > TOI_MAX_ANGLE_DEG:
        high_angle_cap = round(steer_max * HIGH_ANGLE_TORQUE_CAP)
        apply_torque = int(np.clip(apply_torque, -high_angle_cap, high_angle_cap))

    # Clear both the request bit and torque during the high-angle fault-avoidance window.
    self.toi_angle_limit_counter, torque_request = common_fault_avoidance(
      abs(CS.out.steeringAngleDeg) >= TOI_MAX_ANGLE_DEG, lat_active,
      self.toi_angle_limit_counter, TOI_MAX_ANGLE_FRAMES, TOI_BLIP_FRAMES)
    torque_blip = lat_active and not torque_request
    if torque_blip:
      apply_torque = 0
    else:
      self.apply_torque_last = apply_torque
    can_sends.append(create_lka_steering(self.packer, self.frame, CS.acm_lka_hba_cmd,
                                         apply_torque, CC.enabled, torque_request))

    if self.frame % 5 == 0:
      can_sends.append(create_wheel_touch(self.packer, CS.sccm_wheel_touch, CC.enabled))

    # Longitudinal control
    if self.CP.openpilotLongitudinalControl:
      accel = get_longitudinal_accel(actuators.accel, CS.out.gasPressed)
      can_sends.append(create_longitudinal(self.packer, self.frame, accel, CC.enabled))
    else:
      interface_status = None
      if CC.cruiseControl.cancel:
        # if there is a noEntry, we need to send a status of "available" before the ACM will accept "unavailable"
        # send "available" right away as the VDM itself takes a few frames to acknowledge
        interface_status = 1 if self.cancel_frames < 5 else 0
        self.cancel_frames += 1
      else:
        self.cancel_frames = 0

      for msg in CS.vdm_adas_status:
        can_sends.append(create_adas_status(self.packer, msg, interface_status))

    new_actuators = actuators.as_builder()
    new_actuators.torque = apply_torque / steer_max
    new_actuators.torqueOutputCan = apply_torque
    self.frame += 1
    return new_actuators, can_sends
