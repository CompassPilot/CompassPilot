from cereal import car, log
import cereal.messaging as messaging

import pytest

from opendbc.car.rivian.values import RivianFlags
from openpilot.selfdrive.controls.controlsd import (
  get_control_lateral_smooth_seconds,
  turn_lead_allowed,
  uses_angle_lateral_state,
)


LateralControlMode = car.CarControl.Actuators.LateralControlMode


def test_turn_lead_is_suppressed_only_during_applied_angle_control():
  assert not turn_lead_allowed("rivian", LateralControlMode.angle)
  assert turn_lead_allowed("rivian", LateralControlMode.torque)
  assert turn_lead_allowed("rivian", LateralControlMode.torqueRecovering)
  assert turn_lead_allowed("rivian", LateralControlMode.inactive)
  assert turn_lead_allowed("ford", LateralControlMode.angle)


def test_rivian_angle_mode_publishes_saturation_through_angle_state():
  torque_type = car.CarParams.SteerControlType.torque
  angle_type = car.CarParams.SteerControlType.angle

  assert uses_angle_lateral_state(torque_type, True)
  assert not uses_angle_lateral_state(torque_type, False)
  assert uses_angle_lateral_state(angle_type, False)

  dat = messaging.new_message('controlsState')
  lac_log = log.ControlsState.LateralAngleState.new_message()
  lac_log.saturated = True
  dat.controlsState.lateralControlState.angleState = lac_log
  assert dat.controlsState.lateralControlState.which() == 'angleState'
  assert dat.controlsState.lateralControlState.angleState.saturated


@pytest.mark.parametrize("v_ego", [0.0, 5.0, 30.0])
def test_non_rivian_control_smoothing_keeps_starpilot_default(v_ego):
  assert get_control_lateral_smooth_seconds("toyota", v_ego, 0.0) == pytest.approx(0.1)


@pytest.mark.parametrize(("v_ego", "expected"), [
  (0.0, 0.4),
  (5.0, 0.2),
  (30.0, 0.0),
])
def test_subaru_control_smoothing_uses_vehicle_schedule(v_ego, expected):
  assert get_control_lateral_smooth_seconds("subaru", v_ego, 0.4) == pytest.approx(expected)


@pytest.mark.parametrize(("v_ego", "expected"), [
  (0.0, 0.4),
  (5.0, 0.2),
  (30.0, 0.0),
])
def test_rivian_extreme_control_smoothing_uses_crawl_speed_schedule(v_ego, expected):
  assert get_control_lateral_smooth_seconds("rivian", v_ego, 0.0, RivianFlags.ANGLE_HARNESS) == pytest.approx(expected)


@pytest.mark.parametrize("v_ego", [0.0, 5.0, 30.0])
def test_rivian_torque_only_control_smoothing_stays_disabled(v_ego):
  assert get_control_lateral_smooth_seconds("rivian", v_ego, 0.0) == pytest.approx(0.0)
