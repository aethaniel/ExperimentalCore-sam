/*
  Copyright (c) 2015 Thibaut VIARD.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "Arduino.h"
#include "core_private.h"

void initVariant( void )
{
  // Initialize USB pins
  pinPeripheral(PINS_USB, GPIO_PERIPH_A);

  // Initialize CAN pins
  pinPeripheral(PINS_CAN0, GPIO_PERIPH_A);
  pinPeripheral(PINS_CAN1, GPIO_PERIPH_A);

  // Set LED to off
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  // Output MCK to A1 pin
  pinPeripheral(A1, GPIO_PERIPH_B);
  PMC->PMC_PCK[1]=PMC_PCK_CSS_MCK;
  PMC->PMC_SCER|=PMC_SCER_PCK1;

  /*
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
