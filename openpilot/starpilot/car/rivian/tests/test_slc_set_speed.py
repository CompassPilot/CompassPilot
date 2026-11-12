"""SLC owns the Rivian harness SET under Dom's ceiling-model SLC (route 0af24754b0)."""
from collections import defaultdict
from types import SimpleNamespace

import pytest

from opendbc.car import structs
from opendbc.car.common.conversions import Conversions as CV
from openpilot.cereal import messaging
from openpilot.starpilot.car.rivian.slc_set_speed import ENGAGE_HOLD_NS, RivianSlcSetSpeed

MPH = CV.MPH_TO_MS
NOW = 50_000_000_000
ButtonType = structs.CarState.ButtonEvent.Type


class _SM(dict):
  def __init__(self):
    super().__init__()
    self.valid, self.alive, self.logMonoTime = defaultdict(lambda: True), defaultdict(lambda: True), defaultdict(int)

  def publish(self, state, now_ns):
    self['slcState'] = state
    self.logMonoTime['slcState'] = now_ns


def _state(now_ns, *, accepted_mph=None, accepted_ns=1, live_mph=None, offset_mph=0.0, preview=False):
  msg = messaging.new_message('slcState')
  s = msg.slcState
  s.enabled, s.displayOnly, s.sessionId, s.frameMonoTime = True, False, 'session', now_ns
  s.offset = offset_mph * MPH
  if accepted_mph is not None:
    s.hasAccepted, s.acceptedMonoTime, s.acceptedIsPreview = True, accepted_ns, preview
    s.acceptedSpeedLimit = accepted_mph * MPH
    s.hasAcceptedAdjustedLimit, s.acceptedAdjustedLimit = True, (accepted_mph + offset_mph) * MPH
  if live_mph is not None:
    s.observationKind, s.source, s.speedLimit, s.presentationId = 'valid', 'map', live_mph * MPH, 1
    s.hasPresentationAdjustedLimit, s.presentationAdjustedLimit = True, (live_mph + offset_mph) * MPH
  else:
    s.observationKind, s.source = 'unknown', 'none'
  return msg.as_reader().slcState


def _card(sm, *, slc=True):
  return SimpleNamespace(sm=sm, CP=SimpleNamespace(openpilotLongitudinalControl=True), slc_control_enabled=slc,
                         slc_source_floor_ns=0, slc_producer_session='', is_metric=False)


def _cs(*, cruise=True, speed_mph=40.0, buttons=()):
  return SimpleNamespace(canValid=True, canTimeout=False, cruiseState=SimpleNamespace(available=True, enabled=cruise,
                         speed=speed_mph * MPH), buttonEvents=[SimpleNamespace(type=b) for b in buttons])


def _mph(value):
  return None if value is None else round(value / MPH, 1)


@pytest.fixture
def owner():
  pushed = []
  return RivianSlcSetSpeed(), pushed, pushed.append


def test_engage_on_mapd_gap_uses_this_drives_accepted_limit(owner):
  # I-95: Mapd ambiguous (no live limit), 55 mph accepted earlier this drive, offset 10.
  slc, pushed, push = owner
  sm = _SM(); sm.publish(_state(NOW, accepted_mph=55, offset_mph=10), NOW)
  assert _mph(slc.update(_card(sm), _cs(speed_mph=48), NOW, push)) == 65
  # Held through the engaging stalk press, which raises the harness SET to vEgo.
  assert _mph(slc.update(_card(sm), _cs(speed_mph=48), NOW + 100_000_000, push)) == 65
  assert slc.update(_card(sm), _cs(speed_mph=65), NOW + 200_000_000, push) is None
  assert slc.update(_card(sm), _cs(speed_mph=65), NOW + ENGAGE_HOLD_NS + 1, push) is None


def test_engage_uses_the_live_limit_without_history(owner):
  slc, pushed, push = owner
  sm = _SM(); sm.publish(_state(NOW, live_mph=45, offset_mph=7), NOW)
  assert _mph(slc.update(_card(sm), _cs(speed_mph=30), NOW, push)) == 52


def test_previous_drive_history_never_initializes_set(owner):
  slc, pushed, push = owner
  sm = _SM(); sm.publish(_state(NOW, accepted_mph=55, accepted_ns=0), NOW)
  assert slc.update(_card(sm), _cs(speed_mph=48), NOW, push) is None and pushed == []


def test_set_follows_accepted_limit_changes_once_and_keeps_driver_adjustment(owner):
  slc, pushed, push = owner
  sm = _SM(); sm.publish(_state(NOW, accepted_mph=45, live_mph=45), NOW)
  slc.update(_card(sm), _cs(speed_mph=40), NOW, push)
  t = NOW + ENGAGE_HOLD_NS + 1
  # The driver raises SET; SLC keeps it until the accepted limit changes.
  sm.publish(_state(t, accepted_mph=45, live_mph=45), t)
  assert slc.update(_card(sm), _cs(speed_mph=50, buttons=(ButtonType.accelCruise,)), t, push) is None
  assert slc.update(_card(sm), _cs(speed_mph=50), t + 10_000_000, push) is None
  sm.publish(_state(t + 20_000_000, accepted_mph=65, live_mph=65), t + 20_000_000)
  assert _mph(slc.update(_card(sm), _cs(speed_mph=50), t + 20_000_000, push)) == 65
  assert slc.update(_card(sm), _cs(speed_mph=65), t + 30_000_000, push) is None


def test_driver_button_ends_the_engagement_hold(owner):
  slc, pushed, push = owner
  sm = _SM(); sm.publish(_state(NOW, accepted_mph=55, live_mph=55), NOW)
  slc.update(_card(sm), _cs(speed_mph=48), NOW, push)
  assert slc.update(_card(sm), _cs(speed_mph=50, buttons=(ButtonType.decelCruise,)), NOW + 50_000_000, push) is None


def test_first_accepted_limit_after_an_unset_engagement_moves_set(owner):
  slc, pushed, push = owner
  sm = _SM(); sm.publish(_state(NOW), NOW)
  assert slc.update(_card(sm), _cs(speed_mph=30), NOW, push) is None
  t = NOW + ENGAGE_HOLD_NS + 1
  sm.publish(_state(t, accepted_mph=35, live_mph=35, offset_mph=5), t)
  assert _mph(slc.update(_card(sm), _cs(speed_mph=30), t, push)) == 40


@pytest.mark.parametrize('card_kwargs, cs_kwargs', [({'slc': False}, {}), ({}, {'cruise': False})])
def test_no_set_ownership_without_slc_or_acc(owner, card_kwargs, cs_kwargs):
  slc, pushed, push = owner
  sm = _SM(); sm.publish(_state(NOW, accepted_mph=55, live_mph=55), NOW)
  assert slc.update(_card(sm, **card_kwargs), _cs(**cs_kwargs), NOW, push) is None and pushed == []


def test_preview_and_stale_state_do_not_move_set(owner):
  slc, pushed, push = owner
  sm = _SM(); sm.publish(_state(NOW), NOW)
  slc.update(_card(sm), _cs(), NOW, push)
  t = NOW + ENGAGE_HOLD_NS + 1
  sm.publish(_state(t, accepted_mph=65, preview=True), t)
  assert slc.update(_card(sm), _cs(), t, push) is None
  sm.publish(_state(t, accepted_mph=65), t)
  assert slc.update(_card(sm), _cs(), t + 5_000_000_000, push) is None and pushed == []
