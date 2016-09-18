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
#include "variant_driver_usb.h"
#include "../../misc.h"

#define USB_COMMON_CFG_BITS (USBDEV_CSR_RX_DATA_BK0 | USBDEV_CSR_RX_DATA_BK1 | USBDEV_CSR_STALLSENT | USBDEV_CSR_RXSETUP | USBDEV_CSR_TXCOMP)

static uint32_t g_currentReceiveBank = USBDEV_CSR_RX_DATA_BK0;

/*----------------------------------------------------------------------------
 * \brief
 */
P_USB_CDC USB_Open(P_USB_CDC pCdc, USB_DEVICE *pUsb)
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
  USBDEV->USBDEV_TXVC  = USBDEV_TXVC_TXVDIS; // reset PUON and set TXVDIS
  /* Enables the 48MHz USB clock UDPCK */
  PMC->PMC_SCER = PMC_SCER_UDP;

  /* Set device mode */
  MATRIX->CCFG_USBMR |= CCFG_USBMR_USBMODE ;

  MATRIX->CCFG_SYSIO &=  ~(CCFG_SYSIO_SYSIO10 | CCFG_SYSIO_SYSIO11);

  /* Enable USB clock */
  PMC->PMC_PCER1 = (1 << (ID_USBDEV - 32));

  /* Enable the pull-up */
  USBDEV->USBDEV_TXVC = USBDEV_TXVC_PUON; // Set PUON and Clear TXVDIS
}

uint32_t USB_Write(USB_DEVICE *pUsb, const char *pData, uint32_t length, uint8_t ep_num)
{
  uint32_t cpt = 0;
  volatile uint32_t i = 0;

  // Send the first packet
  cpt = min_u32(length, BOARD_USB_EP_CDC_IN_SIZE);
  length -= cpt;

  while (cpt--) pUsb->USBDEV_FDR[BOARD_USB_EP_CDC_IN] = *pData++;
  {
    pUsb->USBDEV_CSR[BOARD_USB_EP_CDC_IN] |= USB_COMMON_CFG_BITS | USBDEV_CSR_TXPKTRDY;
  }

  while ( length )
  {
    // Needed for UDP CSR Synchro
    for (i = 0; i < 15; i++);

    // Fill the second bank
    cpt = min_u32(length, BOARD_USB_EP_CDC_IN_SIZE);
    length -= cpt;
    while (cpt--)
    {
      pUsb->USBDEV_FDR[BOARD_USB_EP_CDC_IN] = *pData++;
    }

    // Wait for the the first bank to be sent
    while ( !(pUsb->USBDEV_CSR[BOARD_USB_EP_CDC_IN] & USBDEV_CSR_TXCOMP) )
    {
/* TODO G55
      if ( !USB_IsConfigured(pCdc) )
      {
        return length;
      }
*/
    }
    pUsb->USBDEV_CSR[BOARD_USB_EP_CDC_IN] &= ~(USBDEV_CSR_TXCOMP);

    while (pUsb->USBDEV_CSR[BOARD_USB_EP_CDC_IN] & USBDEV_CSR_TXCOMP);

    pUsb->USBDEV_CSR[BOARD_USB_EP_CDC_IN] |= USB_COMMON_CFG_BITS | USBDEV_CSR_TXPKTRDY;
  }

  // Wait for the end of transfer
  while ( !(pUsb->USBDEV_CSR[BOARD_USB_EP_CDC_IN] & USBDEV_CSR_TXCOMP) )
  {
/* TODO G55
    if ( !USB_IsConfigured(pCdc) )
    {
      return length;
    }
*/
  }
  pUsb->USBDEV_CSR[BOARD_USB_EP_CDC_IN] &= ~(USBDEV_CSR_TXCOMP);

  while (pUsb->USBDEV_CSR[BOARD_USB_EP_CDC_IN] & USBDEV_CSR_TXCOMP);

  return length;
}

/*----------------------------------------------------------------------------
 * \brief Read available data from Endpoint OUT
 */
uint32_t USB_Read(USB_DEVICE *pUsb, char *pData, uint32_t length)
{
  uint32_t ulPacketSize = 0;
  uint32_t ulBytesReceived = 0;
  uint32_t currentReceiveBank = g_currentReceiveBank;

  while (!ulBytesReceived)
  {
/* TODO G55
    if ( !USB_IsConfigured(pCdc) )
    {
      break;
    }
*/
    if ( pUsb->USBDEV_CSR[BOARD_USB_EP_CDC_OUT] & currentReceiveBank )
    {
      for ( ulPacketSize = min_u32(pUsb->USBDEV_CSR[BOARD_USB_EP_CDC_OUT] >> 16, length) ; ulPacketSize-- ; )
      {
        pData[ulBytesReceived++] = pUsb->USBDEV_FDR[BOARD_USB_EP_CDC_OUT];
      }

      pUsb->USBDEV_CSR[BOARD_USB_EP_CDC_OUT] &= ~(currentReceiveBank);

      if ( currentReceiveBank == USBDEV_CSR_RX_DATA_BK0 )
      {
        currentReceiveBank = USBDEV_CSR_RX_DATA_BK1;
      }
      else
      {
        currentReceiveBank = USBDEV_CSR_RX_DATA_BK0;
      }
    }
  }

  g_currentReceiveBank = currentReceiveBank;

  return ulBytesReceived;
}

/*----------------------------------------------------------------------------
 * \brief Test if the device is configured and handle enumeration
 */
uint8_t USB_IsConfigured(P_USB_CDC pCdc)
{
  USBDev *pUsb = pCdc->pUsb;
	uint32_t isr = pUsb->USBDEV_ISR;

  /* Check for End of Reset flag */

// TODOG55
  // Suspend
  if (isr & USBDEV_ISR_RXSUSP)
  {
    pCdc->currentConfiguration = 0;
    // Acknowledge interrupt
    pUsb->USBDEV_ICR = USBDEV_ICR_RXSUSP;
  }
  // End Of Bus Reset
  else
  {
    if (isr & USBDEV_ISR_ENDBUSRES)
    {
      // Reset current configuration value to 0
      pCdc->currentConfiguration = 0;
//      pCdc->GetSetInterface = 0;
      // reset all endpoints
      pUsb->USBDEV_RST_EP  = (uint32_t) -1;
      pUsb->USBDEV_RST_EP  = 0;
      // Enable the function address
      pUsb->USBDEV_FADDR = USBDEV_FADDR_FEN;
      // Configure endpoint 0
      pUsb->USBDEV_CSR[0] = USB_COMMON_CFG_BITS | USBDEV_CSR_EPEDS | USBDEV_CSR_EPTYPE_CTRL;
      pUsb->USBDEV_ICR = USBDEV_ICR_ENDBUSRES;
    }
    // Endpoint
    else
    {
      if (isr & USBDEV_ISR_EP0INT)
      {
// TODO G55        CDC_Enumerate(pCdc);
      }
      // else Nothing to do
    }
  }

  return pCdc->currentConfiguration;
}

/*----------------------------------------------------------------------------
 * \brief Stall the control endpoint
 */
void USB_SendStall(USB_DEVICE *pUsb)
{
  pUsb->USBDEV_CSR[0] |= USB_COMMON_CFG_BITS | USBDEV_CSR_FORCESTALL;
  while ( !(pUsb->USBDEV_CSR[0] & USBDEV_CSR_STALLSENT) );
  pUsb->USBDEV_CSR[0] &= ~(USBDEV_CSR_FORCESTALL | USBDEV_CSR_STALLSENT);
  while (pUsb->USBDEV_CSR[0] & (USBDEV_CSR_FORCESTALL | USBDEV_CSR_STALLSENT));
}

/*----------------------------------------------------------------------------
 * \brief Send zero length packet through the control endpoint
 */
void USB_SendZlp(USB_DEVICE *pUsb)
{
  pUsb->USBDEV_CSR[0] |= USB_COMMON_CFG_BITS | USBDEV_CSR_TXPKTRDY;
  while ( !(pUsb->USBDEV_CSR[0] & USBDEV_CSR_TXCOMP) );
  pUsb->USBDEV_CSR[0] &= ~(USBDEV_CSR_TXCOMP);
  while (pUsb->USBDEV_CSR[0] & USBDEV_CSR_TXCOMP);
}

/*----------------------------------------------------------------------------
 * \brief Set USB device address obtained from host
 */
void USB_SetAddress(USB_DEVICE *pUsb, uint16_t wValue)
{
  USB_SendZlp(pUsb);
  pUsb->USBDEV_FADDR = ( (wValue&0x7F) | USBDEV_FADDR_FEN );
  pUsb->USBDEV_GLB_STAT  = (wValue&0x7F) ? USBDEV_GLB_STAT_FADDEN : 0;
}

/*----------------------------------------------------------------------------
 * \brief Configure USB device
 */
void USB_Configure(USB_DEVICE *pUsb)
{
// TODOG55
}
