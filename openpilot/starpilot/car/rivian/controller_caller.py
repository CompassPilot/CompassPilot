"""Rivian controller inputs that live outside the CAN stream."""

from openpilot.cereal import messaging
from opendbc.car.rivian.values import RivianFlags
from openpilot.starpilot.car.rivian.slc_set_speed import RivianSlcSetSpeed


class RivianControllerInputs:
  """Feed vehicleParameters (Dom's paramsd output: angle offset, roll, steer
  ratio, stiffness) to the Extreme-harness angle model, and let SLC own the
  harness software SET (see slc_set_speed).

  Angle control is open loop on the steering angle: without the learned angle
  offset it steers by the full sensor offset (route 80fbf9331d: -2.9 deg, a
  steady pull left once the controller hands off from torque to angle)."""

  def __init__(self, cp):
    self.angle_harness = bool(cp.flags & RivianFlags.ANGLE_HARNESS)
    self.longitudinal_harness = bool(cp.flags & RivianFlags.LONGITUDINAL_HARNESS)
    self.live_parameters = messaging.sub_sock('vehicleParameters', conflate=True) if self.angle_harness else None
    self.slc_set_speed = RivianSlcSetSpeed()

  def update(self, card) -> None:
    controller = card.CI.CC
    if self.live_parameters is not None and hasattr(controller, 'update_live_params'):
      msg = messaging.recv_one_or_none(self.live_parameters)
      if msg is not None and msg.valid:
        live = msg.vehicleParameters
        controller.update_live_params(live.roll, live.angleOffsetDeg, live.stiffnessFactor, live.steerRatio)

  def update_set_speed(self, card, cs, now_ns: int) -> None:
    set_cruise_speed = getattr(card.CI.CS, 'set_cruise_speed', None)
    if self.longitudinal_harness and callable(set_cruise_speed):
      self.slc_set_speed.update(card, cs, now_ns, set_cruise_speed)


def update(card, cs, cc, now_ns):
  inputs = getattr(card, '_rivian_controller_inputs', None)
  if inputs is None:
    inputs = card._rivian_controller_inputs = RivianControllerInputs(card.CP)
  inputs.update(card)
  inputs.update_set_speed(card, cs, now_ns)
