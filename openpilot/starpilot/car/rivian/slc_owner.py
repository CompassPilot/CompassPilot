"""Rivian: SLC writes the Extreme-harness SET, so SET is the only cruise target.

Dom's SLC is a planner ceiling under the driver's SET on native-cruise cars.
On the Rivian harness SLC already owns SET (slc_set_speed.py), and a ceiling on
top of it pins the car to the limit when the driver raises SET with the wheel
buttons (routes 31-36, 2026-11-12/13). Like the pre-rework Rivian build, the
planner follows SET: the wheel +/- moves the driven speed, and the gas returns
to SET on release. Every other car keeps Dom's ceiling.
"""
from dataclasses import replace

from opendbc.car.rivian.values import RivianFlags
from openpilot.starpilot.speed_limits.runtime_settings import PedalOverride


def owns_set_speed(cp) -> bool:
  try:
    return bool(cp.brand == 'rivian' and cp.openpilotLongitudinalControl and int(cp.flags) & RivianFlags.LONGITUDINAL_HARNESS)
  except (AttributeError, TypeError, ValueError):
    return False


def runtime_settings(cp, settings):
  """No pedal or wheel ceiling overrides: SET already carries the driver's choice."""
  if not owns_set_speed(cp) or (settings.pedal_override is PedalOverride.OFF and not settings.wheel_override):
    return settings
  return replace(settings, pedal_override=PedalOverride.OFF, wheel_override=False)


def without_ceiling(cp, output):
  """Hand the planner no SLC ceiling and publish no limiting state for it."""
  if output is None or not owns_set_speed(cp) or output.result.ceiling is None:
    return output
  state = output.message.slcState
  state.hasCeiling = False
  state.effectiveCap = 0.
  state.isLimitingMaxSet = False
  if str(state.overrideBasis) != 'wheel':
    state.driverOverrideActive = False
    state.overrideBasis = 'none'
  return replace(output, result=replace(output.result, ceiling=None))
