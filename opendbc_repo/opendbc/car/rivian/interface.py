from opendbc.car import get_safety_config, structs
from opendbc.car.interfaces import CarInterfaceBase
from opendbc.car.rivian.carcontroller import CarController
from opendbc.car.rivian.carstate import CarState
from opendbc.car.rivian.radar_interface import RadarInterface
from opendbc.car.rivian.values import CAR, RivianFlags, RivianSafetyFlags

# Extreme harness bridge identifiers on bus 1.
ANGLE_HARNESS_ADDR = 0x1310
LONGITUDINAL_HARNESS_ADDR = 0x131A


class CarInterface(CarInterfaceBase):
  CarState = CarState
  CarController = CarController
  RadarInterface = RadarInterface

  @staticmethod
  def _get_params(ret: structs.CarParams, candidate, fingerprint, car_fw, alpha_long, is_release, docs) -> structs.CarParams:
    ret.brand = "rivian"

    ret.safetyConfigs = [get_safety_config(structs.CarParams.SafetyModel.rivian)]
    if candidate == CAR.RIVIAN_R1T:
      ret.safetyConfigs[0].safetyParam |= RivianSafetyFlags.R1T.value

    # GEN2 (2025+) doesn't have SCCM_WheelTouch on the bus
    if 0x321 not in fingerprint[0]:
      ret.flags |= RivianFlags.GEN2.value

    angle_harness = ANGLE_HARNESS_ADDR in fingerprint[1]
    longitudinal_harness = LONGITUDINAL_HARNESS_ADDR in fingerprint[1]

    if angle_harness:
      ret.flags |= RivianFlags.ANGLE_HARNESS.value
      ret.safetyConfigs[0].safetyParam |= RivianSafetyFlags.ANGLE_CONTROL.value
      ret.steerActuatorDelay = 0.1
      ret.steerAtStandstill = True
    else:
      ret.steerActuatorDelay = 0.15
      ret.steerAtStandstill = False

    if longitudinal_harness:
      ret.flags |= RivianFlags.LONGITUDINAL_HARNESS.value

    ret.steerLimitTimer = 0.4
    CarInterfaceBase.configure_torque_tune(candidate, ret.lateralTuning)

    ret.steerControlType = structs.CarParams.SteerControlType.torque

    if longitudinal_harness:
      # The bridge supplies the radar, blind spot and wheel-button channels.
      ret.radarUnavailable = False
      ret.deprecated.enableBsm = True
      ret.alphaLongitudinalAvailable = True
    else:
      ret.radarUnavailable = True
      # TODO is GEN2 the same?
      ret.alphaLongitudinalAvailable = docs or not (ret.flags & RivianFlags.GEN2)

    if alpha_long and ret.alphaLongitudinalAvailable:
      ret.openpilotLongitudinalControl = True
      ret.safetyConfigs[0].safetyParam |= RivianSafetyFlags.LONG_CONTROL.value

    if longitudinal_harness:
      ret.longitudinalActuatorDelay = 0.3  # measured command-to-aEgo lag is ~0.26-0.38 s
      ret.stopAccel = -0.2
      ret.longitudinalTuning.kiBP = [0.]
      ret.longitudinalTuning.kiV = [0.2]
    else:
      ret.longitudinalActuatorDelay = 0.35
      ret.stopAccel = 0

    return ret
