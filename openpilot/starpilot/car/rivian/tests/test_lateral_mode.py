from types import SimpleNamespace

from opendbc.car.structs import car
from openpilot.starpilot.car.rivian.lateral_mode import ANGLE_COLOR, DRIVER_OVERRIDE_COLOR, TORQUE_COLOR, wheel_tint

Mode = car.CarControl.Actuators.LateralControlMode
RIVIAN = SimpleNamespace(brand='rivian')


def _output(mode):
  return SimpleNamespace(actuatorsOutput=SimpleNamespace(lateralControlMode=mode))


def test_wheel_tint_reports_the_active_channel():
  control, state = SimpleNamespace(latActive=True), SimpleNamespace(steeringPressed=False)
  assert wheel_tint(RIVIAN, control, state, _output(Mode.angle)) == ANGLE_COLOR
  assert wheel_tint(RIVIAN, control, state, _output(Mode.torque)) == TORQUE_COLOR
  assert wheel_tint(RIVIAN, control, state, _output(Mode.torqueRecovering)) == TORQUE_COLOR
  assert wheel_tint(RIVIAN, control, state, _output(Mode.inactive)) is None
  assert wheel_tint(RIVIAN, control, SimpleNamespace(steeringPressed=True), _output(Mode.angle)) == DRIVER_OVERRIDE_COLOR


def test_wheel_tint_is_rivian_and_lateral_only():
  state = SimpleNamespace(steeringPressed=False)
  assert wheel_tint(SimpleNamespace(brand='toyota'), SimpleNamespace(latActive=True), state, _output(Mode.angle)) is None
  assert wheel_tint(RIVIAN, SimpleNamespace(latActive=False), state, _output(Mode.angle)) is None
  assert wheel_tint(RIVIAN, SimpleNamespace(latActive=True), state, None) is None
