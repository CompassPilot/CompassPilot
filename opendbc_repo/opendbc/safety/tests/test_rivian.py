#!/usr/bin/env python3
import unittest
from opendbc.car.structs import CarParams
from opendbc.safety.tests.libsafety import libsafety_py
import opendbc.safety.tests.common as common
from opendbc.safety.tests.common import CANPackerSafety
from opendbc.car.rivian.values import RivianSafetyFlags
from opendbc.car.rivian.riviancan import checksum as _checksum
from opendbc.safety import ALTERNATIVE_EXPERIENCE


def checksum(msg):
  addr, dat, bus = msg
  ret = bytearray(dat)

  # ESP_Status
  if addr == 0x208:
    ret[0] = _checksum(ret[1:], 0x1D, 0xB1)
  elif addr == 0x150:
    ret[0] = _checksum(ret[1:], 0x1D, 0x9A)
  elif addr == 0x162:
    ret[0] = _checksum(ret[1:], 0x1D, 0xD1)

  return addr, ret, bus


class TestRivianSafetyBase(common.CarSafetyTest, common.DriverTorqueSteeringSafetyTest, common.SteerRequestCutSafetyTest,
                           common.LongitudinalAccelSafetyTest, common.VehicleSpeedSafetyTest):

  TX_MSGS = [[0x120, 0], [0x321, 2], [0x162, 2]]
  RELAY_MALFUNCTION_ADDRS = {0: (0x120,), 2: (0x321, 0x162)}
  FWD_BLACKLISTED_ADDRS = {0: [0x321, 0x162], 2: [0x120]}

  MAX_TORQUE_LOOKUP = [9, 25, 27], [385, 295, 275]
  DYNAMIC_MAX_TORQUE = True
  MAX_RATE_UP = 3
  MAX_RATE_DOWN = 5

  MAX_RT_DELTA = 125

  DRIVER_TORQUE_ALLOWANCE = 100
  DRIVER_TORQUE_FACTOR = 2
  MIN_VALID_STEERING_FRAMES = 89
  MAX_INVALID_STEERING_FRAMES = 2

  cnt_speed = 0
  cnt_speed_2 = 0

  def _torque_driver_msg(self, torque):
    values = {"EPAS_TorsionBarTorque": torque / 100.0}
    return self.packer.make_can_msg_safety("EPAS_SystemStatus", 0, values)

  def _torque_cmd_msg(self, torque, steer_req=1):
    values = {"ACM_lkaStrToqReq": torque, "ACM_lkaActToi": steer_req}
    return self.packer.make_can_msg_safety("ACM_lkaHbaCmd", 0, values)

  def _speed_msg(self, speed, quality_flag=True):
    values = {"ESP_Vehicle_Speed": speed * 3.6, "ESP_Status_Counter": self.cnt_speed % 15,
              "ESP_Vehicle_Speed_Q": 1 if quality_flag else 0}
    self.__class__.cnt_speed += 1
    return self.packer.make_can_msg_safety("ESP_Status", 0, values, fix_checksum=checksum)

  def _speed_msg_2(self, speed, quality_flag=True):
    # Rivian has a dynamic max torque limit based on speed, so it checks two sources
    return self._user_gas_msg(0, speed, quality_flag)

  def _user_brake_msg(self, brake):
    values = {"iBESP2_BrakePedalApplied": brake}
    return self.packer.make_can_msg_safety("iBESP2", 0, values)

  def _user_gas_msg(self, gas, speed=0, quality_flag=True):
    values = {"VDM_AcceleratorPedalPosition": gas, "VDM_VehicleSpeed": speed * 3.6,
              "VDM_PropStatus_Counter": self.cnt_speed_2 % 15, "VDM_VehicleSpeedQ": 1 if quality_flag else 0}
    self.__class__.cnt_speed_2 += 1
    return self.packer.make_can_msg_safety("VDM_PropStatus", 0, values, fix_checksum=checksum)

  def _pcm_status_msg(self, enable):
    values = {"ACM_FeatureStatus": enable, "ACM_Unkown1": 1}
    return self.packer.make_can_msg_safety("ACM_Status", 2, values)

  def _accel_msg(self, accel: float):
    values = {"ACM_AccelerationRequest": accel}
    return self.packer.make_can_msg_safety("ACM_longitudinalRequest", 0, values)

  def test_wheel_touch(self):
    # For hiding hold wheel alert on engage
    for controls_allowed in (True, False):
      self.safety.set_controls_allowed(controls_allowed)
      values = {
        "SCCM_WheelTouch_HandsOn": 1 if controls_allowed else 0,
        "SCCM_WheelTouch_CapacitiveValue": 100 if controls_allowed else 0,
        "SETME_X52": 100,
      }
      self.assertTrue(self._tx(self.packer.make_can_msg_safety("SCCM_WheelTouch", 2, values)))

  def test_rx_hook(self):
    # checksum, counter, and quality flag checks
    for quality_flag in (True, False):
      for msg_type in ("speed", "speed_2"):
        self.safety.set_controls_allowed(True)
        # send multiple times to verify counter checks
        for _ in range(10):
          if msg_type == "speed":
            msg = self._speed_msg(0, quality_flag=quality_flag)
          elif msg_type == "speed_2":
            msg = self._speed_msg_2(0, quality_flag=quality_flag)

          self.assertEqual(quality_flag, self._rx(msg))
          self.assertEqual(quality_flag, self.safety.get_controls_allowed())

        # Mess with checksum to make it fail
        msg[0].data[0] = 0xff
        self.assertFalse(self._rx(msg))
        self.assertFalse(self.safety.get_controls_allowed())

class TestRivianStockSafety(TestRivianSafetyBase):

  LONGITUDINAL = False

  def setUp(self):
    self.packer = CANPackerSafety("rivian_primary_actuator")
    self.safety = libsafety_py.libsafety
    self.safety.set_safety_hooks(CarParams.SafetyModel.rivian, 0)
    self.safety.init_tests()

  def test_adas_status(self):
    # For canceling stock ACC
    for controls_allowed in (True, False):
      self.safety.set_controls_allowed(controls_allowed)
      for interface_status in range(4):
        values = {"VDM_AdasInterfaceStatus": interface_status}
        self.assertTrue(self._tx(self.packer.make_can_msg_safety("VDM_AdasSts", 2, values)))


class TestRivianLongitudinalSafety(TestRivianSafetyBase):

  TX_MSGS = [[0x120, 0], [0x321, 2], [0x160, 0]]
  RELAY_MALFUNCTION_ADDRS = {0: (0x120, 0x160), 2: (0x321,)}
  FWD_BLACKLISTED_ADDRS = {0: [0x321], 2: [0x120, 0x160]}

  def setUp(self):
    self.packer = CANPackerSafety("rivian_primary_actuator")
    self.safety = libsafety_py.libsafety
    self.safety.set_safety_hooks(CarParams.SafetyModel.rivian, RivianSafetyFlags.LONG_CONTROL)
    self.safety.init_tests()


class TestRivianMADSSafety(unittest.TestCase):
  TX_MSGS = []

  def setUp(self):
    self.packer = CANPackerSafety("rivian_primary_actuator")
    self.safety = libsafety_py.libsafety
    self.cnt_adas = 0
    self.cnt_prop = 0

  def _set_mode(self, brake_remains_active=False):
    flags = RivianSafetyFlags.MADS_LATERAL
    if brake_remains_active:
      flags |= RivianSafetyFlags.MADS_BRAKE_REMAINS_ACTIVE
    self.safety.set_safety_hooks(CarParams.SafetyModel.rivian, flags)
    self.safety.init_tests()
    self.safety.set_alternative_experience(ALTERNATIVE_EXPERIENCE.ALWAYS_ON_LATERAL)
    self.cnt_adas = 0
    self.cnt_prop = 0

  def _rx(self, msg):
    return self.safety.safety_rx_hook(msg)

  def _stalk_msg(self, request, *, counter=None, bus=0):
    if counter is None:
      counter = self.cnt_adas % 15
      self.cnt_adas += 1
    values = {"VDM_UserAdasRequest": request, "VDM_AdasStatus_Counter": counter}
    return self.packer.make_can_msg_safety("VDM_AdasSts", bus, values, fix_checksum=checksum)

  def _gear_msg(self, gear):
    values = {
      "VDM_Prndl_Status": gear,
      "VDM_PropStatus_Counter": self.cnt_prop % 15,
      "VDM_VehicleSpeedQ": 1,
    }
    self.cnt_prop += 1
    return self.packer.make_can_msg_safety("VDM_PropStatus", 0, values, fix_checksum=checksum)

  def _acc_msg(self, enabled):
    values = {"ACM_FeatureStatus": 1 if enabled else 0, "ACM_Unkown1": 1}
    return self.packer.make_can_msg_safety("ACM_Status", 2, values)

  def _brake_msg(self, pressed):
    return self.packer.make_can_msg_safety("iBESP2", 0, {"iBESP2_BrakePedalApplied": pressed})

  def test_initial_state_and_half_up_toggle(self):
    self._set_mode()
    self.assertFalse(self.safety.get_lkas_on())
    self.assertFalse(self.safety.get_aol_allowed())

    self.assertTrue(self._rx(self._stalk_msg(1)))
    self.assertFalse(self.safety.get_lkas_on())
    self.assertTrue(self._rx(self._acc_msg(False)))
    self.assertTrue(self.safety.get_lkas_on())
    self.assertTrue(self.safety.get_aol_allowed())
    self.assertTrue(self._rx(self._stalk_msg(0)))

    self.assertTrue(self._rx(self._stalk_msg(1)))
    self.assertTrue(self._rx(self._acc_msg(False)))
    self.assertTrue(self._rx(self._stalk_msg(0)))
    self.assertFalse(self.safety.get_lkas_on())

  def test_full_up_cancels_pending_half_up_and_clears_lateral(self):
    self._set_mode()
    self.assertTrue(self._rx(self._stalk_msg(1)))
    self.assertTrue(self._rx(self._stalk_msg(2)))
    self.assertFalse(self.safety.get_lkas_on())
    self.assertTrue(self._rx(self._stalk_msg(0)))

    self.assertTrue(self._rx(self._acc_msg(True)))
    self.assertTrue(self.safety.get_lkas_on())
    self.assertTrue(self._rx(self._stalk_msg(2)))
    self.assertFalse(self.safety.get_lkas_on())

  def test_acc_enables_lateral_and_cancel_preserves_it(self):
    self._set_mode()
    self.assertTrue(self._rx(self._acc_msg(True)))
    self.assertTrue(self.safety.get_lkas_on())
    self.assertTrue(self._rx(self._acc_msg(False)))
    self.assertTrue(self.safety.get_lkas_on())

    # UP_1 is the native ACC-cancel gesture and must not toggle MADS.
    self.assertTrue(self._rx(self._acc_msg(True)))
    self.assertTrue(self._rx(self._stalk_msg(1)))
    self.assertTrue(self._rx(self._acc_msg(False)))
    self.assertTrue(self._rx(self._stalk_msg(0)))
    self.assertTrue(self.safety.get_lkas_on())

  def test_non_drive_gears_clear_and_drive_does_not_reenable(self):
    for gear in (0, 1, 2, 3):
      self._set_mode(brake_remains_active=True)
      self.assertTrue(self._rx(self._acc_msg(True)))
      self.assertTrue(self.safety.get_lkas_on())
      self.assertTrue(self._rx(self._gear_msg(gear)))
      self.assertFalse(self.safety.get_lkas_on())
      self.assertTrue(self._rx(self._gear_msg(4)))
      self.assertFalse(self.safety.get_lkas_on())

  def test_brake_behavior(self):
    for brake_remains_active in (False, True):
      self._set_mode(brake_remains_active)
      self.assertTrue(self._rx(self._acc_msg(True)))
      self.assertTrue(self._rx(self._brake_msg(True)))
      self.assertEqual(self.safety.get_lkas_on(), brake_remains_active)
      self.assertFalse(self.safety.get_controls_allowed())

  def test_stalk_checksum_counter_and_bus_validation(self):
    self._set_mode()
    valid = self._stalk_msg(1)
    valid[0].data[0] ^= 0xFF
    self.assertFalse(self._rx(valid))
    self.assertFalse(self.safety.get_lkas_on())

    self._set_mode()
    for i in range(common.MAX_WRONG_COUNTERS):
      should_accept = i + 1 < common.MAX_WRONG_COUNTERS
      self.assertEqual(self._rx(self._stalk_msg(0, counter=0)), should_accept)
    self.assertFalse(self.safety.get_lkas_on())

    self._set_mode()
    self.assertTrue(self._rx(self._stalk_msg(1, bus=1)))
    self.assertFalse(self.safety.get_lkas_on())

  def test_mads_composes_with_rivian_harness_flags(self):
    for harness_flags in (
      RivianSafetyFlags(0),
      RivianSafetyFlags.LONG_CONTROL,
    ):
      flags = RivianSafetyFlags.MADS_LATERAL | harness_flags
      self.assertEqual(self.safety.set_safety_hooks(CarParams.SafetyModel.rivian, flags), 0)
      self.safety.init_tests()
      self.safety.set_alternative_experience(ALTERNATIVE_EXPERIENCE.ALWAYS_ON_LATERAL)
      self.assertTrue(self._rx(self._acc_msg(True)))
      self.assertTrue(self.safety.get_lkas_on())


if __name__ == "__main__":
  unittest.main()
