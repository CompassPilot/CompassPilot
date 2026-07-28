from types import SimpleNamespace

from opendbc.car import Bus, structs
from opendbc.car.common.conversions import Conversions as CV
from opendbc.car.rivian import carcontroller as rivian_carcontroller
from opendbc.car.rivian import ext_controller
from opendbc.car.rivian.carcontroller import CarController, get_longitudinal_accel
from opendbc.car.rivian.carstate_ext import RivianLongitudinalState
from opendbc.car.rivian.ext_controller import ExternalController
from opendbc.car.rivian.faults import get_steering_faults
from opendbc.car.rivian.fingerprints import FW_VERSIONS
from opendbc.car.rivian.interface import CarInterface
from opendbc.car.rivian.values import CAR, FW_QUERY_CONFIG, WMI, ModelLine, ModelYear, RivianFlags, RivianSafetyFlags


class TestRivian:
  @staticmethod
  def _car_params(bus_one_messages=(), alpha_long=False):
    fingerprint = {bus: {} for bus in range(8)}
    fingerprint[1] = {address: 8 for address in bus_one_messages}
    return CarInterface.get_params(CAR.RIVIAN_R1_GEN1, fingerprint, [], alpha_long, False, False, SimpleNamespace())

  def test_missing_extreme_harness_is_dashcam_only(self):
    params = self._car_params()

    assert params.dashcamOnly
    assert not params.flags & RivianFlags.ANGLE_HARNESS
    assert not params.safetyConfigs[0].safetyParam & RivianSafetyFlags.ANGLE_CONTROL

  def test_longitudinal_harness_without_extreme_harness_is_dashcam_only(self):
    params = self._car_params((0x131A,), alpha_long=True)

    assert params.dashcamOnly
    assert params.flags & RivianFlags.LONGITUDINAL_HARNESS
    assert not params.flags & RivianFlags.ANGLE_HARNESS

  def test_extreme_harness_enables_angle_control(self):
    params = self._car_params((0x1310,))

    assert not params.dashcamOnly
    assert params.flags & RivianFlags.ANGLE_HARNESS
    assert params.safetyConfigs[0].safetyParam & RivianSafetyFlags.ANGLE_CONTROL

  def test_extreme_and_longitudinal_harnesses_enable_both_paths(self):
    params = self._car_params((0x1310, 0x131A), alpha_long=True)

    assert not params.dashcamOnly
    assert params.flags & RivianFlags.ANGLE_HARNESS
    assert params.flags & RivianFlags.LONGITUDINAL_HARNESS
    assert params.safetyConfigs[0].safetyParam & RivianSafetyFlags.ANGLE_CONTROL
    assert params.safetyConfigs[0].safetyParam & RivianSafetyFlags.LONG_CONTROL
    assert params.openpilotLongitudinalControl

  def test_gas_pedal_zeroes_stale_longitudinal_acceleration(self):
    assert get_longitudinal_accel(0.07, gas_pressed=True) == 0.0
    assert get_longitudinal_accel(-2.44, gas_pressed=True) == 0.0
    assert get_longitudinal_accel(0.07, gas_pressed=False) == 0.07

  def test_live_params_update_rx_dev_command_model(self):
    updates = []
    controller = CarController.__new__(CarController)
    controller.ext_controller = SimpleNamespace(
      roll=0.0,
      angle_offset_deg=0.0,
      VM=SimpleNamespace(update_params=lambda stiffness, ratio: updates.append((stiffness, ratio))),
    )

    controller.update_live_params(0.05, 1.25, 0.8, 16.0)

    assert controller.ext_controller.roll == 0.05
    assert controller.ext_controller.angle_offset_deg == 1.25
    assert updates == [(0.8, 16.0)]

  @staticmethod
  def _controller_actuators(monkeypatch, *, angle_harness, torque_active, requested_torque, applied_torque):
    monkeypatch.setattr(rivian_carcontroller, "create_lka_steering", lambda *args: None)
    monkeypatch.setattr(rivian_carcontroller, "create_angle_steering", lambda *args: None)
    monkeypatch.setattr(rivian_carcontroller, "create_acm_status", lambda *args: None)
    monkeypatch.setattr(rivian_carcontroller, "apply_driver_steer_torque_limits", lambda *args: applied_torque)
    monkeypatch.setattr(rivian_carcontroller, "common_fault_avoidance", lambda *args: (0, True))

    controller = CarController.__new__(CarController)
    controller.CP = SimpleNamespace(openpilotLongitudinalControl=False)
    controller.packer = None
    controller.frame = 1
    controller.apply_torque_last = 0
    controller.cancel_frames = 0
    controller.toi_angle_limit_counter = 0
    controller.angle_harness = angle_harness
    controller.ext_controller = None
    if angle_harness:
      controller.ext_controller = SimpleNamespace(
        update=lambda *args: None,
        apply_torque_last=applied_torque,
        toi_act_cmd=True,
        apply_angle_last=12.0,
        angle_active=not torque_active,
        torque_active=torque_active,
      )

    output = SimpleNamespace()
    actuators = SimpleNamespace(torque=requested_torque, accel=0.0, as_builder=lambda: output)
    car_control = SimpleNamespace(
      actuators=actuators,
      latActive=True,
      enabled=True,
      cruiseControl=SimpleNamespace(cancel=False),
    )
    car_state = SimpleNamespace(
      out=SimpleNamespace(
        gearShifter=structs.CarState.GearShifter.drive,
        vEgoRaw=10.0,
        steeringTorque=0.0,
        steeringAngleDeg=0.0,
      ),
      acm_lka_hba_cmd={},
      vdm_adas_status=(),
    )

    return controller.update(car_control, car_state, 0, SimpleNamespace())[0]

  def test_angle_channel_echoes_requested_torque(self, monkeypatch):
    output = self._controller_actuators(
      monkeypatch,
      angle_harness=True,
      torque_active=False,
      requested_torque=0.42,
      applied_torque=0,
    )

    assert output.torque == 0.42
    assert output.torqueOutputCan == 0

  def test_torque_fallback_reports_applied_can_torque(self, monkeypatch):
    output = self._controller_actuators(
      monkeypatch,
      angle_harness=True,
      torque_active=True,
      requested_torque=0.42,
      applied_torque=100,
    )
    steer_max = round(float(rivian_carcontroller.np.interp(
      10.0,
      rivian_carcontroller.CarControllerParams.STEER_MAX_LOOKUP[0],
      rivian_carcontroller.CarControllerParams.STEER_MAX_LOOKUP[1],
    )))

    assert output.torque == 100 / steer_max
    assert output.torqueOutputCan == 100

  def test_torque_harness_reporting_is_unchanged(self, monkeypatch):
    output = self._controller_actuators(
      monkeypatch,
      angle_harness=False,
      torque_active=False,
      requested_torque=0.42,
      applied_torque=80,
    )
    steer_max = round(float(rivian_carcontroller.np.interp(
      10.0,
      rivian_carcontroller.CarControllerParams.STEER_MAX_LOOKUP[0],
      rivian_carcontroller.CarControllerParams.STEER_MAX_LOOKUP[1],
    )))

    assert output.torque == 80 / steer_max
    assert output.torqueOutputCan == 80

  def test_software_cruise_speed_request_is_clamped_to_rivian_bounds(self):
    state = RivianLongitudinalState(SimpleNamespace(openpilotLongitudinalControl=True))

    assert state.set_cruise_speed(45 * CV.MPH_TO_MS) == 45 * CV.MPH_TO_MS
    assert state.set_cruise_speed(10 * CV.MPH_TO_MS) == 20 * CV.MPH_TO_MS
    assert state.set_cruise_speed(100 * CV.MPH_TO_MS) == 85 * CV.MPH_TO_MS

  @staticmethod
  def _longitudinal_parsers(scroll=0, scroll_click=0):
    return {
      Bus.alt: SimpleNamespace(vl={
        "WheelButtons_Fwd": {
          "RightButton_Scroll": scroll,
          "RightButton_ScrollClick": scroll_click,
          "RightButton_RightClick": 0,
          "RightButton_LeftClick": 0,
        },
        "BSM_BlindSpotIndicator_Fwd": {
          "BSM_BlindSpotIndicator_Left": 0,
          "BSM_BlindSpotIndicator_Right": 0,
        },
      }),
      Bus.adas: SimpleNamespace(vl={"Cluster": {"Cluster_Unit": 1}}),
      Bus.pt: SimpleNamespace(vl={"VDM_AdasSts": {"VDM_UserAdasRequest": 0}}),
    }

  @staticmethod
  def _longitudinal_ret():
    return SimpleNamespace(
      buttonEvents=[],
      cruiseState=SimpleNamespace(enabled=True, speed=0.0),
      vEgoCluster=10.0,
      leftBlindspot=False,
      rightBlindspot=False,
    )

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
    ret = self._longitudinal_ret()

    assert state.update_longitudinal_upgrade(ret, self._longitudinal_parsers()) == []
    events = state.update_longitudinal_upgrade(ret, self._longitudinal_parsers(scroll_click=2))
    assert [(event.type, event.pressed) for event in events] == [(structs.CarState.ButtonEvent.Type.gapAdjustCruise, True)]
    assert state.update_longitudinal_upgrade(ret, self._longitudinal_parsers(scroll_click=2)) == []
    events = state.update_longitudinal_upgrade(ret, self._longitudinal_parsers(scroll_click=0))
    assert [(event.type, event.pressed) for event in events] == [(structs.CarState.ButtonEvent.Type.gapAdjustCruise, False)]

  def test_scroll_controls_are_ignored_without_openpilot_longitudinal(self):
    state = RivianLongitudinalState(SimpleNamespace(openpilotLongitudinalControl=False))
    events = state.update_longitudinal_upgrade(
      self._longitudinal_ret(),
      self._longitudinal_parsers(scroll=1, scroll_click=2),
    )
    assert events == []

  @staticmethod
  def _stalk_parsers(request):
    return {Bus.pt: SimpleNamespace(vl={"VDM_AdasSts": {"VDM_UserAdasRequest": request}})}

  def test_mads_half_up_is_deferred_and_full_up_does_not_toggle(self):
    state = RivianLongitudinalState(SimpleNamespace(flags=0, openpilotLongitudinalControl=False))
    ret = SimpleNamespace(cruiseState=SimpleNamespace(enabled=False))

    assert state.update_stalk_controls(ret, self._stalk_parsers(1), True) == []
    events = state.update_stalk_controls(ret, self._stalk_parsers(0), True)
    assert [(event.type, event.pressed) for event in events] == [(structs.CarState.ButtonEvent.Type.lkas, True)]

    state = RivianLongitudinalState(SimpleNamespace(flags=0, openpilotLongitudinalControl=False))
    assert state.update_stalk_controls(ret, self._stalk_parsers(1), True) == []
    events = state.update_stalk_controls(ret, self._stalk_parsers(2), True)
    assert [(event.type, event.pressed) for event in events] == [(structs.CarState.ButtonEvent.Type.altButton2, True)]

  def test_mads_half_up_used_to_cancel_acc_is_suppressed(self):
    state = RivianLongitudinalState(SimpleNamespace(flags=0, openpilotLongitudinalControl=False))
    ret = SimpleNamespace(cruiseState=SimpleNamespace(enabled=True))

    assert state.update_stalk_controls(ret, self._stalk_parsers(1), True) == []
    ret.cruiseState.enabled = False
    assert state.update_stalk_controls(ret, self._stalk_parsers(0), True) == []

  def test_angle_harness_ignores_toi_fault(self):
    permanent, temporary, disengage = get_steering_faults(True, True, 1, 0)

    assert not permanent
    assert not temporary
    assert not disengage

  def test_angle_harness_reports_active_eac_fault(self):
    permanent, temporary, disengage = get_steering_faults(True, False, 2, 12)

    assert not permanent
    assert temporary
    assert disengage

  def test_torque_harness_reports_toi_fault(self):
    permanent, temporary, disengage = get_steering_faults(False, True, 1, 0)

    assert not permanent
    assert temporary
    assert not disengage

  def test_custom_fuzzy_fingerprinting(self, subtests):
    for platform in CAR:
      with subtests.test(platform=platform.name):
        for wmi in WMI:
          for line in ModelLine:
            for year in ModelYear:
              for bad in (True, False):
                vin = ["0"] * 17
                vin[:3] = wmi
                vin[3] = line.value
                vin[9] = year.value
                if bad:
                  vin[3] = "Z"
                vin = "".join(vin)

                matches = FW_QUERY_CONFIG.match_fw_to_car_fuzzy({}, vin, FW_VERSIONS)
                should_match = year != ModelYear.S_2025 and not bad
                assert (matches == {platform}) == should_match, "Bad match"

  def test_high_angle_torque_blip_resets_limiter_and_ramps_from_zero(self, monkeypatch):
    controller = ExternalController.__new__(ExternalController)
    controller.torque_active = True
    controller.apply_torque_last = 0
    controller.toi_angle_limit_counter = 89
    controller.toi_act_cmd = True

    car_state = SimpleNamespace(out=SimpleNamespace(vEgoRaw=10.0, steeringTorque=0.0, steeringAngleDeg=100.0))
    actuators = SimpleNamespace(torque=1.0)
    toi_states = iter(((90, False), (0, True)))
    monkeypatch.setattr(ext_controller, "common_fault_avoidance", lambda *args: next(toi_states))

    controller._update_torque(car_state, actuators)

    assert controller.apply_torque_last == 0
    assert not controller.toi_act_cmd

    controller._update_torque(car_state, actuators)

    assert controller.apply_torque_last == 3
    assert controller.toi_act_cmd

  @staticmethod
  def _handoff_controller(torque_active=False, lat_active_last=True):
    controller = ExternalController.__new__(ExternalController)
    controller.hands_on = False
    controller.torque_active = torque_active
    controller.torque_active_frames = ext_controller.MIN_TORQUE_FRAMES
    controller.lat_active_last = lat_active_last
    controller.eac_dead_frames = 0
    controller.eac_rearm_release_frames = 0
    controller.eac_rearm_attempted = False
    controller.rate_budget = SimpleNamespace(bounds=lambda *_: (-1000.0, 1000.0))
    return controller

  @staticmethod
  def _handoff_car_state(*, speed=10.0, angle=0.0, rate=0.0, torque=0.0, pressed=False,
                         eac_status=1, eac_error_code=0, temporary_fault=False, permanent_fault=False):
    return SimpleNamespace(
      out=SimpleNamespace(
        vEgoRaw=speed,
        steeringAngleDeg=angle,
        steeringRateDeg=rate,
        steeringTorque=torque,
        steeringPressed=pressed,
        steerFaultTemporary=temporary_fault,
        steerFaultPermanent=permanent_fault,
      ),
      eac_status=eac_status,
      eac_error_code=eac_error_code,
    )

  def test_rx_dev_status_available_hands_off_hands_back_without_extra_delay(self):
    controller = self._handoff_controller(torque_active=True)
    car_state = self._handoff_car_state()

    controller._update_torque_active(car_state, True, 0.0)

    assert not controller.torque_active

  def test_route_opposing_reaction_torque_does_not_force_fallback_without_hands_on(self):
    controller = self._handoff_controller()
    # Route-derived signature from the first incident. rx-dev-src requires its
    # filtered hands-on signal in addition to steeringPressed.
    car_state = self._handoff_car_state(speed=6.85, angle=130.5, torque=-1.64, pressed=True)

    controller._update_torque_active(car_state, True, 135.7)

    assert not controller.torque_active

  def test_confirmed_driver_override_enters_torque_fallback(self):
    controller = self._handoff_controller()
    controller.hands_on = True
    car_state = self._handoff_car_state(torque=2.35, pressed=True)

    controller._update_torque_active(car_state, True, 15.0)

    assert controller.torque_active

  def test_fresh_low_speed_engagement_starts_in_angle_when_epas_available(self):
    controller = self._handoff_controller(lat_active_last=False)
    car_state = self._handoff_car_state(speed=0.0)

    controller._update_torque_active(car_state, True, -25.4)

    assert not controller.torque_active

  def test_fresh_engagement_starts_in_torque_when_epas_not_available(self):
    controller = self._handoff_controller(lat_active_last=False)
    car_state = self._handoff_car_state(eac_status=0)

    controller._update_torque_active(car_state, True, -25.4)

    assert controller.torque_active

  def test_inhibited_no_error_rearms_once_after_continuous_release(self):
    controller = self._handoff_controller(torque_active=True)
    car_state = self._handoff_car_state(eac_status=0)

    for _ in range(ext_controller.EAC_REARM_RELEASE_FRAMES - 1):
      controller._update_torque_active(car_state, True, 0.0)
      assert controller.torque_active

    controller._update_torque_active(car_state, True, 0.0)

    assert not controller.torque_active
    assert controller.eac_rearm_attempted
    assert controller.eac_dead_frames == 1

  def test_inhibited_rearm_release_window_resets_on_driver_input(self):
    controller = self._handoff_controller(torque_active=True)
    car_state = self._handoff_car_state(eac_status=0)

    for _ in range(ext_controller.EAC_REARM_RELEASE_FRAMES - 1):
      controller._update_torque_active(car_state, True, 0.0)

    car_state.out.steeringPressed = True
    controller._update_torque_active(car_state, True, 0.0)
    assert controller.eac_rearm_release_frames == 0
    assert controller.torque_active

    car_state.out.steeringPressed = False
    controller._update_torque_active(car_state, True, 0.0)
    assert controller.eac_rearm_release_frames == 1
    assert controller.torque_active

  def test_failed_inhibited_rearm_falls_back_without_repeated_probes(self):
    controller = self._handoff_controller(torque_active=True)
    car_state = self._handoff_car_state(eac_status=0)

    for _ in range(ext_controller.EAC_REARM_RELEASE_FRAMES):
      controller._update_torque_active(car_state, True, 0.0)
    assert not controller.torque_active

    for _ in range(ext_controller.EAC_RECOVER_FRAMES - 1):
      controller._update_torque_active(car_state, True, 0.0)
      assert not controller.torque_active
    controller._update_torque_active(car_state, True, 0.0)
    assert controller.torque_active

    for _ in range(ext_controller.MIN_TORQUE_FRAMES + ext_controller.EAC_REARM_RELEASE_FRAMES):
      controller._update_torque_active(car_state, True, 0.0)
    assert controller.torque_active
    assert controller.eac_rearm_attempted

  def test_successful_inhibited_rearm_stays_in_angle(self):
    controller = self._handoff_controller(torque_active=True)
    car_state = self._handoff_car_state(eac_status=0)

    for _ in range(ext_controller.EAC_REARM_RELEASE_FRAMES):
      controller._update_torque_active(car_state, True, 0.0)
    assert not controller.torque_active

    car_state.eac_status = 2
    controller._update_torque_active(car_state, True, 0.0)

    assert not controller.torque_active
    assert not controller.eac_rearm_attempted
    assert controller.eac_dead_frames == 0

  def test_inhibited_rearm_rejects_errors_and_faults(self):
    for state in (
      self._handoff_car_state(eac_status=0, eac_error_code=1),
      self._handoff_car_state(eac_status=3),
      self._handoff_car_state(eac_status=0, temporary_fault=True),
      self._handoff_car_state(eac_status=0, permanent_fault=True),
    ):
      controller = self._handoff_controller(torque_active=True)
      for _ in range(ext_controller.MIN_TORQUE_FRAMES + ext_controller.EAC_REARM_RELEASE_FRAMES):
        controller._update_torque_active(state, True, 0.0)
      assert controller.torque_active
      assert not controller.eac_rearm_attempted

  def test_inhibited_rearm_requires_settled_wheel_near_command(self):
    unsafe_states = (
      (self._handoff_car_state(eac_status=0, angle=100.0), 0.0),
      (self._handoff_car_state(eac_status=0, rate=ext_controller.UNWIND_HANDOFF_RATE), 0.0),
      (self._handoff_car_state(eac_status=0, angle=20.0), 0.0),
    )
    for state, desired_angle in unsafe_states:
      controller = self._handoff_controller(torque_active=True)
      for _ in range(ext_controller.MIN_TORQUE_FRAMES + ext_controller.EAC_REARM_RELEASE_FRAMES):
        controller._update_torque_active(state, True, desired_angle)
      assert controller.torque_active
      assert not controller.eac_rearm_attempted

  def test_inhibited_rearm_budget_resets_after_disengagement(self):
    controller = self._handoff_controller(torque_active=True)
    car_state = self._handoff_car_state(eac_status=0)

    for _ in range(ext_controller.EAC_REARM_RELEASE_FRAMES):
      controller._update_torque_active(car_state, True, 0.0)
    assert controller.eac_rearm_attempted

    controller._update_torque_active(car_state, False, 0.0)

    assert not controller.torque_active
    assert not controller.eac_rearm_attempted
