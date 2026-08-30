import math
import re
from types import SimpleNamespace

import pytest

from opendbc.can import CANPacker
from opendbc.car import Bus, structs
from opendbc.car.common.conversions import Conversions as CV
from opendbc.car.docs_definitions import CarHarness
from opendbc.car.rivian import carcontroller as rivian_carcontroller
from opendbc.car.rivian import ext_controller
from opendbc.car.rivian.carcontroller import CarController, get_longitudinal_accel
from opendbc.car.rivian.carstate import get_cruise_available
from opendbc.car.rivian.carstate_ext import RivianLongitudinalState
from opendbc.car.rivian.ext_controller import ExternalController
from opendbc.car.rivian.fingerprints import FW_VERSIONS
from opendbc.car.rivian.faults import get_steering_faults
from opendbc.car.rivian.interface import CarInterface
from opendbc.car.rivian.riviancan import create_wheel_touch
from opendbc.car.rivian.toi_controller import (TOI_ACK_FRAMES, TOI_MAX_ANGLE_FRAMES, TOI_RECOVERY_TIMEOUT_FRAMES,
                                               ToiController, ToiState)
from opendbc.car.rivian.values import (CAR, FW_QUERY_CONFIG, CarControllerParams, ModelLine, ModelYear,
                                       RIVIAN_FW_VERSION_REGEX, RivianFlags, RivianSafetyFlags, WMI)


class TestRivian:
  @staticmethod
  def _car_params(bus_one_messages=(), alpha_long=False, gen2=False):
    fingerprint = {bus: {} for bus in range(8)}
    if not gen2:
      fingerprint[0][0x321] = 8
    fingerprint[1] = {address: 8 for address in bus_one_messages}
    return CarInterface.get_params(CAR.RIVIAN_R1_GEN1, fingerprint, [], alpha_long, False, False, SimpleNamespace())

  def test_base_harness_remains_torque_capable(self):
    params = self._car_params()

    assert not params.dashcamOnly
    assert not params.flags & RivianFlags.ANGLE_HARNESS
    assert not params.safetyConfigs[0].safetyParam & RivianSafetyFlags.ANGLE_CONTROL
    assert math.isclose(params.steerActuatorDelay, 0.15, abs_tol=1e-6)
    assert not params.steerAtStandstill
    assert math.isclose(params.lateralSmoothSeconds, 0.0, abs_tol=1e-6)
    assert params.steerControlType == structs.CarParams.SteerControlType.torque

  def test_extreme_harness_enables_angle_path(self):
    params = self._car_params((0x1310,))

    assert not params.dashcamOnly
    assert params.flags & RivianFlags.ANGLE_HARNESS
    assert params.safetyConfigs[0].safetyParam & RivianSafetyFlags.ANGLE_CONTROL
    assert math.isclose(params.steerActuatorDelay, 0.1, abs_tol=1e-6)
    assert params.steerAtStandstill
    assert math.isclose(params.lateralSmoothSeconds, 0.0, abs_tol=1e-6)
    assert params.steerControlType == structs.CarParams.SteerControlType.torque

  def test_longitudinal_harness_preserves_starpilot_detection(self):
    params = self._car_params((0x1310, 0x131A), alpha_long=True)

    assert params.flags & RivianFlags.LONGITUDINAL_HARNESS
    assert params.openpilotLongitudinalControl
    assert params.enableBsm
    assert not params.radarUnavailable
    assert params.safetyConfigs[0].safetyParam & RivianSafetyFlags.LONG_CONTROL

  def test_longitudinal_harness_without_angle_box_remains_torque_capable(self):
    params = self._car_params((0x131A,), alpha_long=True)

    assert not params.dashcamOnly
    assert params.openpilotLongitudinalControl
    assert params.flags & RivianFlags.LONGITUDINAL_HARNESS
    assert not params.flags & RivianFlags.ANGLE_HARNESS
    assert not params.safetyConfigs[0].safetyParam & RivianSafetyFlags.ANGLE_CONTROL
    assert params.safetyConfigs[0].safetyParam & RivianSafetyFlags.LONG_CONTROL
    assert math.isclose(params.steerActuatorDelay, 0.15, abs_tol=1e-6)
    assert not params.steerAtStandstill
    assert params.steerControlType == structs.CarParams.SteerControlType.torque

  def test_gen2_is_detected_without_enabling_harness_capabilities(self):
    params = self._car_params(gen2=True)

    assert params.flags & RivianFlags.GEN2
    assert not params.flags & RivianFlags.ANGLE_HARNESS
    assert not params.flags & RivianFlags.LONGITUDINAL_HARNESS

  def test_gen2_detection_preserves_explicit_harness_capabilities(self):
    params = self._car_params((0x1310, 0x131A), alpha_long=True, gen2=True)

    assert params.flags & RivianFlags.GEN2
    assert params.flags & RivianFlags.ANGLE_HARNESS
    assert params.flags & RivianFlags.LONGITUDINAL_HARNESS
    assert params.safetyConfigs[0].safetyParam & RivianSafetyFlags.ANGLE_CONTROL
    assert params.safetyConfigs[0].safetyParam & RivianSafetyFlags.LONG_CONTROL

  def test_gen2_hands_on_path_does_not_require_wheel_touch_message(self):
    controller = ExternalController(self._car_params((0x1310,), gen2=True))
    state = SimpleNamespace(
      out=SimpleNamespace(steeringAngleDeg=0.0, steeringTorque=0.0),
      hands_on_level=0,
      sccm_wheel_touch=None,
    )

    controller._update_hands_on(state)

    assert not controller.hands_on

  def test_torque_and_longitudinal_tuning(self):
    params = self._car_params((0x1310, 0x131A), alpha_long=True)

    assert CarControllerParams.STEER_MAX == 385
    assert CarControllerParams.STEER_MAX_LOOKUP == ([9, 13, 25, 27], [385, 350, 295, 275])
    assert math.isclose(params.longitudinalActuatorDelay, 0.3, abs_tol=1e-6)
    assert math.isclose(params.vEgoStopping, 0.25, abs_tol=1e-6)
    assert math.isclose(params.stopAccel, -0.2, abs_tol=1e-6)
    assert list(params.longitudinalTuning.kiV) == pytest.approx([0.2])

  def test_gas_pedal_zeroes_stale_longitudinal_acceleration(self):
    assert get_longitudinal_accel(0.07, gas_pressed=True) == 0.0
    assert get_longitudinal_accel(-2.44, gas_pressed=True) == 0.0
    assert get_longitudinal_accel(0.07, gas_pressed=False) == 0.07

  def test_longitudinal_drag_feedforward_is_active_only_while_controlling(self):
    assert get_longitudinal_accel(0.0, gas_pressed=False, long_active=False, v_ego=8.0) == 0.0
    assert get_longitudinal_accel(0.0, gas_pressed=False, long_active=True, v_ego=8.0) == 0.17
    assert get_longitudinal_accel(0.0, gas_pressed=True, long_active=True, v_ego=8.0) == 0.0

  def test_toi_recovery_failure_is_published_on_state_changes(self):
    writes = []
    controller = CarController.__new__(CarController)
    controller.ext_controller = SimpleNamespace(toi_controller=SimpleNamespace(recovery_failed=False))
    controller.toi_recovery_failed_last = None
    controller.toi_recovery_params = SimpleNamespace(put_bool=lambda key, value: writes.append((key, value)))

    controller._publish_toi_recovery_failed()
    controller._publish_toi_recovery_failed()
    controller.ext_controller.toi_controller.recovery_failed = True
    controller._publish_toi_recovery_failed()

    assert writes == [
      ("RivianToiRecoveryFailed", False),
      ("RivianToiRecoveryFailed", True),
    ]

  @pytest.mark.parametrize("feature_status", range(8))
  def test_stock_harness_cruise_availability_uses_acm_state(self, feature_status):
    assert get_cruise_available(RivianFlags(0), feature_status) == (feature_status in (0, 1))

  @pytest.mark.parametrize("feature_status", range(8))
  def test_longitudinal_harness_cruise_remains_available(self, feature_status):
    assert get_cruise_available(RivianFlags.LONGITUDINAL_HARNESS, feature_status)

  def test_angle_limit_order_is_rivian_local(self, monkeypatch):
    monkeypatch.setattr(ext_controller, "get_max_angle_vm", lambda *args: 50.0)
    monkeypatch.setattr(ext_controller, "get_max_angle_delta_vm", lambda *args: 10.0)

    limited = ext_controller.apply_rivian_steer_angle_limits_vm(
      apply_angle=100.0,
      apply_angle_last=80.0,
      v_ego_raw=10.0,
      steering_angle=0.0,
      lat_active=True,
      limits=CarControllerParams,
      VM=None,
    )

    # Clip to the acceleration envelope first, then unwind toward it instead of
    # snapping from the previous command.
    assert limited == pytest.approx(77.5)

  def test_gen1_docs_use_rivian_a_and_gen2_uses_rivian_b(self):
    docs = CAR.RIVIAN_R1_GEN1.config.car_docs
    gen1_docs = [doc for doc in docs if "2022-24" in doc.name]
    gen2_docs = [doc for doc in docs if "2025" in doc.name]

    assert all(CarHarness.rivian in doc.car_parts.parts for doc in gen1_docs)
    assert all(CarHarness.rivian_b in doc.car_parts.parts for doc in gen2_docs)
    assert all(doc.video == "https://youtu.be/dflSSGQwYNc" for doc in gen1_docs)

  def test_rivian_firmware_regex_matches_database(self):
    for ecus in FW_VERSIONS.values():
      for versions in ecus.values():
        assert all(re.fullmatch(RIVIAN_FW_VERSION_REGEX, version) for version in versions)

  def test_corrected_wheel_touch_signals_pack(self):
    packer = CANPacker("rivian_primary_actuator")
    msg = create_wheel_touch(packer, {
      "SCCM_WheelTouch_Counter": 3,
      "SCCM_WheelTouch_HandsOn": 0,
      "SCCM_WheelTouch_Calibration": 80,
      "SCCM_WheelTouch_CapacitiveValue": 70,
      "SCCM_WheelTouch_ResistiveValue": 60,
    }, True)

    assert msg[0] == 0x321
    assert msg[2] == 2

  def test_aol_configuration_is_still_mirrored_to_panda(self):
    params = self._car_params((0x1310,))
    toggles = SimpleNamespace(
      always_on_lateral=True,
      aol_brake_behavior=1,
      aol_startup_enabled=True,
      rivian_half_up_stalk_aol_toggle=True,
    )

    starpilot_params = CarInterface.get_starpilot_params(
      CAR.RIVIAN_R1_GEN1, {bus: {} for bus in range(8)}, [], params, toggles,
    )
    safety_param = starpilot_params.safetyConfigs[-1].safetyParam

    assert safety_param & RivianSafetyFlags.AOL_LATERAL
    assert safety_param & RivianSafetyFlags.AOL_BRAKE_REMAINS_ACTIVE
    assert safety_param & RivianSafetyFlags.AOL_STALK_TOGGLE
    assert safety_param & RivianSafetyFlags.AOL_START_ENABLED

  def test_disabled_aol_does_not_set_rivian_aol_safety_flags(self):
    params = self._car_params()
    toggles = SimpleNamespace(
      always_on_lateral=False,
      aol_brake_behavior=1,
      aol_startup_enabled=True,
      rivian_half_up_stalk_aol_toggle=True,
    )

    starpilot_params = CarInterface.get_starpilot_params(
      CAR.RIVIAN_R1_GEN1, {bus: {} for bus in range(8)}, [], params, toggles,
    )
    aol_flags = (
      RivianSafetyFlags.AOL_LATERAL |
      RivianSafetyFlags.AOL_BRAKE_REMAINS_ACTIVE |
      RivianSafetyFlags.AOL_STALK_TOGGLE |
      RivianSafetyFlags.AOL_START_ENABLED
    )

    assert not starpilot_params.safetyConfigs[-1].safetyParam & aol_flags

  def test_wheel_reaction_observer_changes_measured_torsion(self):
    controller = ExternalController(self._car_params((0x1310,)))
    state = SimpleNamespace(out=SimpleNamespace(steeringAngleDeg=0.0, steeringTorque=2.0))

    assert controller._update_driver_torque(state) == 2.0
    state.out.steeringAngleDeg = 20.0
    corrected = controller._update_driver_torque(state)

    assert math.isfinite(corrected)
    assert corrected != state.out.steeringTorque

  def test_torque_to_angle_handback_uses_iso_envelope(self, monkeypatch):
    controller = ExternalController(self._car_params((0x1310,)))
    controller.hands_on = False
    controller.torque_active = True
    controller.torque_active_frames = ext_controller.MIN_TORQUE_FRAMES
    controller.hands_off_frames = ext_controller.HANDS_OFF_EXIT_FRAMES
    controller.lat_active_last = True
    controller.rate_budget = SimpleNamespace(bounds=lambda *_: (-1000.0, 1000.0))
    monkeypatch.setattr(ext_controller, "get_max_angle_vm", lambda *args: 10.0)
    state = SimpleNamespace(
      out=SimpleNamespace(vEgoRaw=10.0, steeringAngleDeg=12.0, steeringRateDeg=0.0, steeringPressed=False),
      eac_status=1,
      eac_error_code=0,
    )

    controller._update_torque_active(state, True, 12.0)
    assert controller.torque_active

    state.out.steeringAngleDeg = 9.0
    controller._update_torque_active(state, True, 9.0)
    assert not controller.torque_active

  def test_live_toggle_prearms_torque_before_releasing_angle(self):
    controller = ExternalController(self._car_params((0x1310,)))
    controller.angle_active = True
    controller.force_torque = True
    state = SimpleNamespace(
      out=SimpleNamespace(vEgoRaw=10.0, steeringAngleDeg=0.0, steeringRateDeg=0.0, steeringPressed=False),
      eac_status=2,
      eac_error_code=0,
    )
    actuators = SimpleNamespace(torque=0.5)

    controller._update_torque_active(state, True, 0.0, actuators)

    assert controller.torque_prearm
    assert not controller.torque_active

    steer_max = round(float(ext_controller.np.interp(
      state.out.vEgoRaw,
      ext_controller.CCP.STEER_MAX_LOOKUP[0],
      ext_controller.CCP.STEER_MAX_LOOKUP[1],
    )))
    controller.apply_torque_last = round(actuators.torque * steer_max)
    controller._update_torque_active(state, True, 0.0, actuators)

    assert controller.torque_active
    assert not controller.torque_prearm
    assert controller.prearm_last_outcome == "reached"

  def test_toi_engagement_waits_for_epas_acknowledgement(self):
    controller = ToiController()

    assert controller.update(True, False, False, False, False) == (True, False)
    assert controller.state == ToiState.REARMING
    for _ in range(TOI_ACK_FRAMES):
      assert controller.update(True, False, False, True, False) == (True, False)

    assert controller.state == ToiState.TORQUE
    assert controller.update(True, False, False, True, False) == (True, True)

  def test_toi_fault_forces_torque_release(self):
    controller = ToiController()
    controller.state = ToiState.TORQUE

    assert controller.update(True, False, True, True, False) == (False, False)
    assert controller.state == ToiState.RELEASING

  def test_toi_delayed_acknowledgement_does_not_report_recovery_failure(self):
    controller = ToiController()

    for _ in range(31):
      assert controller.update(True, False, False, False, False) == (True, False)

    assert controller.state == ToiState.REARMING
    assert not controller.recovery_failed

    for _ in range(TOI_ACK_FRAMES):
      assert controller.update(True, False, False, True, False) == (True, False)

    assert controller.state == ToiState.TORQUE
    assert not controller.recovery_failed

  def test_toi_prearm_allows_torque_before_epas_acknowledgement(self):
    controller = ToiController()

    assert controller.update(True, False, False, False, False, prearming=True) == (True, True)
    assert controller.state == ToiState.PREARMING
    assert not controller.recovering

    assert controller.update(True, False, False, False, False) == (True, True)
    assert controller.state == ToiState.ACTIVATING

    for _ in range(TOI_ACK_FRAMES):
      assert controller.update(True, False, False, True, False) == (True, True)

    assert controller.state == ToiState.TORQUE
    assert not controller.recovery_failed

  def test_toi_prearm_resumes_after_high_angle_release(self):
    controller = ToiController()

    for _ in range(TOI_MAX_ANGLE_FRAMES):
      assert controller.update(True, True, False, False, False, prearming=True) == (True, True)

    assert controller.update(True, True, False, False, False, prearming=True) == (False, False)
    assert controller.state == ToiState.RELEASING

    for _ in range(TOI_ACK_FRAMES):
      assert controller.update(True, True, False, False, False, prearming=True) == (False, False)

    assert controller.state == ToiState.PREARMING
    assert controller.update(True, True, False, False, False, prearming=True) == (True, True)

  def test_toi_prearmed_activation_timeout_releases_request(self):
    controller = ToiController()

    assert controller.update(True, False, False, False, False, prearming=True) == (True, True)
    for _ in range(TOI_RECOVERY_TIMEOUT_FRAMES - 1):
      assert controller.update(True, False, False, False, False) == (True, True)

    assert controller.update(True, False, False, False, False) == (False, False)
    assert controller.state == ToiState.RELEASING
    assert controller.recovery_failed

  def test_toi_recovery_timeout_is_reported_and_request_stays_released(self):
    controller = ToiController()
    controller.state = ToiState.RELEASING

    for _ in range(TOI_RECOVERY_TIMEOUT_FRAMES):
      assert controller.update(True, False, True, False, False) == (False, False)

    assert controller.recovery_failed
    assert controller.state == ToiState.RELEASING
    assert not controller.preserve_torque

  def test_high_angle_toi_release_waits_for_epas_feedback(self):
    controller = ToiController()
    controller.state = ToiState.TORQUE

    for _ in range(TOI_MAX_ANGLE_FRAMES):
      assert controller.update(True, True, False, True, False) == (True, True)
    assert controller.update(True, True, False, True, False) == (False, False)
    assert controller.state == ToiState.RELEASING

    for _ in range(3):
      assert controller.update(True, True, False, True, False) == (False, False)
    for _ in range(TOI_ACK_FRAMES):
      assert controller.update(True, True, False, False, False) == (False, False)
    assert controller.state == ToiState.REARMING

  def test_base_harness_torque_waits_for_feedback_and_releases_on_fault(self):
    controller = ExternalController(self._car_params())
    controller.torque_active = True
    state = SimpleNamespace(
      out=SimpleNamespace(vEgoRaw=10.0, steeringTorque=0.0, steeringAngleDeg=0.0),
      toi_fault=False,
      toi_active=False,
      toi_unavailable=False,
    )
    actuators = SimpleNamespace(torque=0.2)

    controller._update_torque(state, actuators)
    assert controller.toi_act_cmd
    assert controller.torque_cmd == 0

    state.toi_active = True
    for _ in range(TOI_ACK_FRAMES):
      controller._update_torque(state, actuators)
    controller._update_torque(state, actuators)
    assert controller.torque_cmd != 0

    state.toi_fault = True
    controller._update_torque(state, actuators)
    assert not controller.toi_act_cmd
    assert controller.torque_cmd == 0
    assert controller.apply_torque_last == 0

  def test_high_angle_torque_leaves_rack_headroom(self):
    controller = ExternalController(self._car_params())
    controller.torque_active = True
    state = SimpleNamespace(
      out=SimpleNamespace(vEgoRaw=10.0, steeringTorque=0.0, steeringAngleDeg=0.0),
      toi_fault=False,
      toi_active=False,
      toi_unavailable=False,
    )
    actuators = SimpleNamespace(torque=1.0)

    controller._update_torque(state, actuators)
    state.toi_active = True
    for _ in range(TOI_ACK_FRAMES):
      controller._update_torque(state, actuators)

    steer_max = round(float(ext_controller.np.interp(
      state.out.vEgoRaw,
      ext_controller.CCP.STEER_MAX_LOOKUP[0],
      ext_controller.CCP.STEER_MAX_LOOKUP[1],
    )))
    controller.apply_torque_last = steer_max
    state.out.steeringAngleDeg = 100.0
    controller._update_torque(state, actuators)

    cap = int(round(steer_max * ext_controller.HIGH_ANGLE_CAP_FRAC))
    assert controller.torque_cmd == cap
    assert abs(controller.torque_cmd) < steer_max

  def test_high_angle_feedback_release_preserves_external_torque_limiter(self):
    controller = ExternalController(self._car_params())
    controller.torque_active = True
    controller.apply_torque_last = 100
    controller.torque_cmd = 100
    controller.toi_controller.state = ToiState.TORQUE
    controller.toi_controller.high_angle_frames = TOI_MAX_ANGLE_FRAMES
    state = SimpleNamespace(
      out=SimpleNamespace(vEgoRaw=10.0, steeringTorque=0.0, steeringAngleDeg=100.0),
      toi_fault=False,
      toi_active=True,
      toi_unavailable=False,
    )
    actuators = SimpleNamespace(torque=0.5)

    controller._update_torque(state, actuators)
    assert controller.torque_cmd == 0
    assert controller.apply_torque_last == 100

    state.toi_active = False
    for _ in range(TOI_ACK_FRAMES):
      controller._update_torque(state, actuators)
    controller._update_torque(state, actuators)

    assert controller.toi_act_cmd
    assert controller.torque_cmd == 0
    assert controller.apply_torque_last == 100

    state.toi_active = True
    for _ in range(TOI_ACK_FRAMES):
      controller._update_torque(state, actuators)
    controller._update_torque(state, actuators)

    assert controller.toi_act_cmd
    assert controller.torque_cmd != 0
    assert controller.apply_torque_last != 0

  def test_toi_fault_during_rearm_zeros_preserved_torque(self):
    controller = ExternalController(self._car_params())
    controller.torque_active = True
    controller.apply_torque_last = 100
    controller.torque_cmd = 100
    controller.toi_controller.state = ToiState.REARMING
    controller.toi_controller.preserve_torque = True
    state = SimpleNamespace(
      out=SimpleNamespace(vEgoRaw=10.0, steeringTorque=0.0, steeringAngleDeg=100.0),
      toi_fault=True,
      toi_active=False,
      toi_unavailable=False,
    )

    controller._update_torque(state, SimpleNamespace(torque=0.5))

    assert not controller.toi_act_cmd
    assert controller.torque_cmd == 0
    assert controller.apply_torque_last == 0

  def test_torque_harness_reports_toi_fault(self):
    permanent, temporary, disengage = get_steering_faults(False, True, False, 1, 0)

    assert not permanent
    assert temporary
    assert not disengage

  def test_angle_harness_ignores_toi_fault(self):
    permanent, temporary, disengage = get_steering_faults(True, True, False, 1, 0)

    assert not permanent
    assert not temporary
    assert not disengage

  def test_angle_harness_reports_active_eac_fault(self):
    permanent, temporary, disengage = get_steering_faults(True, False, False, 2, 12)

    assert not permanent
    assert temporary
    assert disengage

  def test_angle_harness_reports_persistent_toi_fault(self):
    permanent, temporary, disengage = get_steering_faults(True, True, True, 1, 0)

    assert not permanent
    assert temporary
    assert not disengage

  def test_driver_override_enters_torque_fallback(self):
    controller = ExternalController(self._car_params((0x1310,)))
    controller.hands_on = True
    controller.torque_active = False
    controller.lat_active_last = True
    state = SimpleNamespace(
      out=SimpleNamespace(vEgoRaw=10.0, steeringAngleDeg=15.0, steeringRateDeg=0.0, steeringPressed=True),
      eac_status=2,
      eac_error_code=0,
    )

    controller._update_torque_active(state, True, 15.0)

    assert controller.torque_active

  def test_angle_speed_control_uses_hysteresis_after_activation(self):
    controller = CarController.__new__(CarController)
    controller.angle_speed_active = False
    toggles = SimpleNamespace(
      rivian_angle_control=True,
      rivian_angle_speed_control=True,
      rivian_angle_minimum_speed=20.0 * CV.MPH_TO_MS,
    )

    assert not controller._update_angle_request(toggles, 19.9 * CV.MPH_TO_MS)
    assert controller._update_angle_request(toggles, 20.0 * CV.MPH_TO_MS)
    assert controller._update_angle_request(toggles, 19.5 * CV.MPH_TO_MS)
    assert not controller._update_angle_request(toggles, 18.9 * CV.MPH_TO_MS)

    toggles.rivian_angle_speed_control = False
    assert controller._update_angle_request(toggles, 0.0)
    assert not controller.angle_speed_active

  @staticmethod
  def _controller_mode(monkeypatch, *, angle_harness: bool, angle_control: bool, torque_active: bool,
                       gen2: bool = False, frame: int = 1, v_ego: float = 10.0,
                       angle_speed_control: bool = False, angle_minimum_speed: float = 0.0):
    angle_messages = []
    monkeypatch.setattr(rivian_carcontroller, "create_lka_steering", lambda *args: (0x120, b"", 0))
    monkeypatch.setattr(rivian_carcontroller, "create_angle_steering", lambda *args: angle_messages.append(args) or (0x110, b"", 0))
    monkeypatch.setattr(rivian_carcontroller, "create_acm_status", lambda *args: (0x100, b"", 0))

    controller = CarController.__new__(CarController)
    flags = RivianFlags.ANGLE_HARNESS if angle_harness else RivianFlags(0)
    if gen2:
      flags |= RivianFlags.GEN2
    controller.CP = SimpleNamespace(flags=flags, openpilotLongitudinalControl=False)
    controller.packer = None
    controller.frame = frame
    controller.cancel_frames = 0
    controller.apply_torque_last = 0
    controller.angle_harness = angle_harness
    controller.angle_speed_active = False
    controller.ext_controller = SimpleNamespace(
      force_torque=False,
      update=lambda *args: None,
      torque_cmd=80 if torque_active else 0,
      toi_act_cmd=torque_active,
      toi_controller=SimpleNamespace(recovering=False),
      apply_angle_last=12.0,
      angle_active=not torque_active,
      torque_active=torque_active,
      torque_prearm=False,
    )
    output = SimpleNamespace()
    control = SimpleNamespace(
      actuators=SimpleNamespace(accel=0.0, as_builder=lambda: output),
      latActive=True,
      longActive=False,
      enabled=True,
      cruiseControl=SimpleNamespace(cancel=False),
    )
    state = SimpleNamespace(
      out=SimpleNamespace(vEgo=v_ego, vEgoRaw=v_ego, gearShifter=structs.CarState.GearShifter.drive),
      acm_lka_hba_cmd={},
      sccm_wheel_touch={},
      vdm_adas_status=[],
    )
    toggles = SimpleNamespace(
      rivian_angle_control=angle_control,
      rivian_angle_speed_control=angle_speed_control,
      rivian_angle_minimum_speed=angle_minimum_speed,
    )

    result, _ = controller.update(control, state, 0, toggles)
    return controller, result, angle_messages

  def test_angle_speed_control_uses_torque_below_minimum_speed(self, monkeypatch):
    controller, _, _ = self._controller_mode(
      monkeypatch,
      angle_harness=True,
      angle_control=True,
      torque_active=False,
      v_ego=5.0,
      angle_speed_control=True,
      angle_minimum_speed=20.0 * CV.MPH_TO_MS,
    )

    assert controller.ext_controller.force_torque

  def test_angle_toggle_selects_controller_live(self, monkeypatch):
    angle_controller, _, _ = self._controller_mode(
      monkeypatch, angle_harness=True, angle_control=True, torque_active=False,
    )
    torque_controller, _, _ = self._controller_mode(
      monkeypatch, angle_harness=True, angle_control=False, torque_active=True,
    )

    assert not angle_controller.ext_controller.force_torque
    assert torque_controller.ext_controller.force_torque

  def test_base_harness_forces_torque_and_never_sends_angle_frames(self, monkeypatch):
    controller, output, angle_messages = self._controller_mode(
      monkeypatch, angle_harness=False, angle_control=True, torque_active=True,
    )

    assert controller.ext_controller.force_torque
    assert angle_messages == []
    assert output.lateralControlMode == structs.CarControl.Actuators.LateralControlMode.torque

  def test_gen2_does_not_transmit_missing_wheel_touch_message(self, monkeypatch):
    monkeypatch.setattr(
      rivian_carcontroller,
      "create_wheel_touch",
      lambda *args: (_ for _ in ()).throw(AssertionError("Gen 2 has no SCCM wheel-touch message")),
    )

    self._controller_mode(
      monkeypatch, angle_harness=False, angle_control=False, torque_active=True, gen2=True, frame=0,
    )

  def test_gen1_continues_transmitting_wheel_touch_message(self, monkeypatch):
    calls = []
    monkeypatch.setattr(rivian_carcontroller, "create_wheel_touch", lambda *args: calls.append(args))

    self._controller_mode(
      monkeypatch, angle_harness=False, angle_control=False, torque_active=True, frame=0,
    )

    assert len(calls) == 1

  def test_openpilot_long_forwards_vdm_and_clears_stock_driver_mode(self, monkeypatch):
    calls = []
    monkeypatch.setattr(rivian_carcontroller, "create_lka_steering", lambda *args: (0x120, b"", 0))
    monkeypatch.setattr(rivian_carcontroller, "create_angle_steering", lambda *args: (0x110, b"", 0))
    monkeypatch.setattr(rivian_carcontroller, "create_acm_status", lambda *args: (0x100, b"", 0))
    monkeypatch.setattr(rivian_carcontroller, "create_longitudinal", lambda *args: (0x160, b"", 0))
    monkeypatch.setattr(rivian_carcontroller, "create_adas_status", lambda *args: calls.append(args) or (0x162, b"", 2))

    controller = CarController.__new__(CarController)
    controller.CP = SimpleNamespace(flags=RivianFlags(0), openpilotLongitudinalControl=True)
    controller.packer = None
    controller.frame = 1
    controller.cancel_frames = 0
    controller.apply_torque_last = 0
    controller.angle_harness = False
    controller.angle_speed_active = False
    controller.ext_controller = SimpleNamespace(
      update=lambda *args: None,
      torque_cmd=0,
      toi_act_cmd=False,
      toi_controller=SimpleNamespace(recovering=False),
      apply_angle_last=1.0,
      angle_active=True,
      torque_active=False,
      torque_prearm=False,
    )
    output = SimpleNamespace()
    control = SimpleNamespace(
      actuators=SimpleNamespace(accel=0.5, as_builder=lambda: output),
      latActive=True,
      longActive=True,
      enabled=True,
      cruiseControl=SimpleNamespace(cancel=False),
    )
    state = SimpleNamespace(
      out=SimpleNamespace(vEgo=10.0, vEgoRaw=10.0, gasPressed=False, gearShifter=structs.CarState.GearShifter.drive),
      acm_lka_hba_cmd={},
      vdm_adas_status=[{"VDM_AdasDriverModeStatus": 2}],
    )

    controller.update(control, state, 0, SimpleNamespace())

    assert len(calls) == 1
    assert calls[0][2:] == (None, 0)

  @staticmethod
  def _longitudinal_ret(enabled=False, speed_mph=30.0):
    return SimpleNamespace(
      cruiseState=SimpleNamespace(enabled=enabled, speed=0.0),
      vEgoCluster=speed_mph * CV.MPH_TO_MS,
      leftBlindspot=False,
      rightBlindspot=False,
    )

  @staticmethod
  def _longitudinal_parsers(*, stalk=0, scroll=255):
    return {
      Bus.alt: SimpleNamespace(vl={
        "WheelButtons_Fwd": {
          "RightButton_Scroll": scroll,
          "RightButton_ScrollClick": 0,
          "RightButton_RightClick": 0,
          "RightButton_LeftClick": 0,
        },
        "BSM_BlindSpotIndicator_Fwd": {
          "BSM_BlindSpotIndicator_Left": 0,
          "BSM_BlindSpotIndicator_Right": 0,
        },
      }),
      Bus.adas: SimpleNamespace(vl={"Cluster": {"Cluster_Unit": 1}}),
      Bus.pt: SimpleNamespace(vl={"VDM_AdasSts": {"VDM_UserAdasRequest": stalk}}),
    }

  def test_stalk_down_sets_speed_immediately(self):
    state = RivianLongitudinalState(SimpleNamespace(openpilotLongitudinalControl=True))
    state.set_speed = 30 * CV.MPH_TO_MS
    ret = self._longitudinal_ret(enabled=True, speed_mph=45)

    state.update_longitudinal_upgrade(ret, self._longitudinal_parsers(stalk=3))

    assert state.set_speed == 45 * CV.MPH_TO_MS

  def test_scroll_rotation_emits_one_personality_event_per_detent(self):
    state = RivianLongitudinalState(SimpleNamespace(openpilotLongitudinalControl=True))
    ret = self._longitudinal_ret()

    assert state.update_longitudinal_upgrade(ret, self._longitudinal_parsers(scroll=0)) == []
    events = state.update_longitudinal_upgrade(ret, self._longitudinal_parsers(scroll=1))
    assert [(event.type, event.pressed) for event in events] == [(structs.CarState.ButtonEvent.Type.gapAdjustCruise, False)]
    assert state.update_longitudinal_upgrade(ret, self._longitudinal_parsers(scroll=1)) == []
    assert state.update_longitudinal_upgrade(ret, self._longitudinal_parsers(scroll=255)) == []
    events = state.update_longitudinal_upgrade(ret, self._longitudinal_parsers(scroll=2))
    assert [(event.type, event.pressed) for event in events] == [(structs.CarState.ButtonEvent.Type.gapAdjustCruise, False)]

  def test_scroll_click_emits_held_distance_button_edges(self):
    state = RivianLongitudinalState(SimpleNamespace(openpilotLongitudinalControl=True))
    ret = self._longitudinal_ret(enabled=True)
    parsers = self._longitudinal_parsers()

    assert state.update_longitudinal_upgrade(ret, parsers) == []
    parsers[Bus.alt].vl["WheelButtons_Fwd"]["RightButton_ScrollClick"] = 2
    events = state.update_longitudinal_upgrade(ret, parsers)
    assert [(event.type, event.pressed) for event in events] == [(structs.CarState.ButtonEvent.Type.gapAdjustCruise, True)]
    assert state.update_longitudinal_upgrade(ret, parsers) == []
    parsers[Bus.alt].vl["WheelButtons_Fwd"]["RightButton_ScrollClick"] = 0
    events = state.update_longitudinal_upgrade(ret, parsers)
    assert [(event.type, event.pressed) for event in events] == [(structs.CarState.ButtonEvent.Type.gapAdjustCruise, False)]

  @staticmethod
  def _stalk_parsers(request):
    return {Bus.pt: SimpleNamespace(vl={"VDM_AdasSts": {"VDM_UserAdasRequest": request}})}

  def test_aol_half_up_behavior_is_retained(self):
    state = RivianLongitudinalState(SimpleNamespace(flags=0, openpilotLongitudinalControl=False))
    ret = SimpleNamespace(cruiseState=SimpleNamespace(enabled=False))

    assert state.update_stalk_controls(ret, self._stalk_parsers(1), True) == []
    events = state.update_stalk_controls(ret, self._stalk_parsers(0), True)
    assert [(event.type, event.pressed) for event in events] == [(structs.CarState.ButtonEvent.Type.lkas, True)]

    state = RivianLongitudinalState(SimpleNamespace(flags=0, openpilotLongitudinalControl=False))
    assert state.update_stalk_controls(ret, self._stalk_parsers(1), True) == []
    events = state.update_stalk_controls(ret, self._stalk_parsers(2), True)
    assert [(event.type, event.pressed) for event in events] == [(structs.CarState.ButtonEvent.Type.altButton2, True)]

  def test_aol_half_up_used_to_cancel_acc_is_suppressed(self):
    state = RivianLongitudinalState(SimpleNamespace(flags=0, openpilotLongitudinalControl=False))
    ret = SimpleNamespace(cruiseState=SimpleNamespace(enabled=True))

    assert state.update_stalk_controls(ret, self._stalk_parsers(1), True) == []
    ret.cruiseState.enabled = False
    assert state.update_stalk_controls(ret, self._stalk_parsers(0), True) == []

  def test_custom_fuzzy_fingerprinting(self, subtests):
    for platform in CAR:
      with subtests.test(platform=platform.name):
        for wmi in WMI:
          for line in ModelLine:
            for year in ModelYear:
              bad = wmi not in platform.config.wmis or line not in platform.config.lines or year not in platform.config.years
              vin = list("0" * 17)
              vin[:3] = wmi
              vin[3] = line
              vin[9] = year
              matches = FW_QUERY_CONFIG.match_fw_to_car_fuzzy({}, "".join(vin), FW_VERSIONS)
              assert (matches == {platform}) == (not bad)
