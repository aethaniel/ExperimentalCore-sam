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
  { .pGPIO=PIOB, .ulId=ID_PIOB }
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
 * | 0          | N/A              |  PA6   | LED1            |
 * | 1          | N/A              |  PA2   | BP2             | WKUP2
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
*/
  { PORTA, PIO_PA6, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM,  NOT_ON_TIMER },
  { PORTA, PIO_PA2, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM,  NOT_ON_TIMER }, // WKUP2

/* +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | Serial           |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 2          |                  |  PB1   | ICE USB Serial  | URXD0
 * | 3          |                  |  PB0   | ICE USB Serial  | UTXD0
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
*/
  { PORTB, PIO_PB1B_RXD6, GPIO_PERIPH_B, No_Analog_Channel, NOT_ON_PWM,  NOT_ON_TIMER }, // Flexcom 6 RXD6
  { PORTB, PIO_PB0B_TXD6, GPIO_PERIPH_B, No_Analog_Channel, NOT_ON_PWM,  NOT_ON_TIMER }, // Flexcom 6 TXD6

} ;


#ifdef __cplusplus
}
#endif

// TODO: Serialx instanciations (Serial, Serial1, ...)

#if 0 // TODO Serial
/*
 * FLEXCOM/USART objects
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
#endif // TODO Serial

// TODO: Serial peripherals Interrupt handlers


