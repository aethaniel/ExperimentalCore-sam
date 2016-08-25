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

#include "board_driver_serial.h"

bool uart_drv_error_flag = false;

void uart_basic_init(Usart *serial, uint16_t baud_val, enum uart_pad_settings pad_conf)
{
// TODOG55
}

void uart_disable(Usart *serial)
{
// TODOG55
}

void uart_write_byte(Usart *serial, uint8_t data)
{
// TODOG55
}

uint8_t uart_read_byte(Usart *serial)
{
// TODOG55
	return((uint8_t));
}

void uart_write_buffer_polled(Usart *serial, uint8_t *ptr, uint16_t length)
{
	/* Do the following for specified length */
	do {
// TODOG55
	} while (length--);
}

void uart_read_buffer_polled(Usart *serial, uint8_t *ptr, uint16_t length)
{
	/* Do the following for specified length */
	do {
// TODOG55
	} while (length--);
}
