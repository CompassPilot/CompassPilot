"""Card names the path behind every AOL latch clear (diagnostic only)."""
from collections import defaultdict
from types import SimpleNamespace

from openpilot.selfdrive.car import card as card_module
from openpilot.starpilot.aol.transport_pause import TransportPauseFeedback


class _SM(dict):
  def __init__(self, **services):
    super().__init__(services)
    self.seen = defaultdict(bool, {name: True for name in services})
    self.updated = defaultdict(bool)
    self.alive = defaultdict(lambda: True)
    self.valid = defaultdict(lambda: True)


def _car(sm, feedback):
  car = card_module.Car.__new__(card_module.Car)
  car.sm = sm
  car.aol_transport_feedback = feedback
  car.aol_card_intent = SimpleNamespace(allowed_latch=False, latch_clear_reason='disarming_fault')
  return car


def _cs():
  return SimpleNamespace(brakePressed=True, gasPressed=False, cruiseState=SimpleNamespace(enabled=False, available=True),
                         gearShifter='drive', steerFaultTemporary=False, steerFaultPermanent=False,
                         buttonEvents=[SimpleNamespace(type='lkas', pressed=True)])


def test_latch_clear_event_names_reason_and_transport_failure_line(monkeypatch):
  events = []
  monkeypatch.setattr(card_module.cloudlog, 'event', lambda name, **fields: events.append((name, fields)))
  feedback = TransportPauseFeedback.__new__(TransportPauseFeedback)
  feedback.paused = False
  feedback.pending_event = 0
  feedback.session = 'session'
  feedback.retention_started_ns = 0
  feedback.source_retention_started_ns = 0
  feedback.signature = (None,) * 5 + ('none',)
  assert not feedback.failed and feedback.last_failure_line == 0
  feedback.failed = True
  assert feedback.failed and feedback.last_failure_line > 0
  axis = SimpleNamespace(mode='lateralOnly', faultReason='none', desiredLateral=True, lateralActive=True, longitudinalActive=False,
                         observedMonoTime=1_000_000_000 - 36_000_000, validUntilMonoTime=1_000_000_000 - 6_000_000,
                         sourceCarStateMonoTime=1_000_000_000 - 40_000_000, sequence=7)
  native = SimpleNamespace(requestedLateral=True, lateralAllowed=True, requestedLongitudinal=False,
                           longitudinalAllowed=False, observedMonoTime=990)
  car = _car(_SM(onroadEvents=[SimpleNamespace(name='pedalPressed')], aolAxisState=axis), feedback)
  car.log_aol_latch_clear(_cs(), 1_000_000_990, {'native': native, 'transport_reset': True, 'native_lost': False})
  assert len(events) == 1
  name, fields = events[0]
  assert name == 'aol_latch_clear' and fields['reason'] == 'disarming_fault'
  assert fields['transport']['failed'] and fields['transport']['last_return'] == feedback.last_failure_line
  assert fields['native'] == dict(req_lat=True, lat_ok=True, req_long=False, long_ok=False, age_ms=1000.0)
  assert fields['axis']['mode'] == 'lateralOnly' and fields['cs']['brake'] and fields['transport_reset']
  assert fields['axis']['seq'] == 7 and fields['axis']['alive'] and fields['axis']['age_ms'] == 36.0
  assert fields['events'] == ['pedalPressed'] and fields['cs']['buttons'] == [('lkas', True)]


def test_latch_clear_log_never_raises(monkeypatch):
  failures = []
  monkeypatch.setattr(card_module.cloudlog, 'exception', lambda name: failures.append(name))
  car = _car(_SM(), None)
  car.log_aol_latch_clear(None, 0, {})
  assert failures == ['aol_latch_clear_log_failed']
