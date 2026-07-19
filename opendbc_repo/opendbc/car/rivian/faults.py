def get_steering_faults(angle_harness: bool, toi_fault: bool, eac_status: int, eac_error_code: int) -> tuple[bool, bool, bool]:
  if angle_harness:
    # The high-angle torque-request blip can transiently report ToiFlt. On the
    # angle harness, only an active EAC error should fault lateral control.
    return eac_status == 4, eac_status == 2 and eac_error_code != 0, eac_status == 2 and eac_error_code == 12

  return False, toi_fault or eac_error_code != 0, False
