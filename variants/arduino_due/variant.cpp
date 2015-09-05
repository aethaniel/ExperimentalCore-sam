/*
  Copyright (c) 2011 Arduino LLC.  All right reserved.
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

/*
 * DUE Board pin   |  PORT  | Label
 * ----------------+--------+-------
 *   0             |  PA8   | "RX0"
 *   1             |  PA9   | "TX0"
 *   2       TIOA0 |  PB25  |
 *   3       TIOA7 |  PC28  |
 *   4       NPCS1 |  PA29  |
 *           TIOB6 |  PC26  |
 *   5       TIOA6 |  PC25  |
 *   6       PWML7 |  PC24  |
 *   7       PWML6 |  PC23  |
 *   8       PWML5 |  PC22  |
 *   9       PWML4 |  PC21  |
 *  10       NPCS0 |  PA28  |
 *           TIOB7 |  PC29  |
 *  11       TIOA8 |  PD7   |
 *  12       TIOB8 |  PD8   |
 *  13       TIOB0 |  PB27  | LED AMBER "L"
 *  14       TXD3  |  PD4   | "TX3"
 *  15       RXD3  |  PD5   | "RX3"
 *  16       TXD1  |  PA13  | "TX2"
 *  17       RXD1  |  PA12  | "RX2"
 *  18       TXD0  |  PA11  | "TX1"
 *  19       RXD0  |  PA10  | "RX1"
 *  20             |  PB12  | "SDA"
 *  21             |  PB13  | "SCL"
 *  22             |  PB26  |
 *  23             |  PA14  |
 *  24             |  PA15  |
 *  25             |  PD0   |
 *  26             |  PD1   |
 *  27             |  PD2   |
 *  28             |  PD3   |
 *  29             |  PD6   |
 *  30             |  PD9   |
 *  31             |  PA7   |
 *  32             |  PD10  |
 *  33             |  PC1   |
 *  34             |  PC2   |
 *  35             |  PC3   |
 *  36             |  PC4   |
 *  37             |  PC5   |
 *  38             |  PC6   |
 *  39             |  PC7   |
 *  40             |  PC8   |
 *  41             |  PC9   |
 *  42             |  PA19  |
 *  43             |  PA20  |
 *  44             |  PC19  |
 *  45             |  PC18  |
 *  46             |  PC17  |
 *  47             |  PC16  |
 *  48             |  PC15  |
 *  49             |  PC14  |
 *  50             |  PC13  |
 *  51             |  PC12  |
 *  52       NPCS2 |  PB21  |
 *  53             |  PB14  |
 *  54             |  PA16  | "A0"
 *  55             |  PA24  | "A1"
 *  56             |  PA23  | "A2"
 *  57             |  PA22  | "A3"
 *  58       TIOB2 |  PA6   | "A4"
 *  69             |  PA4   | "A5"
 *  60       TIOB1 |  PA3   | "A6"
 *  61       TIOA1 |  PA2   | "A7"
 *  62             |  PB17  | "A8"
 *  63             |  PB18  | "A9"
 *  64             |  PB19  | "A10"
 *  65             |  PB20  | "A11"
 *  66             |  PB15  | "DAC0"
 *  67             |  PB16  | "DAC1"
 *  68             |  PA1   | "CANRX"
 *  69             |  PA0   | "CANTX"
 *  70             |  PA17  | "SDA1"
 *  71             |  PA18  | "SCL1"
 *  72             |  PC30  | LED AMBER "RX"
 *  73             |  PA21  | LED AMBER "TX"
 *  74       MISO  |  PA25  |
 *  75       MOSI  |  PA26  |
 *  76       SCLK  |  PA27  |
 *  77       NPCS0 |  PA28  |
 *  78       NPCS3 |  PB23  | unconnected!
 *
 * USB pin         |  PORT
 * ----------------+--------
 *  ID             |  PB11
 *  VBOF           |  PB10
 *
 */

#ifdef __cplusplus
extern "C" {
#endif

const Port Ports[NUM_PORTS]=
{
  { .pGPIO=PIOA, .ulId=ID_PIOA },
  { .pGPIO=PIOB, .ulId=ID_PIOB },
  { .pGPIO=PIOC, .ulId=ID_PIOC },
  { .pGPIO=PIOD, .ulId=ID_PIOD }
};

/*
 * Pins descriptions
 */
const PinDescription g_aPinMap[]=
{
  // 0 .. 53 - Digital pins
  // ----------------------
  // 0/1 - UART (Serial)
  { PORTA, PIO_PA8A_URXD, GPIO_PERIPH_A, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // URXD
  { PORTA, PIO_PA9A_UTXD, GPIO_PERIPH_A, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // UTXD

  // 2
  { PORTB, PIO_PB25B_TIOA0, GPIO_PERIPH_B, No_Analog_Channel, NOT_ON_PWM, TC0_CHA0 }, // TIOA0
  { PORTC, PIO_PC28B_TIOA7, GPIO_PERIPH_B, No_Analog_Channel, NOT_ON_PWM, TC2_CHA7 }, // TIOA7
  { PORTC, PIO_PC26B_TIOB6, GPIO_PERIPH_B, No_Analog_Channel, NOT_ON_PWM, TC2_CHB6 }, // TIOB6

  // 5
  { PORTC, PIO_PC25B_TIOA6, GPIO_PERIPH_B, No_Analog_Channel, NOT_ON_PWM, TC2_CHA6 }, // TIOA6
  { PORTC, PIO_PC24B_PWML7, GPIO_PERIPH_B, No_Analog_Channel, PWM_CH7, NOT_ON_TIMER }, // PWML7
  { PORTC, PIO_PC23B_PWML6, GPIO_PERIPH_B, No_Analog_Channel, PWM_CH6, NOT_ON_TIMER }, // PWML6
  { PORTC, PIO_PC22B_PWML5, GPIO_PERIPH_B, No_Analog_Channel, PWM_CH5, NOT_ON_TIMER }, // PWML5
  { PORTC, PIO_PC21B_PWML4, GPIO_PERIPH_B, No_Analog_Channel, PWM_CH4, NOT_ON_TIMER }, // PWML4
  // 10
  { PORTC, PIO_PC29B_TIOB7, GPIO_PERIPH_B, No_Analog_Channel, NOT_ON_PWM, TC2_CHB7 }, // TIOB7
  { PORTD, PIO_PD7B_TIOA8, GPIO_PERIPH_B, No_Analog_Channel, NOT_ON_PWM, TC2_CHA8 }, // TIOA8
  { PORTD, PIO_PD8B_TIOB8, GPIO_PERIPH_B, No_Analog_Channel, NOT_ON_PWM, TC2_CHB8 }, // TIOB8

  // 13 - AMBER LED
  { PORTB, PIO_PB27B_TIOB0, GPIO_PERIPH_B, No_Analog_Channel, NOT_ON_PWM, TC0_CHB0 }, // TIOB0

#if 0
  // 14/15 - USART3 (Serial3)
  { PORTD, PIO_PD4B_TXD3, GPIO_PERIPH_B, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // TXD3
  { PORTD, PIO_PD5B_RXD3, GPIO_PERIPH_B, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // RXD3

  // 16/17 - USART1 (Serial2)
  { PORTA, PIO_PA13A_TXD1, GPIO_PERIPH_A, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // TXD1
  { PORTA, PIO_PA12A_RXD1, GPIO_PERIPH_A, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // RXD1

  // 18/19 - USART0 (Serial1)
  { PORTA, PIO_PA11A_TXD0, GPIO_PERIPH_A, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // TXD0
  { PORTA, PIO_PA10A_RXD0, GPIO_PERIPH_A, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // RXD0

  // 20/21 - TWI1
  { PORTB, PIO_PB12A_TWD1, GPIO_PERIPH_A, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // TWD1 - SDA0
  { PORTB, PIO_PB13A_TWCK1, GPIO_PERIPH_A, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // TWCK1 - SCL0

  // 22
  { PORTB, PIO_PB26, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // PIN 22
  { PORTA, PIO_PA14, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // PIN 23
  { PORTA, PIO_PA15, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // PIN 24
  { PORTD, PIO_PD0, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // PIN 25

  // 26
  { PORTD, PIO_PD1, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // PIN 26
  { PORTD, PIO_PD2, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // PIN 27
  { PORTD, PIO_PD3, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // PIN 28
  { PORTD, PIO_PD6, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // PIN 29

  // 30
  { PORTD, PIO_PD9, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // PIN 30
  { PORTA, PIO_PA7, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // PIN 31
  { PORTD, PIO_PD10, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // PIN 32
  { PORTC, PIO_PC1, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // PIN 33

  // 34
  { PORTC, PIO_PC2, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // PIN 34
  { PORTC, PIO_PC3, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // PIN 35
  { PORTC, PIO_PC4, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // PIN 36
  { PORTC, PIO_PC5, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // PIN 37

  // 38
  { PORTC, PIO_PC6, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // PIN 38
  { PORTC, PIO_PC7, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // PIN 39
  { PORTC, PIO_PC8, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // PIN 40
  { PORTC, PIO_PC9, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // PIN 41

  // 42
  { PORTA, PIO_PA19, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // PIN 42
  { PORTA, PIO_PA20, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // PIN 43
  { PORTC, PIO_PC19, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // PIN 44
  { PORTC, PIO_PC18, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // PIN 45

  // 46
  { PORTC, PIO_PC17, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // PIN 46
  { PORTC, PIO_PC16, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // PIN 47
  { PORTC, PIO_PC15, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // PIN 48
  { PORTC, PIO_PC14, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // PIN 49

  // 50
  { PORTC, PIO_PC13, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // PIN 50
  { PORTC, PIO_PC12, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // PIN 51
  { PORTB, PIO_PB21, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // PIN 52
  { PORTB, PIO_PB14, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // PIN 53


  // 54 .. 65 - Analog pins
  // ----------------------
  { PORTA, PIO_PA16X1_AD7, GPIO_NOMUX, ADC_Channel7, NOT_ON_PWM, NOT_ON_TIMER }, // AD0
  { PORTA, PIO_PA24X1_AD6, GPIO_NOMUX, ADC_Channel6, NOT_ON_PWM, NOT_ON_TIMER }, // AD1
  { PORTA, PIO_PA23X1_AD5, GPIO_NOMUX, ADC_Channel5, NOT_ON_PWM, NOT_ON_TIMER }, // AD2
  { PORTA, PIO_PA22X1_AD4, GPIO_NOMUX, ADC_Channel4, NOT_ON_PWM, NOT_ON_TIMER }, // AD3
  // 58
  { PORTA, PIO_PA6X1_AD3, GPIO_NOMUX, ADC_Channel3, NOT_ON_PWM, TC0_CHB2 }, // AD4
  { PORTA, PIO_PA4X1_AD2, GPIO_NOMUX, ADC_Channel2, NOT_ON_PWM, NOT_ON_TIMER }, // AD5
  { PORTA, PIO_PA3X1_AD1, GPIO_NOMUX, ADC_Channel1, NOT_ON_PWM, TC0_CHB1 }, // AD6
  { PORTA, PIO_PA2X1_AD0, GPIO_NOMUX, ADC_Channel0, NOT_ON_PWM, TC0_CHA1 }, // AD7
  // 62
  { PORTB, PIO_PB17X1_AD10, GPIO_NOMUX, ADC_Channel10, NOT_ON_PWM, NOT_ON_TIMER }, // AD8
  { PORTB, PIO_PB18X1_AD11, GPIO_NOMUX, ADC_Channel11, NOT_ON_PWM, NOT_ON_TIMER }, // AD9
  { PORTB, PIO_PB19X1_AD12, GPIO_NOMUX, ADC_Channel12, NOT_ON_PWM, NOT_ON_TIMER }, // AD10
  { PORTB, PIO_PB20X1_AD13, GPIO_NOMUX, ADC_Channel13, NOT_ON_PWM, NOT_ON_TIMER }, // AD11

  // 66/67 - DAC0/DAC1
  { PORTB, PIO_PB15X1_DAC0, GPIO_NOMUX, DAC_Channel0, NOT_ON_PWM, NOT_ON_TIMER }, // DAC0
  { PORTB, PIO_PB16X1_DAC1, GPIO_NOMUX, DAC_Channel1, NOT_ON_PWM, NOT_ON_TIMER }, // DAC1

  // 68/69 - CANRX0/CANTX0
  { PORTA, PIO_PA1A_CANRX0, GPIO_PERIPH_A, NOT_ON_PWM, NOT_ON_TIMER }, // CANRX
  { PORTA, PIO_PA0A_CANTX0, GPIO_PERIPH_A, NOT_ON_PWM, NOT_ON_TIMER }, // CANTX

  // 70/71 - TWI0
  { PORTA, PIO_PA17A_TWD0, GPIO_PERIPH_A, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // TWD0 - SDA1
  { PORTA, PIO_PA18A_TWCK0, GPIO_PERIPH_A, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // TWCK0 - SCL1

  // 72/73 - LEDs
  { PORTC, PIO_PC30, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // LED AMBER RXL
  { PORTA, PIO_PA21, GPIO_NOMUX, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // LED AMBER TXL

  // 74/75/76 - SPI
  { PORTA, PIO_PA25A_SPI0_MISO, GPIO_PERIPH_A, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // MISO
  { PORTA, PIO_PA26A_SPI0_MOSI, GPIO_PERIPH_A, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // MOSI
  { PORTA, PIO_PA27A_SPI0_SPCK, GPIO_PERIPH_A, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // SPCK

  // 77 - SPI CS0
  { PORTA, PIO_PA28A_SPI0_NPCS0, GPIO_PERIPH_A, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // NPCS0

  // 78 - SPI CS3 (unconnected)
  { PORTB, PIO_PB23B_SPI0_NPCS3, GPIO_PERIPH_B, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // NPCS3

  // 79 .. 84 - "All pins" masks

  // 79 - TWI0 all pins
  { PORTA, PIO_PA17A_TWD0|PIO_PA18A_TWCK0, GPIO_PERIPH_A, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER },
  // 80 - TWI1 all pins
  { PORTB, PIO_PB12A_TWD1|PIO_PB13A_TWCK1, GPIO_PERIPH_A, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER },
  // 81 - UART (Serial) all pins
  { PORTA, PIO_PA8A_URXD|PIO_PA9A_UTXD, GPIO_PERIPH_A, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER },
  // 82 - USART0 (Serial1) all pins
  { PORTA, PIO_PA11A_TXD0|PIO_PA10A_RXD0, GPIO_PERIPH_A, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER },
  // 83 - USART1 (Serial2) all pins
  { PORTA, PIO_PA13A_TXD1|PIO_PA12A_RXD1, GPIO_PERIPH_A, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER },
  // 84 - USART3 (Serial3) all pins
  { PORTD, PIO_PD4B_TXD3|PIO_PD5B_RXD3, GPIO_PERIPH_B, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER },

  // 85 - USB
  { PORTB, PIO_PB11A_UOTGID|PIO_PB10A_UOTGVBOF, GPIO_PERIPH_A, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // ID - VBOF

  // 86 - SPI CS2
  { PORTB, PIO_PB21B_SPI0_NPCS2, GPIO_PERIPH_B, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // NPCS2

  // 87 - SPI CS1
  { PORTA, PIO_PA29A_SPI0_NPCS1, GPIO_PERIPH_A, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // NPCS1

  // 88/89 - CANRX1/CANTX1 (same physical pin for 66/53)
  { PORTB, PIO_PB15A_CANRX1, GPIO_PERIPH_A, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // CANRX1
  { PORTB, PIO_PB14A_CANTX1, GPIO_PERIPH_A, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }, // CANTX1

  // 90 .. 91 - "All CAN pins" masks
  // 90 - CAN0 all pins
  { PORTA, PIO_PA1A_CANRX0|PIO_PA0A_CANTX0, GPIO_PERIPH_A, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER },
  // 91 - CAN1 all pins
  { PORTB, PIO_PB15A_CANRX1|PIO_PB14A_CANTX1, GPIO_PERIPH_A, No_Analog_Channel, NOT_ON_PWM, NOT_ON_TIMER }
#endif // 0
} ;

#ifdef __cplusplus
}
#endif

#if 0 // TODO Serial
/*
 * Serialx objects
 */
SAMSerial Serial((Usart*)UART0, UART0_IRQn, ID_UART0);
void serialEvent() __attribute__((weak));
void serialEvent() { }

// IT handlers
void UART0_Handler(void)
{
  Serial.IrqHandler();
}

SAMSerial Serial1(USART0, USART0_IRQn, ID_USART0);
void serialEvent1() __attribute__((weak));
void serialEvent1() { }
SAMSerial Serial2(USART1, USART1_IRQn, ID_USART1);
void serialEvent2() __attribute__((weak));
void serialEvent2() { }
SAMSerial Serial3(USART3, USART3_IRQn, ID_USART3);
void serialEvent3() __attribute__((weak));
void serialEvent3() { }

// IT handlers
void USART0_Handler(void)
{
  Serial1.IrqHandler();
}

void USART1_Handler(void)
{
  Serial2.IrqHandler();
}

void USART3_Handler(void)
{
  Serial3.IrqHandler();
}

// ----------------------------------------------------------------------------

void serialEventRun(void)
{
  if (Serial.available()) serialEvent();
  if (Serial1.available()) serialEvent1();
  if (Serial2.available()) serialEvent2();
  if (Serial3.available()) serialEvent3();
}
#endif // TODO Serial

// ----------------------------------------------------------------------------


