#pragma once

// Extreme harness Always On Lateral. Physical disarm events (full-up stalk,
// brake when configured, leaving Drive, ACM unavailable, EPS shutdown) clear
// the latch immediately. Stock ACC engagement, the deferred half-up stalk
// toggle and the configured Drive startup arm it. A fresh host lateral request
// re-arms only inside the same physical gates the stalk uses.
static bool rivian_harness_aol_enabled = false;
static bool rivian_harness_aol_longitudinal = false;
static bool rivian_harness_aol_brake_remains_active = false;
static bool rivian_harness_aol_stalk_toggle = false;
static bool rivian_harness_aol_start_enabled = false;
static bool rivian_harness_aol_latch = false;
static bool rivian_harness_aol_start_pending = false;
static bool rivian_harness_aol_lkas_pending = false;
static bool rivian_harness_aol_acc_enabled = false;
static bool rivian_harness_aol_available = false;
static bool rivian_harness_aol_in_drive = false;
static bool rivian_harness_aol_driving_seen = false;
static uint8_t rivian_harness_aol_prev_user_request = 0U;
static bool rivian_harness_aol_requested = false;

static void rivian_harness_aol_clear(void) {
  rivian_harness_aol_latch = false;
  rivian_harness_aol_start_pending = false;
  rivian_harness_aol_lkas_pending = false;
}

static void rivian_harness_aol_reset(void) {
  rivian_harness_aol_clear();
  rivian_harness_aol_start_pending = rivian_harness_aol_enabled && rivian_harness_aol_start_enabled;
  rivian_harness_aol_acc_enabled = false;
  rivian_harness_aol_available = false;
  rivian_harness_aol_in_drive = false;
  rivian_harness_aol_driving_seen = false;
  rivian_harness_aol_prev_user_request = 0U;
  rivian_harness_aol_requested = false;
}

static void rivian_harness_aol_request(uint8_t mask) {
  rivian_harness_aol_requested |= mask != 0U;
  // The AOL favorite and other software arms have no vehicle button edge.
  // Re-arm only inside the physical gates used by the stalk: Drive, ACM
  // available, brake released and the full-up stalk position released.
  if (((mask & 1U) != 0U) && !rivian_harness_aol_latch && rivian_harness_aol_in_drive &&
      rivian_harness_aol_available && !brake_pressed && (rivian_harness_aol_prev_user_request != 2U)) {
    rivian_harness_aol_latch = true;
  }
}

static uint8_t rivian_harness_aol_request_mask(void) {
  const bool request_expired = rivian_harness_aol_requested &&
    (safety_get_ts_elapsed(microsecond_timer_get(), aol_host_request_ts) > AOL_HOST_REQUEST_TIMEOUT_US);
  uint8_t request = 0U;
  if (relay_malfunction || safety_rx_checks_invalid || !aol_rx_healthy() || request_expired) {
    rivian_harness_aol_clear();
    rivian_harness_aol_requested = !request_expired && rivian_harness_aol_requested;
  } else if (heartbeat_engaged) {
    request = aol_host_axis_mask;
  } else {
  }
  return request;
}

static uint8_t rivian_harness_aol_permission(void) {
  const uint8_t request = rivian_harness_aol_request_mask();
  uint8_t permission = 0U;
  if (rivian_harness_aol_latch && rivian_harness_aol_in_drive && rivian_harness_aol_available) {
    permission = request & 1U;
  }
  // Gas is an ordinary longitudinal override: get_longitudinal_allowed() still
  // blocks accel while gas_pressed_prev. Revoking the axis here instead made the
  // host see an unacknowledged LONG request on every one-pedal gas touch (and
  // on engaging ACC with the accelerator held), resetting the AOL latch.
  if (rivian_harness_aol_longitudinal && controls_allowed && !brake_pressed) {
    permission |= request & 2U;
  }
  return permission;
}

static void rivian_harness_aol_observe(const CANPacket_t *msg) {
  if (rivian_harness_aol_enabled) {
    if (msg_matches(msg, 0x150U, 0U)) {
      // VDM_Prndl_Status: 1=Park, 2=Reverse, 3=Neutral, 4=Drive.
      // Unknown values fail safe, and returning to Drive never re-enables AOL.
      rivian_harness_aol_in_drive = (msg->data[2] & 0xFU) == 4U;
      if (rivian_harness_aol_in_drive) {
        if (rivian_harness_aol_start_pending && rivian_harness_aol_available) {
          rivian_harness_aol_latch = true;
          rivian_harness_aol_start_pending = false;
        }
        rivian_harness_aol_driving_seen = true;
      } else if (rivian_harness_aol_driving_seen || rivian_harness_aol_latch) {
        rivian_harness_aol_clear();
      } else {
      }
    }

    if (msg_matches(msg, 0x162U, 0U)) {
      const uint8_t user_request = msg->data[7] & 0x7U;
      if (rivian_harness_aol_stalk_toggle && (user_request == 1U) && (rivian_harness_aol_prev_user_request != 1U) &&
          (rivian_harness_aol_prev_user_request != 2U) && !rivian_harness_aol_acc_enabled) {
        rivian_harness_aol_lkas_pending = true;
      }
      if ((user_request == 2U) && (rivian_harness_aol_prev_user_request != 2U)) {
        rivian_harness_aol_clear();
      }
      rivian_harness_aol_prev_user_request = user_request;
    }

    if (msg_matches(msg, 0x38FU, 0U) && !rivian_harness_aol_brake_remains_active && brake_pressed) {
      rivian_harness_aol_clear();
    }

    if (msg_matches(msg, 0x390U, 0U) && (((msg->data[4] >> 1U) & 7U) == 4U)) {
      rivian_harness_aol_clear();
    }

    if (msg_matches(msg, 0x100U, 2U)) {
      const uint8_t feature = msg->data[2] >> 5U;
      const bool acc_enabled = feature == 1U;
      rivian_harness_aol_available = (feature == 0U) || acc_enabled;
      if (!rivian_harness_aol_available) {
        rivian_harness_aol_clear();
      } else if (acc_enabled && !rivian_harness_aol_acc_enabled) {
        rivian_harness_aol_start_pending = false;
        rivian_harness_aol_lkas_pending = false;
        rivian_harness_aol_latch = true;
      } else if (rivian_harness_aol_start_pending && rivian_harness_aol_in_drive) {
        rivian_harness_aol_start_pending = false;
        rivian_harness_aol_latch = true;
      } else if (rivian_harness_aol_lkas_pending) {
        // Resolve the deferred half-up request on the next 100 Hz ACM_Status message.
        rivian_harness_aol_latch = !rivian_harness_aol_latch;
        rivian_harness_aol_lkas_pending = false;
      } else {
      }
      rivian_harness_aol_acc_enabled = acc_enabled;
    }
  }
}
