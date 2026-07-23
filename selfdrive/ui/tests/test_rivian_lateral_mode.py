import importlib.util
from enum import IntFlag
from pathlib import Path
import sys
from types import ModuleType, SimpleNamespace


MODULE_PATH = Path(__file__).resolve().parents[1] / "onroad" / "starpilot" / "rivian_lateral_mode.py"


class FakeSubMaster(dict):
  def __init__(self, *, reported_torque, can_torque):
    super().__init__({
      "carControl": SimpleNamespace(latActive=True),
      "carOutput": SimpleNamespace(
        actuatorsOutput=SimpleNamespace(torque=reported_torque, torqueOutputCan=can_torque),
      ),
    })
    self.frame = 1
    self.recv_frame = {"carControl": 1}


def load_lateral_mode(monkeypatch, *, brand="rivian", angle_harness=True, reported_torque=0.0, can_torque=0):
  class RivianFlags(IntFlag):
    ANGLE_HARNESS = 1

  fake_pyray = ModuleType("pyray")
  fake_pyray.Color = lambda *args: args
  monkeypatch.setitem(sys.modules, "pyray", fake_pyray)

  values_module = ModuleType("opendbc.car.rivian.values")
  values_module.RivianFlags = RivianFlags
  monkeypatch.setitem(sys.modules, "opendbc.car.rivian.values", values_module)

  ui_state = SimpleNamespace(
    CP=SimpleNamespace(brand=brand, flags=RivianFlags.ANGLE_HARNESS if angle_harness else 0),
    sm=FakeSubMaster(reported_torque=reported_torque, can_torque=can_torque),
    started_frame=0,
  )
  ui_state_module = ModuleType("openpilot.selfdrive.ui.ui_state")
  ui_state_module.ui_state = ui_state
  monkeypatch.setitem(sys.modules, "openpilot.selfdrive.ui.ui_state", ui_state_module)

  spec = importlib.util.spec_from_file_location("rivian_lateral_mode_under_test", MODULE_PATH)
  assert spec is not None and spec.loader is not None
  module = importlib.util.module_from_spec(spec)
  spec.loader.exec_module(module)
  return module


def test_angle_mode_uses_zero_can_torque_when_reported_torque_echoes_request(monkeypatch):
  module = load_lateral_mode(monkeypatch, reported_torque=0.42, can_torque=0)
  mode = module.RivianLateralMode()

  mode.update()

  assert mode.mode == "angle"


def test_nonzero_can_torque_selects_torque_mode(monkeypatch):
  module = load_lateral_mode(monkeypatch, reported_torque=0.42, can_torque=100)
  mode = module.RivianLateralMode()

  mode.update()

  assert mode.mode == "torque"


def test_non_angle_rivian_is_not_classified(monkeypatch):
  module = load_lateral_mode(monkeypatch, angle_harness=False, reported_torque=0.42, can_torque=0)
  mode = module.RivianLateralMode()

  mode.update()

  assert mode.mode is None
