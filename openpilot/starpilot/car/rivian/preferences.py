"""Rivian startup preferences: Extreme-harness angle selection and AOL latch behavior."""

import math

from opendbc.car.common.conversions import Conversions as CV
from openpilot.starpilot.saved_source import read_saved

AOL_TOGGLE = 9
KEYS = ('RivianAngleControl', 'RivianAngleSpeedControl', 'RivianAngleMinimumSpeed', 'AOLBrakeBehavior',
        'AOLStartupBehavior')


def _raw(params, key, limit=16):
  try:
    raw, readable = read_saved(params, key, limit)
    return raw if readable else b''
  except (OSError, TypeError, ValueError):
    return b''


def _int(params, key, default, valid):
  raw = _raw(params, key)
  if raw is None:
    return default
  try:
    value = int(raw)
  except ValueError:
    return default
  return value if value in valid else default


def _speed_mps(params, key, default_display):
  raw = _raw(params, key)
  try:
    value = float(raw) if raw is not None else default_display
  except ValueError:
    value = default_display
  if not math.isfinite(value) or not 0.0 <= value <= 100.0:
    value = default_display
  metric = _raw(params, 'IsMetric') == b'1'
  return value * (CV.KPH_TO_MS if metric else CV.MPH_TO_MS)


def read_startup(params, *, enabled: bool) -> dict:
  safe = _raw(params, 'SafeMode') in (None, b'0')
  aol = _raw(params, 'AlwaysOnLateral') in (None, b'1')
  lkas_action = _int(params, 'LKASButtonControl', 0, range(15))
  angle = bool(enabled and safe and _raw(params, 'RivianAngleControl') == b'1')
  speed = bool(angle and _raw(params, 'RivianAngleSpeedControl') == b'1')
  return {
    'rivian_angle_control': angle,
    'rivian_angle_speed_control': speed,
    'rivian_angle_minimum_speed': _speed_mps(params, 'RivianAngleMinimumSpeed', 20.0) if speed else 0.0,
    # 1 = AOL remains active while braking (default), 0 = braking disengages AOL.
    'rivian_aol_brake_remains_active': _int(params, 'AOLBrakeBehavior', 1, (0, 1)) == 1,
    # 0 = AOL arms on entering Drive (default), 1 = wait for an engagement or toggle.
    'rivian_aol_startup': _int(params, 'AOLStartupBehavior', 0, (0, 1)) == 0,
    # The Extreme harness reports the half-up stalk detent as the LKAS button.
    'rivian_stalk_aol_toggle': aol and lkas_action == AOL_TOGGLE,
    'rivian_stalk_controls': aol or lkas_action != 0,
  }
