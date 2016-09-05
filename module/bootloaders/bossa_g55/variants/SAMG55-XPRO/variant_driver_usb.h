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

#ifndef _VARIANT_DRIVER_USB_H_
#define _VARIANT_DRIVER_USB_H_

#include "../../sam_ba_cdc.h"

#define USB_DEVICE USBDev

P_USB_CDC USB_Open(P_USB_CDC pCdc, USB_DEVICE *pUsb);

void USB_Init(void);

uint32_t USB_Write(USB_DEVICE *pUsb, const char *pData, uint32_t length, uint8_t ep_num);
uint32_t USB_Read(USB_DEVICE *pUsb, char *pData, uint32_t length);

uint8_t USB_IsConfigured(P_USB_CDC pCdc);

void USB_SendStall(USB_DEVICE *pUsb);
void USB_SendZlp(USB_DEVICE *pUsb);

void USB_SetAddress(USB_DEVICE *pUsb, uint16_t wValue);
void USB_Configure(USB_DEVICE *pUsb);

#endif // _VARIANT_DRIVER_USB_H_
