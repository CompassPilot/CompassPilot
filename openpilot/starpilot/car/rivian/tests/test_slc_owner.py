"""Rivian: SLC owns SET, so the planner follows SET instead of an SLC ceiling (routes 31-36)."""
from collections import deque
from dataclasses import replace
from types import SimpleNamespace

import pytest

from opendbc.car.rivian.values import RivianFlags
from openpilot.common.constants import CV
from openpilot.starpilot.longitudinal.cruise_ceiling import select_cruise_ceiling
from openpilot.starpilot.car.rivian import slc_owner
from openpilot.starpilot.speed_limits.planner_host import SavedSlcLifecycle
from openpilot.starpilot.speed_limits.runtime import Runtime
from openpilot.starpilot.speed_limits.runtime_settings import PedalOverride, parse
from openpilot.starpilot.speed_limits.speed_domain import OffsetBand, OffsetSchedule
from openpilot.starpilot.speed_limits.tests import test_runtime_replay as replay

START = 2_000_000_000
MPH = CV.MPH_TO_MS


def _rivian(cp, *, harness=True, long=True):
  cp.brand = 'rivian'
  cp.pcmCruise = True
  cp.openpilotLongitudinalControl = long
  cp.flags = int(RivianFlags.GEN2 | RivianFlags.ANGLE_HARNESS | (RivianFlags.LONGITUDINAL_HARNESS if harness else 0))
  return cp


def _lifecycle(cp, *, offset_mph=5.0):
  settings = parse({'SpeedLimitController': True, 'SLCPriority1': 'Dashboard', 'SLCPriority2': 'Off', 'SLCConfirmation': 0})
  lifecycle = SavedSlcLifecycle.__new__(SavedSlcLifecycle)
  lifecycle.params, lifecycle.cp = SimpleNamespace(put=lambda *a, **k: None), cp
  lifecycle.runtime = Runtime(replace(settings, offsets=OffsetSchedule((OffsetBand(0., None, offset_mph * MPH),))))
  return lifecycle


def _drive(set_mph, limit_mph):
  fixture = replay.RuntimeReplayTests()
  fixture.setUp()
  sm, cp = fixture.sm, fixture.cp
  sm['carState'].vCruise = sm['carState'].vCruiseCluster = set_mph * MPH * 3.6
  sm['slcDashboardObservation'].speedMps = limit_mph * MPH
  return sm, cp


def _planner_target_mph(output, set_mph):
  # The planner's own ceiling decision (longitudinal_planner.py): v_cruise = SET unless a cap applies.
  decision = select_cruise_ceiling(output.result.ceiling, driver_v_cruise_kph=set_mph * MPH * 3.6, driver_cruise_mps=set_mph * MPH,
                                   system_long_available=True, long_control_active=True, selfdrive_enabled=True, force_decel=False)
  return decision.status, (decision.effective_mps if decision.effective_mps is not None else set_mph * MPH) / MPH


def _step(lifecycle, sm, step):
  now = START + step * 50_000_000
  sm.advance(now)
  sm['slcDashboardObservation'].validUntilMonoTime = now + 1_000_000_000
  output = lifecycle.step(sm, now, deque(), deque(), drive_changed=False)
  assert not output.result.errors
  return output


def test_rivian_planner_follows_set_raised_above_the_limit():
  # Route 35: + raised SET to 75 with a 55+5 limit; the ceiling held the car at 60.
  sm, cp = _drive(75, 55)
  lifecycle = _lifecycle(_rivian(cp))
  for step in range(3):
    output = _step(lifecycle, sm, step)
    state = output.message.slcState
    assert output.result.ceiling is None
    assert not state.hasCeiling and not state.isLimitingMaxSet and not state.driverOverrideActive
    # The accepted limit is still published: Card's Rivian SET owner reads it.
    assert state.hasAcceptedAdjustedLimit and state.acceptedAdjustedLimit == pytest.approx(60 * MPH)
    status, target = _planner_target_mph(output, 75)
    assert status == 'absent' and target == pytest.approx(75)


def test_other_cars_keep_doms_slc_ceiling():
  sm, cp = _drive(75, 55)
  lifecycle = _lifecycle(cp)
  output = _step(lifecycle, sm, 0)
  assert output.result.ceiling.speed_mps == pytest.approx(60 * MPH)
  assert output.message.slcState.hasCeiling and output.message.slcState.isLimitingMaxSet
  status, target = _planner_target_mph(output, 75)
  assert status == 'applied' and target == pytest.approx(60)


def test_rivian_without_the_longitudinal_harness_keeps_the_ceiling():
  sm, cp = _drive(75, 55)
  output = _step(_lifecycle(_rivian(cp, harness=False)), sm, 0)
  assert not slc_owner.owns_set_speed(cp)
  assert output.result.ceiling is not None and output.message.slcState.hasCeiling
  assert not slc_owner.owns_set_speed(_rivian(cp, long=False))


def test_rivian_settings_drop_pedal_and_wheel_ceiling_overrides():
  settings = replace(parse({'SpeedLimitController': True}), pedal_override=PedalOverride.SPEED_REACHED, wheel_override=True)
  _, cp = _drive(75, 55)
  assert slc_owner.runtime_settings(cp, settings) is settings
  owned = slc_owner.runtime_settings(_rivian(cp), settings)
  assert owned.pedal_override is PedalOverride.OFF and not owned.wheel_override
  assert replace(owned, pedal_override=settings.pedal_override, wheel_override=True) == settings


def test_owns_set_speed_never_raises():
  assert not slc_owner.owns_set_speed(None)
  assert not slc_owner.owns_set_speed(SimpleNamespace(brand='rivian'))
