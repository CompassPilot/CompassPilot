"""Rivian 2026-10-31 route 508271ef35: one late pandad CAN tick must not take over AOL.

At 112.3 s and 372.7 s, lateral-only AOL (ACC off) was active when pandad's CAN
publication arrived 26-27 ms after the previous one. Card's source therefore
crossed INTENT_MAX_AGE_NS before the next sample and selfdrived raised a critical
controlsMismatch. Like the Ford/Toyota/HKG owners, the original unexpired proof
is kept for that one tick only; a fresh source must still re-qualify.
"""
from contextlib import ExitStack
from unittest import mock

import pytest
from opendbc.car.rivian.interface import CarInterface
from opendbc.car.rivian.values import CAR
from openpilot.cereal import log
from openpilot.common.prefix import OpenpilotPrefix
from openpilot.starpilot.aol.tests import test_ioniq_availability as fixture
from openpilot.starpilot.aol.tests.test_ordinary_source_availability import settings

SOURCE = 10_020_000_000
PUBLISHED_OFFSET = 5_920_000
SOURCE_AGE = 33_452_000


def profile():
  fingerprint = {bus: {} for bus in range(8)}
  fingerprint[0][0x321] = 8
  fingerprint[1] = {0x1310: 8, 0x131A: 8}
  cp = CarInterface.get_params(CAR.RIVIAN_R1T, fingerprint, [], True, False, False)
  cp.alternativeExperience = 32
  return cp


def callers(case):
  sd, controls, drive = case._authority_callers(False, cp=profile(), genuine_events=True)

  def cruise_off(tick, **kwargs):
    state = kwargs.get('observed_state') or fixture.car_state()
    state.cruiseState.available = True
    state.cruiseState.enabled = False
    kwargs['observed_state'] = state
    return drive(tick, **kwargs)
  return sd, controls, cruise_off


@pytest.mark.parametrize('socket_timeout', [False, True])
def test_late_can_tick_keeps_only_the_unexpired_lateral_proof(socket_timeout):
  case = fixture.IoniqAvailabilityTests(methodName='runTest')
  with ExitStack() as cleanup:
    cleanup.callback(case.doCleanups)
    cleanup.enter_context(OpenpilotPrefix())
    sd, controls, drive = callers(case)
    assert sd.rivian_source_deadline_supported() and sd.source_deadline_deferral_supported()
    for tick in (0, 1):
      stamp = 10_000_000_000 + tick * 10_000_000
      drive(tick, long_allowed=False, **settings('lateral_only', stamp, tick + 1))
    old, state, command = drive(2, state_stamp=SOURCE, offset_ns=PUBLISHED_OFFSET, long_allowed=False,
                                **settings('lateral_only', SOURCE, 3))
    assert old.lateralActive and command.latActive and not old.longitudinalActive and not command.longActive
    assert not state.enabled
    deadline = old.validUntilMonoTime
    old_data = old.to_dict()
    sd.car_state_poller = mock.Mock()
    sd.car_state_poller.poll.return_value = []
    axis, state, command = drive(5, timeout=socket_timeout, state_stamp=SOURCE, offset_ns=SOURCE_AGE - 30_000_000,
                                 long_allowed=False, **settings('lateral_only', SOURCE, 3))
    assert sd.aol_axis_publication_deferred, 'RIVIAN_LATE_CAN_TICK_NOT_DEFERRED'
    assert axis.to_dict() == old_data and axis.validUntilMonoTime == deadline
    assert log.OnroadEvent.EventName.controlsMismatch not in sd.events.names
    assert not sd.aol_authority_lost
    # The retained proof grants nothing past its original deadline.
    with mock.patch('openpilot.selfdrive.controls.controlsd.time.monotonic_ns', return_value=deadline + 1):
      expired, _ = controls.state_control()
    assert not expired.latActive and not expired.longActive
    fresh = SOURCE + 40_000_000
    axis, state, command = drive(6, state_stamp=fresh, long_allowed=False, **settings('lateral_only', fresh, 4))
    assert axis.lateralActive and command.latActive and not state.enabled and not command.longActive


@pytest.mark.parametrize('fault', ['lateral_denied', 'steer_fault'])
def test_late_tick_deferral_does_not_preserve_a_new_fault(fault):
  case = fixture.IoniqAvailabilityTests(methodName='runTest')
  with ExitStack() as cleanup:
    cleanup.callback(case.doCleanups)
    cleanup.enter_context(OpenpilotPrefix())
    sd, _, drive = callers(case)
    for tick in (0, 1, 2):
      stamp = 10_000_000_000 + tick * 10_000_000
      drive(tick, state_stamp=stamp, offset_ns=PUBLISHED_OFFSET if tick == 2 else 0,
            long_allowed=False, **settings('lateral_only', stamp, tick + 1))
    sd.car_state_poller = mock.Mock()
    sd.car_state_poller.poll.return_value = []
    options = settings('lateral_only', SOURCE, 3)
    state = fixture.car_state()
    if fault == 'lateral_denied':
      options['allowed'] = False
    else:
      state.steerFaultPermanent = True
    axis, _, command = drive(5, timeout=True, state_stamp=SOURCE, offset_ns=SOURCE_AGE - 30_000_000,
                             long_allowed=False, observed_state=state, **options)
    assert not getattr(sd, 'aol_axis_publication_deferred', False)
    assert not axis.lateralActive and not command.latActive
