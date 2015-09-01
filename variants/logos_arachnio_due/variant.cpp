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
 * Arachnio Due pin |  PORT  | Label
 * -----------------+--------+-------
 *   0              |  PA9   | "RX0"
 *   1              |  PA10  | "TX0"
 *   2              |  PA3   | "SDA"
 *   3              |  PA4   | "SCL"
 *   4              |  PB3   | "A7", "TX1"
 *   5         TDI  |  PB4   |
 *   6              |  PB2   | "A6", "RX1"
 *   7       SWDIO  |  PB6   |
 *   8		 SWCLK  |  PB7   |
 *   9 		 	    |  PA5   |
 *  10              |  PA2   |
 *  11              |  PA1   |
 *  12              |  PA11  |
 *  13				|  PA0   | "LED"
 *  14				|  PA17  | "A0"
 *  15				|  PA18  | "A1"
 *  16				|  PA19  | "A2"
 *  17				|  PA20  | "A3"
 *  18				|  PB0   | "A4"
 *  19				|  PB1   | "A5"
 *  20				|  PA12  | "MISO"
 *  21              |  PA13  | "MOSI"
 *  22 	            |  PA14  | "SCK"
 *  23              |  PA16  | "SS", "RXLED", "TXLED"
 *  24              |  PA15  | "CHIP_EN"
 *  25         SWO  |  PB5   | "ESP_RST"
 *
 */

/*
 * Pins descriptions
 */
const PinDescription g_aPinMap[]=
{
	{ PORTA, PIO_PA9A_URXD0, GPIO_PERIPH_A, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, 		// D0/URXD0
	{ PORTA, PIO_PA10A_UTXD0, GPIO_PERIPH_A, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, 	// D1/UTXD0
	{ PORTA, PIO_PA3A_TWD0, GPIO_PERIPH_A, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, 		// D2/SDA
	{ PORTA, PIO_PA4A_TWCK0, GPIO_PERIPH_A, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, 		// D3/SCL
	{ PORTB, PIO_PB3A_UTXD1, GPIO_PERIPH_A, ADC_Channel7, NOT_ON_PWM, NOT_ON_TIMER },			// D4
	{ PORTB, PIO_PB4, GPIO_NOMUX, ADC_Channel7, NOT_ON_PWM, NOT_ON_TIMER },						// D5
	{ PORTB, PIO_PB2A_URXD1, GPIO_PERIPH_A, ADC_Channel6, NOT_ON_PWM, NOT_ON_TIMER },			// D6
	{ PORTB, PIO_PB4, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER },				// D7
	{ PORTB, PIO_PB7, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER },				// D8
	{ PORTB, PIO_PB5, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER },				// D9
	{ PORTB, PIO_PB2, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER },				// D10
	{ PORTB, PIO_PB1, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER },				// D11
	{ PORTB, PIO_PB11, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER },				// D12
	{ PORTB, PIO_PB0, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER },				// D13
	{ PORTA, PIO_PA17, GPIO_NOMUX, ADC_Channel0, NOT_ON_PWM, NOT_ON_TIMER },					// A0
	{ PORTA, PIO_PA18, GPIO_NOMUX, ADC_Channel1, NOT_ON_PWM, NOT_ON_TIMER },					// A1
	{ PORTA, PIO_PA19, GPIO_NOMUX, ADC_Channel2, NOT_ON_PWM, NOT_ON_TIMER },					// A2
	{ PORTA, PIO_PA20, GPIO_NOMUX, ADC_Channel3, NOT_ON_PWM, NOT_ON_TIMER },					// A3
	{ PORTB, PIO_PB0, GPIO_NOMUX, ADC_Channel4, NOT_ON_PWM, NOT_ON_TIMER },						// A4
	{ PORTB, PIO_PB1, GPIO_NOMUX, ADC_Channel5, NOT_ON_PWM, NOT_ON_TIMER },						// A5
	{ PORTA, PIO_PA12A_MISO, GPIO_PERIPH_A, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER },		// MISO
	{ PORTA, PIO_PA13A_MOSI, GPIO_PERIPH_A, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER },		// MOSI
	{ PORTA, PIO_PA14A_SPCK, GPIO_PERIPH_A, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER },		// SCK
	{ PORTA, PIO_PA16, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER },				// SS, RXTXLED
	{ PORTA, PIO_PA15, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER },				// CHIP_EN
	{ PORTB, PIO_PB5, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER },				// ESP_RST
} ;


#ifdef __cplusplus
}
#endif

#if 0 // TODO Serial
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
#endif // TODO Serial

// TODO: Serial peripherals Interrupt handlers


