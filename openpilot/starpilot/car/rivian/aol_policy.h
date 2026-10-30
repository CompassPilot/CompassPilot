#pragma once

#include "openpilot/selfdrive/pandad/aol_protocol.h"

inline bool rivian_aol_param(uint16_t param) {
  // Body style (R1T = 64) never changes the admitted configuration.
  const uint16_t profile = param & ~uint16_t{64U};
  // Base GEN1 stock profile: ordinary torque, or DEBUG longitudinal.
  if ((profile == 0U) || (profile == 1U)) {
    return true;
  }
  // Extreme harness profile: AOL lateral (4) plus angle (2), longitudinal (1),
  // brake-remains-active (8), half-up stalk toggle (16) and Drive startup (32).
  return ((profile & 4U) != 0U) && ((profile & ~uint16_t{63U}) == 0U);
}

// Native capability is additionally required. RELEASE param1 advertises none.
inline constexpr AolSafetyProfile RIVIAN_AOL_PROFILE{33U, rivian_aol_param, true};
