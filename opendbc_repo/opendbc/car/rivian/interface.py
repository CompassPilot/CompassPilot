from opendbc.car import get_safety_config, structs
from opendbc.car.interfaces import CarInterfaceBase
from opendbc.car.rivian.carcontroller import CarController
from opendbc.car.rivian.carstate import CarState
from opendbc.car.rivian.radar_interface import RadarInterface
from opendbc.car.rivian.values import RivianFlags, RivianSafetyFlags


class CarInterface(CarInterfaceBase):
  CarState = CarState
  CarController = CarController
  RadarInterface = RadarInterface

  @staticmethod
  def _get_params(ret: structs.CarParams, candidate, fingerprint, car_fw, alpha_long, is_release, docs) -> structs.CarParams:
    ret.brand = "rivian"

    ret.safetyConfigs = [get_safety_config(structs.CarParams.SafetyModel.rivian)]

    angle_harness = 0x1310 in fingerprint[1]
    longitudinal_harness = 0x131A in fingerprint[1]
    ret.dashcamOnly = not angle_harness

    if angle_harness:
      ret.flags |= RivianFlags.ANGLE_HARNESS.value
      ret.safetyConfigs[0].safetyParam |= RivianSafetyFlags.ANGLE_CONTROL.value

    if longitudinal_harness:
      ret.flags |= RivianFlags.LONGITUDINAL_HARNESS.value

    ret.steerActuatorDelay = 0.1 if angle_harness else 0.15
    ret.lateralSmoothSeconds = 0.4 if angle_harness else 0.0
    ret.steerAtStandstill = angle_harness
    ret.steerLimitTimer = 0.4
    CarInterfaceBase.configure_torque_tune(candidate, ret.lateralTuning)

    ret.steerControlType = structs.CarParams.SteerControlType.torque
    ret.radarUnavailable = not longitudinal_harness
    ret.enableBsm = longitudinal_harness

    ret.alphaLongitudinalAvailable = longitudinal_harness
    if alpha_long and ret.alphaLongitudinalAvailable:
      ret.openpilotLongitudinalControl = True
      ret.safetyConfigs[0].safetyParam |= RivianSafetyFlags.LONG_CONTROL.value

    ret.longitudinalActuatorDelay = 0.2
    ret.vEgoStopping = 0.25
    ret.stopAccel = -0.2
    ret.longitudinalTuning.kiBP = [0.]
    ret.longitudinalTuning.kiV = [0.2]

    return ret
