from opendbc.car.car_helpers import interfaces
from opendbc.car.rivian.values import CAR
from openpilot.starpilot.panda_wake import DEVICE_TYPES, FirmwareChoice, resolve, supported_keys


def _cp(candidate=CAR.RIVIAN_R1):
  fingerprint = {bus: {} for bus in range(8)}
  fingerprint[0][0x321] = 8
  return interfaces[candidate].get_params(candidate, fingerprint, [], False, False, False)


def _sources(**values):
  keys = ('RemoteStartBootsComma', 'HKGRemoteStartBootsComma', 'IgnoreIgnitionLine', 'TeslaWakeOnCAN', 'RivianWakeBootsComma')
  return tuple((key, values.get(key), True) for key in keys)


def test_rivian_wake_selects_comma_4_image():
  for candidate in (CAR.RIVIAN_R1, CAR.RIVIAN_R1T):
    cp = _cp(candidate)
    assert supported_keys(cp) == ('RivianWakeBootsComma',)
    choice = resolve(cp, _sources(RivianWakeBootsComma=b'1'))
    assert choice == FirmwareChoice(rivian=True)
    assert choice.filename('panda_h7.bin.signed') == 'panda_h7_rivian_wake.bin.signed'
    assert choice.filename('panda.bin.signed') == 'panda_rivian_wake.bin.signed'
  assert DEVICE_TYPES['RivianWakeBootsComma'] == ('mici',)


def test_rivian_wake_off_and_foreign_keys_keep_stock_image():
  cp = _cp()
  assert not resolve(cp, _sources()).alternate
  # Keys owned by other vehicles never select an alternate image for Rivian.
  assert not resolve(cp, _sources(TeslaWakeOnCAN=b'1', RemoteStartBootsComma=b'1')).alternate
