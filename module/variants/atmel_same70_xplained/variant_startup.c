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
  .pfnWDT_Handler    = (void*) vector_halt,  /* 4  Watchdog Timer */
  .pfnPMC_Handler    = (void*) vector_halt,  /* 5  Power Management Controller */
  .pfnEFC0_Handler   = (void*) vector_halt,  /* 6  Enhanced Embedded Flash Controller 0 */
#ifdef EFC1
  .pfnEFC1_Handler   = (void*) vector_halt,  /* 7  Enhanced Embedded Flash Controller 1 */
#else
  .pvReserved7       = (void*) (0UL),        /* 7  Reserved */
#endif /* EFC1 */
  .pfnUART0_Handler  = (void*) vector_halt,  /* 8  UART 0 */
  .pfnUART1_Handler  = (void*) vector_halt,  /* 9  UART 1 */
  .pvReserved10      = (void*) (0UL),        /* 10 Reserved */
  .pfnPIOA_Handler   = (void*) vector_halt,  /* 11 Parallel I/O Controller A */
  .pfnPIOB_Handler   = (void*) vector_halt,  /* 12 Parallel I/O Controller B */
#ifdef PIOC
  .pfnPIOC_Handler   = (void*) vector_halt,  /* 13 Parallel I/O Controller C */
#else
  .pvReserved13      = (void*) (0UL),        /* 13 Reserved */
#endif /* PIOC */
  .pfnUSART0_Handler = (void*) vector_halt,  /* 14 USART 0 */
#ifdef USART1
  .pfnUSART1_Handler = (void*) vector_halt,  /* 15 USART 1 */
#else
  .pvReserved15      = (void*) (0UL),        /* 15 Reserved */
#endif /* USART1 */
  .pvReserved16      = (void*) (0UL),        /* 16 Reserved */
  .pvReserved17      = (void*) (0UL),        /* 17 Reserved */
#ifdef HSMCI
  .pfnHSMCI_Handler  = (void*) vector_halt,  /* 18 Multimedia Card Interface */
#else
  .pvReserved18      = (void*) (0UL),        /* 18 Reserved */
#endif /* HSMCI */
  .pfnTWI0_Handler   = (void*) vector_halt,  /* 19 Two Wire Interface 0 */
  .pfnTWI1_Handler   = (void*) vector_halt,  /* 20 Two Wire Interface 1 */
  .pfnSPI0_Handler   = (void*) vector_halt,  /* 21 Serial Peripheral Interface */
  .pfnSSC_Handler    = (void*) vector_halt,  /* 22 Synchronous Serial Controller */
  .pfnTC0_Handler    = (void*) vector_halt,  /* 23 Timer/Counter 0 */
  .pfnTC1_Handler    = (void*) vector_halt,  /* 24 Timer/Counter 1 */
  .pfnTC2_Handler    = (void*) vector_halt,  /* 25 Timer/Counter 2 */
#ifdef TC1
  .pfnTC3_Handler    = (void*) vector_halt,  /* 26 Timer/Counter 3 */
  .pfnTC4_Handler    = (void*) vector_halt,  /* 27 Timer/Counter 4 */
  .pfnTC5_Handler    = (void*) vector_halt,  /* 28 Timer/Counter 5 */
#else
  .pvReserved26      = (void*) (0UL),        /* 26 Reserved */
  .pvReserved27      = (void*) (0UL),        /* 27 Reserved */
  .pvReserved28      = (void*) (0UL),        /* 28 Reserved */
#endif /* TC1 */
  .pfnADC_Handler    = (void*) vector_halt,  /* 29 Analog To Digital Converter */
#ifdef DACC
  .pfnDACC_Handler   = (void*) vector_halt,  /* 30 Digital To Analog Converter */
#else
  .pvReserved30      = (void*) (0UL),        /* 30 Reserved */
#endif /* DACC */
  .pfnPWM_Handler    = (void*) vector_halt,  /* 31 Pulse Width Modulation */
  .pfnCRCCU_Handler  = (void*) vector_halt,  /* 32 CRC Calculation Unit */
  .pfnACC_Handler    = (void*) vector_halt,  /* 33 Analog Comparator */
  .pfnUSBDEV_Handler = (void*) vector_halt   /* 34 USB Device Port */
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
#if defined(EFC1) // Only valid for products with two flash banks
  EFC1->EEFC_FMR = EEFC_FMR_FWS(5)|EEFC_FMR_CLOE;
#endif // EFC1

  /*
   * We are coming from a Hard Reset or Backup mode.
   * The core is clocked by Internal Fast RC @ 4MHz.
   * We intend to use the device @120MHz from external Oscillator.
   * Steps are (cf datasheet chapter '29.14 Programming Sequence'):
   * 1- Activation of external oscillator
   * 2- Switch the MAINCK to the main crystal oscillator
   * 3- Wait for the MOSCSELS to be set
   * 4- Check the main clock frequency
   * 5- Set PLLx and Divider
   * 6- Select the master clock and processor clock
   * 7- Select the programmable clocks (optional)
   */

  /* Step 1 - Activation of external oscillator
   * As we are clocking the core from internal Fast RC, we keep the bit CKGR_MOR_MOSCRCEN.
   * Main Crystal Oscillator Start-up Time (CKGR_MOR_MOSCXTST) is set to maximum value.
   * Then, we wait the startup time to be finished by checking PMC_SR_MOSCXTS in PMC_SR.
   */
  PMC->CKGR_MOR = CKGR_MOR_KEY_PASSWD | CKGR_MOR_MOSCXTST(0xfful) | CKGR_MOR_MOSCRCEN | CKGR_MOR_MOSCXTEN;
  for ( ; (PMC->PMC_SR & PMC_SR_MOSCXTS) != PMC_SR_MOSCXTS ; );

  /* Step 2 - Switch the MAINCK to the main crystal oscillator
   * We add the CKGR_MOR_MOSCSEL bit.
   * Then we wait for the selection to be done by checking PMC_SR_MOSCSELS in PMC_SR.
   */
  PMC->CKGR_MOR = CKGR_MOR_KEY_PASSWD | CKGR_MOR_MOSCXTST(0xfful) | CKGR_MOR_MOSCRCEN | CKGR_MOR_MOSCXTEN | CKGR_MOR_MOSCSEL;
  /* Step 3 - Wait for the MOSCSELS to be set */
  for ( ; (PMC->PMC_SR & PMC_SR_MOSCSELS) != PMC_SR_MOSCSELS ; );

  /* Step 4 - Check the main clock frequency */
  /* As written in the DS, we could check the MAINF value here (0x18a2) */

  /* Step 5 - Set PLLx and Divider
   * The external oscillator is 12MHz. As we intend to clock the system @120MHz,
   * we need to multiply the oscillator frequency by 10.
   * This can be done by setting MULx to value 9 and DIV to 1.
   * We set the maximum PLL Lock time to maximum in CKGR_PLLAR_PLLACOUNT.
   */
  //PMC->CKGR_PLLAR = CKGR_PLLAR_ONE | (CKGR_PLLAR_MULA(0x1dul) | CKGR_PLLAR_DIVA(3ul) | CKGR_PLLAR_PLLACOUNT(0x1ul));
  PMC->CKGR_PLLAR = CKGR_PLLAR_ONE | (CKGR_PLLAR_MULA(0x9ul) | CKGR_PLLAR_DIVA(1ul) | CKGR_PLLAR_PLLACOUNT(0x3ful));
  for ( ; (PMC->PMC_SR & PMC_SR_LOCKA) != PMC_SR_LOCKA ; );

  /* Step 6 - Select the master clock and processor clock
   * Source for MasterClock will be PLLA output (PMC_MCKR_CSS_PLLA_CLK), without frequency division.
   */
  PMC->PMC_MCKR = PMC_MCKR_PRES_CLK_1 | PMC_MCKR_CSS_PLLA_CLK;
  for ( ; (PMC->PMC_SR & PMC_SR_MCKRDY) != PMC_SR_MCKRDY ; );

  /*
   * Step 7 - Select the programmable clocks
   *
   * Output MCK on PCK1/pin PA17
   * Used to validate Master Clock settings
   */
//  PMC->PMC_SCER = PMC_SCER_PCK1 ;

  SystemCoreClock=__SYSTEM_CLOCK_120MHZ;
}

