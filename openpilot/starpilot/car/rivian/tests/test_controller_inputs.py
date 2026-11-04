"""The Extreme-harness angle model must receive paramsd's learned offset and roll.

Route 80fbf9331d (2026-11-04): Card subscribed to the pre-Dom-7.0 'liveParameters'
name, which no longer exists, so angle control ran with a 0 deg offset against a
learned -2.9 deg sensor offset and pulled left after every torque-to-angle handoff.
"""
from types import SimpleNamespace

from openpilot.cereal import messaging
from openpilot.cereal.services import SERVICE_LIST
from opendbc.car.rivian.values import RivianFlags
from openpilot.starpilot.car.rivian import controller_caller


def test_angle_inputs_subscribe_to_an_existing_service(monkeypatch):
  names = []
  monkeypatch.setattr(controller_caller.messaging, 'sub_sock', lambda name, **kwargs: names.append(name) or name)
  controller_caller.RivianControllerInputs(SimpleNamespace(flags=int(RivianFlags.ANGLE_HARNESS)))
  assert names == ['vehicleParameters']
  assert all(name in SERVICE_LIST for name in names)


def test_vehicle_parameters_reach_the_angle_model(monkeypatch):
  msg = messaging.new_message('vehicleParameters', valid=True)
  msg.vehicleParameters.angleOffsetDeg = -2.9
  msg.vehicleParameters.roll = 0.0164
  msg.vehicleParameters.stiffnessFactor = 1.01
  msg.vehicleParameters.steerRatio = 15.3
  reader = msg.as_reader()
  monkeypatch.setattr(controller_caller.messaging, 'sub_sock', lambda name, **kwargs: name)
  monkeypatch.setattr(controller_caller.messaging, 'recv_one_or_none', lambda sock: reader)
  received = []
  controller = SimpleNamespace(update_live_params=lambda *args: received.append(args))
  card = SimpleNamespace(CP=SimpleNamespace(flags=int(RivianFlags.ANGLE_HARNESS)),
                         CI=SimpleNamespace(CC=controller, CS=SimpleNamespace()),
                         v_cruise_helper=SimpleNamespace(slc_pcm=False, v_cruise_kph=0))
  controller_caller.update(card, None, None, 0)
  assert len(received) == 1
  roll, offset, stiffness, steer_ratio = received[0]
  assert abs(offset + 2.9) < 1e-5 and abs(roll - 0.0164) < 1e-6
  assert abs(stiffness - 1.01) < 1e-5 and abs(steer_ratio - 15.3) < 1e-5
