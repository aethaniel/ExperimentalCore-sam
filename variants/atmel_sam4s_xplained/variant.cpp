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
 * |            | Serial           |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 0          |                  |  PA9   | ICE USB Serial  | URXD0
 * | 1          |                  |  PA10  | ICE USB Serial  | UTXD0
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
*/
  { PORTA, PIO_PA9A_URXD0, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM,  NOT_ON_TIMER }, // URXD0
  { PORTA, PIO_PA10A_UTXD0, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM,  NOT_ON_TIMER }, // UTXD0

/* +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | LEDs & button    |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 2          | N/A              |  PC10  | LED1            |
 * | 3          | N/A              |  PC17  | LED2            |
 * | 4          | N/A              |  PA5   | BP2             | WKUP4
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
*/
  { PORTC, PIO_PC10, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM,  NOT_ON_TIMER },
  { PORTC, PIO_PC17, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM,  NOT_ON_TIMER },
  { PORTA, PIO_PA5, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM,  NOT_ON_TIMER }, // WKUP4

/* +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | J1 header        |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 0          | J1.1             |  PA3   | also J4.1       | TWD0
 * | 1          | J1.2             |  PA4   | also J4.2       | TWCK0
 * | 2          | J1.3             |  PB2   | also J4.3       | URXD1/AD6/WKUP12
 * | 3          | J1.4             |  PB3   | also J4.4       | UTXD1/AD7
 * | 4          | J1.5             |  PA31  |                 | NPCS1
 * | 5          | J1.6             |  PA13  | also J4.6       | MOSI
 * | 6          | J1.7             |  PA12  | also J4.7       | MISO
 * | 7          | J1.8             |  PA14  | also J4.8       | SPCK
 * | 7          | J1.9             |        | GND             |
 * | 7          | J1.10            |        | 3.3V            |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
*/

/*
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | J2 header        |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 0          | J2.1             |  PA22  |                 | TXD1
 * | 1          | J2.2             |  PC12  |                 | AD12
 * | 2          | J2.3             |  PB0   |                 | AD4/RTCOUT0
 * | 3          | J2.4             |  PB1   |                 | AD5/PWMH1
 * | 4          | J2.5             |  PA17  |                 | PCK1/PWMH3
 * | 5          | J2.6             |  PA21  |                 | RXD1
 * | 6          | J2.7             |  PC13  |                 | AD10/PWML0
 * | 7          | J2.8             |  PC15  |                 | AD11/PWML0
 * | 7          | J2.9             |        | GND             |
 * | 7          | J2.10            |        | 3.3V            |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
*/

/*
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | J3 header        |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 0          | J3.1             |  PA20  |                 | AD3/PWML1
 * | 1          | J3.2             |  PA11  |                 | PWMH0
 * | 2          | J3.3             |  PA23  |                 | PWMH0/SCK1
 * | 3          | J3.4             |  PA18  |                 | PCK2
 * | 4          | J3.5             |  PA15  |                 | TIOA1/PWML3
 * | 5          | J3.6             |  PA16  |                 | TIOB1/PWMH2
 * | 6          | J3.7             |  PA2   |                 | PWMH2/WKUP2/DATRG
 * | 7          | J3.8             |  PC2   |                 | PWML2
 * | 7          | J3.9             |        | GND             |
 * | 7          | J3.10            |        | 5V              |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
*/

/*
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | J4 header        |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 0          | J4.1             |  PA3   | also J1.1       | TWD0
 * | 1          | J4.2             |  PA4   | also J1.2       | TWCK0
 * | 2          | J4.3             |  PB2   | also J1.3       | URXD1/AD6/WKUP12
 * | 3          | J4.4             |  PB3   | also J1.4       | UTXD1/AD7
 * | 4          | J4.5             |  PA30  |                 | NPCS2
 * | 5          | J4.6             |  PA13  | also J1.6       | MOSI
 * | 6          | J4.7             |  PA12  | also J1.7       | MISO
 * | 7          | J4.8             |  PA14  | also J1.8       | SPCK
 * | 7          | J4.9             |        | GND             |
 * | 7          | J4.10            |        | 3.3V            |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
*/

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

SAMSerial Serial( (Usart*)UART0, UART0_IRQn, Serial_Handler, 1);
void serialEvent() __attribute__((weak));
void serialEvent() { }

void serialEventRun(void)
{
  if (Serial.available()) serialEvent();
}


