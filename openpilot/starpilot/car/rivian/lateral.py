"""Rivian lateral helpers owned by Controls.

The Extreme harness drives a hybrid EPS: the car controller selects torque or
angle each frame and reports the active channel in carOutput. While angle is
active the torque controller must not wind up, the angle controller owns the
published lateral state, and safety limiting is judged on angle. The R1T's
long wheelbase also needs its front path widened so the bed tracks the model.
"""
import numpy as np

from opendbc.car.structs import car
from opendbc.car.rivian.values import CAR, RivianFlags
from openpilot.selfdrive.controls.lib.latcontrol_angle import LatControlAngle, STEER_ANGLE_SATURATION_THRESHOLD

LateralControlMode = car.CarControl.Actuators.LateralControlMode
REAR_AXLE_OFFTRACKING_FOLLOW_FRAC = 0.30


def compensate_rear_axle_offtracking(curvature: float, wheelbase: float,
                                     follow_frac: float = REAR_AXLE_OFFTRACKING_FOLLOW_FRAC) -> float:
  # Command front-axle curvature so a point follow_frac*L behind the front tracks the path.
  # R_front = sqrt(R^2 + L_eff^2) => k' = k / sqrt(1 + (k L_eff)^2).
  L_eff = wheelbase * follow_frac
  if L_eff <= 0.0:
    return float(curvature)
  kl = curvature * L_eff
  return float(curvature / np.sqrt(1.0 + kl * kl))


class RivianLateral:
  def __init__(self, CP, CI, dt):
    self.compensate_offtracking = CP.carFingerprint == CAR.RIVIAN_R1T
    self.wheelbase = float(CP.wheelbase)
    self.angle_controller = LatControlAngle(CP, CI, dt) if CP.flags & RivianFlags.ANGLE_HARNESS else None
    self.angle_steering = False
    self.angle_log = None

  def desired_curvature(self, curvature: float, lat_active: bool) -> float:
    if self.compensate_offtracking and lat_active:
      return compensate_rear_axle_offtracking(curvature, self.wheelbase)
    return curvature

  def observe_output(self, lat_active: bool, car_output) -> bool:
    # Zero torque is a valid Extreme torque-mode command; only the reported channel selects angle.
    self.angle_steering = bool(self.angle_controller is not None and lat_active and
                               car_output.actuatorsOutput.lateralControlMode == LateralControlMode.angle)
    return self.angle_steering

  def update_angle(self, active, CS, VM, params, steer_limited_by_safety, desired_curvature, curvature_limited, lat_delay):
    if self.angle_controller is None:
      self.angle_log = None
      return None
    _, angle_output, angle_log = self.angle_controller.update(active, CS, VM, params, steer_limited_by_safety,
                                                              desired_curvature, curvature_limited, lat_delay)
    if self.angle_steering:
      self.angle_log = angle_log
    else:
      self.angle_log = None
      self.angle_controller.reset()
    return float(angle_output)

  def steer_limited(self, actuators, car_output) -> bool | None:
    if not self.angle_steering:
      return None
    return abs(actuators.steeringAngleDeg - car_output.actuatorsOutput.steeringAngleDeg) > STEER_ANGLE_SATURATION_THRESHOLD
