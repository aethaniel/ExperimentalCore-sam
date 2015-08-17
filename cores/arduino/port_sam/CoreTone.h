/*
  Copyright (c) 2015 Thibaut VIARD & Arduino LLC.  All right reserved.

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

#ifndef _ARDUINO_CORE_TONE_
#define _ARDUINO_CORE_TONE_

#include <stdint.h>

void tone(uint32_t pin, uint32_t frequency, uint32_t duration = 0);
void noTone(uint32_t pin);

#endif /* _ARDUINO_CORE_TONE_ */
