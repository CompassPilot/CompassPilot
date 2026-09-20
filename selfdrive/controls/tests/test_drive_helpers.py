import math

import pytest

from openpilot.selfdrive.controls.lib.drive_helpers import (
  REAR_AXLE_OFFTRACKING_FOLLOW_FRAC,
  compensate_rear_axle_offtracking,
  get_kona_non_scc_lateral_active,
  get_lateral_active,
)


def test_get_lateral_active_requires_enabled_without_aol():
  assert not get_lateral_active(False, True, False, False, False, False, False, True)


def test_get_lateral_active_allows_aol_while_disabled():
  assert get_lateral_active(False, False, True, False, False, False, False, True)


def test_get_lateral_active_does_not_retry_after_a_latched_temporary_fault():
  assert not get_lateral_active(False, False, True, False, False, False, False, True, True)
  assert get_lateral_active(False, False, True, False, False, False, False, True, False)


def test_kona_non_scc_aol_waits_for_driver_steering_to_release():
  assert not get_kona_non_scc_lateral_active(
    False, False, True, False, False, False, False, True, True, False,
  )
  assert get_kona_non_scc_lateral_active(
    False, False, True, False, False, False, False, True, False, False,
  )
  assert get_kona_non_scc_lateral_active(
    False, False, True, False, False, False, False, True, True, True,
  )


def test_kona_non_scc_aol_gate_does_not_change_fault_or_normal_lateral_gates():
  assert not get_kona_non_scc_lateral_active(
    False, False, True, True, False, False, False, True, False, False,
  )
  assert get_kona_non_scc_lateral_active(
    True, True, False, False, False, False, False, True, True, False,
  )


def test_kona_non_scc_recovers_after_temporary_fault_clears():
  assert not get_kona_non_scc_lateral_active(
    False, False, True, True, False, False, False, True, False, True,
  )
  assert not get_kona_non_scc_lateral_active(
    False, False, True, False, False, False, False, True, True, False,
  )
  assert get_kona_non_scc_lateral_active(
    False, False, True, False, False, False, False, True, False, False,
  )


def test_get_lateral_active_honors_manual_pause_while_cruise_is_engaged():
  assert not get_lateral_active(True, True, False, False, False, False, False, False)


def test_rear_axle_offtracking_leaves_straight_and_highway_alone():
  assert compensate_rear_axle_offtracking(0.0, 3.45) == 0.0
  L_eff = 3.45 * REAR_AXLE_OFFTRACKING_FOLLOW_FRAC
  highway = compensate_rear_axle_offtracking(0.01, 3.45)
  assert highway == pytest.approx(0.01 / math.sqrt(1.0 + (0.01 * L_eff) ** 2))
  assert abs(highway - 0.01) < 6e-4


def test_rear_axle_offtracking_uses_partial_wheelbase_follow_point():
  kappa = 0.1
  wheelbase = 3.45
  L_eff = wheelbase * REAR_AXLE_OFFTRACKING_FOLLOW_FRAC
  got = compensate_rear_axle_offtracking(kappa, wheelbase)
  assert REAR_AXLE_OFFTRACKING_FOLLOW_FRAC == 0.15
  assert got == pytest.approx(kappa / math.sqrt(1.0 + (kappa * L_eff) ** 2))
  assert got == pytest.approx(1.0 / math.sqrt((1.0 / kappa) ** 2 + L_eff ** 2))
  full = compensate_rear_axle_offtracking(kappa, wheelbase, follow_frac=1.0)
  half = compensate_rear_axle_offtracking(kappa, wheelbase, follow_frac=0.5)
  assert abs(got) > abs(half) > abs(full)


def test_rear_axle_offtracking_never_tightens_and_keeps_sign():
  wheelbase = 3.45
  for kappa in (-0.16, -0.05, 0.05, 0.16):
    got = compensate_rear_axle_offtracking(kappa, wheelbase)
    assert math.copysign(1.0, got) == math.copysign(1.0, kappa)
    assert abs(got) < abs(kappa)


def test_rear_axle_offtracking_is_a_noop_without_wheelbase():
  assert compensate_rear_axle_offtracking(0.1, 0.0) == 0.1
  assert compensate_rear_axle_offtracking(0.1, -1.0) == 0.1
