"""Rivian ACM traffic-sign recognition feeds SLC's Dashboard source on the Extreme harness."""
import pytest

from opendbc.can import CANPacker
from opendbc.car import Bus
from opendbc.car.common.conversions import Conversions as CV
from opendbc.car.dashboard_speed_limit import Status, rivian_sign
from opendbc.car.rivian.carstate import CarState
from opendbc.car.rivian.interface import CarInterface
from opendbc.car.rivian.values import CAR, RivianFlags

PERIOD_NS = 100_000_000  # ACM_tsrCmd is 10 Hz on the harness bus (route 35)


def _car_params(*, harness=True):
  fingerprint = {bus: {} for bus in range(8)}
  fingerprint[0][0x321] = 8
  fingerprint[1] = {0x1310: 8, 0x131A: 8} if harness else {}
  return CarInterface.get_params(CAR.RIVIAN_R1T, fingerprint, [], harness, False, False)


class _Bus1:
  def __init__(self, cp):
    self.cs = CarState(cp)
    self.parser = CarState.get_can_parsers(cp)[Bus.adas]
    self.packer = CANPacker('rivian_primary_actuator')
    self.counter, self.now = 0, 1_000_000_000

  def tick(self, *, speed=0, status=0, metric=False, tsr=True):
    frames = [self.packer.make_can_msg('Cluster', 1, {'Cluster_Unit': 0 if metric else 1})]
    if tsr:
      self.counter = (self.counter + 1) % 16
      frames.append(self.packer.make_can_msg('ACM_tsrCmd', 1, {'ACM_tsrSpdDisClsMain': speed, 'ACM_tsrStatus': status,
                                                               'ACM_tsrCmd_Counter': self.counter}))
    self.now += PERIOD_NS
    self.parser.update([(self.now, frames)])
    self.cs.update_dashboard_limit(self.parser)
    return self.cs.dashboard_limit.observation


@pytest.mark.parametrize('speed,status,metric,expected', [
  (55, 0, False, (Status.VALID, 55 * CV.MPH_TO_MS)),
  (100, 0, True, (Status.VALID, 100 * CV.KPH_TO_MS)),
  (0, 0, False, (Status.ABSENT, 0.)),           # no recognition
  (253, 0, False, (Status.ABSENT, 0.)),         # unlimited
  (255, 0, False, (Status.UNKNOWN, 0.)),        # invalid
  (55, 1, False, (Status.UNKNOWN, 0.)),         # TSR failure
  (55, 2, False, (Status.UNKNOWN, 0.)),         # temporarily unavailable
])
def test_rivian_sign_decoding(speed, status, metric, expected):
  decoded = rivian_sign(speed, status, metric)
  assert decoded[0] is expected[0] and decoded[1] == pytest.approx(expected[1])


def test_harness_sign_reading_becomes_dashboard_evidence():
  bus = _Bus1(_car_params())
  # The parser learns the 10 Hz cadence before any sign is usable.
  assert bus.tick(speed=55).status is Status.UNKNOWN
  for _ in range(15):
    observation = bus.tick(speed=55)
  assert observation.status is Status.VALID and observation.speed_mps == pytest.approx(55 * CV.MPH_TO_MS)
  assert observation.observed_ns == bus.now and bus.now < observation.valid_until_ns <= bus.now + 1_100_000_000
  episode = observation.episode
  assert bus.tick(speed=55).episode == episode
  # About 20 s after a sign the ACM reports no recognition: absent, never a 0 limit.
  absent = bus.tick(speed=0)
  assert absent.status is Status.ABSENT and absent.speed_mps == 0. and absent.episode == episode + 1
  assert bus.tick(speed=65).speed_mps == pytest.approx(65 * CV.MPH_TO_MS)
  assert bus.tick(speed=65, status=2).status is Status.UNKNOWN


def test_missing_sign_frames_never_affect_can_valid():
  bus = _Bus1(_car_params())
  for _ in range(40):
    bus.tick(speed=55)
  assert bus.parser.can_valid
  last = bus.cs.dashboard_limit.observation
  for _ in range(40):
    observation = bus.tick(tsr=False)
  assert bus.parser.can_valid
  # The last packet stays bound to its own expiry; Dom's runtime treats it as stale after that.
  assert observation == last and bus.now > observation.valid_until_ns


def test_cars_without_the_longitudinal_harness_do_not_read_tsr():
  cp = _car_params(harness=False)
  assert not cp.flags & RivianFlags.LONGITUDINAL_HARNESS
  assert CarState(cp).dashboard_limit is None
  assert 0x370 not in CarState.get_can_parsers(cp)[Bus.adas].message_states
