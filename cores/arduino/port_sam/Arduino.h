/*
  Arduino.h - Main include file for the Arduino SDK
  Copyright (c) 2005-2013 Arduino Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef Arduino_h
#define Arduino_h

#include <stdint.h>
#define __STRICT_ANSI__
#include <stdlib.h>
#undef __STRICT_ANSI__
#include <string.h>
#include <math.h>

// Some libraries and sketches depend on this
// AVR stuff, assuming Arduino.h automatically includes it...
#include "avr_compat/core_pgmspace.h"
#include "avr_compat/core_interrupt.h"

#include "core_binary.h"
#include "core_itoa.h"

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

// Includes Atmel CMSIS headers
#include "sam.h"

#include "core_constants.h"
#include "core_variant.h"

#define clockCyclesPerMicrosecond() ( SystemCoreClock / 1000000L )
#define clockCyclesToMicroseconds(a) ( ((a) * 1000L) / (SystemCoreClock / 1000L) )
#define microsecondsToClockCycles(a) ( (a) * (SystemCoreClock / 1000000L) )

extern void yield(void);

/* sketch */
extern void setup( void ) ;
extern void loop( void ) ;

//typedef void (*voidFuncPtr)( void ) ;

/* Define attribute */
//#define WEAK __attribute__ ((weak))

#ifdef __cplusplus
} // extern "C"

#include "CoreTone.h"
#include "core_pulse.h"
#include "CoreMath.h"
#include "CoreString.h"
#include "CoreHardwareSerial.h"

#endif // __cplusplus

// Include board variant
#include "variant.h"

#include "core.h"
#include "core_delay.h"
#include "core_digital.h"
#include "core_analog.h"
#include "core_shift.h"
#include "core_interrupts.h"

// USB Device
/*
#include "USB/USBDesc.h"
#include "USB/USBCore.h"
#include "USB/USBAPI.h"
*/

#endif // Arduino_h
