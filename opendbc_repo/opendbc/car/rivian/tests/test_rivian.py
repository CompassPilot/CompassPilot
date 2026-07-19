from types import SimpleNamespace

from opendbc.car import Bus, structs
from opendbc.car.rivian.carcontroller import get_longitudinal_accel
from opendbc.car.rivian.carstate_ext import RivianLongitudinalState
from opendbc.car.rivian.fingerprints import FW_VERSIONS
from opendbc.car.rivian.interface import CarInterface
from opendbc.car.rivian.values import CAR, FW_QUERY_CONFIG, WMI, ModelLine, ModelYear, RivianFlags, RivianSafetyFlags


class TestRivian:
  @staticmethod
  def _car_params(bus_one_messages=(), alpha_long=False):
    fingerprint = {bus: {} for bus in range(8)}
    fingerprint[1] = {address: 8 for address in bus_one_messages}
    return CarInterface.get_params(CAR.RIVIAN_R1_GEN1, fingerprint, [], alpha_long, False, False, SimpleNamespace())

  def test_extreme_harness_fingerprint_does_not_enable_angle_control(self):
    params = self._car_params((0x1310,))

    assert params.steerControlType == structs.CarParams.SteerControlType.torque
    assert params.safetyConfigs[0].safetyParam & 2 == 0
    assert not params.dashcamOnly

  def test_longitudinal_harness_fingerprint_enables_rivian_longitudinal(self):
    params = self._car_params((0x131A,), alpha_long=True)

    assert params.flags & RivianFlags.LONGITUDINAL_HARNESS
    assert params.safetyConfigs[0].safetyParam & RivianSafetyFlags.LONG_CONTROL
    assert params.alphaLongitudinalAvailable
    assert params.openpilotLongitudinalControl
    assert not params.radarUnavailable

  def test_gas_pedal_zeroes_stale_longitudinal_acceleration(self):
    assert get_longitudinal_accel(0.07, gas_pressed=True) == 0.0
    assert get_longitudinal_accel(-2.44, gas_pressed=True) == 0.0
    assert get_longitudinal_accel(0.07, gas_pressed=False) == 0.07

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
