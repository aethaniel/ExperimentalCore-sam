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

#ifndef _VARIANT_QBOARD_H_
#define _VARIANT_QBOARD_H_

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/** Frequency of the board main oscillator */
#define VARIANT_MAINOSC   (32768ul) // This system has an on-board 32KHz oscillator

/** Master clock frequency */
#define VARIANT_MCK       (F_CPU) //(120000000ul)

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "core_variant.h"

#ifdef __cplusplus
#include "CoreSerial.hpp"
#endif // __cplusplus

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/

// Number of pins defined in PinDescription array
#define PINS_COUNT           (25ul)
#define NUM_DIGITAL_PINS     (15ul)
#define NUM_ANALOG_INPUTS    (7ul)
#define NUM_ANALOG_OUTPUTS   (0ul)

//#define analogInPinToBit(P)        ( )
#define portOutputRegister(port)   ( &(port->PIO_ODSR) )
#define portInputRegister(port)    ( &(port->PIO_PDSR) )

/*
 * portModeRegister(..) should return a register to set pin mode
 * INPUT or OUTPUT by setting the corresponding bit to 0 or 1.
 * Unfortunately on SAM architecture the PIO_OSR register is
 * read-only and can be set only through the enable/disable registers
 * pair PIO_OER/PIO_ODR.
 */
// #define portModeRegister(port)   ( &(port->PIO_OSR) )

#define digitalPinHasPWM(P)        ( g_aPinMap[P].ulPWMChannel != NOT_ON_PWM || g_aPinMap[P].ulTCChannel != NOT_ON_TIMER )

/*
 * digitalPinToTimer(..) is AVR-specific and is not defined for SAM
 * architecture. If you need to check if a pin supports PWM you must
 * use digitalPinHasPWM(..).
 *
 * https://github.com/arduino/Arduino/issues/1833
 */
// #define digitalPinToTimer(P)

// Interrupts
#define digitalPinToInterrupt(p)  ((p) < NUM_DIGITAL_PINS ? (p) : -1)

// LEDs
#define PIN_LED_GREEN        (22u)
#define PIN_LED_YELLOW       (23u)

#define PIN_LED_13           PIN_LED_GREEN
#define PIN_LED              PIN_LED_13
#define PIN_LED2             PIN_LED_YELLOW
#define LED_BUILTIN          PIN_LED_13
#define LED_BUILTIN2         PIN_LED_YELLOW

// Button
#define PIN_BUTTON_USR       (24u)

/*
 * Analog pins
 */
#if 0 // TODO Analog pins
#define PIN_A0               (15ul)
#define PIN_A1               (16ul)
#define PIN_A2               (17ul)
#define PIN_A3               (18ul)
#define PIN_A4               (19ul)
#define PIN_A5               (20ul)
#define PIN_A6               (21ul)

static const uint8_t A0  = PIN_A0 ;
static const uint8_t A1  = PIN_A1 ;
static const uint8_t A2  = PIN_A2 ;
static const uint8_t A3  = PIN_A3 ;
static const uint8_t A4  = PIN_A4 ;
static const uint8_t A5  = PIN_A5 ;
static const uint8_t A6  = PIN_A6 ;
#define ADC_RESOLUTION		12
#endif // TODO Analog pins

/*
 * Serial interfaces
 */
// Serial (EDBG)
#define PIN_SERIAL_RX       (25ul)
#define PIN_SERIAL_TX       (26ul)

// Serial1
#define PIN_SERIAL1_RX       (13ul)
#define PIN_SERIAL1_TX       (14ul)

#if 0 // TODO SPI
/*
 * SPI Interfaces
 */
#define SPI_INTERFACES_COUNT 2

#define SPI_INTERFACE        SPI2
#define SPI_INTERFACE_ID     ID_FLEXCOM2
#define SPI_CHANNELS_NUM     1

#define PIN_SPI_MOSI         (8ul)
#define PIN_SPI_MISO         (10ul)
#define PIN_SPI_SCK          (9ul)
#define PIN_SPI_SS0          (0xfful)

static const uint8_t SS	  = PIN_SPI_SS0;
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK  = PIN_SPI_SCK;
#endif // TODO SPI

/*
 * WiFi
 */
#define PIN_WINC3400_BASE    (27ul)
#define PIN_WINC3400_MOSI    (PIN_WINC3400_BASE)
#define PIN_WINC3400_MISO    (PIN_WINC3400_BASE+1)
#define PIN_WINC3400_SCK     (PIN_WINC3400_BASE+2)
#define PIN_WINC3400_SS      (PIN_WINC3400_BASE+3)
#define PERIPH_WINC3400      SPI5
//#define PAD_WINC3400_TX      SPI_PAD_2_SCK_3
//#define PAD_WINC3400_RX      SERCOM_RX_PAD_0

#define PIN_WINC3400_IRQN    (PIN_WINC3400_BASE+4)
#define PIN_WINC3400_WAKE    (PIN_WINC3400_BASE+5)
#define PIN_WINC3400_RESET   (PIN_WINC3400_BASE+6)
#define PIN_WINC3400_CHIP_EN (PIN_WINC3400_BASE+7)
#define PIN_WINC3400_RTC_CLK (PIN_WINC3400_BASE+8)

#define WINC3400_RESET_PIN   PIN_WINC3400_RESET
#define WINC3400_INTN_PIN    PIN_WINC3400_IRQN
#define WINC3400_CHIP_EN_PIN PIN_WINC3400_CHIP_EN

/*
 * WINC3400 Bluetooth
 */
//#define PIN_WINC3400_BT_RX   (PIN_WINC3400_BASE+9)
//#define PIN_WINC3400_BT_TX   (PIN_WINC3400_BASE+10)
//#define PIN_WINC3400_BT_RTS  (PIN_WINC3400_BASE+11)
//#define PIN_WINC3400_BT_CTS  (PIN_WINC3400_BASE+12)

#if 0 // TODO Wire
/*
 * Wire Interfaces
 */
#define WIRE_INTERFACES_COUNT 1

#define PIN_WIRE_SDA         (11ul)
#define PIN_WIRE_SCL         (12ul)
#endif // TODO Wire

#if 0 // TODO USB
/*
 * USB
 */
#define PIN_USB_HOST_ENABLE  (ul)
#define PIN_USB_DM           (ul)
#define PIN_USB_DP           (ul)
#endif // TODO USB

#ifdef __cplusplus
}
#endif

/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus

extern SAMSerial Serial;
extern SAMSerial Serial1;

#endif

// These serial port names are intended to allow libraries and architecture-neutral
// sketches to automatically default to the correct port name for a particular type
// of use.  For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
// the first hardware serial port whose RX/TX pins are not dedicated to another use.
//
// SERIAL_PORT_MONITOR        Port which normally prints to the Arduino Serial Monitor
//
// SERIAL_PORT_USBVIRTUAL     Port which is USB virtual serial
//
// SERIAL_PORT_LINUXBRIDGE    Port which connects to a Linux system via Bridge library
//
// SERIAL_PORT_HARDWARE       Hardware serial port, physical RX & TX pins.
//
// SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
//                            pins are NOT connected to anything by default.
#define SERIAL_PORT_USBVIRTUAL      SerialUSB
#define SERIAL_PORT_MONITOR         Serial
// Serial has no physical pins broken out, so it's not listed as HARDWARE port
#define SERIAL_PORT_HARDWARE        Serial1
#define SERIAL_PORT_HARDWARE_OPEN   Serial1

#endif /* _VARIANT_QBOARD_H_ */

