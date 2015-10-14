/*
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
#define __SYSTEM_CLOCK_120MHZ (120000000UL)

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
  .pfnWDT_Handler    = (void*) vector_halt,  /* 4  Watchdog/Dual Watchdog Timer */
  .pfnPMC_Handler    = (void*) vector_halt,  /* 5  Power Management Controller */
  .pfnEFC0_Handler   = (void*) vector_halt,  /* 6  Enhanced Embedded Flash Controller */
  .pfnUART0_Handler  = (void*) vector_halt,  /* 7  UART 0 */
  .pvReserved8       = (void*) (0UL),        /* 8  Reserved */
  .pfnPIOA_Handler   = (void*) vector_halt,  /* 9  Parallel I/O Controller A */
  .pfnPIOB_Handler   = (void*) vector_halt,  /* 10 Parallel I/O Controller B */
#ifdef PIOC
  .pfnPIOC_Handler   = (void*) vector_halt,  /* 11 Parallel I/O Controller C */
#else
  .pvReserved11      = (void*) (0UL),        /* 11 Reserved */
#endif /* PIOC */
  .pfnPIOD_Handler   = (void*) vector_halt,  /* 12 Parallel I/O Controller D */
#ifdef PIOE
  .pfnPIOE_Handler   = (void*) vector_halt,  /* 13 Parallel I/O Controller E */
#else
  .pvReserved13      = (void*) (0UL),        /* 13 Reserved */
#endif /* PIOE */
  .pfnUSART0_Handler = (void*) vector_halt,  /* 14 USART 0 */
  .pfnUSART1_Handler = (void*) vector_halt,  /* 15 USART 1 */
  .pfnHSMCI_Handler  = (void*) vector_halt,  /* 16 Multimedia Card Interface */
  .pfnTWI0_Handler   = (void*) vector_halt,  /* 17 Two Wire Interface 0 */
  .pfnTWI1_Handler   = (void*) vector_halt,  /* 18 Two Wire Interface 1 */
  .pfnSPI_Handler    = (void*) vector_halt,  /* 19 Serial Peripheral Interface */
  .pfnDMAC_Handler   = (void*) vector_halt,  /* 20 DMAC */
  .pfnTC0_Handler    = (void*) vector_halt,  /* 21 Timer/Counter 0 */
  .pfnTC1_Handler    = (void*) vector_halt,  /* 22 Timer/Counter 1 */
  .pfnTC2_Handler    = (void*) vector_halt,  /* 23 Timer/Counter 2 */
#ifdef TC1
  .pfnTC3_Handler    = (void*) vector_halt,  /* 24 Timer/Counter 3 */
  .pfnTC4_Handler    = (void*) vector_halt,  /* 25 Timer/Counter 4 */
  .pfnTC5_Handler    = (void*) vector_halt,  /* 26 Timer/Counter 5 */
#else
  .pvReserved24      = (void*) (0UL),        /* 24 Reserved */
  .pvReserved25      = (void*) (0UL),        /* 25 Reserved */
  .pvReserved26      = (void*) (0UL),        /* 26 Reserved */
#endif /* TC1 */
#ifdef TC2
  .pfnTC6_Handler    = (void*) vector_halt,  /* 27 Timer/Counter 6 */
  .pfnTC7_Handler    = (void*) vector_halt,  /* 28 Timer/Counter 7 */
  .pfnTC8_Handler    = (void*) vector_halt,  /* 29 Timer/Counter 8 */
#else
  .pvReserved27      = (void*) (0UL),        /* 27 Reserved */
  .pvReserved28      = (void*) (0UL),        /* 28 Reserved */
  .pvReserved29      = (void*) (0UL),        /* 29 Reserved */
#endif /* TC2 */
  .pfnAFEC0_Handler  = (void*) vector_halt,  /* 30 Analog Front End 0 */
  .pfnAFEC1_Handler  = (void*) vector_halt,  /* 31 Analog Front End 1 */
  .pfnDACC_Handler   = (void*) vector_halt,  /* 32 Digital To Analog Converter */
  .pfnACC_Handler    = (void*) vector_halt,  /* 33 Analog Comparator */
  .pfnARM_Handler    = (void*) vector_halt,  /* 34 FPU signals : FPIXC, FPOFC, FPUFC, FPIOC, FPDZC, FPIDC, FPIXC */
  .pfnUSBDEV_Handler = (void*) vector_halt,  /* 35 USB DEVICE */
  .pfnPWM_Handler    = (void*) vector_halt,  /* 36 PWM */
  .pfnCAN0_Handler   = (void*) vector_halt,  /* 37 CAN0 */
#ifdef CAN1
  .pfnCAN1_Handler   = (void*) vector_halt,  /* 38 CAN1 */
#else
  .pvReserved38      = (void*) (0UL),        /* 38 Reserved */
#endif /* CAN1 */
  .pfnAES_Handler    = (void*) vector_halt,  /* 39 AES */
  .pvReserved40      = (void*) (0UL),        /* 40 Reserved */
  .pvReserved41      = (void*) (0UL),        /* 41 Reserved */
  .pvReserved42      = (void*) (0UL),        /* 42 Reserved */
  .pvReserved43      = (void*) (0UL),        /* 43 Reserved */
  .pfnGMAC_Handler   = (void*) vector_halt,  /* 44 EMAC */
  .pfnUART1_Handler  = (void*) vector_halt   /* 45 UART */
};

/**
 * \brief Setup the microcontroller system.
 *
 * Initialize the System and update the System Frequency variable.
 */
void SystemInit( void )
{
  /* Set 6 FWS for Embedded Flash Access according to 120MHz configuration */
  EFC0->EEFC_FMR = EEFC_FMR_FWS(5)|EEFC_FMR_CLOE;

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
  PMC->CKGR_PLLAR = CKGR_PLLAR_ONE | CKGR_PLLAR_MULA(0x13ul) | CKGR_PLLAR_PLLACOUNT(0x3ful) | CKGR_PLLAR_DIVA(0x1ul) ;
  for ( ; !(PMC->PMC_SR & PMC_SR_LOCKA) ; );

  /* Switch to main clock */
  PMC->PMC_MCKR = ((PMC_MCKR_PRES_CLK_2 | PMC_MCKR_CSS_PLLA_CLK) & ~PMC_MCKR_CSS_Msk) | PMC_MCKR_CSS_MAIN_CLK;
  for ( ; !(PMC->PMC_SR & PMC_SR_MCKRDY) ; );

  /* Switch to PLLA */
  PMC->PMC_MCKR = PMC_MCKR_PRES_CLK_2 | PMC_MCKR_CSS_PLLA_CLK;
  for ( ; !(PMC->PMC_SR & PMC_SR_MCKRDY) ; );

  SystemCoreClock=__SYSTEM_CLOCK_120MHZ;
}

