"""Display Rivian's active lateral channel and driver steering input on the wheel icon."""
from opendbc.car.structs import car

LateralControlMode = car.CarControl.Actuators.LateralControlMode
ANGLE_COLOR = (0x3A, 0xDB, 0x6D)
TORQUE_COLOR = (0x4D, 0x9D, 0xFF)
DRIVER_OVERRIDE_COLOR = (255, 255, 255)


def wheel_tint(cp, control, car_state, car_output) -> tuple[int, int, int] | None:
  try:
    if cp is None or cp.brand != 'rivian' or control is None or not control.latActive or car_output is None:
      return None
    if car_state is not None and car_state.steeringPressed:
      return DRIVER_OVERRIDE_COLOR
    mode = car_output.actuatorsOutput.lateralControlMode
    if mode == LateralControlMode.angle:
      return ANGLE_COLOR
    if mode in (LateralControlMode.torque, LateralControlMode.torqueRecovering):
      return TORQUE_COLOR
  except (AttributeError, TypeError, ValueError):
    pass
  return None
