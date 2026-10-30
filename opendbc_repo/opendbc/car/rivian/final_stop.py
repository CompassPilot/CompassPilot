"""Rivian final-stop softening for system longitudinal control.

Rivian can retain a stronger PID command into the stopping state, producing a
sharp final brake application. Below 2.8 mph, converge toward its normal
standstill hold request while preserving stronger/urgent planner targets.
"""
import numpy as np
from opendbc.car import DT_CTRL, structs

LongCtrlState = structs.CarControl.Actuators.LongControlState

FINAL_STOP_MAX_SPEED = 1.25
FINAL_STOP_ENTRY_ACCEL = -0.40
FINAL_STOP_HOLD_ACCEL_LIMIT = -0.20
FINAL_STOP_FULL_SOFTEN_TARGET = -0.50
FINAL_STOP_NO_SOFTEN_TARGET = -0.60
FINAL_STOP_NO_LEAD_RELEASE_RATE = 2.0


def policy_for(cp):
  try:
    return RivianFinalStop(float(cp.stopAccel)) if cp.brand == "rivian" and cp.openpilotLongitudinalControl else None
  except (AttributeError, TypeError, ValueError):
    return None


class RivianFinalStop:
  def __init__(self, stop_accel: float):
    self.stop_accel = stop_accel

  def apply(self, output_accel, a_target, should_stop, has_lead, CS, state):
    if has_lead is None:
      return output_accel  # Missing lead evidence keeps the native command.
    no_lead_terminal_stop = not has_lead and should_stop and state == LongCtrlState.stopping
    if CS.brakePressed or (not has_lead and not no_lead_terminal_stop):
      return output_accel
    if output_accel >= 0.0 or CS.vEgo > FINAL_STOP_MAX_SPEED:
      return output_accel
    if a_target >= 0.0 and not should_stop:
      return output_accel
    if a_target <= FINAL_STOP_NO_SOFTEN_TARGET and not no_lead_terminal_stop:
      return output_accel

    hold_accel = min(self.stop_accel, FINAL_STOP_HOLD_ACCEL_LIMIT)
    entry_accel = min(hold_accel, FINAL_STOP_ENTRY_ACCEL)
    accel_floor = float(np.interp(max(CS.vEgo, 0.0), [0.0, FINAL_STOP_MAX_SPEED], [hold_accel, entry_accel]))
    softened_accel = max(float(output_accel), accel_floor)
    if no_lead_terminal_stop:
      # A planner stop without a lead can carry an urgent target and a much stronger
      # inherited command into the final meter. Use the same terminal floor as the
      # lead tune, but release toward it at bounded jerk to avoid an abrupt lurch.
      return min(softened_accel, float(output_accel + FINAL_STOP_NO_LEAD_RELEASE_RATE * DT_CTRL))

    soften_strength = float(np.interp(a_target, [FINAL_STOP_NO_SOFTEN_TARGET, FINAL_STOP_FULL_SOFTEN_TARGET], [0.0, 1.0]))
    return float(output_accel + (softened_accel - output_accel) * soften_strength)
