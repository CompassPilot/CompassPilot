import math
from collections import deque

import numpy as np

from opendbc.car import rate_limit
from opendbc.car.lateral import apply_driver_steer_torque_limits, get_max_angle_delta_vm, get_max_angle_vm
from opendbc.car.rivian.toi_controller import TOI_MAX_ANGLE_DEG, ToiController
from opendbc.car.rivian.values import CAR, CarControllerParams as CCP, RivianFlags
from opendbc.car.vehicle_model import VehicleModel

# EPAS angle envelope (EPAS_High_Angle_Cmd_Err)
EPAS_FW_MAX_ANGLE_BP = [0.0, 2.78, 5.56, 8.33, 12.50, 16.67, 22.22, 27.78]  # m/s
EPAS_FW_MAX_ANGLE_V = [500, 500, 250, 150, 85, 56, 40, 25]  # deg

# EPAS windowed rate limit (EPAS_High_Actual_Angle_Rate_Err)
EPAS_FW_RATE_BP = [5.56, 8.33, 12.50, 16.67]  # m/s
EPAS_FW_RATE_V = [4.50, 1.50, 0.60, 0.18]  # deg/frame

EPAS_FW_ANGLE_MARGIN = 0.98
EPAS_FW_RATE_MARGIN = 0.94

# Final per-frame cap inside Panda's jerk limit.
PANDA_STEP_MARGIN = 0.9

MIN_TORQUE_FRAMES = 50
HANDOFF_EXIT_DEG = 15.0
UNWIND_HANDOFF_RATE = 40.0
HANDOFF_MAX_ANGLE_DEG = 25.0

# Light-torsion presence bridges capacitive dropouts while hands slide on the wheel.
PRESENCE_TORQUE_THRESHOLD = 1.5
PRESENCE_MIN_FRAMES = 30
PRESENCE_HOLD_FRAMES = 100
HANDS_OFF_EXIT_FRAMES = 75
EAC_RECOVER_FRAMES = 15

# Keep angle control active while the independently rate-limited torque channel
# builds enough holding force for a live angle-to-torque selection.
TORQUE_PREARM_EXIT_FRAC = 0.85
TORQUE_PREARM_MIN_HOLD = 20
TORQUE_PREARM_MAX_FRAMES = 150
TORQUE_PREARM_STALL_FRAMES = 12
TORQUE_PREARM_ABORT_LOCKOUT = 50

# Above this angle the rack spends most of its time saturated. Keeping a small
# amount of headroom helps the torque controller recover as geometry unwinds.
HIGH_ANGLE_THRESHOLD_DEG = 90
HIGH_ANGLE_CAP_FRAC = 0.95


def apply_rivian_steer_angle_limits_vm(apply_angle: float, apply_angle_last: float, v_ego_raw: float, steering_angle: float,
                                       lat_active: bool, limits, VM: VehicleModel) -> float:
  """Apply Rivian's jerk, accel, and safety constraints to its angle channel."""
  v_ego_raw = max(v_ego_raw, 1)

  # When the speed-scheduled angle envelope shrinks, Rivian must unwind toward
  # it through the jerk limit instead of snapping directly to the new bound.
  max_angle = get_max_angle_vm(v_ego_raw, VM, limits)
  new_apply_angle = np.clip(apply_angle, -max_angle, max_angle)

  max_angle_delta = get_max_angle_delta_vm(v_ego_raw, VM, limits)
  max_angle_delta = min(max_angle_delta, limits.ANGLE_LIMITS.MAX_ANGLE_RATE)
  new_apply_angle = rate_limit(new_apply_angle, apply_angle_last, -max_angle_delta, max_angle_delta)

  if not lat_active:
    new_apply_angle = steering_angle

  return float(np.clip(new_apply_angle, -limits.ANGLE_LIMITS.STEER_ANGLE_MAX, limits.ANGLE_LIMITS.STEER_ANGLE_MAX))


class _RateBudget:
  # Sliding-window budget for the EPAS rate limit; history is CAN-quantized to 0.1 deg.
  WINDOW_USER_FRAMES = 16
  WINDOW_TIME_S = 0.16

  def __init__(self):
    self.history = deque([0.0] * self.WINDOW_USER_FRAMES, maxlen=self.WINDOW_USER_FRAMES)

  def push(self, sent_angle: float) -> None:
    self.history.append(round(sent_angle * 10) / 10)

  def bounds(self, threshold_dps: float, margin: float) -> tuple[float, float]:
    cmd_oldest = self.history[0]
    budget = threshold_dps * self.WINDOW_TIME_S * margin
    return cmd_oldest - budget, cmd_oldest + budget


def get_safety_CP():
  from opendbc.car.rivian.interface import CarInterface
  return CarInterface.get_non_essential_params(CAR.RIVIAN_R1_GEN1)


class ExternalController:
  def __init__(self, CP):
    self.VM_safety = VehicleModel(get_safety_CP())
    self.gen2 = bool(CP.flags & RivianFlags.GEN2)
    self.angle_harness = bool(CP.flags & RivianFlags.ANGLE_HARNESS)

    # Hands-on detection.
    self.wheel_touch_cnt = 0
    self.torsion_cnt = 0
    self.hands_on = False
    self.wheel_angle = None  # rad
    self.wheel_rate = 0.0  # rad/s
    self.column_angle_last = 0.0
    self.presence_cnt = 0
    self.presence_hold = 0
    self.hands_off_frames = 0

    # Cooperative torque mode.
    self.torque_active = False
    self.torque_active_frames = 0
    self.lat_active_last = False
    self.eac_dead_frames = 0
    self.force_torque = False
    self.torque_prearm = False
    self.prearm_frames = 0
    self.prearm_torque_peak = 0
    self.prearm_stall_frames = 0
    self.prearm_abort_lockout = 0
    self.prearm_last_outcome = ""

    # Angle command.
    self.apply_angle_last = 0.0
    self.angle_active = False
    self.rate_budget = _RateBudget()

    # Cooperative torque and its EPAS feedback handshake.
    self.apply_torque_last = 0
    self.torque_cmd = 0
    self.toi_controller = ToiController()
    self.toi_act_cmd = False

  def update(self, CS, lat_active: bool, actuators) -> None:
    self._update_hands_on(CS)
    desired_angle = float(actuators.steeringAngleDeg)
    self._update_torque_active(CS, lat_active, desired_angle, actuators)
    self._update_angle(CS, lat_active, desired_angle)
    self._update_torque(CS, actuators)

  def _update_wheel_touched(self, wheel_touched: bool, minimum_count: int) -> bool:
    self.wheel_touch_cnt += 1 if wheel_touched else -1
    self.wheel_touch_cnt = int(np.clip(self.wheel_touch_cnt, 0, minimum_count * 2 + 1))
    return self.wheel_touch_cnt > minimum_count

  def _update_torsion(self, torque: float, threshold: float, minimum_count: int) -> bool:
    abs_torque = abs(torque)
    self.torsion_cnt += max(1, math.ceil(abs_torque / threshold)) if abs_torque > threshold else -1
    self.torsion_cnt = int(np.clip(self.torsion_cnt, 0, minimum_count * 2 + 1))
    return self.torsion_cnt > minimum_count

  def _update_torsion_presence(self, torque: float) -> bool:
    self.presence_cnt = self.presence_cnt + 1 if abs(torque) > PRESENCE_TORQUE_THRESHOLD else 0
    if self.presence_cnt >= PRESENCE_MIN_FRAMES:
      self.presence_hold = PRESENCE_HOLD_FRAMES
    elif self.presence_hold > 0:
      self.presence_hold -= 1
    return self.presence_hold > 0

  def _update_driver_torque(self, CS) -> float:
    # EPAS angle control itself loads the torsion bar. Model the wheel's reaction
    # and subtract it before using torsion as evidence of a driver override.
    inertia = 0.0205  # kg*m^2
    stiffness = 51.0  # Nm/rad
    damping = 0.156  # Nm/(rad/s)
    friction = 0.141  # Nm, tanh-blended over 0.0066 rad/s
    substeps = 10

    column_angle = math.radians(CS.out.steeringAngleDeg)
    if self.wheel_angle is None:
      self.wheel_angle = self.column_angle_last = column_angle
    h = 0.01 / substeps
    for i in range(substeps):
      c = self.column_angle_last + (column_angle - self.column_angle_last) * (i + 1) / substeps
      bar_torque = stiffness * (self.wheel_angle - c)
      accel = (-bar_torque - damping * self.wheel_rate - friction * math.tanh(self.wheel_rate / 0.0066)) / inertia
      self.wheel_rate += accel * h
      self.wheel_angle += self.wheel_rate * h
    self.column_angle_last = column_angle
    return CS.out.steeringTorque - stiffness * (self.wheel_angle - column_angle)

  def _update_hands_on(self, CS) -> None:
    driver_torque = self._update_driver_torque(CS)
    wheel_touch = False
    if not self.gen2:
      calibration = CS.sccm_wheel_touch["SCCM_WheelTouch_Calibration"]
      capacitive = CS.sccm_wheel_touch["SCCM_WheelTouch_CapacitiveValue"] > calibration * 0.9
      wheel_touch = self._update_wheel_touched(capacitive, 25)
    torsion = self._update_torsion(driver_torque, 3.0, 9)
    presence = self._update_torsion_presence(driver_torque)
    self.hands_on = wheel_touch or torsion or CS.hands_on_level > 1
    self.hands_off_frames = 0 if self.hands_on or presence else self.hands_off_frames + 1

  def _reset_prearm(self) -> None:
    self.torque_prearm = False
    self.prearm_frames = 0
    self.prearm_torque_peak = 0
    self.prearm_stall_frames = 0

  def _finish_prearm(self, outcome: str) -> None:
    self.prearm_last_outcome = outcome
    self._reset_prearm()

  def _update_torque_active(self, CS, lat_active: bool, desired_angle: float, actuators=None) -> None:
    self.torque_active_frames = self.torque_active_frames + 1 if self.torque_active else 0

    epas_ready = CS.eac_status == 1 and CS.eac_error_code == 0
    eac_active = CS.eac_status == 2
    gap = abs(desired_angle - CS.out.steeringAngleDeg)

    if not lat_active:
      self.torque_active = False
      self.prearm_abort_lockout = 0
      self._reset_prearm()
    elif self.force_torque:
      self.eac_dead_frames = 0
      if self.torque_active:
        self._reset_prearm()
      elif not self.angle_harness or not self.angle_active:
        # Base harnesses and fresh torque-mode engagements have no active angle
        # channel to preserve during activation.
        self.torque_active = True
        self._reset_prearm()
      elif self.prearm_abort_lockout > 0:
        self.prearm_abort_lockout -= 1
        self._reset_prearm()
      else:
        steer_max = round(float(np.interp(CS.out.vEgoRaw, CCP.STEER_MAX_LOOKUP[0], CCP.STEER_MAX_LOOKUP[1])))
        hold_target = abs(int(round(float(getattr(actuators, "torque", 0.0)) * steer_max)))
        driver_took_over = self.hands_on and CS.out.steeringPressed
        if not eac_active or driver_took_over or hold_target < TORQUE_PREARM_MIN_HOLD:
          self.torque_active = True
          self._reset_prearm()
        else:
          # Evaluate the torque reached on the prior frame, while angle remains
          # active for this frame.
          self.torque_prearm = True
          self.prearm_frames += 1
          if abs(self.apply_torque_last) > self.prearm_torque_peak:
            self.prearm_torque_peak = abs(self.apply_torque_last)
            self.prearm_stall_frames = 0
          else:
            self.prearm_stall_frames += 1

          reached = abs(self.apply_torque_last) >= TORQUE_PREARM_EXIT_FRAC * hold_target
          stalled = self.prearm_stall_frames >= TORQUE_PREARM_STALL_FRAMES
          if reached:
            self.torque_active = True
            self._finish_prearm("reached")
          elif self.prearm_frames >= TORQUE_PREARM_MAX_FRAMES:
            if stalled:
              self._finish_prearm("abort")
              self.prearm_abort_lockout = TORQUE_PREARM_ABORT_LOCKOUT
            else:
              self.torque_active = True
              self._finish_prearm("backstop")
    elif self.hands_on and CS.out.steeringPressed:
      self.prearm_abort_lockout = 0
      self._reset_prearm()
      self.torque_active = True
    elif self.eac_dead_frames >= EAC_RECOVER_FRAMES:
      self.prearm_abort_lockout = 0
      self._reset_prearm()
      self.torque_active = True
    elif not self.lat_active_last and not epas_ready:
      self.prearm_abort_lockout = 0
      self._reset_prearm()
      self.torque_active = True
    else:
      self.prearm_abort_lockout = 0
      self._reset_prearm()
      if (self.torque_active and self.torque_active_frames >= MIN_TORQUE_FRAMES and
          self.hands_off_frames >= HANDS_OFF_EXIT_FRAMES and epas_ready):
        fw_max = float(np.interp(CS.out.vEgoRaw, EPAS_FW_MAX_ANGLE_BP, EPAS_FW_MAX_ANGLE_V)) * EPAS_FW_ANGLE_MARGIN
        iso_max = get_max_angle_vm(max(CS.out.vEgoRaw, 1.0), self.VM_safety, CCP)
        in_envelope = abs(CS.out.steeringAngleDeg) < min(fw_max, HANDOFF_MAX_ANGLE_DEG, iso_max)
        threshold_dps = float(np.interp(CS.out.vEgoRaw, EPAS_FW_RATE_BP, EPAS_FW_RATE_V)) * 100.0
        lower, upper = self.rate_budget.bounds(threshold_dps, EPAS_FW_RATE_MARGIN)
        rate_settled = lower <= CS.out.steeringAngleDeg <= upper and abs(CS.out.steeringRateDeg) < UNWIND_HANDOFF_RATE
        if in_envelope and rate_settled and gap < HANDOFF_EXIT_DEG:
          self.torque_active = False

    if lat_active and not self.torque_active and not eac_active:
      self.eac_dead_frames += 1
    else:
      self.eac_dead_frames = 0

    self.lat_active_last = lat_active

  def _update_angle(self, CS, lat_active: bool, desired_angle: float) -> None:
    self.angle_active = lat_active and not self.torque_active

    # Use future vEgo so the jerk limit ramps angle down before the lateral-
    # acceleration envelope shrinks.
    v_lookahead = max(CS.out.vEgoRaw + max(CS.out.aEgo, 0.0), 1.0)
    apply_angle = apply_rivian_steer_angle_limits_vm(desired_angle, self.apply_angle_last, v_lookahead,
                                                     CS.out.steeringAngleDeg, self.angle_active, CCP, self.VM_safety)

    if self.angle_active:
      fw_max = float(np.interp(CS.out.vEgoRaw, EPAS_FW_MAX_ANGLE_BP, EPAS_FW_MAX_ANGLE_V)) * EPAS_FW_ANGLE_MARGIN
      apply_angle = float(np.clip(apply_angle, -fw_max, fw_max))

      threshold_dps = float(np.interp(CS.out.vEgoRaw, EPAS_FW_RATE_BP, EPAS_FW_RATE_V)) * 100.0
      lower, upper = self.rate_budget.bounds(threshold_dps, EPAS_FW_RATE_MARGIN)
      apply_angle = float(np.clip(apply_angle, lower, upper))

      step = get_max_angle_delta_vm(max(CS.out.vEgoRaw, 1.0), self.VM_safety, CCP) * PANDA_STEP_MARGIN
      apply_angle = float(np.clip(apply_angle, self.apply_angle_last - step, self.apply_angle_last + step))

    self.apply_angle_last = apply_angle
    self.rate_budget.push(apply_angle)

  def _update_torque(self, CS, actuators) -> None:
    torque_requested = self.torque_active or self.torque_prearm
    self.toi_act_cmd, torque_allowed = self.toi_controller.update(
      torque_requested,
      abs(CS.out.steeringAngleDeg) >= TOI_MAX_ANGLE_DEG,
      bool(getattr(CS, "toi_fault", False)),
      bool(getattr(CS, "toi_active", False)),
      bool(getattr(CS, "toi_unavailable", False)),
      prearming=self.torque_prearm,
    )

    if not torque_requested:
      self.apply_torque_last = 0
      self.torque_cmd = 0
      return

    if not torque_allowed:
      # Keep the limiter through a scheduled high-angle ToI cycle so assist
      # resumes without a sawtooth. The wire stays at zero until torque is
      # allowed; panda preserves desired_torque_last across that cut.
      # Engagement waits, faults, and failed activation still restart from zero.
      if not self.toi_controller.preserve_torque:
        self.apply_torque_last = 0
      self.torque_cmd = 0
      return

    steer_max = round(float(np.interp(CS.out.vEgoRaw, CCP.STEER_MAX_LOOKUP[0], CCP.STEER_MAX_LOOKUP[1])))
    new_torque = int(round(float(actuators.torque) * steer_max))
    apply_torque = apply_driver_steer_torque_limits(new_torque, self.apply_torque_last,
                                                    CS.out.steeringTorque, CCP, steer_max)
    if abs(CS.out.steeringAngleDeg) > HIGH_ANGLE_THRESHOLD_DEG:
      cap = int(round(steer_max * HIGH_ANGLE_CAP_FRAC))
      apply_torque = int(np.clip(apply_torque, -cap, cap))

    self.apply_torque_last = apply_torque
    self.torque_cmd = apply_torque
