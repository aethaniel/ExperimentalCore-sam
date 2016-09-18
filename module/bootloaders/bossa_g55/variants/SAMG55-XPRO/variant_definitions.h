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

#ifndef _VARIANT_DEFINITIONS_H_
#define _VARIANT_DEFINITIONS_H_

/* Frequency of the board main oscillator */
#define BOARD_MAINOSC                             (8000000ul)
#define BOARD_CPU_FREQUENCY                       (120000000ul)

/*
 * The bootloader is started if the selected pin is tied LOW.
 */
#define BOOT_LOAD_PIN                             PIO_PA2 // GPIO port A Pin 2
#define BOOT_LOAD_PIN_PORT                        PIOA // GPIO port A
#define BOOT_LOAD_PIN_PORT_ID                     ID_IOA // GPIO port A ID for input clock
#define BOOT_LOAD_PIN_MASK                        (1U << (BOOT_LOAD_PIN & 0x1f))

/*
 * LEDs definitions
 */
#define BOARD_LED_PORT                            (0)
#define BOARD_LED_PIN                             (17)

#define BOARD_LEDRX_PORT                          (1)
#define BOARD_LEDRX_PIN                           (3)

#define BOARD_LEDTX_PORT                          (0)
#define BOARD_LEDTX_PIN                           (27)

/*
 * Serial definitions
 */
#define BOOT_USART_MODULE                         USART0

/*
 * USB definitions
 */
#define BOARD_USB_EP_CTRL                         (0u)
#define BOARD_USB_EP_CDC_OUT                      (2u)
#define BOARD_USB_EP_CDC_OUT_SIZE                 (0x40u)
#define BOARD_USB_EP_CDC_IN                       (1u)
#define BOARD_USB_EP_CDC_IN_SIZE                  (0x40u)
#define BOARD_USB_EP_CDC_COMM                     (3u)
#define BOARD_USB_EP_MAX                          (4u)

#endif // _VARIANT_DEFINITIONS_H_
