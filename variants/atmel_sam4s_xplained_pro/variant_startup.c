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

/**
 * \brief Default interrupt handler for unused IRQs.
 */
static void vector_halt(void)
{
  // Halts
  while (1);
}

/* Peripherals handlers */
void SUPC_Handler   ( void ) __attribute__ ((weak, alias("vector_halt")));
void RSTC_Handler   ( void ) __attribute__ ((weak, alias("vector_halt")));
void RTC_Handler    ( void ) __attribute__ ((weak, alias("vector_halt")));
void RTT_Handler    ( void ) __attribute__ ((weak, alias("vector_halt")));
void WDT_Handler    ( void ) __attribute__ ((weak, alias("vector_halt")));
void PMC_Handler    ( void ) __attribute__ ((weak, alias("vector_halt")));
void EFC0_Handler   ( void ) __attribute__ ((weak, alias("vector_halt")));
#ifdef EFC1
void EFC1_Handler   ( void ) __attribute__ ((weak, alias("vector_halt")));
#endif /* EFC1 */
void UART0_Handler  ( void ) __attribute__ ((weak, alias("vector_halt")));
void UART1_Handler  ( void ) __attribute__ ((weak, alias("vector_halt")));
void PIOA_Handler   ( void ) __attribute__ ((weak, alias("vector_halt")));
void PIOB_Handler   ( void ) __attribute__ ((weak, alias("vector_halt")));
#ifdef PIOC
void PIOC_Handler   ( void ) __attribute__ ((weak, alias("vector_halt")));
#endif /* PIOC */
void USART0_Handler ( void ) __attribute__ ((weak, alias("vector_halt")));
#ifdef USART1
void USART1_Handler ( void ) __attribute__ ((weak, alias("vector_halt")));
#endif /* USART1 */
#ifdef HSMCI
void HSMCI_Handler  ( void ) __attribute__ ((weak, alias("vector_halt")));
#endif /* HSMCI */
void TWI0_Handler   ( void ) __attribute__ ((weak, alias("vector_halt")));
void TWI1_Handler   ( void ) __attribute__ ((weak, alias("vector_halt")));
void SPI_Handler    ( void ) __attribute__ ((weak, alias("vector_halt")));
void SSC_Handler    ( void ) __attribute__ ((weak, alias("vector_halt")));
void TC0_Handler    ( void ) __attribute__ ((weak, alias("vector_halt")));
void TC1_Handler    ( void ) __attribute__ ((weak, alias("vector_halt")));
void TC2_Handler    ( void ) __attribute__ ((weak, alias("vector_halt")));
#ifdef TC1
void TC3_Handler    ( void ) __attribute__ ((weak, alias("vector_halt")));
void TC4_Handler    ( void ) __attribute__ ((weak, alias("vector_halt")));
void TC5_Handler    ( void ) __attribute__ ((weak, alias("vector_halt")));
#endif /* TC1 */
void ADC_Handler    ( void ) __attribute__ ((weak, alias("vector_halt")));
#ifdef DACC
void DACC_Handler   ( void ) __attribute__ ((weak, alias("vector_halt")));
#endif /* DACC */
void PWM_Handler    ( void ) __attribute__ ((weak, alias("vector_halt")));
void CRCCU_Handler  ( void ) __attribute__ ((weak, alias("vector_halt")));
void ACC_Handler    ( void ) __attribute__ ((weak, alias("vector_halt")));
void USBDEV_Handler ( void ) __attribute__ ((weak, alias("vector_halt")));

/* Exception Table */
__attribute__ ((section(".ram_isr_vector")))
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
  .pfnSUPC_Handler   = (void*) SUPC_Handler,   /* 0  Supply Controller */
  .pfnRSTC_Handler   = (void*) RSTC_Handler,   /* 1  Reset Controller */
  .pfnRTC_Handler    = (void*) RTC_Handler,    /* 2  Real Time Clock */
  .pfnRTT_Handler    = (void*) RTT_Handler,    /* 3  Real Time Timer */
  .pfnWDT_Handler    = (void*) WDT_Handler,    /* 4  Watchdog Timer */
  .pfnPMC_Handler    = (void*) PMC_Handler,    /* 5  Power Management Controller */
  .pfnEFC0_Handler   = (void*) EFC0_Handler,   /* 6  Enhanced Embedded Flash Controller 0 */
#ifdef EFC1
  .pfnEFC1_Handler   = (void*) EFC1_Handler,   /* 7  Enhanced Embedded Flash Controller 1 */
#else
  .pvReserved7       = (void*) (0UL),          /* 7  Reserved */
#endif /* EFC1 */
  .pfnUART0_Handler  = (void*) UART0_Handler,  /* 8  UART 0 */
  .pfnUART1_Handler  = (void*) UART1_Handler,  /* 9  UART 1 */
  .pvReserved10      = (void*) (0UL),          /* 10 Reserved */
  .pfnPIOA_Handler   = (void*) PIOA_Handler,   /* 11 Parallel I/O Controller A */
  .pfnPIOB_Handler   = (void*) PIOB_Handler,   /* 12 Parallel I/O Controller B */
#ifdef PIOC
  .pfnPIOC_Handler   = (void*) PIOC_Handler,   /* 13 Parallel I/O Controller C */
#else
  .pvReserved13      = (void*) (0UL),          /* 13 Reserved */
#endif /* PIOC */
  .pfnUSART0_Handler = (void*) USART0_Handler, /* 14 USART 0 */
#ifdef USART1
  .pfnUSART1_Handler = (void*) USART1_Handler, /* 15 USART 1 */
#else
  .pvReserved15      = (void*) (0UL),          /* 15 Reserved */
#endif /* USART1 */
  .pvReserved16      = (void*) (0UL),          /* 16 Reserved */
  .pvReserved17      = (void*) (0UL),          /* 17 Reserved */
#ifdef HSMCI
  .pfnHSMCI_Handler  = (void*) HSMCI_Handler,  /* 18 Multimedia Card Interface */
#else
  .pvReserved18      = (void*) (0UL),          /* 18 Reserved */
#endif /* HSMCI */
  .pfnTWI0_Handler   = (void*) TWI0_Handler,   /* 19 Two Wire Interface 0 */
  .pfnTWI1_Handler   = (void*) TWI1_Handler,   /* 20 Two Wire Interface 1 */
  .pfnSPI_Handler    = (void*) SPI_Handler,    /* 21 Serial Peripheral Interface */
  .pfnSSC_Handler    = (void*) SSC_Handler,    /* 22 Synchronous Serial Controller */
  .pfnTC0_Handler    = (void*) TC0_Handler,    /* 23 Timer/Counter 0 */
  .pfnTC1_Handler    = (void*) TC1_Handler,    /* 24 Timer/Counter 1 */
  .pfnTC2_Handler    = (void*) TC2_Handler,    /* 25 Timer/Counter 2 */
#ifdef TC1
  .pfnTC3_Handler    = (void*) TC3_Handler,    /* 26 Timer/Counter 3 */
  .pfnTC4_Handler    = (void*) TC4_Handler,    /* 27 Timer/Counter 4 */
  .pfnTC5_Handler    = (void*) TC5_Handler,    /* 28 Timer/Counter 5 */
#else
  .pvReserved26      = (void*) (0UL),          /* 26 Reserved */
  .pvReserved27      = (void*) (0UL),          /* 27 Reserved */
  .pvReserved28      = (void*) (0UL),          /* 28 Reserved */
#endif /* TC1 */
  .pfnADC_Handler    = (void*) ADC_Handler,    /* 29 Analog To Digital Converter */
#ifdef DACC
  .pfnDACC_Handler   = (void*) DACC_Handler,   /* 30 Digital To Analog Converter */
#else
  .pvReserved30      = (void*) (0UL),          /* 30 Reserved */
#endif /* DACC */
  .pfnPWM_Handler    = (void*) PWM_Handler,    /* 31 Pulse Width Modulation */
  .pfnCRCCU_Handler  = (void*) CRCCU_Handler,  /* 32 CRC Calculation Unit */
  .pfnACC_Handler    = (void*) ACC_Handler,    /* 33 Analog Comparator */
  .pfnUSBDEV_Handler = (void*) USBDEV_Handler     /* 34 USB Device Port */
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
   * *
   * Output MCK on PCK1/pin PA17
   * Used to validate Master Clock settings
   */
//  PMC->PMC_SCER = PMC_SCER_PCK1 ;

  SystemCoreClock=__SYSTEM_CLOCK_120MHZ;
}

