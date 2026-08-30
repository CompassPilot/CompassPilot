#pragma once

void ignition_can_hook(CANPacket_t *msg) {
  int len = GET_LEN(msg);

  #ifdef PANDA_HKG_REMOTE_START
  if ((msg->bus == 1U) && (msg->addr == 0x384U) && (len == 8)) {
    hkg_remote_climate_wake = msg->data[3] != 0U;
    hkg_remote_climate_wake_cnt = 0U;
  }
  #endif

  if (msg->bus == 0U) {
    // GM exception
    // Remote-start mode uses 0xC9 bit 4 (SystemPowerMode=Run) for ignition detection.
    // Stock mode uses 0x1F1 bit 1 (SystemPowerMode=Run/Crank Request).
    #ifdef PANDA_GM_REMOTE_START_C9
    if ((msg->addr == 0xC9U) && (len == 8)) {
      ignition_can = (msg->data[6] & 0x10U) != 0U;
      ignition_can_cnt = 0U;
    }
    #else
    if (gm_remote_start_boots_comma) {
      if ((msg->addr == 0xC9U) && (len == 8)) {
        ignition_can = (msg->data[6] & 0x10U) != 0U;
        ignition_can_cnt = 0U;
      }
    } else {
      if ((msg->addr == 0x1F1U) && (len == 8)) {
        // SystemPowerMode (2=Run, 3=Crank Request)
        ignition_can = (msg->data[0] & 0x2U) != 0U;
        ignition_can_cnt = 0U;
      }
    }
    #endif

    // Rivian R1S/T GEN1 exception
    if ((msg->addr == 0x152U) && (len == 8)) {
      // 0x152 overlaps with Subaru pre-global which has this bit as the high beam
      int counter = msg->data[1] & 0xFU;  // max is only 14

      static int prev_counter_rivian = -1;
      if ((counter == ((prev_counter_rivian + 1) % 15)) && (prev_counter_rivian != -1)) {
        // VDM_OutputSignals->VDM_EpasPowerMode
        ignition_can = ((msg->data[7] >> 4U) & 0x3U) == 1U;  // VDM_EpasPowerMode_Drive_On=1
        ignition_can_cnt = 0U;
      }
      prev_counter_rivian = counter;
    }

    // Tesla Model 3/Y exception
    if ((msg->addr == 0x221U) && (len == 8)) {
      // 0x221 overlaps with Rivian which has random data on byte 0
      int counter = msg->data[6] >> 4;

      static int prev_counter_tesla = -1;
      if ((counter == ((prev_counter_tesla + 1) % 16)) && (prev_counter_tesla != -1)) {
        // VCFRONT_LVPowerState->VCFRONT_vehiclePowerState
        int power_state = (msg->data[0] >> 5U) & 0x3U;
        ignition_can = power_state == 0x3;  // VEHICLE_POWER_STATE_DRIVE=3
        ignition_can_cnt = 0U;
      }
      prev_counter_tesla = counter;
    }

    // Tesla Model S pre-AP exception
    if ((msg->addr == 0x101U) && (len == 3)) {
      // Validate Tesla checksum/counter to avoid false positives on overlapping frames.
      int counter = msg->data[1] & 0xFU;
      int checksum = (((msg->addr & 0xFFU) + ((msg->addr >> 8U) & 0xFFU) + msg->data[0] + msg->data[1]) & 0xFFU);

      static int prev_counter_tesla_preap = -1;
      if ((msg->data[2] == checksum) && (counter == ((prev_counter_tesla_preap + 1) % 16)) && (prev_counter_tesla_preap != -1)) {
        // GTW_epasPowerMode=1 is DRIVE_ON, which is the only ignition source on pre-AP cars.
        int power_mode = (msg->data[0] >> 3U) & 0xFU;
        ignition_can = power_mode == 0x1U;
        ignition_can_cnt = 0U;
      }
      prev_counter_tesla_preap = counter;
    }

    // Mazda exception
    if ((msg->addr == 0x9EU) && (len == 8)) {
      ignition_can = (msg->data[0] >> 5) == 0x6U;
      ignition_can_cnt = 0U;
    }

  }
}
