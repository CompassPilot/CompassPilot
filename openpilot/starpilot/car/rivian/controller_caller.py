"""Rivian controller inputs that live outside the CAN stream."""

from openpilot.cereal import messaging
from opendbc.car.common.conversions import Conversions as CV
from opendbc.car.rivian.values import RivianFlags
from openpilot.selfdrive.car.cruise import V_CRUISE_UNSET


class RivianControllerInputs:
  """Feed liveParameters to the Extreme-harness angle model and keep the car's
  software set speed aligned with Card's software cruise when SLC owns it."""

  def __init__(self, cp):
    self.angle_harness = bool(cp.flags & RivianFlags.ANGLE_HARNESS)
    self.longitudinal_harness = bool(cp.flags & RivianFlags.LONGITUDINAL_HARNESS)
    self.live_parameters = messaging.sub_sock('liveParameters', conflate=True) if self.angle_harness else None

  def update(self, card) -> None:
    controller = card.CI.CC
    if self.live_parameters is not None and hasattr(controller, 'update_live_params'):
      msg = messaging.recv_one_or_none(self.live_parameters)
      if msg is not None and msg.valid:
        live = msg.liveParameters
        controller.update_live_params(live.roll, live.angleOffsetDeg, live.stiffnessFactor, live.steerRatio)

    helper = card.v_cruise_helper
    set_cruise_speed = getattr(card.CI.CS, 'set_cruise_speed', None)
    if (self.longitudinal_harness and callable(set_cruise_speed) and getattr(helper, 'slc_pcm', False) and
        0 < helper.v_cruise_kph < V_CRUISE_UNSET):
      # Rivian publishes its software-owned set speed as PCM cruise state every cycle.
      set_cruise_speed(helper.v_cruise_kph * CV.KPH_TO_MS)


def update(card, cs, cc, now_ns):
  inputs = getattr(card, '_rivian_controller_inputs', None)
  if inputs is None:
    inputs = card._rivian_controller_inputs = RivianControllerInputs(card.CP)
  inputs.update(card)
