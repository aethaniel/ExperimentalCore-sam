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
  { PORTA, PIO_PA6, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM,  NOT_ON_TIMER },
  { PORTA, PIO_PA2, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM,  NOT_ON_TIMER }, // WKUP2

/* +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | Serial           |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 2          |                  |  PB1   | ICE USB Serial  | URXD0
 * | 3          |                  |  PB0   | ICE USB Serial  | UTXD0
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
*/
  { PORTB, PIO_PB1B_RXD6, GPIO_PERIPH_B, NOT_ON_ANALOG, NOT_ON_PWM,  NOT_ON_TIMER }, // Flexcom 6 RXD6
  { PORTB, PIO_PB0B_TXD6, GPIO_PERIPH_B, NOT_ON_ANALOG, NOT_ON_PWM,  NOT_ON_TIMER }, // Flexcom 6 TXD6

/* +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | Analog           |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | xxx        |                  |  PA17  | A0              | I2SDO0  PCK1    AD0
 * | xxx        |                  |  PA18  | A1              | I2SMCK0 PCK2    AD1
 * | xxx        |                  |  PA19  | A2              | TCLK1   I2SCK1  AD2
 * | xxx        |                  |  PA20  | A3              | TCLK2   I2SWS1  AD3
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
*/
  { PORTA, PIO_PA17X1_AD0, GPIO_NOMUX, ADC_CHL0, NOT_ON_PWM,  NOT_ON_TIMER }, // AD0
  { PORTA, PIO_PA18X1_AD1, GPIO_NOMUX, ADC_CHL1, NOT_ON_PWM,  NOT_ON_TIMER }, // AD1
  { PORTA, PIO_PA19X1_AD2, GPIO_NOMUX, ADC_CHL2, NOT_ON_PWM,  NOT_ON_TIMER }, // AD2
  { PORTA, PIO_PA20X1_AD3, GPIO_NOMUX, ADC_CHL3, NOT_ON_PWM,  NOT_ON_TIMER }, // AD3

} ;

#ifdef __cplusplus
}
#endif

/*
 * Serialx objects
 */
// Serial Interrupt handler
static void Serial_Handler(void)
{
  Serial.IrqHandler();
}

SAMSerial Serial( (Usart*)USART6, FLEXCOM6_IRQn, Serial_Handler, 1);
void serialEvent() __attribute__((weak));
void serialEvent() { }

void serialEventRun(void)
{
  if (Serial.available()) serialEvent();
}


