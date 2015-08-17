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
#include "variant.h"

#ifdef __cplusplus
extern "C" {
#endif

const Port Ports[NUM_PORTS]=
{
  { .pGPIO=PIOA, .ulId=ID_PIOA },
  { .pGPIO=PIOB, .ulId=ID_PIOB },
  { .pGPIO=PIOC, .ulId=ID_PIOC }
};

/*
 * Pins descriptions
 */
const PinDescription g_aPinMap[]=
{
/*
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * + Pin number +  Board pin       |  PIN   | Label/Name      | Comments (* is for default peripheral in use)
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | LEDs & button    |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 0          | N/A              |  PD22  | LED0            | TIOA3
 * | 1          | N/A              |  PA2   | SW0             | WKUP2
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
*/
  { PORTD, PIO_PD22, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM,  NOT_ON_TIMER },
  { PORTA, PIO_PA2, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM,  NOT_ON_TIMER },

/* +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | Serial           |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 2          |                  |  PB2   | ICE USB Serial  | RXD0
 * | 3          |                  |  PB3   | ICE USB Serial  | TXD0
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
*/
  { PORTA, PIO_PA9A_RXD0, GPIO_PERIPH_A, No_Analog_Channel, NOT_ON_PWM,  NOT_ON_TIMER }, // RXD0
  { PORTA, PIO_PA10A_TXD0, GPIO_PERIPH_A, No_Analog_Channel, NOT_ON_PWM,  NOT_ON_TIMER }, // TXD0

} ;


#ifdef __cplusplus
}
#endif

#if 0
/*
 * UART objects
 */
UARTClass Serial( (Usart*)UART0, UART0_IRQn, ID_UART0, 1);
void serialEvent() __attribute__((weak));
void serialEvent() { }

// IT handlers
void UART0_Handler(void)
{
  Serial.IrqHandler();
}

// ----------------------------------------------------------------------------

void serialEventRun(void)
{
  if (Serial.available()) serialEvent();
}
#endif //0

// TODO: Serial peripherals Interrupt handlers


