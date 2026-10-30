#pragma once

#include "opendbc/safety/declarations.h"
#include "opendbc/safety/modes/rivian_stock_aol.h"
#include "opendbc/safety/modes/rivian_harness_aol.h"

#define RIVIAN_PARAM_LONG_CONTROL 1U
#define RIVIAN_PARAM_ANGLE_CONTROL 2U
#define RIVIAN_PARAM_AOL_LATERAL 4U
#define RIVIAN_PARAM_AOL_BRAKE_REMAINS_ACTIVE 8U
#define RIVIAN_PARAM_AOL_STALK_TOGGLE 16U
#define RIVIAN_PARAM_AOL_START_ENABLED 32U
#define RIVIAN_PARAM_R1T 64U

// Angle steering is supplied only by the Extreme harness bridge.
static bool rivian_angle_control = false;
static bool rivian_r1t = false;

static uint8_t rivian_get_counter(const CANPacket_t *msg) {
  // Signal: ESP_Status_Counter, VDM_PropStatus_Counter
  return msg->data[1] & 0xFU;
}

static uint32_t rivian_get_checksum(const CANPacket_t *msg) {
  return msg->data[0];
}

static uint8_t _rivian_compute_checksum(const CANPacket_t *msg, uint8_t poly, uint8_t xor_output) {
  int len = GET_LEN(msg);

  uint8_t crc = 0;
  // Skip the checksum byte
  for (int i = 1; i < len; i++) {
    crc = crc8_update(crc, msg->data[i], poly);
  }
  return crc ^ xor_output;
}

static uint32_t rivian_compute_checksum(const CANPacket_t *msg) {
  uint8_t chksum = 0;
  if (msg->addr == 0x208U) {
    chksum = _rivian_compute_checksum(msg, 0x1D, 0xB1);
  }
  if (msg->addr == 0x150U) {
    chksum = _rivian_compute_checksum(msg, 0x1D, 0x9A);
  }
  if (msg->addr == 0x380U) {
    chksum = _rivian_compute_checksum(msg, 0x1D, 0x1E);
  }
  if (msg->addr == 0x38FU) {
    chksum = _rivian_compute_checksum(msg, 0x1D, 0x37);
  }
  if (msg->addr == 0x100U) {
    chksum = _rivian_compute_checksum(msg, 0x1D, 0x5F);
  }
  if (msg->addr == 0x162U) {
    chksum = _rivian_compute_checksum(msg, 0x1D, 0xD1);
  }
  if (msg->addr == 0x390U) {
    chksum = crc8_update(0U, 0x90U, 0x1DU);
    chksum = crc8_update(chksum, 0x03U, 0x1DU);
    const int len = GET_LEN(msg);
    for (int i = 1; i < len; i++) {
      chksum = crc8_update(chksum, msg->data[i], 0x1DU);
    }
  }
  return chksum;
}

static bool rivian_get_quality_flag_valid(const CANPacket_t *msg) {
  bool valid = false;
  if (msg->addr == 0x208U) {
    valid = ((msg->data[3] >> 3) & 0x3U) == 0x1U;  // ESP_Vehicle_Speed_Q
  }
  if (msg->addr == 0x150U) {
    valid = (msg->data[1] >> 6) == 0x1U;  // VDM_VehicleSpeedQ
  }
  if (msg->addr == 0x38FU) {
    valid = ((msg->data[2] >> 5) & 0x3U) == 0x1U;  // iBESP2_BrakePedalApplied_Q
  }
  return valid;
}

static void rivian_rx_hook(const CANPacket_t *msg) {
  // Vehicle speed
  if (msg_matches(msg, 0x208U, 0U)) {
    float speed = ((msg->data[6] << 8) | msg->data[7]) * 0.01;
    vehicle_moving = speed > 0.0;
    UPDATE_VEHICLE_SPEED(speed * KPH_TO_MS);
  }

  // Gas pressed and second speed source for variable torque limit
  if (msg_matches(msg, 0x150U, 0U)) {
    gas_pressed = msg->data[3] | (msg->data[4] & 0xC0U);

    // Disable controls if speeds from VDM and ESP ECUs are too far apart.
    float vdm_speed = ((msg->data[5] << 8) | msg->data[6]) * 0.01 * KPH_TO_MS;
    speed_mismatch_check(vdm_speed);
  }

  // Driver torque
  if (msg_matches(msg, 0x380U, 0U)) {
    int torque_driver_new = (((msg->data[2] << 4) | (msg->data[3] >> 4))) - 2050U;
    update_sample(&torque_driver, torque_driver_new);
  }

  // Measured steering angle from EPAS, stored in 0.1 degrees to match
  // ACM_SteeringAngleRequest and angle_deg_to_can.
  if (msg_matches(msg, 0x390U, 0U)) {
    int angle_meas_new = ((msg->data[5] << 6) | (msg->data[6] >> 2)) - 8192U;
    update_sample(&angle_meas, angle_meas_new);
  }

  // Brake pressed
  if (msg_matches(msg, 0x38fU, 0U)) {
    brake_pressed = (msg->data[2] >> 7) & 1U;
  }

  // Cruise state
  if (msg_matches(msg, 0x100U, 2U)) {
    const int feature_status = msg->data[2] >> 5U;
    pcm_cruise_check(feature_status == 1);
  }
  rivian_aol_observe(msg);
  rivian_harness_aol_observe(msg);
}

static bool rivian_tx_hook(const CANPacket_t *msg) {
  const AngleSteeringLimits RIVIAN_ANGLE_STEERING_LIMITS = {
    .max_angle = 5000,
    .angle_deg_to_can = 10,
    .frequency = 100U,
  };

  const AngleSteeringParams RIVIAN_R1S_ANGLE_STEERING_PARAMS = {
    .slip_factor = -0.0005445721739802007,  // calc_slip_factor(VM)
    .steer_ratio = 15.2,
    .wheelbase = 3.08,
  };
  const AngleSteeringParams RIVIAN_R1T_ANGLE_STEERING_PARAMS = {
    .slip_factor = -0.00048616874521194406,  // calc_slip_factor(VM)
    .steer_ratio = 15.2,
    .wheelbase = 3.45,
  };
  const AngleSteeringParams angle_steering_params = rivian_r1t ? RIVIAN_R1T_ANGLE_STEERING_PARAMS :
                                                                 RIVIAN_R1S_ANGLE_STEERING_PARAMS;

  // Rivian utilizes more torque at low speed to maintain the same lateral accel
  const TorqueSteeringLimits RIVIAN_STEERING_LIMITS = {
    .max_torque = 385,
    .dynamic_max_torque = true,
    // Three-point envelope around the software four-point
    // [9,13,25,27] -> [385,350,295,275] tune. This curve is never below the
    // software lookup, so Panda permits every command the controller can emit.
    .max_torque_lookup = {
      {9., 25., 27.},
      {385, 295, 275},
    },
    .max_rate_up = 3,
    .max_rate_down = 5,
    .max_rt_delta = 125,
    .driver_torque_multiplier = 2,
    .driver_torque_allowance = 100,
    .type = TorqueDriverLimited,
    .min_valid_request_frames = 89,
    .max_invalid_request_frames = 2,
    .min_valid_request_rt_interval = 810000,
    .has_steer_req_tolerance = true,
    // Feedback-driven ToI releases may last longer than two frames, and rearm
    // holds (req=1, torque=0) until EPAS acknowledges. Preserve the limiter
    // reference across any zero-torque cut so assist can resume without a sawtooth.
    .preserve_torque_on_zero_request = true,
  };

  const LongitudinalLimits RIVIAN_LONG_LIMITS = {
    .max_accel = 200,
    .min_accel = -350,
    .inactive_accel = 0,
  };

  bool tx = true;

  // Angle steering, Extreme harness only
  if (msg_matches(msg, 0x110U, 0U)) {
    int desired_angle = ((msg->data[2] << 7) | (msg->data[3] >> 1)) - 16384U;
    bool angle_active = GET_BIT(msg, 12U);
    if (!rivian_angle_control || steer_angle_cmd_checks_vm(desired_angle, angle_active, RIVIAN_ANGLE_STEERING_LIMITS,
                                                           angle_steering_params)) {
      tx = false;
    }
  }

  // Steering control
  if (msg_matches(msg, 0x120U, 0U)) {
    int desired_torque = ((msg->data[2] << 3U) | (msg->data[3] >> 5U)) - 1024U;
    bool steer_req = (msg->data[3] >> 4) & 1U;

    if (steer_torque_cmd_checks(desired_torque, steer_req, RIVIAN_STEERING_LIMITS)) {
      tx = false;
    }
  }

  // Longitudinal control
  if (msg_matches(msg, 0x160U, 0U)) {
    int raw_accel = ((msg->data[2] << 3) | (msg->data[3] >> 5)) - 1024U;
    if (longitudinal_accel_checks(raw_accel, RIVIAN_LONG_LIMITS)) {
      tx = false;
    }
  }

  return tx;
}

static safety_config rivian_init(uint16_t param) {
  // SCCM_WheelTouch: for hiding hold wheel alert
  // VDM_AdasSts: for canceling stock ACC
  // 0x120 = ACM_lkaHbaCmd, 0x321 = SCCM_WheelTouch, 0x162 = VDM_AdasSts
  static const CanMsg RIVIAN_TX_MSGS[] = {
    {0x120, 0, 8, .check_relay = true},
    {0x321, 2, 7, .check_relay = true},
    {0x162, 2, 8, .check_relay = true},
  };
  // Extreme harness angle control: 0x100 = ACM_Status, 0x110 = ACM_SteeringControl
  static const CanMsg RIVIAN_ANGLE_TX_MSGS[] = {
    {0x100, 0, 8, .check_relay = true},
    {0x110, 0, 8, .check_relay = true},
    {0x120, 0, 8, .check_relay = true},
    {0x321, 2, 7, .check_relay = true},
    {0x162, 2, 8, .check_relay = true},
  };
  // 0x160 = ACM_longitudinalRequest. The longitudinal harness keeps forwarding
  // VDM_AdasSts so the disconnected stock ACM cannot wind up a request.
#ifdef ALLOW_DEBUG
  static const CanMsg RIVIAN_LONG_TX_MSGS[] = {
    {0x120, 0, 8, .check_relay = true},
    {0x321, 2, 7, .check_relay = true},
    {0x160, 0, 5, .check_relay = true},
    {0x162, 2, 8, .check_relay = true},
  };
  static const CanMsg RIVIAN_ANGLE_LONG_TX_MSGS[] = {
    {0x100, 0, 8, .check_relay = true},
    {0x110, 0, 8, .check_relay = true},
    {0x120, 0, 8, .check_relay = true},
    {0x321, 2, 7, .check_relay = true},
    {0x160, 0, 5, .check_relay = true},
    {0x162, 2, 8, .check_relay = true},
  };
#endif

  static const RxCheck rivian_rx_descriptors[] = {
    {.msg = {{0x208, 0, 8, 50U, .max_counter = 14U}, { 0 }, { 0 }}},   // ESP_Status (speed)
    {.msg = {{0x150, 0, 7, 50U, .max_counter = 14U}, { 0 }, { 0 }}},   // VDM_PropStatus (gas pedal & 2nd speed)
    {.msg = {{0x38f, 0, 6, 50U, .max_counter = 14U}, { 0 }, { 0 }}},   // iBESP2 (brakes)
    {.msg = {{0x380, 0, 5, 100U, .max_counter = 14U, .ignore_quality_flag = true}, { 0 }, { 0 }}},  // EPAS_SystemStatus (driver torque)
    {.msg = {{0x100, 2, 8, 100U, .max_counter = 14U, .ignore_quality_flag = true}, { 0 }, { 0 }}},  // ACM_Status (cruise state)
    {.msg = {{0x390, 0, 7, 100U, .max_counter = 14U, .ignore_quality_flag = true}, { 0 }, { 0 }}},  // EPAS angle fault/status
    {.msg = {{0x162, 0, 8, 50U, .max_counter = 14U, .ignore_quality_flag = true}, { 0 }, { 0 }}},   // VDM_AdasSts (stalk requests)
  };

  // H7 DTCM is constrained. AXI SRAM is NOLOAD, so initialize every row from
  // the immutable checked catalog on each mode entry, including its status.
#if defined(STM32H7)
  static RxCheck rivian_rx_checks[7] __attribute__((section(".axisram")));
#else
  static RxCheck rivian_rx_checks[7];
#endif
  for (unsigned int i = 0U; i < 7U; i++) {
    rivian_rx_checks[i] = rivian_rx_descriptors[i];
  }

  const uint16_t known_params = RIVIAN_PARAM_LONG_CONTROL | RIVIAN_PARAM_ANGLE_CONTROL | RIVIAN_PARAM_AOL_LATERAL |
                                RIVIAN_PARAM_AOL_BRAKE_REMAINS_ACTIVE | RIVIAN_PARAM_AOL_STALK_TOGGLE |
                                RIVIAN_PARAM_AOL_START_ENABLED | RIVIAN_PARAM_R1T;
  const bool params_known = (param & ~known_params) == 0U;
  rivian_angle_control = GET_FLAG(param, RIVIAN_PARAM_ANGLE_CONTROL);
  rivian_r1t = GET_FLAG(param, RIVIAN_PARAM_R1T);
  const bool harness_aol_requested = GET_FLAG(param, RIVIAN_PARAM_AOL_LATERAL);
  // The base GEN1 stock profile admits only the ordinary torque (and DEBUG
  // longitudinal) configuration of either body style.
  const uint16_t stock_param = param & ~RIVIAN_PARAM_R1T;
  bool aol_param_supported = stock_param == 0U;
  bool rivian_longitudinal = false;

  safety_config ret = rivian_angle_control ? BUILD_SAFETY_CFG(rivian_rx_checks, RIVIAN_ANGLE_TX_MSGS) :
                                             BUILD_SAFETY_CFG(rivian_rx_checks, RIVIAN_TX_MSGS);
  rivian_aol_reset();
#ifdef ALLOW_DEBUG
  rivian_longitudinal = GET_FLAG(param, RIVIAN_PARAM_LONG_CONTROL);
  rivian_aol_longitudinal = rivian_longitudinal;
  aol_param_supported |= stock_param == RIVIAN_PARAM_LONG_CONTROL;
  if (rivian_longitudinal) {
    ret = rivian_angle_control ? BUILD_SAFETY_CFG(rivian_rx_checks, RIVIAN_ANGLE_LONG_TX_MSGS) :
                                 BUILD_SAFETY_CFG(rivian_rx_checks, RIVIAN_LONG_TX_MSGS);
  }
#endif
  const bool aol_experience = (unsigned int)alternative_experience == 32U;
  rivian_aol_enabled = aol_experience && aol_param_supported;

  rivian_harness_aol_enabled = aol_experience && params_known && harness_aol_requested;
  rivian_harness_aol_longitudinal = rivian_longitudinal;
  rivian_harness_aol_brake_remains_active = GET_FLAG(param, RIVIAN_PARAM_AOL_BRAKE_REMAINS_ACTIVE);
  rivian_harness_aol_stalk_toggle = GET_FLAG(param, RIVIAN_PARAM_AOL_STALK_TOGGLE);
  rivian_harness_aol_start_enabled = GET_FLAG(param, RIVIAN_PARAM_AOL_START_ENABLED);
  rivian_harness_aol_reset();

  if (rivian_aol_enabled) {
    static const AolSafetyPolicy policy = {
      .reset = rivian_aol_reset,
      .host_request = rivian_aol_request,
      .request_mask = rivian_aol_request_mask,
      .permission_mask = rivian_aol_permission,
      .rx_invalid = rivian_aol_clear,
    };
    aol_policy = &policy;
  } else if (rivian_harness_aol_enabled) {
    static const AolSafetyPolicy harness_policy = {
      .reset = rivian_harness_aol_reset,
      .host_request = rivian_harness_aol_request,
      .request_mask = rivian_harness_aol_request_mask,
      .permission_mask = rivian_harness_aol_permission,
      .rx_invalid = rivian_harness_aol_clear,
    };
    aol_policy = &harness_policy;
  } else {
  }

  // Ordinary upstream RX catalog remains exactly five rows. Native AOL and the
  // angle channel also require EPAS status; the harness AOL latch needs the stalk.
  if (rivian_harness_aol_enabled) {
  } else if (rivian_aol_enabled || rivian_angle_control) {
    ret.rx_checks_len -= 1;
  } else {
    ret.rx_checks_len -= 2;
  }
  if (aol_experience && !rivian_aol_enabled && !rivian_harness_aol_enabled) {
    ret.tx_msgs = NULL;
    ret.tx_msgs_len = 0;
  }
  return ret;
}

const safety_hooks rivian_hooks = {
  .init = rivian_init,
  .rx = rivian_rx_hook,
  .tx = rivian_tx_hook,
  .get_counter = rivian_get_counter,
  .get_checksum = rivian_get_checksum,
  .compute_checksum = rivian_compute_checksum,
  .get_quality_flag_valid = rivian_get_quality_flag_valid,
};
