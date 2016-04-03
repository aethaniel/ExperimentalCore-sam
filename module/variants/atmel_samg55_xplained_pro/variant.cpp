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
 * |            | Serial           |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 0          | N/A              |  PA27  | ICE USB Serial  | RXD7
 * | 1          | N/A              |  PA28  | ICE USB Serial  | TXD7
 * | 2          | EXT1_13          |  PA9   | USART RX        | RXD0
 * | 3          | EXT1_14          |  PA10  | USART TX        | TXD0
 * | 4          | EXT3_13          |  PB1   | USART RX        | RXD6
 * | 5          | EXT3_14          |  PB0   | USART TX        | TXD6
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
*/
// Serial
  { PORTA, PIO_PA27B_RXD7, GPIO_PERIPH_B, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // Flexcom 7 RXD7
  { PORTA, PIO_PA28B_TXD7, GPIO_PERIPH_B, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // Flexcom 7 TXD7
// Serial 1
  { PORTA, PIO_PA9A_RXD0, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // Flexcom 0 RXD0
  { PORTA, PIO_PA10A_TXD0, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // Flexcom 0 TXD0
// Serial 2
  { PORTB, PIO_PB1B_RXD6, GPIO_PERIPH_B, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // Flexcom 6 RXD6
  { PORTB, PIO_PB0B_TXD6, GPIO_PERIPH_B, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // Flexcom 6 TXD6

/* +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | LEDs & button    |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 6          | N/A              |  PA6   | LED1            |
 * | 7          | N/A              |  PA2   | BP2             | WKUP2
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
*/
  { PORTA, PIO_PA6, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // LED1
  { PORTA, PIO_PA2, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // BP2

/* +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | Digital (14)     |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 8          | EXT1_5           |  PA26  | GPIO            | SPI0_NPCS1/RTS0 I2SMCK1
 * | 9          | EXT1_6           |  PA25  | GPIO            | SPI0_NPCS0/CTS0 I2SDO1
 * | 10         | EXT1_7           |  PA0   | PWM(+)          | I2SCK0 *TIOA0 WKUP0
 * | 11         | EXT1_8           |  PA23  | PWM(-)          | I2SDO1 *TIOA1 WKUP3
 * | 12         | EXT1_9           |  PA24  | IRQ/GPIO        | I2SMCK1 SCK2/SPI2_SPCK *WKUP11
 * | 13         | EXT1_10          |  PA29  | SPI_SS_B/GPIO   | SPI1_NPCS1/RTS1 SCK7/SPI7_SPCK
 * | 14         | EXT3_5           |  PA30  | GPIO            | PCK1 SPI7_NPCS0/CTS7
 * | 15         | EXT3_6           |  PB15  | GPIO            | SPI3_NPCS1/RTS3 SPI6_NPCS1/RTS6
 * | 16         | EXT3_7           |  PA1   | PWM(+)          | I2SWS0 *TIOB0 WKUP1
 * | 17         | EXT3_8           |  PB13  | PWM(-)          | SCK3/SPI3_SPCK SCK6/SPI6_SPCK
 * | 18         | EXT3_9           |  PB3   | IRQ/GPIO        | TXD1/SPI1_MOSI/TWD1 PCK2 AD7/ *WKUP13
 * | 19         | EXT3_10          |  PA15  | SPI_SS_B/GPIO   | SPI2_NPCS1/RTS2 SCK2/SPI2_SPCK
 * | 20         | EXT4_5           |  PA31  | GPIO            | PCK2 SPI7_NPCS1/RTS7
 * | 21         | EXT4_9           |  PB14  | IRQ/GPIO        | SPI3_NPCS0/CTS3 SPI6_NPCS0/CTS6
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
*/
// EXT1
  { PORTA, PIO_PA26, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // EXT1_5
  { PORTA, PIO_PA25, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // EXT1_6
  { PORTA, PIO_PA0B_TIOA0, GPIO_PERIPH_B, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // EXT1_7
  { PORTA, PIO_PA23B_TIOA1, GPIO_PERIPH_B, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // EXT1_8
  { PORTA, PIO_PA24, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // EXT1_9
  { PORTA, PIO_PA29, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // EXT1_10
// EXT3
  { PORTA, PIO_PA30, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // EXT3_5
  { PORTB, PIO_PB15, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // EXT3_6
  { PORTA, PIO_PA1B_TIOB0, GPIO_PERIPH_B, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // EXT3_7
  { PORTB, PIO_PB13, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // EXT3_8
  { PORTB, PIO_PB3, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // EXT3_9
  { PORTA, PIO_PA15, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // EXT3_10
// EXT4
  { PORTA, PIO_PA31, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // EXT4_5
  { PORTB, PIO_PB14, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // EXT4_9

/* +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | Analog (4)       |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 22         |                  |  PA17  | A0              | I2SDO0  PCK1    AD0
 * | 23         |                  |  PA18  | A1              | I2SMCK0 PCK2    AD1
 * | 24         |                  |  PA19  | A2              | TCLK1   I2SCK1  AD2
 * | 25         |                  |  PA20  | A3              | TCLK2   I2SWS1  AD3
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
*/
  { PORTA, PIO_PA17X1_AD0, GPIO_NOMUX, ADC_CHL0, NOT_ON_PWM, NOT_ON_TIMER }, // AD0
  { PORTA, PIO_PA18X1_AD1, GPIO_NOMUX, ADC_CHL1, NOT_ON_PWM, NOT_ON_TIMER }, // AD1
  { PORTA, PIO_PA19X1_AD2, GPIO_NOMUX, ADC_CHL2, NOT_ON_PWM, NOT_ON_TIMER }, // AD2
  { PORTA, PIO_PA20X1_AD3, GPIO_NOMUX, ADC_CHL3, NOT_ON_PWM, NOT_ON_TIMER }, // AD3

/* +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | Wire             |        |                 | !! Warning, schematics seem to be false !!
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 26         | EXT1_11          |  PB10  |                 | TWD6
 * | 27         | EXT1_12          |  PB11  |                 | TWCK6
 * | 28         | EXT3_11          |  PB8   |                 | TWD4
 * | 29         | EXT3_12          |  PB9   |                 | TWCK4
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 */
// Wire
  { PORTB, PIO_PB10B_TWD6, GPIO_PERIPH_B, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // TWD6
  { PORTB, PIO_PB11B_TWCK6, GPIO_PERIPH_B, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // TWCK6
// Wire 1
  { PORTB, PIO_PB8A_TWD4, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // TWD4
  { PORTB, PIO_PB9A_TWCK4, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // TWCK4

/* +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | SPI              |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 30         | EXT1_16          |  PA13  | SPI_MOSI        |
 * | 31         | EXT1_17          |  PA12  | SPI_MISO        |
 * | 32         | EXT1_18          |  PA14  | SPI_SCK         |
 * | 33         | EXT1_15          |  PA11  | SPI_SS_A        |
 * | 34         | EXT3_15          |  PA5   | SPI_SS_A        |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 */
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // Fake definition
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // Fake definition
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // Fake definition
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // Fake definition
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // Fake definition
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

SAMSerial Serial( (Usart*)USART7, PIN_SERIAL_RX, PIN_SERIAL_TX, Serial_Handler, 0);

// Serial1 Interrupt handler
static void Serial1_Handler(void)
{
  Serial1.IrqHandler();
}

SAMSerial Serial1( (Usart*)USART0, PIN_SERIAL1_RX, PIN_SERIAL1_TX, Serial1_Handler, 0);

// Serial2 Interrupt handler
static void Serial2_Handler(void)
{
  Serial2.IrqHandler();
}

SAMSerial Serial2( (Usart*)USART6, PIN_SERIAL2_RX, PIN_SERIAL2_TX, Serial2_Handler, 0);

/*
 * Serial Event handler
 */
void serialEvent() __attribute__((weak));
void serialEvent() { }

void serialEventRun(void)
{
  if (Serial.available()) serialEvent();
}

// Wire Interrupt handler
static void Wire_Handler(void)
{
  Wire.onService();
}

TwoWire Wire(WIRE_INTERFACE, PIN_WIRE_SDA, PIN_WIRE_SCL, Wire_Handler);

// Wire1 Interrupt handler
static void Wire1_Handler(void)
{
  Wire1.onService();
}

TwoWire Wire1(WIRE1_INTERFACE, PIN_WIRE1_SDA, PIN_WIRE1_SCL, Wire1_Handler);
