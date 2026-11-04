"""Card may see the newer PandaStates one tick before the aolSafetyWire read from it.

Routes 97f9d501b5 (161/521/3419 s), 14ba1ad03f (1563 s) and 80fbf9331d (895/1634 s):
after ACC ended, the newer PandaStates (controls_allowed=False) met the older wire that
still reported the LONG axis requested, and the latest-PandaStates LONG veto cleared AOL.
"""
from types import SimpleNamespace

import pytest

from openpilot.starpilot.aol import transport_pause
import openpilot.starpilot.car.rivian.aol as rivian_aol

SESSION = 'session'


class _SM(dict):
  def __init__(self, axis, seen=True):
    super().__init__(aolAxisState=axis)
    self.seen = {'aolAxisState': seen}


def _axis(**kwargs):
  values = dict(sessionId=SESSION, desiredLongitudinal=False, longitudinalActive=False)
  values.update(kwargs)
  return SimpleNamespace(**values)


@pytest.fixture
def rivian(monkeypatch):
  monkeypatch.setattr(rivian_aol, 'marked', lambda cp: cp.brand == 'rivian')
  return SimpleNamespace(brand='rivian')


def test_newer_panda_states_after_host_long_withdrawal_is_waived(rivian):
  native = SimpleNamespace(sourcePandaStatesMonoTime=100)
  assert transport_pause._rivian_host_long_withdrawn_ahead_of_native(_SM(_axis()), rivian, SESSION, native, 200)


@pytest.mark.parametrize('axis, ps_ns, seen', [
  (_axis(desiredLongitudinal=True), 200, True),      # host still wants LONG: panda revocation must veto
  (_axis(longitudinalActive=True), 200, True),       # host still applying LONG
  (_axis(sessionId='other'), 200, True),             # different axis session
  (_axis(), 100, True),                              # PandaStates is the wire's own source, not newer
  (_axis(), 50, True),                               # PandaStates older than the wire
  (_axis(), 200, False),                             # no axis observation
])
def test_waiver_does_not_apply(rivian, axis, ps_ns, seen):
  native = SimpleNamespace(sourcePandaStatesMonoTime=100)
  assert not transport_pause._rivian_host_long_withdrawn_ahead_of_native(_SM(axis, seen), rivian, SESSION, native, ps_ns)


def test_other_brands_keep_the_latest_panda_states_veto(rivian):
  native = SimpleNamespace(sourcePandaStatesMonoTime=100)
  assert not transport_pause._rivian_host_long_withdrawn_ahead_of_native(_SM(_axis()), SimpleNamespace(brand='ford'),
                                                                        SESSION, native, 200)
