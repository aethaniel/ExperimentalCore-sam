/*
  Copyright (c) 2015 Arduino LLC.  All right reserved.
  Copyright (c) 2015 Atmel Corporation/Thibaut VIARD.  All right reserved.

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

#ifndef CDC_ENUMERATE_H
#define CDC_ENUMERATE_H

#include <sam.h>
#include <stdbool.h>
#include "variant_definitions.h"
#include "usb_chapter9.h"

typedef struct _USB_CDC
{
	// Private members
	USBDev *pUsb;
	uint8_t currentConfiguration;
	uint8_t currentConnection;
	// Public Methods:
	uint8_t (*IsConfigured)(struct _USB_CDC *pCdc);
//	uint32_t (*Write) (Usb *pUsb, const char *pData, uint32_t length, uint8_t ep_num);
//	uint32_t (*Read)  (Usb *pUsb, char *pData, uint32_t length);
} USB_CDC, *P_USB_CDC;

/**
 * \brief Initializes the USB module
 *
 * \return Pointer to the USB CDC structure
 */
P_USB_CDC usb_init(void);

void sam_ba_usb_CDC_Enumerate(P_USB_CDC pCdc);

#if 0 // TODO: pending validation
uint32_t USB_SendString(USBDev *pUsb, const char* ascii_string, uint8_t length, uint8_t maxLength);
#endif // 0

extern USB_CDC sam_ba_cdc;



#endif // CDC_ENUMERATE_H
