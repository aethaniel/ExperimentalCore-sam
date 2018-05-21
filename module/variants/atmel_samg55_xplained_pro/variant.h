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

#ifndef _VARIANT_ATMEL_SAMG55_XPLAINED_PRO_H_
#define _VARIANT_ATMEL_SAMG55_XPLAINED_PRO_H_

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
#include "CoreWire.hpp"
#endif // __cplusplus

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/

// Number of pins defined in PinDescription array
#define PINS_COUNT           (20ul) //(35ul) //(sizeof(g_aPinMap)/sizeof(g_aPinMap[0]))
#define NUM_DIGITAL_PINS     (27ul)
#define NUM_ANALOG_INPUTS    (4ul)
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
#define PIN_LED_13           (6u)
#define PIN_LED              PIN_LED_13
#define LED_BUILTIN          PIN_LED_13

/*
 * Analog pins
 */
#define PIN_A0               (22ul)
#define PIN_A1               (23ul)
#define PIN_A2               (24ul)
#define PIN_A3               (25ul)

static const uint8_t A0  = PIN_A0 ;
static const uint8_t A1  = PIN_A1 ;
static const uint8_t A2  = PIN_A2 ;
static const uint8_t A3  = PIN_A3 ;
#define ADC_RESOLUTION		12

/*
 * Serial interfaces
 */
// Serial (EDBG)
#define PIN_SERIAL_RX       (0ul)
#define PIN_SERIAL_TX       (1ul)

// Serial1
#define PIN_SERIAL1_RX       (2ul)
#define PIN_SERIAL1_TX       (3ul)

// Serial2
#define PIN_SERIAL2_RX       (4ul)
#define PIN_SERIAL2_TX       (5ul)

#if 0 // TODO SPI
/*
 * SPI Interfaces
 */
#define SPI_INTERFACES_COUNT 1

#define SPI_INTERFACE        SPI
#define SPI_INTERFACE_ID     ID_SPI
#define SPI_CHANNELS_NUM     2

#define PIN_SPI_MISO         (ul)
#define PIN_SPI_MOSI         (ul)
#define PIN_SPI_SCK          (ul)
#define PIN_SPI_SS0          (ul)
#define PIN_SPI_SS1          (ul)

static const uint8_t SS	  = PIN_SPI_SS0;
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK  = PIN_SPI_SCK;
#endif // TODO SPI

/*
 * Wire Interfaces
 */
#define WIRE_INTERFACES_COUNT 2

#define PIN_WIRE_SDA         (26ul)
#define PIN_WIRE_SCL         (27ul)
//#define PIN_WIRE_SDA_PERIPH  (GPIO_PERIPH_B)
//#define PIN_WIRE_SCL_PERIPH  (GPIO_PERIPH_B)
#define WIRE_INTERFACE       TWI6
//#define WIRE_INTERFACE_ID    ID_FLEXCOM6
//#define WIRE_ISR_HANDLER     FLEXCOM6_Handler
//#define WIRE_ISR_ID          FLEXCOM6_IRQn

#define PIN_WIRE1_SDA        (28ul)
#define PIN_WIRE1_SCL        (29ul)
//#define PIN_WIRE1_SDA_PERIPH (GPIO_PERIPH_A)
//#define PIN_WIRE1_SCL_PERIPH (GPIO_PERIPH_A)
#define WIRE1_INTERFACE      TWI4
//#define WIRE1_INTERFACE_ID   ID_FLEXCOM4
//#define WIRE1_ISR_HANDLER    FLEXCOM4_Handler
//#define WIRE1_ISR_ID         FLEXCOM4_IRQn

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
extern SAMSerial Serial2;

extern TwoWire Wire;
extern TwoWire Wire1;

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
#define SERIAL_PORT_HARDWARE1       Serial2
#define SERIAL_PORT_HARDWARE_OPEN   Serial1
#define SERIAL_PORT_HARDWARE_OPEN1  Serial2

#endif /* _VARIANT_ATMEL_SAMG55_XPLAINED_PRO_H_ */

