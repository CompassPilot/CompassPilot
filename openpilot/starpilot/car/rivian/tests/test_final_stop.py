from types import SimpleNamespace

import pytest

from opendbc.car import DT_CTRL, structs
from opendbc.car.car_helpers import interfaces
from opendbc.car.rivian.final_stop import (FINAL_STOP_MAX_SPEED, FINAL_STOP_NO_LEAD_RELEASE_RATE, RivianFinalStop,
                                           policy_for)
from opendbc.car.rivian.values import CAR
from openpilot.starpilot.longitudinal.extension import create_extension

LongCtrlState = structs.CarControl.Actuators.LongControlState


def _cp(alpha_long, harness=True):
  fingerprint = {bus: {} for bus in range(8)}
  fingerprint[0][0x321] = 8
  if harness:
    fingerprint[1][0x131A] = 8
  return interfaces[CAR.RIVIAN_R1].get_params(CAR.RIVIAN_R1, fingerprint, [], alpha_long, False, False)


def _cs(v_ego, brake=False):
  return SimpleNamespace(vEgo=v_ego, brakePressed=brake)


def test_policy_requires_system_longitudinal():
  assert policy_for(_cp(alpha_long=True)) is not None
  assert policy_for(_cp(alpha_long=False)) is None
  extension = create_extension(_cp(alpha_long=True))
  assert extension is not None and extension.final_stop is not None
  # Final-stop shaping must not take start ownership from faster takeoffs.
  assert extension.stopping_policy is None and not extension.starting


def test_lead_stop_converges_to_hold_request_below_creep_speed():
  stop = RivianFinalStop(-0.2)
  softened = stop.apply(-1.2, -0.5, True, True, _cs(0.5), LongCtrlState.pid)
  assert -1.2 < softened < 0.0
  # Strong/urgent planner targets keep the native command.
  assert stop.apply(-1.2, -0.8, True, True, _cs(0.5), LongCtrlState.pid) == -1.2
  # Above the creep band, braking and missing evidence the command is unchanged.
  assert stop.apply(-1.2, -0.5, True, True, _cs(FINAL_STOP_MAX_SPEED + 0.1), LongCtrlState.pid) == -1.2
  assert stop.apply(-1.2, -0.5, True, True, _cs(0.5, brake=True), LongCtrlState.pid) == -1.2
  assert stop.apply(-1.2, -0.5, True, None, _cs(0.5), LongCtrlState.pid) == -1.2


def test_no_lead_terminal_stop_releases_at_bounded_jerk():
  stop = RivianFinalStop(-0.2)
  released = stop.apply(-2.0, -1.5, True, False, _cs(0.5), LongCtrlState.stopping)
  assert released == pytest.approx(-2.0 + FINAL_STOP_NO_LEAD_RELEASE_RATE * DT_CTRL)
  # Without a lead, only the stopping state is softened.
  assert stop.apply(-2.0, -1.5, True, False, _cs(0.5), LongCtrlState.pid) == -2.0
