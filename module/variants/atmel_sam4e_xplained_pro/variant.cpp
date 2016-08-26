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
 * | Pin number |  Board pin       |  PIN   | Label/Name      | Comments (* is for default peripheral in use)
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | Serial           |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 0          |                  |  PA9   | ICE USB Serial  | URXD0
 * | 1          |                  |  PA10  | ICE USB Serial  | UTXD0
 * | 2          | EXT1_13          |  PA21  | USART RX        | RXD1  + todo
 * | 3          | EXT1_14          |  PA22  | USART TX        | TXD1  + todo
 * | 4          | EXT2_13          |  PA5   | USART RX        | URXD1 + todo
 * | 5          | EXT2_14          |  PA6   | USART TX        | UTXD1 + todo
 * | 4          | EXT3_13          |  PA5   | USART RX        | URXD1 + todo
 * | 5          | EXT3_14          |  PA6   | USART TX        | UTXD1 + todo
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
*/
  { PORTA, PIO_PA9A_URXD0, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM,  NOT_ON_TIMER }, // URXD0
  { PORTA, PIO_PA10A_UTXD0, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM,  NOT_ON_TIMER }, // UTXD0
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // todo
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // todo
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // todo
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // todo
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // todo
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // todo

/* +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | Pin number |  Board pin       |  PIN   | Label/Name      | Comments (* is for default peripheral in use)
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | LEDs & button    |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 6          | N/A              |  PD22  | LED0            | PWMH2
 * | 7          | N/A              |  PA2   | SW0             | WKUP2
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
*/
  { PORTD, PIO_PD22, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // LED0
  { PORTA, PIO_PA2, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // SW0

/* +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | Pin number |  Board pin       |  PIN   | Label/Name      | Comments (* is for default peripheral in use)
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | Digital (17)     |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 8          | EXT1_5           |  PA24  | GPIO            | todo
 * | 9          | EXT1_6           |  PA25  | GPIO            | todo
 * | 10         | EXT1_7           |  PA15  | PWM(+)          | todo
 * | 11         | EXT1_8           |  PA16  | PWM(-)          | todo
 * | 12         | EXT1_9           |  PA11  | IRQ/GPIO        | todo
 * | 13         | EXT1_10          |  PD25  | SPI_SS_B/GPIO   | todo
 * | 14         | EXT2_5           |  PE2   | GPIO            | todo
 * | 15         | EXT2_6           |  PB5   | GPIO            | todo
 * | 16         | EXT2_7           |  PD21  | PWM(+)          | todo
 * | 17         | EXT2_9           |  PD29  | IRQ/GPIO        | todo
 * | 18         | EXT2_10          |  PB4   | SPI_SS_B/GPIO   | todo
 * | 19         | EXT3_5           |  PD28  | GPIO            | todo
 * | 20         | EXT3_6           |  PD17  | GPIO            | todo
 * | 21         | EXT3_7           |  PD20  | PWM(+)          | todo
 * | 22         | EXT3_8           |  PD24  | PWM(-)          | todo
 * | 23         | EXT3_9           |  PE1   | IRQ/GPIO        | todo
 * | 24         | EXT3_10          |  PD26  | SPI_SS_B/GPIO   | todo
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
*/
// EXT1
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // todo
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // todo
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // todo
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // todo
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // todo
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // todo
// EXT2
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // todo
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // todo
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // todo
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // todo
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // todo
// EXT3
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // todo
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // todo
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // todo
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // todo
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // todo
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // todo

/* +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | Pin number |  Board pin       |  PIN   | Label/Name      | Comments (* is for default peripheral in use)
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | Analog (4)       |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 25         | EXT1_3           |  PB2   | A0              | todo
 * | 26         | EXT1_4           |  PB3   | A1              | todo
 * | 27         | EXT3_3           |  PA17  | A2              | todo
 * | 28         | EXT3_4           |  PC13  | A3              | todo
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
*/
  { PORTB, PIO_PB2X1_AFE1_AD0, GPIO_NOMUX, ADC_CHL0, NOT_ON_PWM, NOT_ON_TIMER }, // AFE1/AD0
  { PORTB, PIO_PB3X1_AFE1_AD1, GPIO_NOMUX, ADC_CHL1, NOT_ON_PWM, NOT_ON_TIMER }, // AFE1/AD1
  { PORTA, PIO_PA17X1_AFE0_AD0, GPIO_NOMUX, ADC_CHL0, NOT_ON_PWM, NOT_ON_TIMER }, // AFE0/AD0
  { PORTC, PIO_PC13X1_AFE0_AD6, GPIO_NOMUX, ADC_CHL6, NOT_ON_PWM, NOT_ON_TIMER }, // AFE0/AD6

/* +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | Pin number |  Board pin       |  PIN   | Label/Name      | Comments (* is for default peripheral in use)
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | Wire             |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 29         | EXT1/2/3_11      |  PA3   |                 | TWD0
 * | 30         | EXT1/2/3_12      |  PA4   |                 | TWCK0
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 */
// Wire
  { PORTA, PIO_PA3A_TWD0, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // TWD0
  { PORTA, PIO_PA4A_TWCK0, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // TWCK0

/* +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | Pin number |  Board pin       |  PIN   | Label/Name      | Comments (* is for default peripheral in use)
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | SPI              |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 31         | EXT1_16          |  PA13  | SPI_MOSI        | todo
 * | 32         | EXT1_17          |  PA12  | SPI_MISO        | todo
 * | 33         | EXT1_18          |  PA14  | SPI_SCK         | todo
 * | 34         | EXT1_15          |  PB14  | SPI_SS_A        | todo
 * | 35         | EXT2_15          |  PD23  | SPI_SS_A        | todo
 * | 36         | EXT3_15          |  PD30  | SPI_SS_A        | todo
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 */
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // todo
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // todo
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // todo
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // todo
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // todo
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // todo
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

SAMSerial Serial((Usart*)UART0, PIN_SERIAL_RX, PIN_SERIAL_TX, Serial_Handler, 1);
/*
 * Serial Event handler
 */
void serialEvent() __attribute__((weak));
void serialEvent() { }

void serialEventRun(void)
{
  if (Serial.available()) serialEvent();
}


