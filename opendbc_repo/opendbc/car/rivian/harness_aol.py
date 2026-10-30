"""Extreme harness AOL admission. The bridge supplies angle and/or longitudinal
channels; preferences select only the native latch behavior, never authority."""
from opendbc.car import structs
from opendbc.car.rivian.values import CAR, RivianFlags, RivianSafetyFlags

HARNESS_FLAGS = RivianFlags.ANGLE_HARNESS | RivianFlags.LONGITUDINAL_HARNESS
PREFERENCE_FLAGS = (RivianSafetyFlags.AOL_BRAKE_REMAINS_ACTIVE | RivianSafetyFlags.AOL_STALK_TOGGLE |
                    RivianSafetyFlags.AOL_START_ENABLED)


def expected_param(cp) -> int:
  param = int(RivianSafetyFlags.ANGLE_CONTROL) if cp.flags & RivianFlags.ANGLE_HARNESS else 0
  param |= int(RivianSafetyFlags.LONG_CONTROL) if cp.openpilotLongitudinalControl else 0
  param |= int(RivianSafetyFlags.R1T) if cp.carFingerprint == CAR.RIVIAN_R1T else 0
  return param


def qualified(cp, *, marked_only=False):
  try:
    param = int(cp.safetyConfigs[0].safetyParam)
    marked = bool(param & RivianSafetyFlags.AOL_LATERAL)
    return bool(cp.brand == 'rivian' and cp.carFingerprint in (CAR.RIVIAN_R1, CAR.RIVIAN_R1T) and
      int(cp.flags) & HARNESS_FLAGS and not (cp.passive or cp.notCar or cp.dashcamOnly) and
      cp.fingerprintSource != structs.CarParams.FingerprintSource.fixed and
      len(cp.safetyConfigs) == 1 and cp.safetyConfigs[0].safetyModel == structs.CarParams.SafetyModel.rivian and
      param & ~int(RivianSafetyFlags.AOL_LATERAL | PREFERENCE_FLAGS) == expected_param(cp) and
      (marked and cp.alternativeExperience == 32 if marked_only else
       cp.alternativeExperience in (0, 32) and (not marked or cp.alternativeExperience == 32)))
  except (AttributeError, TypeError, ValueError, IndexError):
    return False


def prepare(cp, *, brake_remains_active: bool, stalk_toggle: bool, startup_enabled: bool) -> None:
  """Select the native latch behavior for an Extreme harness at vehicle startup."""
  try:
    if (cp.brand != 'rivian' or not int(cp.flags) & HARNESS_FLAGS or len(cp.safetyConfigs) != 1 or
        cp.safetyConfigs[0].safetyModel != structs.CarParams.SafetyModel.rivian):
      return
    param = int(cp.safetyConfigs[0].safetyParam) & ~int(PREFERENCE_FLAGS)
    if brake_remains_active:
      param |= int(RivianSafetyFlags.AOL_BRAKE_REMAINS_ACTIVE)
    if stalk_toggle:
      param |= int(RivianSafetyFlags.AOL_STALK_TOGGLE)
    if startup_enabled:
      param |= int(RivianSafetyFlags.AOL_START_ENABLED)
    cp.safetyConfigs[0].safetyParam = param
  except (AttributeError, TypeError, ValueError, IndexError):
    return


def flags(cp) -> int:
  try:
    return int(cp.safetyConfigs[0].safetyParam)
  except (AttributeError, TypeError, ValueError, IndexError):
    return 0
