import math
from types import SimpleNamespace

import pytest

from opendbc.car.car_helpers import interfaces
from opendbc.car.structs import car
from opendbc.car.rivian.values import CAR
from openpilot.starpilot.car.rivian.lateral import (REAR_AXLE_OFFTRACKING_FOLLOW_FRAC, RivianLateral,
                                                    compensate_rear_axle_offtracking)

LateralControlMode = car.CarControl.Actuators.LateralControlMode


def _ci(candidate=CAR.RIVIAN_R1, angle_harness=False):
  fingerprint = {bus: {} for bus in range(8)}
  fingerprint[0][0x321] = 8
  if angle_harness:
    fingerprint[1][0x1310] = 8
  CI = interfaces[candidate]
  return CI(CI.get_params(candidate, fingerprint, [], False, False, False))


def _output(mode):
  return SimpleNamespace(actuatorsOutput=SimpleNamespace(lateralControlMode=mode, steeringAngleDeg=0.0))


def test_rear_axle_offtracking_leaves_straight_and_highway_alone():
  assert compensate_rear_axle_offtracking(0.0, 3.45) == 0.0
  L_eff = 3.45 * REAR_AXLE_OFFTRACKING_FOLLOW_FRAC
  highway = compensate_rear_axle_offtracking(0.01, 3.45)
  assert highway == pytest.approx(0.01 / math.sqrt(1.0 + (0.01 * L_eff) ** 2))
  assert abs(highway - 0.01) < 6e-4


def test_rear_axle_offtracking_uses_configured_follow_point():
  kappa = 0.1
  wheelbase = 3.45
  L_eff = wheelbase * REAR_AXLE_OFFTRACKING_FOLLOW_FRAC
  got = compensate_rear_axle_offtracking(kappa, wheelbase)
  assert got == pytest.approx(kappa / math.sqrt(1.0 + (kappa * L_eff) ** 2))
  assert got == pytest.approx(1.0 / math.sqrt((1.0 / kappa) ** 2 + L_eff ** 2))
  full = compensate_rear_axle_offtracking(kappa, wheelbase, follow_frac=1.0)
  assert abs(got) > abs(full)


def test_rear_axle_offtracking_never_tightens_and_keeps_sign():
  for kappa in (-0.16, -0.05, 0.05, 0.16):
    got = compensate_rear_axle_offtracking(kappa, 3.45)
    assert math.copysign(1.0, got) == math.copysign(1.0, kappa)
    assert abs(got) < abs(kappa)


def test_rear_axle_offtracking_is_a_noop_without_wheelbase():
  assert compensate_rear_axle_offtracking(0.1, 0.0) == 0.1
  assert compensate_rear_axle_offtracking(0.1, -1.0) == 0.1


def test_offtracking_applies_only_to_active_r1t():
  ci = _ci(CAR.RIVIAN_R1T)
  r1t = RivianLateral(ci.CP, ci, 0.01)
  assert r1t.desired_curvature(0.1, True) < 0.1
  assert r1t.desired_curvature(0.1, False) == 0.1
  ci = _ci()
  assert RivianLateral(ci.CP, ci, 0.01).desired_curvature(0.1, True) == 0.1


def test_angle_channel_is_observed_only_on_the_angle_harness():
  ci = _ci()
  base = RivianLateral(ci.CP, ci, 0.01)
  assert base.angle_controller is None
  assert not base.observe_output(True, _output(LateralControlMode.angle))

  ci = _ci(angle_harness=True)
  harness = RivianLateral(ci.CP, ci, 0.01)
  assert harness.observe_output(True, _output(LateralControlMode.angle))
  assert not harness.observe_output(True, _output(LateralControlMode.torque))
  assert not harness.observe_output(False, _output(LateralControlMode.angle))
  assert harness.steer_limited(SimpleNamespace(steeringAngleDeg=10.0), _output(LateralControlMode.torque)) is None
