/* ---------------------------------------------------------------------------- */
/*                  Atmel Microcontroller Software Support                      */
/*                       SAM Software Package License                           */
/* ---------------------------------------------------------------------------- */
/* Copyright (c) 2015, Atmel Corporation                                        */
/*                                                                              */
/* All rights reserved.                                                         */
/*                                                                              */
/* Redistribution and use in source and binary forms, with or without           */
/* modification, are permitted provided that the following condition is met:    */
/*                                                                              */
/* - Redistributions of source code must retain the above copyright notice,     */
/* this list of conditions and the disclaimer below.                            */
/*                                                                              */
/* Atmel's name may not be used to endorse or promote products derived from     */
/* this software without specific prior written permission.                     */
/*                                                                              */
/* DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR   */
/* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE   */
/* DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,      */
/* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT */
/* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,  */
/* OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF    */
/* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING         */
/* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, */
/* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                           */
/* ---------------------------------------------------------------------------- */

#ifndef _SAMG55_USBDEV_COMPONENT_
#define _SAMG55_USBDEV_COMPONENT_

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR USB Device Port */
/* ============================================================================= */
/** \addtogroup SAMG55_USBDEV USB Device Port */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief USBDev hardware registers */
typedef struct {
  __I  uint32_t USBDEV_FRM_NUM;  /**< \brief (USBDev Offset: 0x000) Frame Number Register */
  __IO uint32_t USBDEV_GLB_STAT; /**< \brief (USBDev Offset: 0x004) Global State Register */
  __IO uint32_t USBDEV_FADDR;    /**< \brief (USBDev Offset: 0x008) Function Address Register */
  __I  uint32_t Reserved1[1];
  __O  uint32_t USBDEV_IER;      /**< \brief (USBDev Offset: 0x010) Interrupt Enable Register */
  __O  uint32_t USBDEV_IDR;      /**< \brief (USBDev Offset: 0x014) Interrupt Disable Register */
  __I  uint32_t USBDEV_IMR;      /**< \brief (USBDev Offset: 0x018) Interrupt Mask Register */
  __I  uint32_t USBDEV_ISR;      /**< \brief (USBDev Offset: 0x01C) Interrupt Status Register */
  __O  uint32_t USBDEV_ICR;      /**< \brief (USBDev Offset: 0x020) Interrupt Clear Register */
  __I  uint32_t Reserved2[1];
  __IO uint32_t USBDEV_RST_EP;   /**< \brief (USBDev Offset: 0x028) Reset Endpoint Register */
  __I  uint32_t Reserved3[1];
  __IO uint32_t USBDEV_CSR[6];   /**< \brief (USBDev Offset: 0x030) Endpoint Control and Status Register */
  __I  uint32_t Reserved4[2];
  __IO uint32_t USBDEV_FDR[6];   /**< \brief (USBDev Offset: 0x050) Endpoint FIFO Data Register */
  __I  uint32_t Reserved5[3];
  __IO uint32_t USBDEV_TXVC;     /**< \brief (USBDev Offset: 0x074) Transceiver Control Register */
} USBDev;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- USBDEV_FRM_NUM : (USBDEV Offset: 0x000) Frame Number Register -------- */
#define USBDEV_FRM_NUM_FRM_NUM_Pos 0
#define USBDEV_FRM_NUM_FRM_NUM_Msk (0x7ffu << USBDEV_FRM_NUM_FRM_NUM_Pos) /**< \brief (USBDEV_FRM_NUM) Frame Number as Defined in the Packet Field Formats */
#define USBDEV_FRM_NUM_FRM_ERR (0x1u << 16) /**< \brief (USBDEV_FRM_NUM) Frame Error */
#define USBDEV_FRM_NUM_FRM_OK (0x1u << 17) /**< \brief (USBDEV_FRM_NUM) Frame OK */
/* -------- USBDEV_GLB_STAT : (USBDEV Offset: 0x004) Global State Register -------- */
#define USBDEV_GLB_STAT_FADDEN (0x1u << 0) /**< \brief (USBDEV_GLB_STAT) Function Address Enable */
#define USBDEV_GLB_STAT_CONFG (0x1u << 1) /**< \brief (USBDEV_GLB_STAT) Configured */
#define USBDEV_GLB_STAT_ESR (0x1u << 2) /**< \brief (USBDEV_GLB_STAT) Enable Send Resume */
#define USBDEV_GLB_STAT_RSMINPR (0x1u << 3) /**< \brief (USBDEV_GLB_STAT)  */
#define USBDEV_GLB_STAT_RMWUPE (0x1u << 4) /**< \brief (USBDEV_GLB_STAT) Remote Wakeup Enable */
/* -------- USBDEV_FADDR : (USBDEV Offset: 0x008) Function Address Register -------- */
#define USBDEV_FADDR_FADD_Pos 0
#define USBDEV_FADDR_FADD_Msk (0x7fu << USBDEV_FADDR_FADD_Pos) /**< \brief (USBDEV_FADDR) Function Address Value */
#define USBDEV_FADDR_FADD(value) ((USBDEV_FADDR_FADD_Msk & ((value) << USBDEV_FADDR_FADD_Pos)))
#define USBDEV_FADDR_FEN (0x1u << 8) /**< \brief (USBDEV_FADDR) Function Enable */
/* -------- USBDEV_IER : (USBDEV Offset: 0x010) Interrupt Enable Register -------- */
#define USBDEV_IER_EP0INT (0x1u << 0) /**< \brief (USBDEV_IER) Enable Endpoint 0 Interrupt */
#define USBDEV_IER_EP1INT (0x1u << 1) /**< \brief (USBDEV_IER) Enable Endpoint 1 Interrupt */
#define USBDEV_IER_EP2INT (0x1u << 2) /**< \brief (USBDEV_IER) Enable Endpoint 2Interrupt */
#define USBDEV_IER_EP3INT (0x1u << 3) /**< \brief (USBDEV_IER) Enable Endpoint 3 Interrupt */
#define USBDEV_IER_EP4INT (0x1u << 4) /**< \brief (USBDEV_IER) Enable Endpoint 4 Interrupt */
#define USBDEV_IER_EP5INT (0x1u << 5) /**< \brief (USBDEV_IER) Enable Endpoint 5 Interrupt */
#define USBDEV_IER_RXSUSP (0x1u << 8) /**< \brief (USBDEV_IER) Enable USBDEV Suspend Interrupt */
#define USBDEV_IER_RXRSM (0x1u << 9) /**< \brief (USBDEV_IER) Enable USBDEV Resume Interrupt */
#define USBDEV_IER_EXTRSM (0x1u << 10) /**< \brief (USBDEV_IER)  */
#define USBDEV_IER_SOFINT (0x1u << 11) /**< \brief (USBDEV_IER) Enable Start Of Frame Interrupt */
#define USBDEV_IER_WAKEUP (0x1u << 13) /**< \brief (USBDEV_IER) Enable USBDEV Bus Wakeup Interrupt */
/* -------- USBDEV_IDR : (USBDEV Offset: 0x014) Interrupt Disable Register -------- */
#define USBDEV_IDR_EP0INT (0x1u << 0) /**< \brief (USBDEV_IDR) Disable Endpoint 0 Interrupt */
#define USBDEV_IDR_EP1INT (0x1u << 1) /**< \brief (USBDEV_IDR) Disable Endpoint 1 Interrupt */
#define USBDEV_IDR_EP2INT (0x1u << 2) /**< \brief (USBDEV_IDR) Disable Endpoint 2 Interrupt */
#define USBDEV_IDR_EP3INT (0x1u << 3) /**< \brief (USBDEV_IDR) Disable Endpoint 3 Interrupt */
#define USBDEV_IDR_EP4INT (0x1u << 4) /**< \brief (USBDEV_IDR) Disable Endpoint 4 Interrupt */
#define USBDEV_IDR_EP5INT (0x1u << 5) /**< \brief (USBDEV_IDR) Disable Endpoint 5 Interrupt */
#define USBDEV_IDR_RXSUSP (0x1u << 8) /**< \brief (USBDEV_IDR) Disable USBDEV Suspend Interrupt */
#define USBDEV_IDR_RXRSM (0x1u << 9) /**< \brief (USBDEV_IDR) Disable USBDEV Resume Interrupt */
#define USBDEV_IDR_EXTRSM (0x1u << 10) /**< \brief (USBDEV_IDR)  */
#define USBDEV_IDR_SOFINT (0x1u << 11) /**< \brief (USBDEV_IDR) Disable Start Of Frame Interrupt */
#define USBDEV_IDR_WAKEUP (0x1u << 13) /**< \brief (USBDEV_IDR) Disable USB Bus Interrupt */
/* -------- USBDEV_IMR : (USBDEV Offset: 0x018) Interrupt Mask Register -------- */
#define USBDEV_IMR_EP0INT (0x1u << 0) /**< \brief (USBDEV_IMR) Mask Endpoint 0 Interrupt */
#define USBDEV_IMR_EP1INT (0x1u << 1) /**< \brief (USBDEV_IMR) Mask Endpoint 1 Interrupt */
#define USBDEV_IMR_EP2INT (0x1u << 2) /**< \brief (USBDEV_IMR) Mask Endpoint 2 Interrupt */
#define USBDEV_IMR_EP3INT (0x1u << 3) /**< \brief (USBDEV_IMR) Mask Endpoint 3 Interrupt */
#define USBDEV_IMR_EP4INT (0x1u << 4) /**< \brief (USBDEV_IMR) Mask Endpoint 4 Interrupt */
#define USBDEV_IMR_EP5INT (0x1u << 5) /**< \brief (USBDEV_IMR) Mask Endpoint 5 Interrupt */
#define USBDEV_IMR_RXSUSP (0x1u << 8) /**< \brief (USBDEV_IMR) Mask USBDEV Suspend Interrupt */
#define USBDEV_IMR_RXRSM (0x1u << 9) /**< \brief (USBDEV_IMR) Mask USBDEV Resume Interrupt. */
#define USBDEV_IMR_EXTRSM (0x1u << 10) /**< \brief (USBDEV_IMR)  */
#define USBDEV_IMR_SOFINT (0x1u << 11) /**< \brief (USBDEV_IMR) Mask Start Of Frame Interrupt */
#define USBDEV_IMR_BIT12 (0x1u << 12) /**< \brief (USBDEV_IMR) USBDEV_IMR Bit 12 */
#define USBDEV_IMR_WAKEUP (0x1u << 13) /**< \brief (USBDEV_IMR) USB Bus Wakeup Interrupt */
/* -------- USBDEV_ISR : (USBDEV Offset: 0x01C) Interrupt Status Register -------- */
#define USBDEV_ISR_EP0INT (0x1u << 0) /**< \brief (USBDEV_ISR) Endpoint 0 Interrupt Status */
#define USBDEV_ISR_EP1INT (0x1u << 1) /**< \brief (USBDEV_ISR) Endpoint 1 Interrupt Status */
#define USBDEV_ISR_EP2INT (0x1u << 2) /**< \brief (USBDEV_ISR) Endpoint 2 Interrupt Status */
#define USBDEV_ISR_EP3INT (0x1u << 3) /**< \brief (USBDEV_ISR) Endpoint 3 Interrupt Status */
#define USBDEV_ISR_EP4INT (0x1u << 4) /**< \brief (USBDEV_ISR) Endpoint 4 Interrupt Status */
#define USBDEV_ISR_EP5INT (0x1u << 5) /**< \brief (USBDEV_ISR) Endpoint 5 Interrupt Status */
#define USBDEV_ISR_RXSUSP (0x1u << 8) /**< \brief (USBDEV_ISR) USBDEV Suspend Interrupt Status */
#define USBDEV_ISR_RXRSM (0x1u << 9) /**< \brief (USBDEV_ISR) USBDEV Resume Interrupt Status */
#define USBDEV_ISR_EXTRSM (0x1u << 10) /**< \brief (USBDEV_ISR)  */
#define USBDEV_ISR_SOFINT (0x1u << 11) /**< \brief (USBDEV_ISR) Start of Frame Interrupt Status */
#define USBDEV_ISR_ENDBUSRES (0x1u << 12) /**< \brief (USBDEV_ISR) End of BUS Reset Interrupt Status */
#define USBDEV_ISR_WAKEUP (0x1u << 13) /**< \brief (USBDEV_ISR) USBDEV Resume Interrupt Status */
/* -------- USBDEV_ICR : (USBDEV Offset: 0x020) Interrupt Clear Register -------- */
#define USBDEV_ICR_RXSUSP (0x1u << 8) /**< \brief (USBDEV_ICR) Clear USBDEV Suspend Interrupt */
#define USBDEV_ICR_RXRSM (0x1u << 9) /**< \brief (USBDEV_ICR) Clear USBDEV Resume Interrupt */
#define USBDEV_ICR_EXTRSM (0x1u << 10) /**< \brief (USBDEV_ICR)  */
#define USBDEV_ICR_SOFINT (0x1u << 11) /**< \brief (USBDEV_ICR) Clear Start Of Frame Interrupt */
#define USBDEV_ICR_ENDBUSRES (0x1u << 12) /**< \brief (USBDEV_ICR) Clear End of Bus Reset Interrupt */
#define USBDEV_ICR_WAKEUP (0x1u << 13) /**< \brief (USBDEV_ICR) Clear Wakeup Interrupt */
/* -------- USBDEV_RST_EP : (USBDEV Offset: 0x028) Reset Endpoint Register -------- */
#define USBDEV_RST_EP_EP0 (0x1u << 0) /**< \brief (USBDEV_RST_EP) Reset Endpoint 0 */
#define USBDEV_RST_EP_EP1 (0x1u << 1) /**< \brief (USBDEV_RST_EP) Reset Endpoint 1 */
#define USBDEV_RST_EP_EP2 (0x1u << 2) /**< \brief (USBDEV_RST_EP) Reset Endpoint 2 */
#define USBDEV_RST_EP_EP3 (0x1u << 3) /**< \brief (USBDEV_RST_EP) Reset Endpoint 3 */
#define USBDEV_RST_EP_EP4 (0x1u << 4) /**< \brief (USBDEV_RST_EP) Reset Endpoint 4 */
#define USBDEV_RST_EP_EP5 (0x1u << 5) /**< \brief (USBDEV_RST_EP) Reset Endpoint 5 */
/* -------- USBDEV_CSR[6] : (USBDEV Offset: 0x030) Endpoint Control and Status Register -------- */
#define USBDEV_CSR_TXCOMP (0x1u << 0) /**< \brief (USBDEV_CSR[6]) Generates an IN Packet with Data Previously Written in the DPR */
#define USBDEV_CSR_RX_DATA_BK0 (0x1u << 1) /**< \brief (USBDEV_CSR[6]) Receive Data Bank 0 */
#define USBDEV_CSR_RXSETUP (0x1u << 2) /**< \brief (USBDEV_CSR[6]) Received Setup */
#define USBDEV_CSR_STALLSENT (0x1u << 3) /**< \brief (USBDEV_CSR[6]) Stall Sent */
#define USBDEV_CSR_TXPKTRDY (0x1u << 4) /**< \brief (USBDEV_CSR[6]) Transmit Packet Ready */
#define USBDEV_CSR_FORCESTALL (0x1u << 5) /**< \brief (USBDEV_CSR[6]) Force Stall (used by Control, Bulk and Isochronous Endpoints) */
#define USBDEV_CSR_RX_DATA_BK1 (0x1u << 6) /**< \brief (USBDEV_CSR[6]) Receive Data Bank 1 (only used by endpoints with ping-pong attributes) */
#define USBDEV_CSR_DIR (0x1u << 7) /**< \brief (USBDEV_CSR[6]) Transfer Direction (only available for control endpoints) (Read/Write) */
#define USBDEV_CSR_EPTYPE_Pos 8
#define USBDEV_CSR_EPTYPE_Msk (0x7u << USBDEV_CSR_EPTYPE_Pos) /**< \brief (USBDEV_CSR[6]) Endpoint Type (Read/Write) */
#define USBDEV_CSR_EPTYPE(value) ((USBDEV_CSR_EPTYPE_Msk & ((value) << USBDEV_CSR_EPTYPE_Pos)))
#define   USBDEV_CSR_EPTYPE_CTRL (0x0u << 8) /**< \brief (USBDEV_CSR[6]) Control */
#define   USBDEV_CSR_EPTYPE_ISO_OUT (0x1u << 8) /**< \brief (USBDEV_CSR[6]) Isochronous OUT */
#define   USBDEV_CSR_EPTYPE_BULK_OUT (0x2u << 8) /**< \brief (USBDEV_CSR[6]) Bulk OUT */
#define   USBDEV_CSR_EPTYPE_INT_OUT (0x3u << 8) /**< \brief (USBDEV_CSR[6]) Interrupt OUT */
#define   USBDEV_CSR_EPTYPE_ISO_IN (0x5u << 8) /**< \brief (USBDEV_CSR[6]) Isochronous IN */
#define   USBDEV_CSR_EPTYPE_BULK_IN (0x6u << 8) /**< \brief (USBDEV_CSR[6]) Bulk IN */
#define   USBDEV_CSR_EPTYPE_INT_IN (0x7u << 8) /**< \brief (USBDEV_CSR[6]) Interrupt IN */
#define USBDEV_CSR_DTGLE (0x1u << 11) /**< \brief (USBDEV_CSR[6]) Data Toggle (Read-only) */
#define USBDEV_CSR_EPEDS (0x1u << 15) /**< \brief (USBDEV_CSR[6]) Endpoint Enable Disable */
#define USBDEV_CSR_RXBYTECNT_Pos 16
#define USBDEV_CSR_RXBYTECNT_Msk (0x7ffu << USBDEV_CSR_RXBYTECNT_Pos) /**< \brief (USBDEV_CSR[6]) Number of Bytes Available in the FIFO (Read-only) */
#define USBDEV_CSR_RXBYTECNT(value) ((USBDEV_CSR_RXBYTECNT_Msk & ((value) << USBDEV_CSR_RXBYTECNT_Pos)))
#define USBDEV_CSR_ISOERROR (0x1u << 3) /**< \brief (USBDEV_CSR[6]) A CRC error has been detected in an isochronous transfer */
/* -------- USBDEV_FDR[6] : (USBDEV Offset: 0x050) Endpoint FIFO Data Register -------- */
#define USBDEV_FDR_FIFO_DATA_Pos 0
#define USBDEV_FDR_FIFO_DATA_Msk (0xffu << USBDEV_FDR_FIFO_DATA_Pos) /**< \brief (USBDEV_FDR[6]) FIFO Data Value */
#define USBDEV_FDR_FIFO_DATA(value) ((USBDEV_FDR_FIFO_DATA_Msk & ((value) << USBDEV_FDR_FIFO_DATA_Pos)))
/* -------- USBDEV_TXVC : (USBDEV Offset: 0x074) Transceiver Control Register -------- */
#define USBDEV_TXVC_TXVDIS (0x1u << 8) /**< \brief (USBDEV_TXVC) Transceiver Disable */
#define USBDEV_TXVC_PUON (0x1u << 9) /**< \brief (USBDEV_TXVC) Pull-up On */

/*@}*/


#endif /* _SAMG55_USBDEV_COMPONENT_ */
