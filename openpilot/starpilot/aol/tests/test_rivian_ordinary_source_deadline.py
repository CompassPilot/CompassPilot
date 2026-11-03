"""Rivian 2026-11-02 route 9d4266c6a7 (1421 s, 1691 s): one late pandad CAN tick with ACC engaged.

Card's source arrived 28 ms after the previous one while AOL was combined
(lateral+longitudinal). selfdrived withdrew ordinary engagement with a commIssue
"TAKE CONTROL" alert although the original proof was still unexpired. As for the
GM owners, keep only that unexpired lease for one tick; the next source decides.
"""
from contextlib import ExitStack
from unittest.mock import patch

import pytest

from openpilot.common.prefix import OpenpilotPrefix
from openpilot.starpilot.aol.intent import read_settings
from openpilot.starpilot.aol.tests import test_ioniq_availability as fixture
from openpilot.starpilot.aol.tests.test_input_deadline_continuity import BASE, intent
from openpilot.starpilot.aol.tests.test_rivian_source_deadline import profile


def engaged_state(gas=False):
  cs = fixture.car_state()
  cs.cruiseState.available = True
  cs.cruiseState.enabled = True
  cs.gasPressed = gas  # one-pedal driving holds the accelerator under ACC
  return cs


@pytest.mark.parametrize('gas', [False, True], ids=['released', 'held_gas'])
@pytest.mark.parametrize('successor', ['fresh', 'missing'])
def test_engaged_cutoff_keeps_only_original_lease_then_consumes_next_source(successor, gas):
  case = fixture.IoniqAvailabilityTests(methodName='runTest')
  with OpenpilotPrefix(), ExitStack() as cleanup:
    cleanup.callback(case.doCleanups)
    sd, controls, step = case._authority_callers(True, cp=profile(), genuine_events=True)
    sd.aol_settings = read_settings(sd.params)
    cs = engaged_state(gas)
    # ACC was already engaged (steady events), as on the recorded drive.
    for tick, stamp in ((0, BASE - 20_000_000), (1, BASE - 10_000_000)):
      step(tick, state_stamp=stamp, intent_message=intent(stamp, tick + 1), observed_state=cs, native_request_long=True)
    old, _, command = step(2, state_stamp=BASE, offset_ns=5_467_396,
      intent_message=intent(BASE, 3), observed_state=cs, native_request_long=True)
    assert old.lateralActive and command.latActive and (gas or command.longActive)
    deadline = old.validUntilMonoTime
    clock = [BASE + 29_900_000]
    actual_controls_receive = controls.sm.update_msgs

    def empty_control_receive(timeout):
      assert timeout == 0
      actual_controls_receive(clock[0] / 1e9, [])

    cleanup.enter_context(patch.object(controls.sm, 'update', side_effect=empty_control_receive))
    original = sd.update_process_health

    def finish_preamble():
      value = original()
      clock[0] = BASE + 32_985_260
      return value

    with patch('openpilot.selfdrive.selfdrived.selfdrived.time.monotonic_ns', side_effect=lambda: clock[0]), \
         patch.object(sd, 'update_process_health', side_effect=finish_preamble):
      held, state, _ = step(5, timeout=True, state_stamp=BASE, offset_ns=-100_000,
        intent_message=intent(BASE, 3), observed_state=cs, native_request_long=True)
    assert sd.aol_axis_publication_deferred, (sd.events.names, sd.aol_fault_reason)
    assert held.to_dict() == old.to_dict() and held.validUntilMonoTime == deadline
    assert not sd.aol_authority_lost and state.enabled
    with patch('openpilot.selfdrive.selfdrived.selfdrived.time.monotonic_ns', return_value=deadline + 1):
      expired, _ = controls.state_control()
    assert not expired.latActive and not expired.longActive
    fresh = BASE + 36_000_000
    axis, state, command = step(6, state_stamp=fresh, timeout=successor == 'missing',
      intent_message=intent(fresh, 4) if successor == 'fresh' else intent(BASE, 3),
      observed_state=cs, native_request_long=True)
    assert not sd.aol_axis_publication_deferred
    if successor == 'fresh':
      assert axis.sourceCarStateMonoTime == fresh and axis.lateralActive and command.latActive, \
        (axis.to_dict(), sd.events.names, sd.aol_fault_reason)
      assert (gas or command.longActive) and state.enabled
      assert not sd.aol_authority_lost
    else:
      assert not axis.lateralActive and not axis.longitudinalActive
      assert not command.latActive and not command.longActive
