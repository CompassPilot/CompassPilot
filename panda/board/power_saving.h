#include "power_saving_declarations.h"

// WARNING: STM's functional-safety conditions (CoU_3) prohibit hardware low-power
// modes while Panda is executing a safety function.
//
// The Rivian C4 firmware enters H7 stop mode only after the SoM is powered off
// and Panda has been placed in SAFETY_SILENT, so no safety function is active.
// Any wake source exits stop mode through a full system reset, returning Panda
// to its safe startup state before normal operation resumes.

int power_save_status = POWER_SAVE_STATUS_DISABLED;

void enable_can_transceivers(bool enabled) {
  // Leave main CAN always on for CAN-based ignition detection
  uint8_t main_bus = (harness.status == HARNESS_STATUS_FLIPPED) ? 3U : 1U;
  for(uint8_t i=1U; i<=4U; i++){
    bool transceiver_enabled = (i == main_bus) || enabled;
    #ifdef PANDA_HKG_REMOTE_START
    uint8_t hkg_bus = (harness.status == HARNESS_STATUS_FLIPPED) ? 4U : 2U;
    transceiver_enabled = transceiver_enabled || (i == hkg_bus);
    #endif
    current_board->enable_can_transceiver(i, transceiver_enabled);
  }
}

void set_power_save_state(int state) {
  bool is_valid_state = (state == POWER_SAVE_STATUS_ENABLED) || (state == POWER_SAVE_STATUS_DISABLED);
  if (is_valid_state && (state != power_save_status)) {
    bool enable = false;
    if (state == POWER_SAVE_STATUS_ENABLED) {
      print("enable power savings\n");

      // Disable CAN interrupts
      if (harness.status == HARNESS_STATUS_FLIPPED) {
        llcan_irq_disable(cans[0]);
      } else {
        llcan_irq_disable(cans[2]);
      }
      #ifndef PANDA_HKG_REMOTE_START
      llcan_irq_disable(cans[1]);
      #endif
    } else {
      print("disable power savings\n");

      if (harness.status == HARNESS_STATUS_FLIPPED) {
        llcan_irq_enable(cans[0]);
      } else {
        llcan_irq_enable(cans[2]);
      }
      llcan_irq_enable(cans[1]);

      enable = true;
    }

    enable_can_transceivers(enable);

    // Switch off IR when in power saving
    if(!enable){
      current_board->set_ir_power(0U);
    }

    power_save_status = state;
  }
}

#if defined(PANDA_RIVIAN_WAKE) && defined(STM32H7)
// Stop mode is entered only after the C4 SoM is off and Panda is in
// SAFETY_SILENT. Any configured CAN or SBU edge wakes Panda through a reset.
static void enter_stop_mode(void) {
  // Analog mode minimizes GPIO power and disables pull resistors.
  register_set(&(GPIOA->MODER), 0xFFFFFFFFU, 0xFFFFFFFFU);
  register_set(&(GPIOB->MODER), 0xFFFFFFFFU, 0xFFFFFFFFU);
  register_set(&(GPIOC->MODER), 0xFFFFFFFFU, 0xFFFFFFFFU);
  register_set(&(GPIOD->MODER), 0xFFFFFFFFU, 0xFFFFFFFFU);
  register_set(&(GPIOE->MODER), 0xFFFFFFFFU, 0xFFFFFFFFU);
  register_set(&(GPIOF->MODER), 0xFFFFFFFFU, 0xFFFFFFFFU);
  register_set(&(GPIOG->MODER), 0xFFFFFFFFU, 0xFFFFFFFFU);

  current_board->set_bootkick(BOOT_STANDBY);
  current_board->set_amp_enabled(false);
  for (uint8_t i = 1U; i <= 4U; i++) {
    current_board->enable_can_transceiver(i, false);
  }

  // Disable ADCs and clocks/retention which are unnecessary in stop mode.
  ADC1->CR &= ~(ADC_CR_ADEN);
  ADC1->CR |= ADC_CR_DEEPPWD;
  ADC2->CR &= ~(ADC_CR_ADEN);
  ADC2->CR |= ADC_CR_DEEPPWD;
  register_clear_bits(&(RCC->CR), RCC_CR_HSI48ON);
  register_clear_bits(&(RCC->AHB2LPENR), RCC_AHB2LPENR_SRAM1LPEN | RCC_AHB2LPENR_SRAM2LPEN);
  register_clear_bits(&(RCC->AHB4LPENR), RCC_AHB4LPENR_SRAM4LPEN);
  register_clear_bits(&(RCC->AHB3LPENR), RCC_AHB3LPENR_AXISRAMLPEN);

  // SBU wake inputs: EXTI1 is SBU2 (PA1), EXTI4 is SBU1 (PC4).
  set_gpio_mode(current_board->harness_config->GPIO_SBU1,
                current_board->harness_config->pin_SBU1, MODE_INPUT);
  set_gpio_mode(current_board->harness_config->GPIO_SBU2,
                current_board->harness_config->pin_SBU2, MODE_INPUT);
  register_set(&(SYSCFG->EXTICR[0]), SYSCFG_EXTICR1_EXTI1_PA, 0xF0U);
  register_set(&(SYSCFG->EXTICR[1]), SYSCFG_EXTICR2_EXTI4_PC, 0xFU);
  register_set_bits(&(EXTI->IMR1), (1U << 1) | (1U << 4));
  register_set_bits(&(EXTI->RTSR1), (1U << 1) | (1U << 4));
  register_set_bits(&(EXTI->FTSR1), (1U << 1) | (1U << 4));

  // CAN wake inputs: FDCAN1 RX (PB8), FDCAN2 RX (PB5), FDCAN3 RX (PD12).
  set_gpio_mode(GPIOB, 8, MODE_INPUT);
  register_set(&(SYSCFG->EXTICR[2]), SYSCFG_EXTICR3_EXTI8_PB, 0xFU);
  set_gpio_mode(GPIOB, 5, MODE_INPUT);
  register_set(&(SYSCFG->EXTICR[1]), SYSCFG_EXTICR2_EXTI5_PB, 0xF0U);
  set_gpio_mode(GPIOD, 12, MODE_INPUT);
  register_set(&(SYSCFG->EXTICR[3]), SYSCFG_EXTICR4_EXTI12_PD, 0xFU);
  const uint32_t can_exti_line = (1UL << 8) | (1UL << 5) | (1UL << 12);
  register_set_bits(&(EXTI->IMR1), can_exti_line);
  register_set_bits(&(EXTI->FTSR1), can_exti_line);

  EXTI->PR1 = (1U << 1) | (1U << 4) | can_exti_line;

  // Close the race where the ignition line rises while stop mode is prepared.
  #ifndef PANDA_IGNORE_IGNITION_LINE
  if (harness_check_ignition()) {
    NVIC_SystemReset();
  }
  #endif

  register_clear_bits(&(PWR->CPUCR), PWR_CPUCR_PDDS_D1 | PWR_CPUCR_PDDS_D2 | PWR_CPUCR_PDDS_D3);
  register_set(&(PWR->CR1), PWR_CR1_SVOS_0 | PWR_CR1_FLPS, PWR_CR1_SVOS | PWR_CR1_FLPS);
  SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

  __disable_irq();
  for (uint32_t i = 0U; i < 8U; i++) {
    NVIC->ICER[i] = 0xFFFFFFFFU;
    NVIC->ICPR[i] = 0xFFFFFFFFU;
  }
  NVIC_EnableIRQ(EXTI1_IRQn);
  NVIC_EnableIRQ(EXTI4_IRQn);
  NVIC_EnableIRQ(EXTI9_5_IRQn);
  NVIC_EnableIRQ(EXTI15_10_IRQn);

  __DSB();
  __ISB();
  __WFI();

  NVIC_SystemReset();
}
#endif
