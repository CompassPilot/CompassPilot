import pyray as rl

from opendbc.car.rivian.values import RivianFlags
from openpilot.selfdrive.ui.ui_state import ui_state

ANGLE_COLOR = rl.Color(0x3A, 0xDB, 0x6D, 255)
TORQUE_COLOR = rl.Color(0x4D, 0x9D, 0xFF, 255)
ZERO_TORQUE_HOLD = 10


class RivianLateralMode:
  """Infer the active Extreme-harness channel from the commanded output."""

  def __init__(self):
    self.mode: str | None = None
    self.zero_torque_count = ZERO_TORQUE_HOLD
    self._frame = -1

  def update(self) -> None:
    sm = ui_state.sm
    if sm.frame == self._frame:
      return
    self._frame = sm.frame

    CP = ui_state.CP
    angle_rivian = CP is not None and CP.brand == "rivian" and bool(CP.flags & RivianFlags.ANGLE_HARNESS)
    if not angle_rivian or sm.recv_frame["carControl"] < ui_state.started_frame or not sm["carControl"].latActive:
      self.mode = None
      return

    if abs(sm["carOutput"].actuatorsOutput.torque) < 1e-3:
      self.zero_torque_count = min(self.zero_torque_count + 1, ZERO_TORQUE_HOLD)
    else:
      self.zero_torque_count = 0
    self.mode = "angle" if self.zero_torque_count >= ZERO_TORQUE_HOLD else "torque"

  @property
  def wheel_tint(self) -> "rl.Color | None":
    if self.mode == "angle":
      return ANGLE_COLOR
    if self.mode == "torque":
      return TORQUE_COLOR
    return None


rivian_lateral_mode = RivianLateralMode()
