"""Rivian: SLC owns the Extreme-harness software SET.

Dom's SLC rework made SLC a planner ceiling under the driver's SET on every
native-cruise (pcmCruise) car, and engagement adoption non-pcmCruise only. The
Rivian's SET is software state in the harness (ACM engages, openpilot drives), so
keep the behavior these cars had before: SET follows the accepted limit plus
offset, with no button press. Dom's own SLC rules pick every target:

* On engagement, `engagement_target`: a limit accepted earlier in this drive (so
  data gaps such as Mapd's ambiguous I-95 stretches still set SET), else the
  current presentation. History from previous drives never initializes SET.
* While engaged, each change of the accepted adjusted limit moves SET once; the
  driver's +/- keeps its value until the next change.
"""
from opendbc.car import structs
from openpilot.selfdrive.car.cruise import slc_target_kph
from openpilot.starpilot.speed_limits import physical_actions as slc_physical

ButtonType = structs.CarState.ButtonEvent.Type
CRUISE_BUTTONS = (ButtonType.accelCruise, ButtonType.decelCruise)
# The stalk press that engages ACC raises the harness SET to vEgo while held.
ENGAGE_HOLD_NS = 2_000_000_000
TARGET_EPSILON_MPS = 0.01


def _rounded_mps(target_mps: float, is_metric: bool) -> float:
  return slc_target_kph(target_mps, is_metric) / 3.6


def accepted_target(sm, now_ns: int, *, after_ns: int = 0) -> float | None:
  state = slc_physical._state(sm, now_ns)
  if (state is None or int(state.frameMonoTime) <= after_ns or not state.hasAccepted or
      not state.hasAcceptedAdjustedLimit or int(state.acceptedMonoTime) <= 0 or state.acceptedIsPreview):
    return None
  target = float(state.acceptedAdjustedLimit)
  return target if slc_physical.finite_speed(target) else None


class RivianSlcSetSpeed:
  def __init__(self):
    self.engaged = False
    self.engage_ns = 0
    self.engage_target: float | None = None
    self.last_target: float | None = None

  def reset(self) -> None:
    self.engaged = False
    self.engage_target = None
    self.last_target = None

  def update(self, card, cs, now_ns: int, set_cruise_speed) -> float | None:
    """Return the SET (m/s) pushed to the harness this cycle, if any."""
    if not (getattr(card, 'slc_control_enabled', False) and card.CP.openpilotLongitudinalControl and
            cs.canValid and not cs.canTimeout and cs.cruiseState.available and cs.cruiseState.enabled):
      self.reset()
      return None
    after_ns = int(getattr(card, 'slc_source_floor_ns', 0))
    is_metric = bool(getattr(card, 'is_metric', False))
    if not self.engaged:
      self.engaged, self.engage_ns = True, now_ns
      target, _ = slc_physical.engagement_target(card.sm, None, getattr(card, 'slc_producer_session', ''), now_ns,
                                                 after_ns=after_ns)
      self.engage_target = _rounded_mps(target, is_metric) if target is not None else None
      self.last_target = self.engage_target
    if any(b.type in CRUISE_BUTTONS for b in cs.buttonEvents):
      self.engage_target = None
    if self.engage_target is not None and now_ns - self.engage_ns <= ENGAGE_HOLD_NS:
      if abs(float(cs.cruiseState.speed) - self.engage_target) > TARGET_EPSILON_MPS:
        set_cruise_speed(self.engage_target)
        return self.engage_target
      return None
    self.engage_target = None
    accepted = accepted_target(card.sm, now_ns, after_ns=after_ns)
    if accepted is None:
      return None
    target = _rounded_mps(accepted, is_metric)
    if self.last_target is not None and abs(target - self.last_target) <= TARGET_EPSILON_MPS:
      return None
    self.last_target = target
    set_cruise_speed(target)
    return target
