#include "Arduino.h"

void initVariant( void )
{
  // Initialize Serial port U(S)ART pins
  /*
  PIO_Configure(
    g_aPinMap[PINS_UART].pPort,
    g_aPinMap[PINS_UART].ulPinType,
    g_aPinMap[PINS_UART].ulPin,
    g_aPinMap[PINS_UART].ulPinConfiguration);
  digitalWrite(0, HIGH); // Enable pullup for RX0
  PIO_Configure(
    g_aPinMap[PINS_USART0].pPort,
    g_aPinMap[PINS_USART0].ulPinType,
    g_aPinMap[PINS_USART0].ulPin,
    g_aPinMap[PINS_USART0].ulPinConfiguration);
  PIO_Configure(
    g_aPinMap[PINS_USART1].pPort,
    g_aPinMap[PINS_USART1].ulPinType,
    g_aPinMap[PINS_USART1].ulPin,
    g_aPinMap[PINS_USART1].ulPinConfiguration);
  PIO_Configure(
    g_aPinMap[PINS_USART3].pPort,
    g_aPinMap[PINS_USART3].ulPinType,
    g_aPinMap[PINS_USART3].ulPin,
    g_aPinMap[PINS_USART3].ulPinConfiguration);

  // Initialize USB pins
  PIO_Configure(
    g_aPinMap[PINS_USB].pPort,
    g_aPinMap[PINS_USB].ulPinType,
    g_aPinMap[PINS_USB].ulPin,
    g_aPinMap[PINS_USB].ulPinConfiguration);

  // Initialize CAN pins
  PIO_Configure(
    g_aPinMap[PINS_CAN0].pPort,
    g_aPinMap[PINS_CAN0].ulPinType,
    g_aPinMap[PINS_CAN0].ulPin,
    g_aPinMap[PINS_CAN0].ulPinConfiguration);
  PIO_Configure(
    g_aPinMap[PINS_CAN1].pPort,
    g_aPinMap[PINS_CAN1].ulPinType,
    g_aPinMap[PINS_CAN1].ulPin,
    g_aPinMap[PINS_CAN1].ulPinConfiguration);

  // Initialize Analog Controller
  pmc_enable_periph_clk(ID_ADC);
  adc_init(ADC, SystemCoreClock, ADC_FREQ_MAX, ADC_STARTUP_FAST);
  adc_configure_timing(ADC, 0, ADC_SETTLING_TIME_3, 1);
  adc_configure_trigger(ADC, ADC_TRIG_SW, 0); // Disable hardware trigger.
  adc_disable_interrupt(ADC, 0xFFFFFFFF); // Disable all ADC interrupts.
  adc_disable_all_channel(ADC);

  // Initialize analogOutput module
  analogOutputInit();
*/  
}
