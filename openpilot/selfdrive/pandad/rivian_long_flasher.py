#!/usr/bin/env python3
"""Firmware management for the Rivian Gen 1 Extreme harness bridge."""

import os
from itertools import accumulate

from panda import Panda
from openpilot.common.params import Params
from openpilot.common.swaglog import cloudlog
from openpilot.starpilot.saved_source import read_saved

FW_PATH = os.path.join(os.path.dirname(os.path.abspath(__file__)), "rivian_long_fw.bin.signed")
SECTOR_SIZES = [0x4000] * 4 + [0x10000] + [0x20000] * 11
# The bridge is an F4 Black Panda, which the Panda library no longer lists as supported.
HW_TYPE_BLACK = b'\x03'
CAR_PARAMS_KEYS = ("CarParamsPersistent", "CarParamsCache", "CarParamsPrevRoute")


def _saved_car_params(params, key):
  """Return the verified CarParams payload saved under key, or None."""
  from openpilot.cereal import messaging
  from openpilot.starpilot.schema_cache import inspect_cache
  from opendbc.car.structs import car
  raw, readable = read_saved(params, key, 1_048_576)
  if not readable or raw is None:
    return None
  inspected = inspect_cache(key, raw)
  if inspected.status != 'valid' or inspected.payload is None:
    return None
  return messaging.log_from_bytes(inspected.payload, car.CarParams)


def _is_rivian() -> bool:
  params = Params()

  # The first valid record is the freshest one. A current non-Rivian record
  # must not be overridden by a stale Rivian CarParamsPrevRoute value.
  for key in CAR_PARAMS_KEYS:
    try:
      cp = _saved_car_params(params, key)
      if cp is not None:
        return cp.brand == "rivian"
    except Exception:
      cloudlog.exception(f"Unable to read {key} while identifying Rivian vehicle")

  return False


def is_rivian_vehicle() -> bool:
  return _is_rivian()


def _flash_static(handle, code: bytes) -> None:
  assert Panda.flasher_present(handle)
  last_sector = next((i + 1 for i, value in enumerate(accumulate(SECTOR_SIZES[1:])) if value > len(code)), -1)
  assert 1 <= last_sector < 7, "Invalid Rivian bridge firmware size"

  handle.controlWrite(Panda.REQUEST_IN, 0xB1, 0, 0, b'')
  for sector in range(1, last_sector + 1):
    handle.controlWrite(Panda.REQUEST_IN, 0xB2, sector, 0, b'')
  for offset in range(0, len(code), 0x10):
    handle.bulkWrite(2, code[offset:offset + 0x10])
  try:
    handle.controlWrite(Panda.REQUEST_IN, 0xD8, 0, 0, b'', expect_disconnect=True)
  except Exception:
    pass


def _flash_panda(panda: Panda) -> None:
  expected_signature = Panda.get_signature_from_firmware(FW_PATH)
  if not panda.bootstub and panda.get_signature() == expected_signature:
    cloudlog.info(f"Rivian bridge {panda.get_usb_serial()} already up to date")
    return

  cloudlog.info(f"Flashing Rivian Extreme harness bridge {panda.get_usb_serial()}")
  with open(FW_PATH, "rb") as firmware:
    code = firmware.read()

  if not panda.bootstub:
    # Old F4 firmware cannot use Panda.reset(); enter its bootstub directly.
    try:
      panda._handle.controlWrite(Panda.REQUEST_IN, 0xD1, 1, 0, b'', timeout=15000, expect_disconnect=True)
    except Exception:
      pass
    panda.close()
    panda.reconnect()

  _flash_static(panda._handle, code)
  panda.reconnect()
  cloudlog.info(f"Successfully flashed Rivian Extreme harness bridge {panda.get_usb_serial()}")


def is_rivian_bridge_panda(panda: Panda, rivian: bool | None = None) -> bool:
  if panda.is_internal() or panda.get_type() != HW_TYPE_BLACK:
    return False
  # A cached Rivian CarParams record is not sufficient evidence to identify a
  # bridge. An arbitrary external Black Panda may be connected at the same
  # time, and flashing it would permanently replace its firmware. Only the
  # signed bridge image can positively identify the hardware.
  try:
    expected_signature = Panda.get_signature_from_firmware(FW_PATH)
    return not panda.bootstub and panda.get_signature() == expected_signature
  except Exception:
    return False


def prepare_rivian_bridge(panda_serials: list[str]) -> set[str]:
  """Identify bridge serials which must not be passed to normal Panda management."""
  firmware_available = os.path.isfile(FW_PATH)
  if not firmware_available:
    cloudlog.error(f"Rivian bridge firmware not found at {FW_PATH}")

  rivian = _is_rivian()
  usb_serials = set(Panda.usb_list())
  bridge_serials: set[str] = set()

  for serial in panda_serials:
    if serial not in usb_serials:
      continue
    panda = None
    try:
      panda = Panda(serial)
      if panda.is_internal() or panda.get_type() != HW_TYPE_BLACK:
        continue

      bridge_confirmed = is_rivian_bridge_panda(panda, rivian)
      if not bridge_confirmed and not rivian:
        continue

      bridge_serials.add(serial)
      if bridge_confirmed and rivian and firmware_available:
        _flash_panda(panda)
      elif rivian:
        cloudlog.warning(f"External Black Panda {serial} is not signed with the Rivian bridge firmware; leaving it untouched")
    except Exception:
      cloudlog.exception(f"Failed to prepare Rivian Extreme harness bridge {serial}")
    finally:
      if panda is not None:
        panda.close()

  return bridge_serials


if __name__ == '__main__':
  prepare_rivian_bridge(Panda.list())
