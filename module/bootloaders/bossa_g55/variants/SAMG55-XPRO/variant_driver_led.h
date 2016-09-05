/*
  Copyright (c) 2015 Arduino LLC.  All right reserved.
  Copyright (c) 2015 Atmel Corporation/Thibaut VIARD.  All right reserved.
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

#ifndef _VARIANT_DRIVER_LED_
#define _VARIANT_DRIVER_LED_

#include <sam.h>
#include "variant_definitions.h"

inline void LED_init(void)   { /* TODOG55; */ }
inline void LED_on(void)     { /* TODOG55; */ }
inline void LED_off(void)    { /* TODOG55; */ }
inline void LED_toggle(void) { /* TODOG55; */ }

inline void LEDRX_init(void)   { /* TODOG55; */ }
inline void LEDRX_on(void)     { /* TODOG55; */ }
inline void LEDRX_off(void)    { /* TODOG55; */ }
inline void LEDRX_toggle(void) { /* TODOG55; */ }

inline void LEDTX_init(void)   { /* TODOG55; */ }
inline void LEDTX_on(void)     { /* TODOG55; */ }
inline void LEDTX_off(void)    { /* TODOG55; */ }
inline void LEDTX_toggle(void) { /* TODOG55; */ }

#endif // _VARIANT_DRIVER_LED_
