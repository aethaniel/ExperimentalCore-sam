/*
  Copyright (c) 2016 Thibaut VIARD.  All right reserved.

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
#include "core_private.h"

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
 * | Digital (14)
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | Pin number |  Board pin       |  PIN   | Label/Name      | Comments (* is for default peripheral in use)
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 0~         | D0               |  PA00  |                 | TIOA0
 * | 1~         | D1               |  PA01  |                 | TIOB0
 * | 2          | D2               |  PA02  |                 |
 * | 3~         | D3               |  PA23  |                 | TIOA1
 * | 4~         | D4               |  PA16  |                 | TIOB1
 * | 5          | D5               |  PA29  |                 |
 * | 6          | D6               |  PB04  |                 |
 * | 7          | D7               |  PB15  |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 */
  { PORTA, PIO_PA0B_TIOA0, GPIO_PERIPH_B, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // D0
  { PORTA, PIO_PA1B_TIOB0, GPIO_PERIPH_B, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // D1
  { PORTA, PIO_PA2, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // D2
  { PORTA, PIO_PA23B_TIOA1, GPIO_PERIPH_B, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // D3
  { PORTA, PIO_PA16B_TIOB1, GPIO_PERIPH_B, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // D4
  { PORTA, PIO_PA29, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // D5
  { PORTB, PIO_PB4, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // D6
  { PORTB, PIO_PB15, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // D7

/* +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | SPI
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 8          | D8               |  PA06  | MOSI            |
 * | 9          | D9               |  PA15  | SCK             |
 * | 10         | D10              |  PA05  | MISO            |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 */
  { PORTA, PIO_PA6A_SPI2_MOSI, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // SPI MOSI (Flexcom 2)
  { PORTA, PIO_PA15B_SPI2_SPCK, GPIO_PERIPH_B, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // SPI SCK (Flexcom 2)
  { PORTA, PIO_PA5A_SPI2_MISO, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // SPI MISO (Flexcom 2)

/* +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | Wire
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 11         | D11              |  PB10  | SDA             |
 * | 12         | D12              |  PB11  | SCL             |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 */
  { PORTB, PIO_PB10A_TWD4, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // Wire SDA (Flexcom 4)
  { PORTB, PIO_PB11A_TWCK4, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // Wire SCL (Flexcom 4)

/*
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | Serial1
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | Pin number |  Board pin       |  PIN   | Label/Name      | Comments (* is for default peripheral in use)
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 13         | D13              |  PA04  | USART RX        | RXD3
 * | 14         | D14              |  PA03  | USART TX        | TXD3
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
*/
  { PORTA, PIO_PA3A_TXD3, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // Fake definition
  { PORTA, PIO_PA4A_RXD3, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // Fake definition

/* +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | Analog (7)
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | Pin number |  Board pin       |  PIN   | Label/Name      | Comments (* is for default peripheral in use)
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 15         |                  |  PA20  | A0              | AD3
 * | 16         |                  |  PB00  | A1              | AD4
 * | 17         |                  |  PB01  | A2              | AD5
 * | 18         |                  |  PB02  | A3              | AD6
 * | 19         |                  |  PB03  | A4              | AD7
 * | 20         |                  |  PA17  | A5              | AD0
 * | 21         |                  |  PA18  | A6              | AD1
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
*/
  { PORTA, PIO_PA20X1_AD3, GPIO_NOMUX, ADC_CHL3, NOT_ON_PWM, NOT_ON_TIMER }, // A0/AD3
  { PORTB, PIO_PB0X1_AD4, GPIO_NOMUX, ADC_CHL4, NOT_ON_PWM, NOT_ON_TIMER }, // A1/AD4
  { PORTB, PIO_PB1X1_AD5, GPIO_NOMUX, ADC_CHL5, NOT_ON_PWM, NOT_ON_TIMER }, // A2/AD5
  { PORTB, PIO_PB2X1_AD6, GPIO_NOMUX, ADC_CHL6, NOT_ON_PWM, NOT_ON_TIMER }, // A3/AD6
  { PORTB, PIO_PB3X1_AD7, GPIO_NOMUX, ADC_CHL7, NOT_ON_PWM, NOT_ON_TIMER }, // A4/AD7
  { PORTA, PIO_PA17X1_AD0, GPIO_NOMUX, ADC_CHL0, NOT_ON_PWM, NOT_ON_TIMER }, // A5/AD0
  { PORTA, PIO_PA18X1_AD1, GPIO_NOMUX, ADC_CHL1, NOT_ON_PWM, NOT_ON_TIMER }, // A6/AD1

/* +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | LEDs & button
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | Pin number |  Board pin       |  PIN   | Label/Name      | Comments (* is for default peripheral in use)
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 22         | N/A              |  PB04  | LG              |
 * | 23         | N/A              |  PB15  | LY              |
 * | 24         | N/A              |  PA31  | USR             |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
*/
  { PORTB, PIO_PB4, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // LED GREEN
  { PORTB, PIO_PB15, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // LED YELLOW
  { PORTA, PIO_PA31, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // USR BTN

/*
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | Serial
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | Pin number |  Board pin       |  PIN   | Label/Name      | Comments (* is for default peripheral in use)
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 25         | N/A              |  PA27  | ICE USB Serial  | RXD7
 * | 26         | N/A              |  PA28  | ICE USB Serial  | TXD7
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
*/
  { PORTA, PIO_PA27B_RXD7, GPIO_PERIPH_B, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // Flexcom 7 RXD7
  { PORTA, PIO_PA28B_TXD7, GPIO_PERIPH_B, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // Flexcom 7 TXD7

/*
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | WINC3400 WiFi (SPI+GPIOs)
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | Pin number |  Board pin       |  PIN   | Label/Name      | Comments (* is for default peripheral in use)
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 27         | N/A              |  PA13  | SPI_MOSI        |
 * | 28         | N/A              |  PA12  | SPI_MISO        |
 * | 29         | N/A              |  PA14  | SPI_SCK         |
 * | 30         | N/A              |  PA11  | SPI_CS          |
 * | 31         | N/A              |  PA24  | IRQ_N           |
 * | 32         | N/A              |  PB09  | WAKEUP          |
 * | 33         | N/A              |  PB14  | RESET           |
 * | 34         | N/A              |  PB13  | CHIP_EN         |
 * | 35         | N/A              |  PA30  | RTC_CLK         |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 */
  { PORTA, PIO_PA13A_SPI5_MOSI, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // WINC3400 WiFi SPI MOSI
  { PORTA, PIO_PA12A_SPI5_MISO, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // WINC3400 WiFi SPI MISO
  { PORTA, PIO_PA14A_SPI5_SPCK, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // WINC3400 WiFi SPI SCK
  { PORTA, PIO_PA11A_SPI5_NPCS0, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // WINC3400 WiFi SPI CS

  { PORTA, PIO_PA24, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // WINC3400 IRQ_N
  { PORTB, PIO_PB9, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // WINC3400 WAKEUP
  { PORTB, PIO_PB14, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // WINC3400 RESET
  { PORTB, PIO_PB13, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // WINC3400 CHIP_EN
  { PORTA, PIO_PA30, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // WINC3400 RTC_CLK

/*
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | WINC3400 Bluetooth (serial)
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | Pin number |  Board pin       |  PIN   | Label/Name      | Comments (* is for default peripheral in use)
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 36         | N/A              |  PA09  | BT RXD          |
 * | 37         | N/A              |  PA10  | BT TXD          |
 * | 38         | N/A              |  PA26  | BT RTS          |
 * | 39         | N/A              |  PA25  | BT CTS          |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 */
  { PORTA, PIO_PA9A_RXD0, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // BT RXD (Flexcom 0 RXD)
  { PORTA, PIO_PA10A_TXD0, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // BT TXD (Flexcom 0 TXD)
  { PORTA, PIO_PA26A_RTS0, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // BT RTS (Flexcom 0 RTS)
  { PORTA, PIO_PA25A_CTS0, GPIO_PERIPH_A, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, // BT CTS (Flexcom 0 CTS)

/*
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | Sensor
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | Pin number |  Board pin       |  PIN   | Label/Name      | Comments (* is for default peripheral in use)
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 35         | N/A              |  PB08  | IRQ             | WKUP14
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
*/
  { PORTB, PIO_PB8, GPIO_NOMUX, NOT_ON_ANALOG, NOT_ON_PWM, NOT_ON_TIMER }, //

/*
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | Battery
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | Pin number |  Board pin       |  PIN   | Label/Name      | Comments (* is for default peripheral in use)
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 36         | N/A              |  PA19  |                 | AD2
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
*/
  { PORTA, PIO_PA19X1_AD2, GPIO_NOMUX, ADC_CHL2, NOT_ON_PWM, NOT_ON_TIMER }, // AD2

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

/*
 * Serial Event handler
 */
void serialEvent() __attribute__((weak));
void serialEvent() { }

void serialEventRun(void)
{
  if (Serial.available()) serialEvent();
}

#if WIRE_INTERFACES_COUNT > 0

// Wire Interrupt handler
static void Wire_Handler(void)
{
  Wire.onService();
}

TwoWire Wire(WIRE_INTERFACE, PIN_WIRE_SDA, PIN_WIRE_SCL, Wire_Handler);

#endif
