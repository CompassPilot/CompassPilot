#!/usr/bin/env python3
import unittest
import numpy as np

from opendbc.car import STD_CARGO_KG, scale_rot_inertia, scale_tire_stiffness
from opendbc.car.lateral import get_max_angle_delta_vm, get_max_angle_vm
from opendbc.car.structs import CarParams
from opendbc.car.vehicle_model import VehicleModel
from opendbc.car.rivian.values import CarControllerParams, MAX_ALLOWED_LATERAL_ACCEL
from opendbc.safety.tests.libsafety import libsafety_py
import opendbc.safety.tests.common as common
from opendbc.safety.tests.common import CANPackerSafety
from opendbc.car.rivian.values import RivianSafetyFlags
from opendbc.car.rivian.riviancan import checksum as _checksum
from opendbc.safety import ALTERNATIVE_EXPERIENCE


def get_safety_vm():
  CP = CarParams()
  CP.mass = 3206. + STD_CARGO_KG
  CP.wheelbase = 3.08
  CP.centerToFront = CP.wheelbase * 0.5
  CP.steerRatio = 15.2
  CP.steerRatioRear = 0.
  CP.rotationalInertia = scale_rot_inertia(CP.mass, CP.wheelbase)
  CP.tireStiffnessFront, CP.tireStiffnessRear = scale_tire_stiffness(CP.mass, CP.wheelbase, CP.centerToFront, 1.0)
  return VehicleModel(CP)


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

  ANGLE = False

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

  def test_angle_messages_require_harness_flag(self):
    if self.ANGLE:
      raise unittest.SkipTest("Angle harness safety configuration")
    self.assertFalse(self._tx(self.packer.make_can_msg_safety("ACM_SteeringControl", 0, {})))
    self.assertFalse(self._tx(self.packer.make_can_msg_safety("ACM_Status", 0, {})))

  def test_toi_blip_freeze_resume(self):
    """A feedback-driven ToI release may take more than two zero-command frames.
    Panda must retain the pre-release reference so torque can resume immediately."""
    self.safety.init_tests()
    self.safety.set_timer(self.MIN_VALID_STEERING_RT_INTERVAL)
    self.safety.set_controls_allowed(True)
    self._set_prev_torque(self.MAX_TORQUE)

    for _ in range(self.MIN_VALID_STEERING_FRAMES):
      self.assertTrue(self._tx(self._torque_cmd_msg(self.MAX_TORQUE, steer_req=1)))

    for _ in range(5):
      self.assertTrue(self._tx(self._torque_cmd_msg(0, steer_req=0)))

    self.assertTrue(self._tx(self._torque_cmd_msg(self.MAX_TORQUE, steer_req=1)))

  def test_toi_torque_reference_resets_while_controls_disallowed(self):
    self.safety.init_tests()
    self.safety.set_controls_allowed(True)
    self._set_prev_torque(self.MAX_TORQUE)

    self.safety.set_controls_allowed(False)
    self.assertTrue(self._tx(self._torque_cmd_msg(0, steer_req=0)))

    self.safety.set_controls_allowed(True)
    self.assertFalse(self._tx(self._torque_cmd_msg(self.MAX_TORQUE, steer_req=1)))


class TestRivianAngleSafetyBase(TestRivianSafetyBase, common.AngleSteeringSafetyTest):
  ANGLE = True
  LONGITUDINAL = False
  TX_MSGS = [[0x100, 0], [0x110, 0], [0x120, 0], [0x321, 2], [0x162, 2]]
  RELAY_MALFUNCTION_ADDRS = {0: (0x100, 0x110, 0x120), 2: (0x321, 0x162)}
  FWD_BLACKLISTED_ADDRS = {0: [0x321, 0x162], 2: [0x100, 0x110, 0x120]}

  STEER_ANGLE_MAX = 500
  DEG_TO_CAN = 10
  ANGLE_RATE_BP = None
  ANGLE_RATE_UP = None
  ANGLE_RATE_DOWN = None
  LATERAL_FREQUENCY = 100
  cnt_angle_cmd = 0

  def _get_steer_cmd_angle_max(self, speed):
    return get_max_angle_vm(max(speed, 1), self.VM, CarControllerParams)

  def _angle_cmd_msg(self, angle: float, enabled: bool, increment_timer: bool = True):
    values = {"ACM_SteeringAngleRequest": angle, "ACM_EacEnabled": enabled}
    if increment_timer:
      self.safety.set_timer(self.cnt_angle_cmd * int(1e6 / self.LATERAL_FREQUENCY))
      self.__class__.cnt_angle_cmd += 1
    return self.packer.make_can_msg_safety("ACM_SteeringControl", 0, values)

  def _angle_meas_msg(self, angle: float):
    return self.packer.make_can_msg_safety("EPAS_AdasStatus", 0, {"EPAS_InternalSas": angle})

  def test_angle_cmd_when_enabled(self):
    # The VM-based lateral acceleration and jerk limits are exercised by the
    # dedicated tests below; keep this common-suite hook explicit rather than
    # silently skipping the enabled-angle coverage.
    self._check_lateral_accel_limit()
    self._check_lateral_jerk_limit()

  def test_product_lateral_accel_limit(self):
    self.assertLessEqual(CarControllerParams.ANGLE_LIMITS.MAX_LATERAL_ACCEL, MAX_ALLOWED_LATERAL_ACCEL)

  def _can_to_deg(self, can_value):
    return can_value / self.DEG_TO_CAN

  @staticmethod
  def _round_speed(speed):
    speed_kph_can = round((speed + 1) * 3.6 / 0.01) * 0.01
    stored = round(speed_kph_can / 3.6 * 1000)
    return max(stored / 1000.0 - 1.0, 1.0)

  def _check_lateral_accel_limit(self):
    for speed in np.linspace(0, 40, 100):
      speed = max(self._round_speed(speed), 1)
      for sign in (-1, 1):
        self.safety.set_controls_allowed(True)
        self._reset_speed_measurement(speed + 1)
        max_angle_can = int(get_max_angle_vm(speed, self.VM, CarControllerParams) * self.DEG_TO_CAN) + 1
        max_angle_can = min(max_angle_can, self.STEER_ANGLE_MAX * self.DEG_TO_CAN)

        self.safety.set_desired_angle_last(max_angle_can * sign)
        self.assertTrue(self._tx(self._angle_cmd_msg(self._can_to_deg(max_angle_can) * sign, True)))

        above_can = max_angle_can + 1
        above_deg = self._can_to_deg(above_can) * sign
        self._tx(self._angle_cmd_msg(above_deg, True))
        should_tx = above_can > self.STEER_ANGLE_MAX * self.DEG_TO_CAN
        self.assertEqual(should_tx, self._tx(self._angle_cmd_msg(above_deg, True)))

  def _check_lateral_jerk_limit(self):
    for speed in np.linspace(0, 40, 100):
      speed = max(self._round_speed(speed), 1)
      for sign in (-1, 1):
        self.safety.set_controls_allowed(True)
        self._reset_speed_measurement(speed + 1)
        self._tx(self._angle_cmd_msg(0, True))
        max_delta_can = int(get_max_angle_delta_vm(speed, self.VM, CarControllerParams) * self.DEG_TO_CAN) + 1

        self.assertTrue(self._tx(self._angle_cmd_msg(self._can_to_deg(max_delta_can) * sign, True)))
        self.assertTrue(self._tx(self._angle_cmd_msg(self._can_to_deg(max_delta_can) * sign, True)))
        self.assertTrue(self._tx(self._angle_cmd_msg(0, True)))

        above_can = max_delta_can + 1
        self.assertFalse(self._tx(self._angle_cmd_msg(self._can_to_deg(above_can) * sign, True)))
        self.safety.set_desired_angle_last(above_can * sign)
        self.assertTrue(self._tx(self._angle_cmd_msg(self._can_to_deg(above_can) * sign, True)))
        self.assertFalse(self._tx(self._angle_cmd_msg(0, True)))
        self.assertTrue(self._tx(self._angle_cmd_msg(0, True)))


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


class TestRivianAngleSafety(TestRivianAngleSafetyBase):
  def setUp(self):
    self.VM = get_safety_vm()
    self.packer = CANPackerSafety("rivian_primary_actuator")
    self.safety = libsafety_py.libsafety
    self.safety.set_safety_hooks(CarParams.SafetyModel.rivian, RivianSafetyFlags.ANGLE_CONTROL)
    self.safety.init_tests()


class TestRivianAOLSafety(unittest.TestCase):
  TX_MSGS = []

  def setUp(self):
    self.packer = CANPackerSafety("rivian_primary_actuator")
    self.safety = libsafety_py.libsafety
    self.cnt_adas = 0
    self.cnt_prop = 0

  def _set_mode(self, brake_remains_active=False, stalk_toggle=True, start_enabled=False):
    flags = RivianSafetyFlags.AOL_LATERAL
    if brake_remains_active:
      flags |= RivianSafetyFlags.AOL_BRAKE_REMAINS_ACTIVE
    if stalk_toggle:
      flags |= RivianSafetyFlags.AOL_STALK_TOGGLE
    if start_enabled:
      flags |= RivianSafetyFlags.AOL_START_ENABLED
    self.safety.set_safety_hooks(CarParams.SafetyModel.rivian, flags)
    self.safety.init_tests()
    self.safety.set_alternative_experience(ALTERNATIVE_EXPERIENCE.ALWAYS_ON_LATERAL)
    self.cnt_adas = 0
    self.cnt_prop = 0

  def _rx(self, msg):
    return self.safety.safety_rx_hook(msg)

  def _tx(self, msg):
    return self.safety.safety_tx_hook(msg)

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
    return self._feature_status_msg(1 if enabled else 0)

  def _feature_status_msg(self, feature_status):
    values = {"ACM_FeatureStatus": feature_status, "ACM_Unkown1": 1}
    return self.packer.make_can_msg_safety("ACM_Status", 2, values)

  def _brake_msg(self, pressed):
    return self.packer.make_can_msg_safety("iBESP2", 0, {"iBESP2_BrakePedalApplied": pressed})

  def _torque_cmd_msg(self, torque=0, steer_req=True):
    values = {"ACM_lkaStrToqReq": torque, "ACM_lkaActToi": steer_req}
    return self.packer.make_can_msg_safety("ACM_lkaHbaCmd", 0, values)

  def _angle_cmd_msg(self, angle=0, active=True):
    values = {"ACM_SteeringAngleRequest": angle, "ACM_EacEnabled": active}
    return self.packer.make_can_msg_safety("ACM_SteeringControl", 0, values)

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

    # UP_1 is the native ACC-cancel gesture and must not toggle AOL.
    self.assertTrue(self._rx(self._acc_msg(True)))
    self.assertTrue(self._rx(self._stalk_msg(1)))
    self.assertTrue(self._rx(self._acc_msg(False)))
    self.assertTrue(self._rx(self._stalk_msg(0)))
    self.assertTrue(self.safety.get_lkas_on())

  def test_unavailable_feature_status_clears_lateral(self):
    for feature_status in range(2, 8):
      self._set_mode()
      self.assertTrue(self._rx(self._acc_msg(True)))
      self.assertTrue(self.safety.get_lkas_on())
      self.assertTrue(self.safety.get_aol_allowed())

      self.assertTrue(self._rx(self._feature_status_msg(feature_status)))
      self.assertFalse(self.safety.get_lkas_on())
      self.assertFalse(self.safety.get_aol_allowed())

      # Returning to standby only restores availability, not the AOL latch.
      self.assertTrue(self._rx(self._acc_msg(False)))
      self.assertFalse(self.safety.get_lkas_on())
      self.assertFalse(self.safety.get_aol_allowed())

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

  def test_half_up_requires_explicit_stalk_mapping(self):
    self._set_mode(stalk_toggle=False)
    self.assertTrue(self._rx(self._stalk_msg(1)))
    self.assertTrue(self._rx(self._acc_msg(False)))
    self.assertFalse(self.safety.get_lkas_on())

    self.assertTrue(self._rx(self._acc_msg(True)))
    self.assertTrue(self._rx(self._stalk_msg(2)))
    self.assertFalse(self.safety.get_lkas_on())

  def test_start_enabled_arms_once_when_drive_ready(self):
    self._set_mode(start_enabled=True)
    self.assertFalse(self.safety.get_lkas_on())

    self.assertTrue(self._rx(self._acc_msg(False)))
    self.assertFalse(self.safety.get_lkas_on())
    self.assertTrue(self._rx(self._gear_msg(4)))
    self.assertTrue(self.safety.get_lkas_on())

    self.assertTrue(self._rx(self._stalk_msg(2)))
    self.assertFalse(self.safety.get_lkas_on())
    self.assertTrue(self._rx(self._acc_msg(False)))
    self.assertTrue(self._rx(self._gear_msg(4)))
    self.assertFalse(self.safety.get_lkas_on())

  def test_start_off_ignores_availability_until_engagement(self):
    self._set_mode(start_enabled=False)
    self.assertTrue(self._rx(self._acc_msg(False)))
    self.assertTrue(self._rx(self._gear_msg(4)))
    self.assertFalse(self.safety.get_lkas_on())
    self.assertTrue(self._rx(self._acc_msg(True)))
    self.assertTrue(self.safety.get_lkas_on())

  def test_live_aol_torque_request_rearms_with_physical_gates(self):
    self._set_mode(start_enabled=False)
    self.assertTrue(self._rx(self._acc_msg(False)))
    self.assertTrue(self._rx(self._gear_msg(4)))
    self.assertFalse(self.safety.get_lkas_on())

    self.assertTrue(self._tx(self._torque_cmd_msg()))
    self.assertTrue(self.safety.get_lkas_on())
    self.assertTrue(self.safety.get_aol_allowed())

    self.assertTrue(self._rx(self._stalk_msg(2)))
    self.assertFalse(self.safety.get_lkas_on())
    # A zero-torque request is harmless and may pass the common torque check,
    # but full-up must still prevent it from re-arming AOL.
    self.assertTrue(self._tx(self._torque_cmd_msg()))
    self.assertFalse(self.safety.get_lkas_on())

    self.assertTrue(self._rx(self._stalk_msg(0)))
    self.assertTrue(self._tx(self._torque_cmd_msg()))
    self.assertTrue(self.safety.get_lkas_on())

  def test_live_aol_angle_request_rearms_angle_harness(self):
    flags = RivianSafetyFlags.AOL_LATERAL | RivianSafetyFlags.ANGLE_CONTROL
    self.assertEqual(self.safety.set_safety_hooks(CarParams.SafetyModel.rivian, flags), 0)
    self.safety.init_tests()
    self.safety.set_alternative_experience(ALTERNATIVE_EXPERIENCE.ALWAYS_ON_LATERAL)
    self.assertTrue(self._rx(self._acc_msg(False)))
    self.assertTrue(self._rx(self._gear_msg(4)))

    self.assertTrue(self._tx(self._angle_cmd_msg()))
    self.assertTrue(self.safety.get_lkas_on())
    self.assertTrue(self.safety.get_aol_allowed())

  def test_aol_composes_with_all_rivian_harness_flags(self):
    for harness_flags in (
      RivianSafetyFlags(0),
      RivianSafetyFlags.ANGLE_CONTROL,
      RivianSafetyFlags.LONG_CONTROL,
      RivianSafetyFlags.ANGLE_CONTROL | RivianSafetyFlags.LONG_CONTROL,
    ):
      flags = RivianSafetyFlags.AOL_LATERAL | harness_flags
      self.assertEqual(self.safety.set_safety_hooks(CarParams.SafetyModel.rivian, flags), 0)
      self.safety.init_tests()
      self.safety.set_alternative_experience(ALTERNATIVE_EXPERIENCE.ALWAYS_ON_LATERAL)
      self.assertTrue(self._rx(self._acc_msg(True)))
      self.assertTrue(self.safety.get_lkas_on())


class TestRivianAngleLongitudinalSafety(TestRivianAngleSafetyBase):
  LONGITUDINAL = True
  TX_MSGS = [[0x100, 0], [0x110, 0], [0x120, 0], [0x321, 2], [0x160, 0]]
  RELAY_MALFUNCTION_ADDRS = {0: (0x100, 0x110, 0x120, 0x160), 2: (0x321,)}
  FWD_BLACKLISTED_ADDRS = {0: [0x321], 2: [0x100, 0x110, 0x120, 0x160]}

  def setUp(self):
    self.VM = get_safety_vm()
    self.packer = CANPackerSafety("rivian_primary_actuator")
    self.safety = libsafety_py.libsafety
    flags = RivianSafetyFlags.ANGLE_CONTROL | RivianSafetyFlags.LONG_CONTROL
    self.safety.set_safety_hooks(CarParams.SafetyModel.rivian, flags)
    self.safety.init_tests()


if __name__ == "__main__":
  unittest.main()
