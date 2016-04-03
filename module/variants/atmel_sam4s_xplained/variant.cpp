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
 * | 5          | J1.1             |  PA3   | also J4.1       | TWD0
 * | 6          | J1.2             |  PA4   | also J4.2       | TWCK0
 * | xxx        | J1.3             |  PB2   | also J4.3       | URXD1/AD6/WKUP12
 * | xxx        | J1.4             |  PB3   | also J4.4       | UTXD1/AD7
 * | xxx        | J1.5             |  PA31  |                 | NPCS1
 * | xxx        | J1.6             |  PA13  | also J4.6       | MOSI
 * | xxx        | J1.7             |  PA12  | also J4.7       | MISO
 * | xxx        | J1.8             |  PA14  | also J4.8       | SPCK
 * |            | J1.9             |        | GND             |
 * |            | J1.10            |        | 3.3V            |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
*/
  { PORTA, PIO_PA3A_TWD0, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM,  NOT_ON_TIMER }, // Wire data
  { PORTA, PIO_PA4A_TWCK0, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM,  NOT_ON_TIMER }, // Wire clock
  { PORTB, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM,  NOT_ON_TIMER }, // Fake definition
  { PORTB, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM,  NOT_ON_TIMER }, // Fake definition
  { PORTA, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM,  NOT_ON_TIMER }, // Fake definition
  { PORTA, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM,  NOT_ON_TIMER }, // Fake definition
  { PORTA, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM,  NOT_ON_TIMER }, // Fake definition
  { PORTA, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM,  NOT_ON_TIMER }, // Fake definition

/*
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | J2 header        |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 13         | J2.1             |  PA22  |                 | TXD1
 * | xxx        | J2.2             |  PC12  |                 | AD12
 * | xxx        | J2.3             |  PB0   |                 | AD4/RTCOUT0
 * | xxx        | J2.4             |  PB1   |                 | AD5/PWMH1
 * | xxx        | J2.5             |  PA17  |                 | PCK1/PWMH3
 * | 18         | J2.6             |  PA21  |                 | RXD1
 * | xxx        | J2.7             |  PC13  |                 | AD10/PWML0
 * | xxx        | J2.8             |  PC15  |                 | AD11/PWML0
 * |            | J2.9             |        | GND             |
 * |            | J2.10            |        | 3.3V            |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
*/
  { PORTA, PIO_PA22A_TXD1, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM,  NOT_ON_TIMER }, // TXD1
  { PORTC, PIO_PC12X1_AD12, GPIO_NOMUX, ADC_CHL12, NOT_ON_PWM,  NOT_ON_TIMER }, // AD12
  { PORTB, PIO_PB0X1_AD4, GPIO_NOMUX, ADC_CHL4, NOT_ON_PWM,  NOT_ON_TIMER }, // AD4
  { PORTB, PIO_PB1X1_AD5, GPIO_NOMUX, ADC_CHL5, NOT_ON_PWM,  NOT_ON_TIMER }, // AD5
  { PORTA, PIO_PA17C_PWMH3, GPIO_PERIPH_C, NOT_ON_ANALOG, PWM_CHL3,  NOT_ON_TIMER }, // PWMH3
  { PORTA, PIO_PA21A_RXD1, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM,  NOT_ON_TIMER }, // RXD1
  { PORTB, PIO_PC13B_PWML0, GPIO_PERIPH_B, ADC_CHL10, PWM_CHL0,  NOT_ON_TIMER }, // AD10/PWML0
  { PORTB, PIO_PC15B_PWML1, GPIO_NOMUX, ADC_CHL11, PWM_CHL1,  NOT_ON_TIMER }, // AD11/PWML0

/*
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | J3 header        |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | xxx        | J3.1             |  PA20  |                 | AD3/PWML1
 * | xxx        | J3.2             |  PA11  |                 | PWMH0
 * | xxx        | J3.3             |  PA23  |                 | PWMH0/SCK1
 * | xxx        | J3.4             |  PA18  |                 | PCK2
 * | xxx        | J3.5             |  PA15  |                 | TIOA1/PWML3
 * | xxx        | J3.6             |  PA16  |                 | TIOB1/PWMH2
 * | xxx        | J3.7             |  PA2   |                 | PWMH2/WKUP2/DATRG
 * | xxx        | J3.8             |  PC2   |                 | PWML2
 * |            | J3.9             |        | GND             |
 * |            | J3.10            |        | 5V              |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
*/
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM,  NOT_ON_TIMER }, // Fake definition
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM,  NOT_ON_TIMER }, // Fake definition
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM,  NOT_ON_TIMER }, // Fake definition
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM,  NOT_ON_TIMER }, // Fake definition
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM,  NOT_ON_TIMER }, // Fake definition
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM,  NOT_ON_TIMER }, // Fake definition
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM,  NOT_ON_TIMER }, // Fake definition
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM,  NOT_ON_TIMER }, // Fake definition

/*
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | J4 header        |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | xxx        | J4.1             |  PA3   | also J1.1       | TWD0
 * | xxx        | J4.2             |  PA4   | also J1.2       | TWCK0
 * | xxx        | J4.3             |  PB2   | also J1.3       | URXD1/AD6/WKUP12
 * | xxx        | J4.4             |  PB3   | also J1.4       | UTXD1/AD7
 * | xxx        | J4.5             |  PA30  |                 | NPCS2
 * | xxx        | J4.6             |  PA13  | also J1.6       | MOSI
 * | xxx        | J4.7             |  PA12  | also J1.7       | MISO
 * | xxx        | J4.8             |  PA14  | also J1.8       | SPCK
 * |            | J4.9             |        | GND             |
 * |            | J4.10            |        | 3.3V            |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
*/
  { PORTA, PIO_PA3A_TWD0, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM,  NOT_ON_TIMER }, // Wire data
  { PORTA, PIO_PA4A_TWCK0, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM,  NOT_ON_TIMER }, // Wire clock
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM,  NOT_ON_TIMER }, // Fake definition
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM,  NOT_ON_TIMER }, // Fake definition
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM,  NOT_ON_TIMER }, // Fake definition
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM,  NOT_ON_TIMER }, // Fake definition
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM,  NOT_ON_TIMER }, // Fake definition
  { NOT_A_PORT, 0, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM,  NOT_ON_TIMER }, // Fake definition
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

SAMSerial Serial( (Usart*)UART0, PIN_SERIAL_RX, PIN_SERIAL_TX, Serial_Handler, 1);

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


