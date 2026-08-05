#!/usr/bin/env python3
from opendbc.car import structs
from opendbc.car.chrysler.values import pacifica_hybrid_aol_requires_set_press
from opendbc.car.hyundai.values import CAR as HYUNDAI_CAR, HyundaiFlags
from opendbc.safety import ALTERNATIVE_EXPERIENCE
from openpilot.common.params import Params
from openpilot.selfdrive.car.cruise import CRUISE_LONG_PRESS, ButtonType
from openpilot.selfdrive.selfdrived.events import ET

from openpilot.starpilot.common.experimental_state import (
  CCStatus,
  CEStatus,
  next_manual_cc_status,
  next_manual_ce_status,
  sync_manual_cc_state,
  sync_manual_ce_state,
)
from openpilot.starpilot.common.favorite_slots import FAVORITE_ACTION_AOL_COUNTER, FAVORITE_ACTION_TRAFFIC_MODE_COUNTER, toggle_favorite_slot
from openpilot.starpilot.common.starpilot_variables import ERROR_LOGS_PATH, GearShifter, NON_DRIVING_GEARS

HYUNDAI_MAIN_CRUISE_AOL_CONFIRM_TIMEOUT_FRAMES = 100


class StarPilotCard:
  @staticmethod
  def _button_type_raw(button_event) -> int:
    button_type = getattr(button_event, "type", button_event)
    return int(getattr(button_type, "raw", button_type))

  def __init__(self, CP, FPCP):
    self.CP = CP

    self.params = Params(return_defaults=True)
    self.params_memory = Params(memory=True)

    self.accel_pressed = False
    self.always_on_lateral_allowed = False
    self.aol_active_last = None
    self.aol_driving_seen = False
    self.aol_startup_initialized = False
    self.aol_startup_pending = False
    self.aol_toggle_counter = self.params_memory.get_int(FAVORITE_ACTION_AOL_COUNTER)
    hyundai_flags = getattr(self.CP, "flags", 0)
    kia_forte_non_scc = (
      getattr(self.CP, "carFingerprint", None) in (HYUNDAI_CAR.KIA_FORTE_2019_NON_SCC, HYUNDAI_CAR.KIA_FORTE_2021_NON_SCC) and
      bool(hyundai_flags & HyundaiFlags.NON_SCC)
    )
    hyundai_aol_before_engagement = kia_forte_non_scc or getattr(self.CP, "carFingerprint", None) == HYUNDAI_CAR.GENESIS_G90
    self.hyundai_preserve_aol_across_reverse = getattr(self.CP, "carFingerprint", None) == HYUNDAI_CAR.HYUNDAI_SONATA_HYBRID
    self.hyundai_aol_needs_engagement = (
      self.CP.brand == "hyundai" and not (hyundai_flags & HyundaiFlags.CANFD) and not hyundai_aol_before_engagement
    )
    self.hyundai_aol_ready = False
    self.g70_main_cruise_aol_pending = False
    self.g70_main_cruise_aol_pending_frames = 0
    self.prev_cruise_available = None
    self.prev_active = False
    self.prev_cruise_enabled = False
    self.decel_pressed = False
    self.cancelPressed_previously = False
    self.cancel_pulse_glide_suppressed = False
    self.distancePressed_previously = False
    self.force_coast = False
    self.pulse_and_glide = False
    self.modePressed_previously = False
    self.mode_counter = 0
    self.customPressed_previously = False
    self.custom_counter = 0
    self.pause_lateral = False
    self.pause_longitudinal = False
    self.switchback_mode_enabled = self.params_memory.get_bool("SwitchbackModeEnabled")
    self.traffic_mode_enabled = False
    self._favorite_traffic_mode_counter = self.params_memory.get_int(FAVORITE_ACTION_TRAFFIC_MODE_COUNTER)
    self._rivian_acc_enabled = False

    self.gap_counter = 0
    self.cancel_counter = 0
    self._distance_poll_counter = 0
    self._onroad_distance_pressed = False

    self.always_on_lateral_set = bool(FPCP.alternativeExperience & ALTERNATIVE_EXPERIENCE.ALWAYS_ON_LATERAL)
    self.long_press_threshold = CRUISE_LONG_PRESS
    self.very_long_press_threshold = CRUISE_LONG_PRESS * 5

    self.error_log = ERROR_LOGS_PATH / "error.txt"

  def handle_button_event(self, key, sm, starpilot_toggles):
    # Rivian keeps ACC enabled while accelerator override temporarily pauses longActive.
    traffic_mode_allowed = self._rivian_acc_enabled if self.CP.brand == "rivian" else sm["carControl"].longActive

    if sm["carControl"].longActive and getattr(starpilot_toggles, f"experimental_mode_via_{key}"):
      self.handle_experimental_mode(sm, starpilot_toggles)
    elif getattr(starpilot_toggles, f"bookmark_via_{key}"):
      self.handle_bookmark()
    elif getattr(starpilot_toggles, f"force_coast_via_{key}"):
      self.force_coast = not self.force_coast
    elif getattr(starpilot_toggles, f"pulse_and_glide_via_{key}"):
      if getattr(sm["carControl"], "longActive", False) or self.pulse_and_glide:
        self.pulse_and_glide = not self.pulse_and_glide
        return True
    elif getattr(starpilot_toggles, f"pause_lateral_via_{key}"):
      self.pause_lateral = not self.pause_lateral
    elif getattr(starpilot_toggles, f"pause_longitudinal_via_{key}"):
      self.pause_longitudinal = not self.pause_longitudinal
    elif getattr(starpilot_toggles, f"switchback_mode_via_{key}"):
      self.switchback_mode_enabled = not self.switchback_mode_enabled
      self.params_memory.put_bool("SwitchbackModeEnabled", self.switchback_mode_enabled)
    elif traffic_mode_allowed and getattr(starpilot_toggles, f"traffic_mode_via_{key}"):
      self.traffic_mode_enabled = not self.traffic_mode_enabled
    else:
      for slot_index in range(3):
        if getattr(starpilot_toggles, f"favorite_{slot_index + 1}_via_{key}", False):
          toggle_favorite_slot(slot_index, self.params, self.params_memory)
          break

  def handle_bookmark(self):
    counter = self.params_memory.get_int("WheelButtonBookmarkCounter")
    self.params_memory.put_int("WheelButtonBookmarkCounter", counter + 1)

  def _handle_favorite_traffic_mode_action(self, sm):
    counter = self.params_memory.get_int(FAVORITE_ACTION_TRAFFIC_MODE_COUNTER)
    pending = counter - self._favorite_traffic_mode_counter
    self._favorite_traffic_mode_counter = counter

    traffic_mode_allowed = self._rivian_acc_enabled if self.CP.brand == "rivian" else sm["carControl"].longActive
    if pending > 0 and traffic_mode_allowed and pending % 2:
      self.traffic_mode_enabled = not self.traffic_mode_enabled

  def handle_experimental_mode(self, sm, starpilot_toggles):
    if getattr(starpilot_toggles, "safe_mode", False):
      return

    if starpilot_toggles.conditional_experimental_mode:
      current_status = self.params_memory.get_int("CEStatus", default=CEStatus["OFF"])
      override_value = next_manual_ce_status(current_status, sm["selfdriveState"].experimentalMode)
      self.params_memory.put_int("CEStatus", override_value)
      sync_manual_ce_state(self.params, override_value)
    elif getattr(starpilot_toggles, "conditional_chill_mode", False):
      current_status = self.params_memory.get_int("CCStatus", default=CCStatus["OFF"])
      override_value = next_manual_cc_status(current_status, sm["selfdriveState"].experimentalMode)
      self.params_memory.put_int("CCStatus", override_value)
      sync_manual_cc_state(self.params, override_value)
    else:
      self.params.put_bool_nonblocking("ExperimentalMode", not sm["selfdriveState"].experimentalMode)

  def toggle_aol_latch(self):
    # A pending Start Enabled request represents the logical on state even
    # before the vehicle becomes drive-ready. Toggling it cancels that request.
    self.always_on_lateral_allowed = not (self.always_on_lateral_allowed or self.aol_startup_pending)
    self.aol_startup_pending = False

  def update(self, carState, starpilotCarState, sm, starpilot_toggles):
    self.switchback_mode_enabled = self.params_memory.get_bool("SwitchbackModeEnabled")
    self._rivian_acc_enabled = self.CP.brand == "rivian" and carState.cruiseState.enabled
    self._handle_favorite_traffic_mode_action(sm)

    pulse_glide_cancel_override = (
      (bool(getattr(sm["carControl"], "longActive", False)) or self.pulse_and_glide) and
      any(
        getattr(starpilot_toggles, f"pulse_and_glide_via_cancel{suffix}", False)
        for suffix in ("", "_long", "_very_long")
      )
    )
    cancel_pressed = bool(getattr(starpilotCarState, "cancelPressed", False))
    if pulse_glide_cancel_override:
      carState.buttonEvents = [
        be for be in carState.buttonEvents
        if not (
          self._button_type_raw(be) == int(ButtonType.cancel) and
          (be.pressed or self.cancel_pulse_glide_suppressed)
        )
      ]

    lkas_pressed = any(
      self._button_type_raw(be) == int(ButtonType.lkas) and be.pressed
      for be in carState.buttonEvents
    )
    pulse_glide_lkas_override = (
      (bool(getattr(sm["carControl"], "longActive", False)) or self.pulse_and_glide) and
      getattr(starpilot_toggles, "pulse_and_glide_via_lkas", False)
    )
    if pulse_glide_lkas_override:
      carState.buttonEvents = [
        be for be in carState.buttonEvents
        if self._button_type_raw(be) != int(ButtonType.lkas)
      ]

    button_event_types = [self._button_type_raw(be) for be in carState.buttonEvents]
    aol_configured = bool(
      starpilot_toggles.always_on_lateral or
      starpilot_toggles.always_on_lateral_lkas or
      starpilot_toggles.always_on_lateral_main
    )
    aol_startup_enabled = getattr(starpilot_toggles, "aol_startup_enabled", True)
    rivian_aol = aol_configured and self.CP.brand == "rivian"
    driving_gear = carState.gearShifter not in NON_DRIVING_GEARS
    if not self.aol_startup_initialized:
      self.aol_startup_initialized = True
      self.aol_startup_pending = aol_configured and aol_startup_enabled

    aol_toggle_counter = self.params_memory.get_int(FAVORITE_ACTION_AOL_COUNTER)
    aol_favorite_toggled = (aol_toggle_counter - self.aol_toggle_counter) % 2 == 1
    self.aol_toggle_counter = aol_toggle_counter

    button_aol_supported = self.CP.brand == "hyundai" or starpilot_toggles.lkas_allowed_for_aol
    if getattr(self.CP, "carFingerprint", None) == HYUNDAI_CAR.HYUNDAI_SONATA_HYBRID:
      button_aol_supported = bool(starpilot_toggles.lkas_allowed_for_aol)
    existing_button_managed_aol = (
      starpilot_toggles.always_on_lateral_lkas or
      (button_aol_supported and starpilot_toggles.main_cruise_aol_toggle)
    )
    button_managed_aol = rivian_aol or not aol_startup_enabled or existing_button_managed_aol
    g70_main_cruise_aol_managed = (
      getattr(self.CP, "carFingerprint", None) == HYUNDAI_CAR.GENESIS_G70_2020
      and starpilot_toggles.main_cruise_aol_toggle
    )

    if carState.gearShifter in NON_DRIVING_GEARS or not g70_main_cruise_aol_managed:
      self.g70_main_cruise_aol_pending = False
      self.g70_main_cruise_aol_pending_frames = 0

    hyundai_aol_needs_engagement = self.hyundai_aol_needs_engagement and not starpilot_toggles.always_on_lateral_lkas
    aol_button_toggled = False

    if aol_favorite_toggled and aol_configured and self.always_on_lateral_set:
      self.toggle_aol_latch()
      aol_button_toggled = True

    if hyundai_aol_needs_engagement:
      if carState.gearShifter in NON_DRIVING_GEARS:
        preserve_reverse_latch = self.hyundai_preserve_aol_across_reverse and carState.gearShifter == GearShifter.reverse
        if not preserve_reverse_latch:
          self.hyundai_aol_ready = False
          self.always_on_lateral_allowed = False
      elif sm["selfdriveState"].active or carState.cruiseState.enabled:
        self.hyundai_aol_ready = True

    if button_aol_supported and not rivian_aol:
      for be, be_type in zip(carState.buttonEvents, button_event_types, strict=False):
        if be_type == ButtonType.lkas and be.pressed and starpilot_toggles.always_on_lateral_lkas:
          aol_button_toggled = True
          if hyundai_aol_needs_engagement:
            self.hyundai_aol_ready = True
          self.always_on_lateral_allowed = not self.always_on_lateral_allowed
          if carState.cruiseState.enabled or self.pause_lateral:
            self.pause_lateral = not self.always_on_lateral_allowed
        elif be_type == ButtonType.mainCruise and be.pressed:
          if starpilot_toggles.main_cruise_aol_toggle:
            aol_button_toggled = True
            if hyundai_aol_needs_engagement:
              self.hyundai_aol_ready = True
            if g70_main_cruise_aol_managed:
              # The G70 reports the main-cruise transition after the button press.
              # Wait for that state change before sending active LKAS11 torque.
              self.g70_main_cruise_aol_pending = True
              self.g70_main_cruise_aol_pending_frames = 0
            else:
              self.always_on_lateral_allowed = not self.always_on_lateral_allowed
          elif starpilot_toggles.main_cruise_slc_adopt and starpilot_toggles.speed_limit_controller:
            self.params_memory.put_bool("SLCAdoptSpeedLimit", True)

    cruise_available_changed = self.prev_cruise_available is not None and carState.cruiseState.available != self.prev_cruise_available
    ford_lateral_session_started = self.CP.brand == "ford" and (
      (cruise_available_changed and carState.cruiseState.available) or
      (carState.cruiseState.enabled and not self.prev_cruise_enabled)
    )
    if ford_lateral_session_started:
      self.pause_lateral = False

    if self.g70_main_cruise_aol_pending:
      if cruise_available_changed:
        self.always_on_lateral_allowed = carState.cruiseState.available
        self.g70_main_cruise_aol_pending = False
        self.g70_main_cruise_aol_pending_frames = 0
      else:
        self.g70_main_cruise_aol_pending_frames += 1
        if self.g70_main_cruise_aol_pending_frames >= HYUNDAI_MAIN_CRUISE_AOL_CONFIRM_TIMEOUT_FRAMES:
          self.g70_main_cruise_aol_pending = False
          self.g70_main_cruise_aol_pending_frames = 0

    car_fingerprint = getattr(self.CP, "carFingerprint", None)
    pcm_cruise = getattr(self.CP, "pcmCruise", False)
    pacifica_requires_set = pacifica_hybrid_aol_requires_set_press(car_fingerprint, pcm_cruise)
    if starpilot_toggles.always_on_lateral_main and not button_managed_aol:
      if pacifica_requires_set:
        # Chrysler Pacifica Hybrid stock ACC can fall back to plain cruise if AOL
        # starts steering before the driver presses SET.
        if not carState.cruiseState.available:
          self.always_on_lateral_allowed = False
        elif carState.cruiseState.enabled and not self.prev_cruise_enabled:
          self.always_on_lateral_allowed = True
          self.aol_startup_pending = False
      elif self.aol_startup_pending and driving_gear and carState.cruiseState.available:
        self.always_on_lateral_allowed = True
        self.aol_startup_pending = False

    # Rivian uses a dedicated drive-scoped AOL latch. Start Enabled arms it
    # once when the vehicle first becomes drive-ready; Start Off waits for a
    # normal engagement or the configured half-up stalk action.
    if rivian_aol and self.aol_startup_pending and driving_gear and carState.cruiseState.available:
      self.always_on_lateral_allowed = True
      self.aol_startup_pending = False

    # A normal lateral or cruise engagement enables AOL so lateral remains
    # available after longitudinal control is cancelled.
    aol_engaged = ((carState.cruiseState.enabled and not self.prev_cruise_enabled) or
                   (sm["selfdriveState"].active and not self.prev_active))
    if aol_configured and self.always_on_lateral_set and aol_engaged and not aol_button_toggled:
      if hyundai_aol_needs_engagement:
        self.hyundai_aol_ready = True
      self.always_on_lateral_allowed = True
      self.aol_startup_pending = False

    rivian_half_up_pressed = rivian_aol and any(
      be.pressed and be_type == ButtonType.lkas
      for be, be_type in zip(carState.buttonEvents, button_event_types, strict=False)
    )
    if (rivian_half_up_pressed and getattr(starpilot_toggles, "rivian_half_up_stalk_aol_toggle", False) and
        not (carState.cruiseState.enabled or self.prev_cruise_enabled)):
      self.toggle_aol_latch()

    rivian_full_up_pressed = rivian_aol and any(
      be.pressed and be_type == ButtonType.altButton2
      for be, be_type in zip(carState.buttonEvents, button_event_types, strict=False)
    )
    preserve_reverse_latch = self.hyundai_preserve_aol_across_reverse and carState.gearShifter == GearShifter.reverse
    left_driving_gear = self.aol_driving_seen and not driving_gear and not preserve_reverse_latch
    disengage_on_brake = getattr(starpilot_toggles, "aol_brake_behavior", 0) == 0
    if aol_configured and (rivian_full_up_pressed or left_driving_gear or (disengage_on_brake and carState.brakePressed)):
      self.always_on_lateral_allowed = False
      self.aol_startup_pending = False

    self.aol_driving_seen |= driving_gear

    self.prev_active = sm["selfdriveState"].active
    self.prev_cruise_enabled = carState.cruiseState.enabled
    self.prev_cruise_available = carState.cruiseState.available

    self.always_on_lateral_enabled = self.always_on_lateral_allowed and self.always_on_lateral_set
    self.always_on_lateral_enabled &= carState.gearShifter not in NON_DRIVING_GEARS
    self.always_on_lateral_enabled &= not hyundai_aol_needs_engagement or self.hyundai_aol_ready
    self.always_on_lateral_enabled &= sm["starpilotPlan"].lateralCheck
    self.always_on_lateral_enabled &= sm["liveCalibration"].calPerc >= 1
    alert_types = sm["selfdriveState"].alertType + sm["starpilotSelfdriveState"].alertType
    self.always_on_lateral_enabled &= ET.IMMEDIATE_DISABLE not in alert_types
    self.always_on_lateral_enabled &= not (carState.brakePressed and carState.vEgo < starpilot_toggles.always_on_lateral_pause_speed) or carState.standstill
    self.always_on_lateral_enabled &= not self.error_log.is_file()

    if sm.updated["starpilotPlan"] or any(be_type in (ButtonType.accelCruise, ButtonType.resumeCruise) for be_type in button_event_types):
      self.accel_pressed = any(be_type in (ButtonType.accelCruise, ButtonType.resumeCruise) for be_type in button_event_types)

    if sm.updated["starpilotPlan"] or any(be_type == ButtonType.decelCruise for be_type in button_event_types):
      self.decel_pressed = any(be_type == ButtonType.decelCruise for be_type in button_event_types)

    self._distance_poll_counter += 1
    if self._distance_poll_counter >= 10:
      self._distance_poll_counter = 0
      self._onroad_distance_pressed = self.params_memory.get_bool("OnroadDistanceButtonPressed")
    starpilotCarState.distancePressed |= self._onroad_distance_pressed

    if starpilotCarState.distancePressed:
      self.gap_counter += 1
    elif not self.distancePressed_previously:
      self.gap_counter = 0

    distance_released = not starpilotCarState.distancePressed and self.distancePressed_previously
    has_distance_release = any(
      self._button_type_raw(be) == int(ButtonType.gapAdjustCruise) and not be.pressed
      for be in carState.buttonEvents
    )
    if getattr(self.CP, "carFingerprint", None) == HYUNDAI_CAR.HYUNDAI_ELANTRA_HEV_2024 and \
        distance_released and not has_distance_release:
      carState.buttonEvents = [
        *carState.buttonEvents,
        structs.CarState.ButtonEvent(pressed=False, type=ButtonType.gapAdjustCruise),
      ]

    self.distancePressed_previously = starpilotCarState.distancePressed

    if not starpilotCarState.distancePressed and 1 <= self.gap_counter < self.long_press_threshold:
      self.handle_button_event("distance", sm, starpilot_toggles)
    elif self.gap_counter == self.long_press_threshold:
      self.handle_button_event("distance_long", sm, starpilot_toggles)
    elif self.gap_counter == self.very_long_press_threshold:
      self.handle_button_event("distance_very_long", sm, starpilot_toggles)

    if cancel_pressed:
      self.cancel_counter += 1
    elif not self.cancelPressed_previously:
      self.cancel_counter = 0

    self.cancelPressed_previously = cancel_pressed

    pulse_glide_cancel_consumed = False
    if not cancel_pressed and self.cancel_pulse_glide_suppressed:
      pass
    elif not cancel_pressed and 1 <= self.cancel_counter < self.long_press_threshold:
      pulse_glide_cancel_consumed = self.handle_button_event("cancel", sm, starpilot_toggles) or False
    elif self.cancel_counter == self.long_press_threshold:
      pulse_glide_cancel_consumed = self.handle_button_event("cancel_long", sm, starpilot_toggles) or False
    elif self.cancel_counter == self.very_long_press_threshold:
      pulse_glide_cancel_consumed = self.handle_button_event("cancel_very_long", sm, starpilot_toggles) or False

    if pulse_glide_cancel_consumed:
      self.cancel_pulse_glide_suppressed = True
      carState.buttonEvents = [
        be for be in carState.buttonEvents
        if self._button_type_raw(be) != int(ButtonType.cancel)
      ]
    elif not cancel_pressed and self.cancel_pulse_glide_suppressed:
      self.cancel_pulse_glide_suppressed = False

    if lkas_pressed:
      if self.CP.brand != "ford" or carState.cruiseState.available:
        if self.CP.brand == "ford" and getattr(starpilot_toggles, "ford_lkas_aol_toggle", False):
          self.pause_lateral = not self.pause_lateral
        else:
          self.handle_button_event("lkas", sm, starpilot_toggles)

    if getattr(starpilot_toggles, "has_canfd_media_buttons", False):
      if starpilotCarState.modePressed:
        self.mode_counter += 1
      elif not self.modePressed_previously:
        self.mode_counter = 0
      self.modePressed_previously = starpilotCarState.modePressed

      if not starpilotCarState.modePressed and 1 <= self.mode_counter < self.long_press_threshold:
        self.handle_button_event("mode", sm, starpilot_toggles)
      elif self.mode_counter == self.long_press_threshold:
        self.handle_button_event("mode_long", sm, starpilot_toggles)
      elif self.mode_counter == self.very_long_press_threshold:
        self.handle_button_event("mode_very_long", sm, starpilot_toggles)

      if starpilotCarState.customPressed:
        self.custom_counter += 1
      elif not self.customPressed_previously:
        self.custom_counter = 0
      self.customPressed_previously = starpilotCarState.customPressed

      if not starpilotCarState.customPressed and 1 <= self.custom_counter < self.long_press_threshold:
        self.handle_button_event("star", sm, starpilot_toggles)
      elif self.custom_counter == self.long_press_threshold:
        self.handle_button_event("star_long", sm, starpilot_toggles)
      elif self.custom_counter == self.very_long_press_threshold:
        self.handle_button_event("star_very_long", sm, starpilot_toggles)

    if not getattr(starpilot_toggles, "pulse_and_glide_available", False):
      self.pulse_and_glide = False
    self.force_coast &= not (carState.brakePressed or carState.gasPressed)

    if self.always_on_lateral_allowed != self.aol_active_last:
      put_bool = getattr(self.params_memory, "put_bool_nonblocking", None) or self.params_memory.put_bool
      put_bool("AOLActive", self.always_on_lateral_allowed)
      self.aol_active_last = self.always_on_lateral_allowed

    starpilotCarState.accelPressed = self.accel_pressed
    starpilotCarState.alwaysOnLateralAllowed = self.always_on_lateral_allowed
    starpilotCarState.alwaysOnLateralEnabled = self.always_on_lateral_enabled
    starpilotCarState.cancelLongPressed = self.very_long_press_threshold > self.cancel_counter >= self.long_press_threshold
    starpilotCarState.cancelVeryLongPressed = self.cancel_counter >= self.very_long_press_threshold
    starpilotCarState.decelPressed = self.decel_pressed
    starpilotCarState.distanceLongPressed = self.very_long_press_threshold > self.gap_counter >= self.long_press_threshold
    starpilotCarState.distanceVeryLongPressed = self.gap_counter >= self.very_long_press_threshold
    starpilotCarState.forceCoast = self.force_coast
    starpilotCarState.pulseAndGlide = self.pulse_and_glide
    starpilotCarState.isParked = carState.gearShifter == GearShifter.park
    starpilotCarState.pauseLateral = self.pause_lateral
    starpilotCarState.pauseLongitudinal = self.pause_longitudinal
    starpilotCarState.trafficModeEnabled = self.traffic_mode_enabled

    return starpilotCarState
