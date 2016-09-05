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

#ifndef _VARIANT_SERIAL_DRIVER_H_
#define _VARIANT_SERIAL_DRIVER_H_

#include <stdio.h>
#include <stdbool.h>
#include <sam.h>

#define PINMUX_UNUSED          0xFFFFFFFF

#define SERIAL Usart

/**
 * \brief Initializes the UART
 *
 * \param Pointer to SERIAL instance
 * \param Baud value corresponding to the desired baudrate
 * \param SERIAL pad settings
 */
void uart_basic_init(SERIAL *serial, uint16_t baud_val);

/**
 * \brief Disables UART interface
 *
 * \param Pointer to SERIAL instance
 */
void uart_disable(SERIAL *serial);

/**
 * \brief Sends a single byte through UART interface
 *
 * \param Pointer to SERIAL instance
 * \param Data to send
 */
void uart_write_byte(SERIAL *serial, uint8_t data);

/**
 * \brief Reads a single character from UART interface
 *
 * \param Pointer to SERIAL instance
 * \return Data byte read
 */
uint8_t uart_read_byte(SERIAL *serial);

/**
 * \brief Sends buffer on UART interface
 *
 * \param Pointer to SERIAL instance
 * \param Pointer to data to send
 * \param Number of bytes to send
 */
void uart_write_buffer_polled(SERIAL *serial, uint8_t *ptr, uint16_t length);

/**
 * \brief Reads data on UART interface
 *
 * \param Pointer to SERIAL instance
 * \param Pointer to store read data
 * \param Number of bytes to read
 */
void uart_read_buffer_polled(SERIAL *serial, uint8_t *ptr, uint16_t length);

#endif // _VARIANT_SERIAL_DRIVER_H_
