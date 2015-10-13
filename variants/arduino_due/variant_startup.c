/*
  Copyright (c) 2011-2012 Arduino LLC.  All right reserved.
  Copyright (c) 2015 Thibaut VIARD.  All right reserved.

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

#include "sam.h"
#include "variant.h"
#include "core_delay.h" /* for Systick handler */
#include "core_hooks.h" /* for PendSV and SVC handlers */
#include "core_cortex_vectors.h" /* for vector_halt() */

#define __SYSTEM_CLOCK_4MHZ   (4000000UL)
#define __SYSTEM_CLOCK_84MHZ  (84000000UL)

/* Clock Settings (4MHz) using Internal Fast RC */
uint32_t SystemCoreClock = __SYSTEM_CLOCK_4MHZ ;

/* Exception Table */
__attribute__ ((section(".data.ram_isr_vector")))
DeviceVectors exception_table=
{
  /* Configure Initial Stack Pointer, using linker-generated symbols */
  .pvStack = 0ul, // not used (void*) (&__StackTop),

  .pfnReset_Handler      = (void*) (0UL),
  .pfnNMI_Handler        = (void*) NMI_Handler,
  .pfnHardFault_Handler  = (void*) HardFault_Handler,
  .pfnMemManage_Handler  = (void*) MemManage_Handler,
  .pfnBusFault_Handler   = (void*) BusFault_Handler,
  .pfnUsageFault_Handler = (void*) UsageFault_Handler,
  .pfnReserved1_Handler  = (void*) (0UL),          /* Reserved */
  .pfnReserved2_Handler  = (void*) (0UL),          /* Reserved */
  .pfnReserved3_Handler  = (void*) (0UL),          /* Reserved */
  .pfnReserved4_Handler  = (void*) (0UL),          /* Reserved */
  .pfnSVC_Handler        = (void*) SVC_Handler,
  .pfnDebugMon_Handler   = (void*) DebugMon_Handler,
  .pfnReserved5_Handler  = (void*) (0UL),          /* Reserved */
  .pfnPendSV_Handler     = (void*) PendSV_Handler,
  .pfnSysTick_Handler    = (void*) SysTick_Handler,

  /* Configurable interrupts */
  .pfnSUPC_Handler   = (void*) vector_halt,  /* 0  Supply Controller */
  .pfnRSTC_Handler   = (void*) vector_halt,  /* 1  Reset Controller */
  .pfnRTC_Handler    = (void*) vector_halt,  /* 2  Real Time Clock */
  .pfnRTT_Handler    = (void*) vector_halt,  /* 3  Real Time Timer */
  .pfnWDT_Handler    = (void*) vector_halt,  /* 4  Watchdog Timer */
  .pfnPMC_Handler    = (void*) vector_halt,  /* 5  Power Management Controller */
  .pfnEFC0_Handler   = (void*) vector_halt,  /* 6  Enhanced Embedded Flash Controller 0 */
  .pfnEFC1_Handler   = (void*) vector_halt,  /* 7  Enhanced Embedded Flash Controller 1 */
  .pfnUART_Handler   = (void*) vector_halt,  /* 8  Universal Asynchronous Receiver Transceiver */
#ifdef SMC
  .pfnSMC_Handler    = (void*) vector_halt,  /* 9  Static Memory Controller */
#else
  .pvReserved9       = (void*) (0UL),        /* 9  Reserved */
#endif /* SMC */
  .pvReserved10      = (void*) (0UL),        /* 10 Reserved */
  .pfnPIOA_Handler   = (void*) vector_halt,  /* 11 Parallel I/O Controller A, */
  .pfnPIOB_Handler   = (void*) vector_halt,  /* 12 Parallel I/O Controller B */
#ifdef PIOC
  .pfnPIOC_Handler   = (void*) vector_halt,  /* 13 Parallel I/O Controller C */
#else
  .pvReserved13      = (void*) (0UL),        /* 13 Reserved */
#endif /* PIOC */
#ifdef PIOD
  .pfnPIOD_Handler   = (void*) vector_halt,  /* 14 Parallel I/O Controller D */
#else
  .pvReserved14      = (void*) (0UL),        /* 14 Reserved */
#endif /* PIOD */
#ifdef PIOE
  .pfnPIOE_Handler   = (void*) vector_halt,  /* 15 Parallel I/O Controller E */
#else
  .pvReserved15      = (void*) (0UL),        /* 15 Reserved */
#endif /* PIOE */
  .pvReserved16      = (void*) (0UL),        /* 16 Reserved */
  .pfnUSART0_Handler = (void*) vector_halt,  /* 17 USART 0 */
  .pfnUSART1_Handler = (void*) vector_halt,  /* 18 USART 1 */
  .pfnUSART2_Handler = (void*) vector_halt,  /* 19 USART 2 */
#ifdef USART3
  .pfnUSART3_Handler = (void*) vector_halt,  /* 20 USART 3 */
#else
  .pvReserved20      = (void*) (0UL),        /* 20 Reserved */
#endif /* USART3 */
  .pfnHSMCI_Handler  = (void*) vector_halt,  /* 21 Multimedia Card Interface */
  .pfnTWI0_Handler   = (void*) vector_halt,  /* 22 Two-Wire Interface 0 */
  .pfnTWI1_Handler   = (void*) vector_halt,  /* 23 Two-Wire Interface 1 */
  .pfnSPI0_Handler   = (void*) vector_halt,  /* 24 Serial Peripheral Interface */
#ifdef SPI1
  .pfnSPI1_Handler   = (void*) vector_halt,  /* 25 Serial Peripheral Interface */
#else
  .pvReserved25      = (void*) (0UL),        /* 25 Reserved */
#endif /* SPI1 */
  .pfnSSC_Handler    = (void*) vector_halt,  /* 26 Synchronous Serial Controller */
  .pfnTC0_Handler    = (void*) vector_halt,  /* 27 Timer Counter 0 */
  .pfnTC1_Handler    = (void*) vector_halt,  /* 28 Timer Counter 1 */
  .pfnTC2_Handler    = (void*) vector_halt,  /* 29 Timer Counter 2 */
  .pfnTC3_Handler    = (void*) vector_halt,  /* 30 Timer Counter 3 */
  .pfnTC4_Handler    = (void*) vector_halt,  /* 31 Timer Counter 4 */
  .pfnTC5_Handler    = (void*) vector_halt,  /* 32 Timer Counter 5 */
#ifdef TC2
  .pfnTC6_Handler    = (void*) vector_halt,  /* 33 Timer Counter 6 */
  .pfnTC7_Handler    = (void*) vector_halt,  /* 34 Timer Counter 7 */
  .pfnTC8_Handler    = (void*) vector_halt,  /* 35 Timer Counter 8 */
#else
  .pvReserved33      = (void*) (0UL),        /* 33 Reserved */
  .pvReserved34      = (void*) (0UL),        /* 34 Reserved */
  .pvReserved35      = (void*) (0UL),        /* 35 Reserved */
#endif /* TC2 */
  .pfnPWM_Handler    = (void*) vector_halt,  /* 36 Pulse Width Modulation Controller */
  .pfnADC_Handler    = (void*) vector_halt,  /* 37 ADC Controller */
  .pfnDACC_Handler   = (void*) vector_halt,  /* 38 DAC Controller */
  .pfnDMAC_Handler   = (void*) vector_halt,  /* 39 DMA Controller */
  .pfnUOTGHS_Handler = (void*) vector_halt,  /* 40 USB OTG High Speed */
  .pfnTRNG_Handler   = (void*) vector_halt,  /* 41 True Random Number Generator */
#ifdef EMAC
  .pfnEMAC_Handler   = (void*) vector_halt,  /* 42 Ethernet MAC */
#else
  .pvReserved42      = (void*) (0UL),        /* 42 Reserved */
#endif /* EMAC */
  .pfnCAN0_Handler   = (void*) vector_halt,  /* 43 CAN Controller 0 */
  .pfnCAN1_Handler   = (void*) vector_halt   /* 44 CAN Controller 1 */
} ;

/**
 * \brief Setup the microcontroller system.
 *
 * Initialize the System and update the System Frequency variable.
 */
void SystemInit( void )
{
  /* Set 5 FWS for Embedded Flash Access according to 84MHz configuration */
  EFC0->EEFC_FMR = EEFC_FMR_FWS(4);
  EFC1->EEFC_FMR = EEFC_FMR_FWS(4);

  /* Initialize main oscillator */
  if ( !(PMC->CKGR_MOR & CKGR_MOR_MOSCSEL) )
  {
    PMC->CKGR_MOR = CKGR_MOR_KEY_PASSWD | CKGR_MOR_MOSCXTST(0x8ul) | CKGR_MOR_MOSCRCEN | CKGR_MOR_MOSCXTEN;
    for ( ; !(PMC->PMC_SR & PMC_SR_MOSCXTS) ; );
  }

  /* Switch to 3-20MHz Xtal oscillator */
  PMC->CKGR_MOR = CKGR_MOR_KEY_PASSWD | CKGR_MOR_MOSCXTST(0x8ul) | CKGR_MOR_MOSCRCEN | CKGR_MOR_MOSCXTEN | CKGR_MOR_MOSCSEL;
  for ( ; !(PMC->PMC_SR & PMC_SR_MOSCSELS) ; );

  PMC->PMC_MCKR = (PMC->PMC_MCKR & ~(uint32_t)PMC_MCKR_CSS_Msk) | PMC_MCKR_CSS_MAIN_CLK;
  for ( ; !(PMC->PMC_SR & PMC_SR_MCKRDY) ; );

  /* Initialize PLLA */
  PMC->CKGR_PLLAR = CKGR_PLLAR_ONE | CKGR_PLLAR_MULA(0xdul) | CKGR_PLLAR_PLLACOUNT(0x3ful) | CKGR_PLLAR_DIVA(0x1ul) ;
  for ( ; !(PMC->PMC_SR & PMC_SR_LOCKA) ; );

  /* Switch to main clock */
  PMC->PMC_MCKR = ((PMC_MCKR_PRES_CLK_2 | PMC_MCKR_CSS_PLLA_CLK) & ~PMC_MCKR_CSS_Msk) | PMC_MCKR_CSS_MAIN_CLK;
  for ( ; !(PMC->PMC_SR & PMC_SR_MCKRDY) ; );

  /* Switch to PLLA */
  PMC->PMC_MCKR = PMC_MCKR_PRES_CLK_2 | PMC_MCKR_CSS_PLLA_CLK;
  for ( ; !(PMC->PMC_SR & PMC_SR_MCKRDY) ; );

  SystemCoreClock = __SYSTEM_CLOCK_84MHZ;
}

