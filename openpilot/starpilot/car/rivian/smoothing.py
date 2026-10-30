"""Rivian Extreme-harness crawl-speed lateral smoothing, shared by modeld and Controls."""
import math

import numpy as np
from opendbc.car.rivian.values import RivianFlags

LAT_SMOOTH_BP = [2.0, 8.0]
RIVIAN_LAT_SMOOTH_MAX = 0.4


def maximum(cp) -> float:
  try:
    return RIVIAN_LAT_SMOOTH_MAX if cp.brand == 'rivian' and int(cp.flags) & RivianFlags.ANGLE_HARNESS else 0.0
  except (AttributeError, TypeError, ValueError):
    return 0.0


def seconds(speed: float, smooth_maximum: float) -> float:
  if smooth_maximum <= 0.0 or not math.isfinite(speed):
    return 0.0
  return float(np.interp(speed, LAT_SMOOTH_BP, [smooth_maximum, 0.0]))
