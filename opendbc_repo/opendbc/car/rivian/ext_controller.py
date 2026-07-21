"""Rivian Gen 1 hybrid steering for the Extreme harness."""

import math
from collections import deque

import numpy as np

from opendbc.car.lateral import (apply_driver_steer_torque_limits, apply_steer_angle_limits_vm,
                                 common_fault_avoidance, get_max_angle_delta_vm)
from opendbc.car.rivian.values import CAR, CarControllerParams as CCP
from opendbc.car.vehicle_model import VehicleModel

# Limits observed in the Gen 1 EPAS firmware. Margins keep commands inside the
# firmware's absolute-angle and sliding-window rate checks.
EPAS_FW_MAX_ANGLE_BP = [0.0, 2.78, 5.56, 8.33, 12.50, 16.67, 22.22, 27.78]
EPAS_FW_MAX_ANGLE_V = [500, 500, 250, 150, 85, 56, 40, 25]
EPAS_FW_RATE_BP = [5.56, 8.33, 12.50, 16.67]
EPAS_FW_RATE_V = [4.50, 1.50, 0.60, 0.18]
EPAS_FW_ANGLE_MARGIN = 0.98
EPAS_FW_RATE_MARGIN = 0.94
PANDA_STEP_MARGIN = 0.9

MIN_TORQUE_FRAMES = 50
HANDOFF_EXIT_DEG = 15.0
UNWIND_HANDOFF_RATE = 40.0
EAC_RECOVER_FRAMES = 15

EAC_REARM_RELEASE_FRAMES = 25

# Gen 1 EPAS can latch ToiFlt if the torque-request bit remains asserted at a
# high steering angle. A two-frame request blip avoids that fault.
TOI_MAX_ANGLE_DEG = 90
TOI_MAX_ANGLE_FRAMES = 89
TOI_BLIP_FRAMES = 2


class _RateBudget:
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
  """Hybrid Gen 1 steering: EPAS angle control with cooperative torque fallback."""

  def __init__(self, CP):
    self.VM = VehicleModel(CP)
    self.VM_safety = VehicleModel(get_safety_CP())

    self.wheel_touch_cnt = 0
    self.torsion_cnt = 0
    self.torsion_sign = 0
    self.hands_on = False

    self.torque_active = False
    self.torque_active_frames = 0
    self.lat_active_last = False
    self.eac_dead_frames = 0
    self.eac_rearm_release_frames = 0
    self.eac_rearm_attempted = False

    self.apply_angle_last = 0.0
    self.angle_active = False
    self.rate_budget = _RateBudget()
    self.roll = 0.0
    self.angle_offset_deg = 0.0

    self.apply_torque_last = 0
    self.toi_angle_limit_counter = 0
    self.toi_act_cmd = False

  def update(self, CS, lat_active: bool, actuators) -> None:
    self._update_hands_on(CS)
    desired_angle = math.degrees(self.VM.get_steer_from_curvature(
      -float(actuators.curvature), CS.out.vEgo, self.roll)) + self.angle_offset_deg
    self._update_torque_active(CS, lat_active, desired_angle)
    self._update_angle(CS, lat_active, desired_angle)
    self._update_torque(CS, actuators)

  def _update_wheel_touched(self, wheel_touched: bool, minimum_count: int) -> bool:
    self.wheel_touch_cnt += 1 if wheel_touched else -1
    self.wheel_touch_cnt = int(np.clip(self.wheel_touch_cnt, 0, minimum_count * 2 + 1))
    return self.wheel_touch_cnt > minimum_count

  def _update_torsion(self, torque: float, threshold: float, minimum_count: int) -> bool:
    abs_torque = abs(torque)
    pressed = abs_torque > threshold
    sign = int(np.sign(torque))
    if pressed and self.torsion_sign and sign != self.torsion_sign:
      self.torsion_cnt = 0
    else:
      self.torsion_cnt += max(1, math.ceil(abs_torque / threshold)) if pressed else -1
      self.torsion_cnt = int(np.clip(self.torsion_cnt, 0, minimum_count * 2 + 1))
    if pressed:
      self.torsion_sign = sign
    return self.torsion_cnt > minimum_count

  def _update_hands_on(self, CS) -> None:
    calibration = CS.sccm_wheel_touch["SETME_X52"]
    capacitive = CS.sccm_wheel_touch["SCCM_WheelTouch_CapacitiveValue"] > calibration * 0.9
    wheel_touch = self._update_wheel_touched(capacitive, 25)
    torsion = self._update_torsion(CS.out.steeringTorque, 4.0, 9)
    self.hands_on = wheel_touch or torsion or CS.hands_on_level > 1

  def _update_torque_active(self, CS, lat_active: bool, desired_angle: float) -> None:
    self.torque_active_frames = self.torque_active_frames + 1 if self.torque_active else 0
    epas_ready = CS.eac_status == 1 and CS.eac_error_code == 0
    eac_active = CS.eac_status == 2
    epas_inhibited = CS.eac_status == 0 and CS.eac_error_code == 0
    gap = abs(desired_angle - CS.out.steeringAngleDeg)

    if (lat_active and self.torque_active and epas_inhibited and
        not self.hands_on and not CS.out.steeringPressed):
      self.eac_rearm_release_frames = min(self.eac_rearm_release_frames + 1, EAC_REARM_RELEASE_FRAMES)
    else:
      self.eac_rearm_release_frames = 0

    if not lat_active:
      self.torque_active = False
      self.eac_rearm_attempted = False
    elif self.hands_on and CS.out.steeringPressed:
      self.torque_active = True
      self.eac_rearm_attempted = False
    elif self.eac_dead_frames >= EAC_RECOVER_FRAMES:
      self.torque_active = True
    elif not self.lat_active_last and not epas_ready:
      self.torque_active = True
      self.eac_rearm_attempted = False
    elif self.torque_active and self.torque_active_frames >= MIN_TORQUE_FRAMES and not self.hands_on:
      fw_max = float(np.interp(CS.out.vEgoRaw, EPAS_FW_MAX_ANGLE_BP, EPAS_FW_MAX_ANGLE_V)) * EPAS_FW_ANGLE_MARGIN
      in_envelope = abs(CS.out.steeringAngleDeg) < fw_max
      threshold_dps = float(np.interp(CS.out.vEgoRaw, EPAS_FW_RATE_BP, EPAS_FW_RATE_V)) * 100.0
      lower, upper = self.rate_budget.bounds(threshold_dps, EPAS_FW_RATE_MARGIN)
      rate_settled = lower <= CS.out.steeringAngleDeg <= upper and abs(CS.out.steeringRateDeg) < UNWIND_HANDOFF_RATE

      rearm_ready = (epas_inhibited and not self.eac_rearm_attempted and
                     self.eac_rearm_release_frames >= EAC_REARM_RELEASE_FRAMES and
                     not CS.out.steeringPressed and not CS.out.steerFaultTemporary and
                     not CS.out.steerFaultPermanent)
      if (epas_ready or rearm_ready) and in_envelope and rate_settled and gap < HANDOFF_EXIT_DEG:
        self.torque_active = False
        self.eac_rearm_attempted = rearm_ready

    if eac_active:
      self.eac_rearm_attempted = False

    if lat_active and not self.torque_active and not eac_active:
      self.eac_dead_frames += 1
    else:
      self.eac_dead_frames = 0
    self.lat_active_last = lat_active

  def _update_angle(self, CS, lat_active: bool, desired_angle: float) -> None:
    self.angle_active = lat_active and not self.torque_active
    v_lookahead = max(CS.out.vEgoRaw + max(CS.out.aEgo, 0.0), 1.0)
    apply_angle = apply_steer_angle_limits_vm(desired_angle, self.apply_angle_last, v_lookahead,
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
    if not self.torque_active:
      self.apply_torque_last = 0
      self.toi_act_cmd = False
      self.toi_angle_limit_counter = 0
      return

    steer_max = round(float(np.interp(CS.out.vEgoRaw, CCP.STEER_MAX_LOOKUP[0], CCP.STEER_MAX_LOOKUP[1])))
    requested_torque = int(round(float(actuators.torque) * steer_max))
    torque_cmd = apply_driver_steer_torque_limits(requested_torque, self.apply_torque_last,
                                                  CS.out.steeringTorque, CCP, steer_max)

    self.toi_angle_limit_counter, toi_act = common_fault_avoidance(
      abs(CS.out.steeringAngleDeg) >= TOI_MAX_ANGLE_DEG, self.torque_active,
      self.toi_angle_limit_counter, TOI_MAX_ANGLE_FRAMES, TOI_BLIP_FRAMES)

    # Reset the limiter during the request-bit blip so torque ramps back from zero.
    if not toi_act:
      torque_cmd = 0

    self.apply_torque_last = torque_cmd
    self.toi_act_cmd = toi_act
