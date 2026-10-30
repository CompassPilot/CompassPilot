"""Rivian Extreme-harness steering and Always On Lateral preferences, selected at startup."""
import math

from opendbc.car.rivian.harness_aol import HARNESS_FLAGS
from opendbc.car.rivian.values import RivianFlags
from openpilot.starpilot.saved_document import commit_exact
from openpilot.starpilot.saved_source import read_saved
from openpilot.starpilot.ui.feature_settings_state import FeatureRow

ANGLE_KEYS = ('RivianAngleControl', 'RivianAngleSpeedControl', 'RivianAngleMinimumSpeed')
AOL_KEYS = ('AOLBrakeBehavior', 'AOLStartupBehavior')
KEYS = frozenset(ANGLE_KEYS + AOL_KEYS)
# Matches Rivian-src: whole display-unit speeds from 0 (angle at every speed) to 99.
SPEED_MINIMUM, SPEED_MAXIMUM = 0, 99
BRAKE_CHOICES = {b'1': 'Remain Active', b'0': 'Disengage'}
STARTUP_CHOICES = {b'0': 'On Entering Drive', b'1': 'After Engagement'}
APPLIES = ' Applies after the next startup.'


def _choice(table, raw, default):
  return table.get(default if raw is None else raw)


def _speed(raw):
  """Saved or requested whole speed in display units; None when out of range."""
  if raw is None:
    return 20
  try:
    number = float(raw)
  except ValueError:
    return None
  if not math.isfinite(number) or number != int(number) or not SPEED_MINIMUM <= number <= SPEED_MAXIMUM:
    return None
  return int(number)


class RivianFeature:
  def __init__(self, owner):
    self.params = owner.params
    self.authority = owner.authority
    self.vehicle_params = owner.vehicle_params
    self.vehicle_fingerprint = owner.vehicle_fingerprint

  def capability(self):
    cp = self.vehicle_params()
    try:
      if cp is None or cp.brand != 'rivian' or not int(cp.flags) & HARNESS_FLAGS:
        return None
      return (str(cp.carFingerprint), str(cp.brand), int(cp.flags), bool(cp.openpilotLongitudinalControl))
    except (AttributeError, TypeError, ValueError):
      return None

  def _metric(self):
    return read_saved(self.params, 'IsMetric', 8)[0] == b'1'

  def rows(self, parked):
    capability = self.capability()
    if capability is None:
      return ()
    allowed = parked and self.authority('parked_preferences')
    saved = {key: read_saved(self.params, key, 8) for key in KEYS}
    rows = []
    if capability[2] & RivianFlags.ANGLE_HARNESS:
      for key, label, reason in (
        ('RivianAngleControl', 'Angle Steering',
         'Steer through the Extreme harness angle channel. Driver input hands control back to torque.'),
        ('RivianAngleSpeedControl', 'Speed-Based Angle Steering',
         'Use angle steering only above the minimum speed below, and torque at lower speeds.'),
      ):
        raw, readable = saved[key]
        valid = readable and raw in (None, b'0', b'1')
        enabled_parent = key == 'RivianAngleControl' or saved['RivianAngleControl'][0] == b'1'
        rows.append(FeatureRow(key, label, ('On' if raw == b'1' else 'Off') if valid else 'Invalid saved choice',
                               source=raw, choices=('Off', 'On') if valid else (), default_value='Off',
                               available=allowed and valid and enabled_parent, capability=capability,
                               reason=(reason + APPLIES) if valid else 'Invalid saved choice'))
      raw, readable = saved['RivianAngleMinimumSpeed']
      value = _speed(raw)
      valid = readable and value is not None
      unit = 'km/h' if self._metric() else 'mph'
      rows.append(FeatureRow('RivianAngleMinimumSpeed', 'Angle Steering Minimum Speed',
                             str(value) if valid else 'Invalid saved choice', source=raw,
                             step=1.0 if valid else 0.0, minimum=SPEED_MINIMUM, maximum=SPEED_MAXIMUM,
                             unit=unit, default_value='20', capability=capability,
                             available=allowed and valid and saved['RivianAngleSpeedControl'][0] == b'1',
                             reason=('Speed at or above which Speed-Based Angle Steering selects angle. '
                                     '0 selects angle at every speed.' + APPLIES)
                             if valid else 'Invalid saved choice'))
    for key, label, table, default, reason in (
      ('AOLBrakeBehavior', 'AOL While Braking', BRAKE_CHOICES, b'1',
       'Keep Always On Lateral steering while you brake, or disengage it with the brake pedal.'),
      ('AOLStartupBehavior', 'AOL Startup', STARTUP_CHOICES, b'0',
       'Arm Always On Lateral when you shift into Drive, or wait for cruise engagement or the half-up stalk.'),
    ):
      raw, readable = saved[key]
      value = _choice(table, raw, default) if readable else None
      rows.append(FeatureRow(key, label, value or 'Invalid saved choice', source=raw,
                             choices=tuple(table.values()) if value else (), default_value=table[default],
                             available=allowed and value is not None, capability=capability,
                             reason=(reason + APPLIES) if value else 'Invalid saved choice'))
    return tuple(rows)

  def _encode(self, key, value):
    if key in ('RivianAngleControl', 'RivianAngleSpeedControl'):
      return {'Off': b'0', 'On': b'1'}.get(value)
    if key == 'RivianAngleMinimumSpeed':
      speed = _speed(value.encode()) if isinstance(value, str) else None
      return f'{float(speed):.1f}'.encode() if speed is not None else None
    table = BRAKE_CHOICES if key == 'AOLBrakeBehavior' else STARTUP_CHOICES
    return next((raw for raw, label in table.items() if label == value), None)

  def apply(self, request):
    raw = self._encode(request.key, request.value) if request.key in KEYS else None
    # Boolean rows are confirmed through the shared vehicle-preference question.
    confirmed = request.confirmation or request.key not in ('RivianAngleControl', 'RivianAngleSpeedControl')
    if (raw is None or not confirmed or request.related_source is not None or request.direction or
        (request.expected is not None and (type(request.expected) is not bytes or len(request.expected) > 8))):
      return False

    def authorized():
      return (self.authority('parked_preferences') and bool(request.vehicle_fingerprint) and
              self.vehicle_fingerprint() == request.vehicle_fingerprint and request.capability is not None and
              self.capability() == request.capability)

    result = commit_exact(self.params, key=request.key, max_bytes=8, expected=request.expected, raw=raw,
                          authorized=authorized, temp_prefix='.rivian-')
    return result.committed and result.verified
