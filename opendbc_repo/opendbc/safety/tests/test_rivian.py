#!/usr/bin/env python3
import unittest
import numpy as np

from opendbc.car.lateral import get_max_angle_delta_vm, get_max_angle_vm
from opendbc.car.rivian.ext_controller import get_safety_CP
from opendbc.car.rivian.values import CAR, CarControllerParams, RivianSafetyFlags
from opendbc.car.structs import CarParams
from opendbc.car.vehicle_model import VehicleModel
from opendbc.safety.tests.libsafety import libsafety_py
import opendbc.safety.tests.common as common
from opendbc.safety.tests.common import CANPackerSafety


class TestRivianSafetyBase(common.CarSafetyTest, common.DriverTorqueSteeringSafetyTest, common.SteerRequestCutSafetyTest,
                           common.LongitudinalAccelSafetyTest, common.VehicleSpeedSafetyTest):

  DBC = "rivian_primary_actuator"
  SAFETY_MODEL = CarParams.SafetyModel.rivian

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

  # Angle limits (VM-based, no simple breakpoint rates)
  STEER_ANGLE_MAX = 360
  DEG_TO_CAN = 10
  ANGLE_RATE_BP = None
  ANGLE_RATE_UP = None
  ANGLE_RATE_DOWN = None
  LATERAL_FREQUENCY = 100

  cnt_speed = 0
  cnt_speed_2 = 0
  cnt_torque = 0
  cnt_brake = 0
  cnt_pcm = 0
  cnt_angle = 0
  cnt_angle_cmd = 0

  def setUp(self):
    self.VM = VehicleModel(get_safety_CP())
    super().setUp()

  def _get_steer_cmd_angle_max(self, speed):
    return get_max_angle_vm(max(speed, 1), self.VM, CarControllerParams)

  def _angle_cmd_msg(self, angle: float, enabled: bool, increment_timer: bool = True):
    values = {"ACM_SteeringAngleRequest": angle, "ACM_EacEnabled": enabled}
    if increment_timer:
      self.safety.set_timer(self.cnt_angle_cmd * int(1e6 / self.LATERAL_FREQUENCY))
      self.__class__.cnt_angle_cmd += 1
    return self.packer.make_can_msg_safety("ACM_SteeringControl", 0, values)

  def _angle_meas_msg(self, angle: float):
    values = {"EPAS_InternalSas": angle, "EPAS_AdasStatus_Counter": self.cnt_angle % 15}
    self.__class__.cnt_angle += 1
    return self.packer.make_can_msg_safety("EPAS_AdasStatus", 0, values)

  def _torque_driver_msg(self, torque):
    values = {"EPAS_TorsionBarTorque": torque / 100.0, "EPAS_SystemStatus_Counter": self.cnt_torque % 15}
    self.__class__.cnt_torque += 1
    return self.packer.make_can_msg_safety("EPAS_SystemStatus", 0, values)

  def _torque_cmd_msg(self, torque, steer_req=1):
    values = {"ACM_lkaStrToqReq": torque, "ACM_lkaActToi": steer_req}
    return self.packer.make_can_msg_safety("ACM_lkaHbaCmd", 0, values)

  def _speed_msg(self, speed, quality_flag=True):
    values = {"ESP_Vehicle_Speed": speed * 3.6, "ESP_Status_Counter": self.cnt_speed % 15,
              "ESP_Vehicle_Speed_Q": 1 if quality_flag else 0}
    self.__class__.cnt_speed += 1
    return self.packer.make_can_msg_safety("ESP_Status", 0, values)

  def _speed_msg_2(self, speed, quality_flag=True):
    # Rivian has a dynamic max torque limit based on speed, so it checks two sources
    return self._user_gas_msg(0, speed, quality_flag)

  def _user_brake_msg(self, brake, quality_flag=True):
    values = {"iBESP2_BrakePedalApplied": brake, "iBESP2_BrakePedalApplied_Q": 1 if quality_flag else 2,
              "iBESP2_AliveCounter": self.cnt_brake % 15}
    self.__class__.cnt_brake += 1
    return self.packer.make_can_msg_safety("iBESP2", 0, values)

  def _user_gas_msg(self, gas, speed=0, quality_flag=True):
    values = {"VDM_AcceleratorPedalPosition": gas, "VDM_VehicleSpeed": speed * 3.6,
              "VDM_PropStatus_Counter": self.cnt_speed_2 % 15, "VDM_VehicleSpeedQ": 1 if quality_flag else 0}
    self.__class__.cnt_speed_2 += 1
    return self.packer.make_can_msg_safety("VDM_PropStatus", 0, values)

  def _pcm_status_msg(self, enable):
    values = {"ACM_FeatureStatus": enable, "ACM_Unkown1": 1, "ACM_Status_Counter": self.cnt_pcm % 15}
    self.__class__.cnt_pcm += 1
    return self.packer.make_can_msg_safety("ACM_Status", 2, values)

  def _accel_msg(self, accel: float):
    values = {"ACM_AccelerationRequest": accel}
    return self.packer.make_can_msg_safety("ACM_longitudinalRequest", 0, values)

  def _can_to_deg(self, can_val):
    return can_val / self.DEG_TO_CAN

  @staticmethod
  def _round_speed(speed):
    """Round speed through CAN encoding to match what safety computes after fudge"""
    speed_kph_can = round((speed + 1) * 3.6 / 0.01) * 0.01
    stored = round(speed_kph_can / 3.6 * 1000)
    return max(stored / 1000.0 - 1.0, 1.0)

  def test_toi_feedback_release_preserves_torque_reference(self):
    self.safety.set_timer(1_000_000)
    self.safety.set_controls_allowed(True)
    self._set_prev_torque(self.MAX_TORQUE)

    for _ in range(5):
      self.assertTrue(self._tx(self._torque_cmd_msg(0, steer_req=0)))

    # Rearm holds request high with zero torque until EPAS overlay acks.
    for _ in range(5):
      self.assertTrue(self._tx(self._torque_cmd_msg(0, steer_req=1)))

    self.assertTrue(self._tx(self._torque_cmd_msg(self.MAX_TORQUE, steer_req=1)))

  def test_toi_torque_reference_resets_while_controls_disallowed(self):
    self.safety.init_tests()
    self.safety.set_controls_allowed(True)
    self._set_prev_torque(self.MAX_TORQUE)

    self.safety.set_controls_allowed(False)
    self.assertTrue(self._tx(self._torque_cmd_msg(0, steer_req=0)))

    self.safety.set_controls_allowed(True)
    self.assertFalse(self._tx(self._torque_cmd_msg(self.MAX_TORQUE, steer_req=1)))

  def test_angle_messages_require_harness_flag(self):
    if self.ANGLE:
      raise unittest.SkipTest("Angle harness safety configuration")
    self.safety.set_controls_allowed(True)
    self.assertFalse(self._tx(self.packer.make_can_msg_safety("ACM_SteeringControl", 0, {})))
    self.assertFalse(self._tx(self.packer.make_can_msg_safety("ACM_Status", 0, {})))

  def test_wheel_touch(self):
    # For hiding hold wheel alert on engage
    for controls_allowed in (True, False):
      self.safety.set_controls_allowed(controls_allowed)
      values = {
        "SCCM_WheelTouch_HandsOn": 1 if controls_allowed else 0,
        "SCCM_WheelTouch_CapacitiveValue": 100 if controls_allowed else 0,
        "SCCM_WheelTouch_Calibration": 100,
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

    # The DBC defines counters for the remaining monitored RX messages too.
    for make_msg in (self._torque_driver_msg, self._user_brake_msg, self._pcm_status_msg):
      self._reset_safety_hooks()
      self.safety.set_controls_allowed(True)
      for _ in range(10):
        self.assertTrue(self._rx(make_msg(0) if make_msg == self._torque_driver_msg else make_msg(False)))

      msg = make_msg(0) if make_msg == self._torque_driver_msg else make_msg(False)
      msg[0].data[0] ^= 0xff
      self.assertFalse(self._rx(msg))
      self.assertFalse(self.safety.get_controls_allowed())

      if make_msg == self._user_brake_msg:
        self._reset_safety_hooks()
        self.safety.set_controls_allowed(True)
        self.assertFalse(self._rx(self._user_brake_msg(False, quality_flag=False)))
        self.assertFalse(self.safety.get_controls_allowed())

      # A single bad counter is tolerated, but repeated bad counters must disengage.
      self._reset_safety_hooks()
      self.safety.set_controls_allowed(True)
      for _ in range(7):
        msg = make_msg(0) if make_msg == self._torque_driver_msg else make_msg(False)
        msg[0].data[1] &= 0xf0
        valid = self._rx(msg)
      self.assertFalse(valid)
      self.assertFalse(self.safety.get_controls_allowed())


class TestRivianAngleSafetyBase(TestRivianSafetyBase, common.AngleSteeringSafetyTest):
  ANGLE = True
  SAFETY_PARAM = RivianSafetyFlags.ANGLE_CONTROL
  TX_MSGS = [[0x100, 0], [0x110, 0], [0x120, 0], [0x321, 2], [0x162, 2]]
  RELAY_MALFUNCTION_ADDRS = {0: (0x100, 0x110, 0x120), 2: (0x321, 0x162)}
  FWD_BLACKLISTED_ADDRS = {0: [0x321, 0x162], 2: [0x100, 0x110, 0x120]}

  def _reset_speed_measurement(self, speed):
    common.AngleSteeringSafetyTest._reset_speed_measurement(self, speed)

  def test_angle_cmd_when_enabled(self):
    # VM-based limits tested in test_lateral_accel_limit and test_lateral_jerk_limit
    pass

  def test_lateral_accel_limit(self):
    for speed in np.linspace(0, 40, 100):
      speed = max(self._round_speed(speed), 1)
      for sign in (-1, 1):
        self.safety.set_controls_allowed(True)
        self._reset_speed_measurement(speed + 1)

        # safety: max_angle_can = (max_angle_deg * DEG_TO_CAN) + 1
        max_angle_can = int(get_max_angle_vm(speed, self.VM, CarControllerParams) * self.DEG_TO_CAN) + 1
        max_angle_can = min(max_angle_can, self.STEER_ANGLE_MAX * self.DEG_TO_CAN)

        # at limit
        self.safety.set_desired_angle_last(max_angle_can * sign)
        self.assertTrue(self._tx(self._angle_cmd_msg(self._can_to_deg(max_angle_can) * sign, True)))

        # 1 unit above limit
        above_can = max_angle_can + 1
        above_deg = self._can_to_deg(above_can) * sign
        self._tx(self._angle_cmd_msg(above_deg, True))
        should_tx = above_can > self.STEER_ANGLE_MAX * self.DEG_TO_CAN
        self.assertEqual(should_tx, self._tx(self._angle_cmd_msg(above_deg, True)))

  def test_lateral_jerk_limit(self):
    for speed in np.linspace(0, 40, 100):
      speed = max(self._round_speed(speed), 1)
      for sign in (-1, 1):
        self.safety.set_controls_allowed(True)
        self._reset_speed_measurement(speed + 1)
        self._tx(self._angle_cmd_msg(0, True))

        # safety: max_delta_can = (max_delta_deg * DEG_TO_CAN) + 1
        max_delta_can = int(get_max_angle_delta_vm(speed, self.VM, CarControllerParams) * self.DEG_TO_CAN) + 1

        # within limits
        self.assertTrue(self._tx(self._angle_cmd_msg(self._can_to_deg(max_delta_can) * sign, True)))
        self.assertTrue(self._tx(self._angle_cmd_msg(self._can_to_deg(max_delta_can) * sign, True)))
        self.assertTrue(self._tx(self._angle_cmd_msg(0, True)))

        # too high rate
        above_can = max_delta_can + 1
        self.assertFalse(self._tx(self._angle_cmd_msg(self._can_to_deg(above_can) * sign, True)))

        # recover
        self.safety.set_desired_angle_last(round(self._can_to_deg(above_can) * sign * self.DEG_TO_CAN))
        self.assertTrue(self._tx(self._angle_cmd_msg(self._can_to_deg(above_can) * sign, True)))
        self.assertFalse(self._tx(self._angle_cmd_msg(0, True)))
        self.assertTrue(self._tx(self._angle_cmd_msg(0, True)))


class TestRivianStockSafety(TestRivianSafetyBase):

  LONGITUDINAL = False

  def test_adas_status(self):
    # For canceling stock ACC
    for controls_allowed in (True, False):
      self.safety.set_controls_allowed(controls_allowed)
      for interface_status in range(4):
        values = {"VDM_AdasInterfaceStatus": interface_status}
        self.assertTrue(self._tx(self.packer.make_can_msg_safety("VDM_AdasSts", 2, values)))


class TestRivianLongitudinalSafety(TestRivianSafetyBase):

  SAFETY_PARAM = RivianSafetyFlags.LONG_CONTROL

  TX_MSGS = [[0x120, 0], [0x321, 2], [0x160, 0], [0x162, 2]]
  RELAY_MALFUNCTION_ADDRS = {0: (0x120, 0x160), 2: (0x321, 0x162)}
  FWD_BLACKLISTED_ADDRS = {0: [0x321, 0x162], 2: [0x120, 0x160]}


class TestRivianAngleSafety(TestRivianAngleSafetyBase):
  LONGITUDINAL = False


class TestRivianAngleSafetyR1T(TestRivianAngleSafetyBase):
  LONGITUDINAL = False
  SAFETY_PARAM = RivianSafetyFlags.ANGLE_CONTROL | RivianSafetyFlags.R1T

  def setUp(self):
    super().setUp()
    self.VM = VehicleModel(get_safety_CP(CAR.RIVIAN_R1T))

  def test_r1t_angle_limit_exceeds_r1s(self):
    r1s_max = get_max_angle_vm(10.0, VehicleModel(get_safety_CP()), CarControllerParams)
    r1t_max = get_max_angle_vm(10.0, self.VM, CarControllerParams)
    self.assertGreater(r1t_max, r1s_max)


class TestRivianAngleLongitudinalSafety(TestRivianAngleSafetyBase):
  LONGITUDINAL = True
  SAFETY_PARAM = RivianSafetyFlags.ANGLE_CONTROL | RivianSafetyFlags.LONG_CONTROL
  TX_MSGS = [[0x100, 0], [0x110, 0], [0x120, 0], [0x321, 2], [0x160, 0], [0x162, 2]]
  RELAY_MALFUNCTION_ADDRS = {0: (0x100, 0x110, 0x120, 0x160), 2: (0x321, 0x162)}
  FWD_BLACKLISTED_ADDRS = {0: [0x321, 0x162], 2: [0x100, 0x110, 0x120, 0x160]}


class TestRivianHarnessAOLSafety(unittest.TestCase):
  """Extreme harness AOL latch behind the shared native AOL host protocol."""

  BASE_FLAGS = RivianSafetyFlags.AOL_LATERAL | RivianSafetyFlags.ANGLE_CONTROL

  def setUp(self):
    self.packer = CANPackerSafety("rivian_primary_actuator")
    self.safety = libsafety_py.libsafety
    self.safety.init_tests()
    self.safety.set_alternative_experience(32)
    self.cnt = 0

  def tearDown(self):
    self.safety.set_alternative_experience(0)

  def _hooks(self, flags=0, alternative=32):
    self.safety.set_alternative_experience(alternative)
    result = self.safety.set_safety_hooks(CarParams.SafetyModel.rivian, int(self.BASE_FLAGS | flags))
    self.safety.set_aol_test_heartbeat(True)
    return result

  def _feed(self, gear=4, feature=0, brake=False, user_request=0, eps_state=1, request=1):
    self.cnt += 1
    self.safety.set_timer(1_000_000 + self.cnt * 10_000)
    counter = self.cnt % 15
    msgs = (
      ("ESP_Status", 0, {"ESP_Vehicle_Speed": 0, "ESP_Status_Counter": counter, "ESP_Vehicle_Speed_Q": 1}),
      ("VDM_PropStatus", 0, {"VDM_Prndl_Status": gear, "VDM_PropStatus_Counter": counter, "VDM_VehicleSpeedQ": 1}),
      ("iBESP2", 0, {"iBESP2_BrakePedalApplied": brake, "iBESP2_BrakePedalApplied_Q": 1, "iBESP2_AliveCounter": counter}),
      ("EPAS_SystemStatus", 0, {"EPAS_SystemStatus_Counter": counter}),
      ("ACM_Status", 2, {"ACM_FeatureStatus": feature, "ACM_Unkown1": 1, "ACM_Status_Counter": counter}),
      ("EPAS_AdasStatus", 0, {"EPAS_AdasStatus_Counter": counter, "EPAS_EacStatus": eps_state}),
      ("VDM_AdasSts", 0, {"VDM_UserAdasRequest": user_request, "VDM_AdasStatus_Counter": counter}),
    )
    for name, bus, values in msgs:
      self.assertTrue(self.safety.safety_rx_hook(self.packer.make_can_msg_safety(name, bus, values)), name)
    self.safety.safety_tick()
    self.safety.aol_set_host_request(request)
    return self.safety.aol_get_permission_mask()

  def test_requires_aol_experience_and_known_params(self):
    self.assertEqual(0, self._hooks(alternative=0))
    for _ in range(3):
      self.assertEqual(0, self._feed(feature=1))
    self.assertEqual(0, self._hooks(1 << 9))
    for _ in range(3):
      self.assertEqual(0, self._feed(feature=1))

  def test_drive_startup_arms_latch(self):
    self.assertEqual(0, self._hooks(RivianSafetyFlags.AOL_START_ENABLED))
    self._feed(gear=1, request=0)
    self.assertEqual(1, self._feed(gear=4))

  def test_acc_engagement_arms_and_host_cannot_request_outside_drive(self):
    self.assertEqual(0, self._hooks())
    self.assertEqual(0, self._feed(gear=3))
    self.assertEqual(1, self._feed(feature=1))
    self.assertEqual(1, self._feed(feature=0))
    self.assertEqual(0, self._feed(gear=1))
    self.assertEqual(0, self._feed(gear=4, request=0))

  def test_brake_behavior(self):
    self.assertEqual(0, self._hooks(RivianSafetyFlags.AOL_BRAKE_REMAINS_ACTIVE))
    self._feed(feature=1)
    self.assertEqual(1, self._feed(brake=True))

    self.assertEqual(0, self._hooks())
    self._feed(feature=1)
    self.assertEqual(0, self._feed(brake=True))
    # The host may re-arm only after the brake is released.
    self.assertEqual(1, self._feed())

  def test_full_up_stalk_and_acm_unavailable_disarm(self):
    self.assertEqual(0, self._hooks())
    self._feed(feature=1)
    self.assertEqual(0, self._feed(user_request=2))
    self.assertEqual(0, self._feed(user_request=2))
    self.assertEqual(1, self._feed())
    self.assertEqual(0, self._feed(feature=4))

  def test_eps_shutdown_disarms(self):
    self.assertEqual(0, self._hooks())
    self._feed(feature=1)
    self.assertEqual(0, self._feed(eps_state=4, request=0))
    self.assertEqual(0, self._feed(eps_state=1, request=0))


class TestRivianIgnition(common.SafetyTestBase):
  DBC = "rivian_primary_actuator"
  SAFETY_MODEL = None

  TX_MSGS: list = []

  def _msg(self, counter, mode):
    return self.packer.make_can_msg_safety("VDM_OutputSignals", 0,
                                           {"VDM_OutputSigs_Counter": counter,
                                            "VDM_EpasPowerMode": mode})

  # VDM_EpasPowerMode_Drive_On=1
  def test_ignition_on(self):
    for i in range(15):
      self.safety.init_tests()
      self.safety.ignition_can_hook(self._msg(i, 1))
      self.assertFalse(self.safety.get_ignition_can())
      self.safety.ignition_can_hook(self._msg((i + 1) % 15, 1))
      self.assertTrue(self.safety.get_ignition_can())

  def test_ignition_off(self):
    self.safety.ignition_can_hook(self._msg(0, 1))
    self.safety.ignition_can_hook(self._msg(1, 1))
    self.assertTrue(self.safety.get_ignition_can())
    self.safety.ignition_can_hook(self._msg(2, 0))
    self.safety.ignition_can_hook(self._msg(3, 0))
    self.assertFalse(self.safety.get_ignition_can())


if __name__ == "__main__":
  unittest.main()
