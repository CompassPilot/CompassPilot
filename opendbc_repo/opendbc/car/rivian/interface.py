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

    # Gen 2 (2025+) does not publish SCCM_WheelTouch on the powertrain bus.
    if 0x321 not in fingerprint[0]:
      ret.flags |= RivianFlags.GEN2.value

    angle_harness = 0x1310 in fingerprint[1]
    longitudinal_harness = 0x131A in fingerprint[1]

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

    # modeld owns Extreme-harness crawl-speed smoothing; torque-only stays at 0.
    ret.lateralSmoothSeconds = 0.0
    ret.steerLimitTimer = 0.4
    CarInterfaceBase.configure_torque_tune(candidate, ret.lateralTuning)

    ret.steerControlType = structs.CarParams.SteerControlType.torque
    ret.radarUnavailable = not longitudinal_harness
    ret.enableBsm = longitudinal_harness

    ret.alphaLongitudinalAvailable = longitudinal_harness
    if alpha_long and ret.alphaLongitudinalAvailable:
      ret.openpilotLongitudinalControl = True
      ret.safetyConfigs[0].safetyParam |= RivianSafetyFlags.LONG_CONTROL.value

    ret.longitudinalActuatorDelay = 0.3  # measured command-to-aEgo lag is ~0.26-0.38 s
    ret.vEgoStopping = 0.25
    ret.stopAccel = -0.2
    ret.longitudinalTuning.kiBP = [0.]
    ret.longitudinalTuning.kiV = [0.2]

    return ret
