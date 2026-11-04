"""Full-up stalk ends harness AOL only with ACC off (2026-11-03 route 97f9d501b5 4388 s)."""
from opendbc.car import structs
from opendbc.car.rivian.values import RivianSafetyFlags
from openpilot.starpilot.aol.intent import AolSettings
from openpilot.starpilot.car.rivian.aol import RivianHarnessCardIntent

ButtonType = structs.CarState.ButtonEvent.Type
PARAM = int(RivianSafetyFlags.AOL_LATERAL | RivianSafetyFlags.AOL_BRAKE_REMAINS_ACTIVE | RivianSafetyFlags.AOL_STALK_TOGGLE)


def _state(*, cruise, full_up=None):
  cs = structs.CarState(canValid=True, gearShifter=structs.CarState.GearShifter.drive, vEgo=14.0)
  cs.cruiseState.available = True
  cs.cruiseState.enabled = cruise
  if full_up is not None:
    cs.buttonEvents = [structs.CarState.ButtonEvent(type=ButtonType.altButton2, pressed=full_up)]
  return cs.as_reader()


def _armed():
  intent = RivianHarnessCardIntent(AolSettings(True, 0.0, 9, 0, (1, 5, 6), (0, 0, 0)), PARAM)
  intent.update(_state(cruise=True), fault_active=False, now_ns=1)
  intent.allowed_latch = True
  intent.pause_lateral = False
  return intent


def test_full_up_with_acc_engaged_only_cancels_acc():
  intent = _armed()
  for now, state in enumerate((_state(cruise=True, full_up=True), _state(cruise=False), _state(cruise=False, full_up=False)), 2):
    intent.update(state, fault_active=False, now_ns=now)
    assert intent.allowed_latch, intent.latch_clear_reason


def test_full_up_with_acc_off_turns_aol_off():
  intent = _armed()
  intent.update(_state(cruise=False), fault_active=False, now_ns=2)
  assert intent.allowed_latch
  intent.update(_state(cruise=False, full_up=True), fault_active=False, now_ns=3)
  assert not intent.allowed_latch and intent.latch_clear_reason == 'stalk_full_up'
