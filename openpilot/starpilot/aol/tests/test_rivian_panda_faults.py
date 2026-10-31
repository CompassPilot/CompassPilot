"""Rivian's recorded bus-2/bus-3 IRQ load diagnostics; every other fault still blocks."""
import pytest

from opendbc.car import structs
from opendbc.car.rivian import harness_aol
from opendbc.car.rivian.interface import CarInterface
from opendbc.car.rivian.values import CAR
from openpilot.cereal import log
from openpilot.starpilot.aol.panda_faults import blocking_fault_mask, blocking_fault_list

DIAGNOSTIC = ('interruptRateCan2', 'interruptRateCan3')
FAULTS = log.PandaState.FaultType.schema.enumerants


def rivian(harness=True, candidate=CAR.RIVIAN_R1T, aol=True):
  fingerprint = {bus: {} for bus in range(8)}
  fingerprint[0][0x321] = 8
  if harness:
    fingerprint[1] = {0x1310: 8, 0x131A: 8}
  cp = CarInterface.get_params(candidate, fingerprint, [], harness, False, False)
  cp.fingerprintSource = structs.CarParams.FingerprintSource.can
  if harness and aol:
    harness_aol.prepare(cp, brake_remains_active=True, stalk_toggle=True, startup_enabled=False)
    cp.alternativeExperience = 32
  return cp


@pytest.mark.parametrize('harness', (True, False))
@pytest.mark.parametrize('candidate', (CAR.RIVIAN_R1, CAR.RIVIAN_R1T))
def test_recorded_irq_load_diagnostics_do_not_block(harness, candidate):
  cp = rivian(harness, candidate)
  assert not blocking_fault_mask((1 << FAULTS['interruptRateCan2']) | (1 << FAULTS['interruptRateCan3']), cp)
  assert not blocking_fault_list([FAULTS[name] for name in DIAGNOSTIC], cp)
  assert not blocking_fault_list([], cp)


def test_harness_without_aol_marking_is_still_exempt():
  # Selfdrived checks panda faults for every car, AOL or not.
  cp = rivian(aol=False)
  assert not blocking_fault_list([FAULTS['interruptRateCan2']], cp)


@pytest.mark.parametrize('fault,value', tuple(FAULTS.items()))
def test_every_other_and_mixed_fault_still_blocks(fault, value):
  cp = rivian()
  blocks = fault not in DIAGNOSTIC
  assert blocking_fault_mask(1 << value, cp) == blocks
  assert blocking_fault_mask((1 << value) | (1 << FAULTS['interruptRateCan2']), cp) == blocks
  assert blocking_fault_list([value], cp) == blocks
  assert blocking_fault_list([FAULTS['interruptRateCan2'], value], cp) == blocks


@pytest.mark.parametrize('mutation', ('passive', 'dashcam', 'fixed', 'extra_panda', 'wrong_model', 'other_brand'))
def test_unqualified_configurations_cannot_borrow_exception(mutation):
  cp = rivian()
  if mutation == 'passive':
    cp.passive = True
  elif mutation == 'dashcam':
    cp.dashcamOnly = True
  elif mutation == 'fixed':
    cp.fingerprintSource = structs.CarParams.FingerprintSource.fixed
  elif mutation == 'extra_panda':
    cp.safetyConfigs = [*cp.safetyConfigs, structs.CarParams.SafetyConfig(safetyModel=structs.CarParams.SafetyModel.noOutput)]
  elif mutation == 'wrong_model':
    cp.safetyConfigs[0].safetyModel = structs.CarParams.SafetyModel.noOutput
  else:
    cp.brand = 'tesla'
  assert blocking_fault_list([FAULTS['interruptRateCan2']], cp)
  assert blocking_fault_mask(1 << FAULTS['interruptRateCan2'], cp)
