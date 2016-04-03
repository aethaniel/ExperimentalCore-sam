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
 * | 0          |                  |  PB2   | EDBG/EXT3_13    | *URXD1
 * | 1          |                  |  PB3   | EDBG/EXT3_14    | *UTXD1
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
*/
  { PORTB, PIO_PB2A_URXD1, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // URXD1
  { PORTB, PIO_PB3A_UTXD1, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // UTXD1

/* +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | LEDs & button    |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 2          | N/A              |  PC23  | LED0            | TIOA3
 * | 3          | N/A              |  PA2   | SW0             | WKUP2
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
*/
  { PORTC, PIO_PC23, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER },
  { PORTA, PIO_PA2, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER },

/* +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | Digital          |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 4          |                  |  PA24  | EXT1_5          | RTS1  PWMH1 A20         PIODC0
 * | 5          |                  |  PA25  | EXT1_6          | CTS1  PWMH2 A23         PIODC1
 * | 6          |                  |  PA1   | EXT1_9          | PWMH1 TIOB0 A18         WKUP1
 * | 7          |                  |  PA6   | EXT1_10         | TXD0  PCK0
 * | 8          |                  |  PC24  | EXT1_5          | A6    TIOB3
 * | 9          |                  |  PC25  | EXT1_6          | A7    TCLK3
 * | 10         |                  |  PC26  | EXT1_9          | A8    TIOA4
 * | 11         |                  |  PC27  | EXT1_10         | A9    TIOB4
 * | 12         |                  |  PC21  | EXT1_5          | A3    PWMH3
 * | 13         |                  |  PC22  | EXT1_6          | A4    PWML3
 * | 14         |                  |  PA0   | EXT1_9          | PWMH0 TIOA0 A17 WKUP0
 * | 15         |                  |  PC31  | EXT1_10         | A13   TCLK5
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
*/
  { PORTA, PIO_PA24, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER },
  { PORTA, PIO_PA25, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER },
  { PORTA, PIO_PA1, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER },
  { PORTA, PIO_PA6, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER },

  { PORTC, PIO_PC24, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER },
  { PORTC, PIO_PC25, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER },
  { PORTC, PIO_PC26, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER },
  { PORTC, PIO_PC27, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER },

  { PORTC, PIO_PC21, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER },
  { PORTC, PIO_PC22, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER },
  { PORTA, PIO_PA0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER },
  { PORTC, PIO_PC31, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER },

/* +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | Digital/PWM      |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 16         | PWM+             |  PA23  | EXT1_7          | SCK1 *PWMH0 A19       PIODCCLK
 * | 17         | PWM-             |  PA19  | EXT1_8          | RK   *PWML0 A15       AD2/WKUP9
 * | 18         | PWM+             |  PC19  | EXT2_7          | A1   *PWMH1
 * | 19         | PWM-             |  PA20  | EXT2_8          | RF   *PWML1 A16       AD3/WKUP10
 * | 20         | PWM+             |  PC20  | EXT3_7          | A2   *PWMH2
 * | 21         | PWM-             |  PA16  | EXT3_8          | TK   TIOB1  *PWML2    WKUP15/PIODCEN2
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
*/
  { PORTA, PIO_PA23B_PWMH0, GPIO_PERIPH_B, NOT_ON_ANALOG, PWM_CHL0, NOT_ON_TIMER }, // PWM0+
  { PORTA, PIO_PA19B_PWML0, GPIO_PERIPH_B, ADC_CHL2, PWM_CHL1, NOT_ON_TIMER }, // PWM0-
  { PORTC, PIO_PC19B_PWMH1, GPIO_PERIPH_B, NOT_ON_ANALOG, PWM_CHL2, NOT_ON_TIMER }, // PWM1+
  { PORTA, PIO_PA20B_PWML1, GPIO_PERIPH_B, ADC_CHL3, PWM_CHL3, NOT_ON_TIMER }, // PWM1-
  { PORTC, PIO_PC20B_PWMH2, GPIO_PERIPH_B, NOT_ON_ANALOG, PWM_CHL4, NOT_ON_TIMER }, // PWM2+
  { PORTA, PIO_PA16C_PWML2, GPIO_PERIPH_C, NOT_ON_ANALOG, PWM_CHL5, NOT_ON_TIMER }, // PWM2-

/* +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | Analog           |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 22         |                  |  PA17  | A0/EXT1_3       | TD    PCK1       PWMH3    *AD0
 * | 23         |                  |  PA18  | A1/EXT1_4       | RD    PCK2  A14  PWMFI2   *AD1
 * | 24         |                  |  PB0   | A2/EXT2_3       | PWMH0                     *AD4/RTCOUT0
 * | 25         |                  |  PB1   | A3/EXT2_4       | PWMH1                     *AD5/RTCOUT1
 * | 26         |                  |  PC29  | A4/EXT3_3       | A11   TIOA5               *AD13
 * | 27         |                  |  PC30  | A5/EXT3_4       | A12   TIOB5               *AD14
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
*/
  { PORTA, PIO_PA17X1_AD0, GPIO_NOMUX, ADC_CHL0, NOT_ON_PWM,  NOT_ON_TIMER }, // AD0
  { PORTA, PIO_PA18X1_AD1, GPIO_NOMUX, ADC_CHL1, NOT_ON_PWM,  NOT_ON_TIMER }, // AD1
  { PORTB, PIO_PB0X1_AD4, GPIO_NOMUX, ADC_CHL4, NOT_ON_PWM,  NOT_ON_TIMER }, // AD4
  { PORTB, PIO_PB1X1_AD5, GPIO_NOMUX, ADC_CHL5, NOT_ON_PWM,  NOT_ON_TIMER }, // AD5
  { PORTC, PIO_PC29X1_AD13, GPIO_NOMUX, ADC_CHL13, NOT_ON_PWM,  NOT_ON_TIMER }, // AD13
  { PORTC, PIO_PC30X1_AD14, GPIO_NOMUX, ADC_CHL14, NOT_ON_PWM,  NOT_ON_TIMER }, // AD14

/* +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | Serial1          |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 28         |                  |  PA21  | EXT1_13/EXT2_13 | *RXD1 PCK1        AD8
 * | 29         |                  |  PA22  | EXT1_14/EXT2_14 | *TXD1 NPCS3 NCS2  AD9
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
*/
  { PORTB, PIO_PA21A_RXD1, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // RXD1
  { PORTB, PIO_PA22A_TXD1, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // TXD1

/* +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | Wire             |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 30         |                  |  PA3   | EXT1_11/EXT2_11 | *TWD0  NPCS3
 * | 31         |                  |  PA4   | EXT1_12/EXT2_12 | *TWCK0 TCLK0       WKUP3
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
*/
  { PORTA, PIO_PA3A_TWD0, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // SDA0
  { PORTA, PIO_PA4A_TWCK0, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // SCL0

/* +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | Wire1            |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 32         |                  |  PB4   | EXT3_11         | *TWD1  PWMH2
 * | 33         |                  |  PB5   | EXT3_12         | *TWCK1 PWML0       WKUP13
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
*/
  { PORTB, PIO_PB4A_TWD1, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // SDA1
  { PORTB, PIO_PB5A_TWCK1, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // SCL1

/* +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | SPI              |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | xx         |                  |  PA13  | MOSI/EXTx_16    | *MOSI PWMH2
 * | xx         |                  |  PA12  | MISO/EXTx_17    | *MISO PWMH1
 * | xx         |                  |  PA14  | SCK/EXTx_18     | *SPCK PWMH3
 * | xx         |                  |  PA11  | SS0/EXT1_15     |
 * | xx         |                  |  PA9   | SS1/EXT2_15     |
 * | xx         |                  |  PA10  | SS2/EXT3_15     |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
*/
  { PORTA, PIO_PA13A_MOSI, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // MOSI
  { PORTA, PIO_PA12A_MISO, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // MISO
  { PORTA, PIO_PA14A_SPCK, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // SCK
  { PORTA, PIO_PA11A_NPCS0, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // SS0
  { PORTA, PIO_PA9B_NPCS1, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // SS1
  { PORTA, PIO_PA10B_NPCS2, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // SS2

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

SAMSerial Serial((Usart*)UART1, PIN_SERIAL_RX, PIN_SERIAL_TX, Serial_Handler, 1);

// Serial1 Interrupt handler
static void Serial1_Handler(void)
{
  Serial1.IrqHandler();
}

SAMSerial Serial1( USART1, PIN_SERIAL1_RX, PIN_SERIAL1_TX, Serial1_Handler, 0);

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

