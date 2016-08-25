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

#include <string.h>
#include "board_driver_usb.h"
#include "sam_ba_usb.h"
#include "sam_ba_cdc.h"


static volatile bool read_job = false;

/*----------------------------------------------------------------------------
 * \brief
 */
P_USB_CDC USB_Open(P_USB_CDC pCdc, Usb *pUsb)
{
  pCdc->pUsb = pUsb;
  pCdc->currentConfiguration = 0;
  pCdc->currentConnection    = 0;
  pCdc->IsConfigured = USB_IsConfigured;
//  pCdc->Write        = USB_Write;
//  pCdc->Read         = USB_Read;

// TODOG55  pCdc->pUsb->HOST.CTRLA.bit.ENABLE = true;

  return pCdc;
}

/*----------------------------------------------------------------------------
 * \brief Initializes USB
 */
void USB_Init(void)
{
  uint32_t pad_transn, pad_transp, pad_trim;

  /* Enable USB clock */
// TODOG55  PM->APBBMASK.reg |= PM_APBBMASK_USB;

}

uint32_t USB_Write(Usb *pUsb, const char *pData, uint32_t length, uint8_t ep_num)
{
  uint32_t data_address;
  uint8_t buf_index;

  /* Set buffer index */
  buf_index = (ep_num == 0) ? 0 : 1;

  /* Check for requirement for multi-packet or auto zlp */
// TODOG55


  /* Wait for transfer to complete */
// TODOG55  while (  );

  return length;
}

/*----------------------------------------------------------------------------
 * \brief Read available data from Endpoint OUT
 */
uint32_t USB_Read(Usb *pUsb, char *pData, uint32_t length)
{
  uint32_t packetSize = 0;

  if (!read_job)
  {
// TODOG55

    /* set the user flag */
    read_job = true;
  }

  /* Check for Transfer Complete 0 flag */
  if ( pUsb->DEVICE.DeviceEndpoint[USB_EP_OUT].EPINTFLAG.bit.TRCPT & (1<<0) )
  {
// TODOG55

    /* Clear the user flag */
    read_job = false;
  }

  return packetSize;
}

uint32_t USB_Read_blocking(Usb *pUsb, char *pData, uint32_t length)
{
  if (read_job)
  {
    /* Stop the reception by setting the bank 0 ready bit */
// TODOG55    pUsb->DEVICE.DeviceEndpoint[USB_EP_OUT].EPSTATUSSET.bit.BK0RDY = true;
    /* Clear the user flag */
    read_job = false;
  }

// TODOG55

  return length;
}

/*----------------------------------------------------------------------------
 * \brief Test if the device is configured and handle enumeration
 */
uint8_t USB_IsConfigured(P_USB_CDC pCdc)
{
  Usb *pUsb = pCdc->pUsb;

  /* Check for End of Reset flag */

// TODOG55

  return pCdc->currentConfiguration;
}

/*----------------------------------------------------------------------------
 * \brief Stall the control endpoint
 */
void USB_SendStall(Usb *pUsb, bool direction_in)
{
  /* Check the direction */
  if (direction_in)
  {
    /* Set STALL request on IN direction */
// TODOG55
  }
  else
  {
    /* Set STALL request on OUT direction */
// TODOG55
  }
}

/*----------------------------------------------------------------------------
 * \brief Send zero length packet through the control endpoint
 */
void USB_SendZlp(Usb *pUsb)
{
// TODOG55
}

/*----------------------------------------------------------------------------
 * \brief Set USB device address obtained from host
 */
void USB_SetAddress(Usb *pUsb, uint16_t wValue)
{
// TODOG55
}

/*----------------------------------------------------------------------------
 * \brief Configure USB device
 */
void USB_Configure(Usb *pUsb)
{
// TODOG55
}
