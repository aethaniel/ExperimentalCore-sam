/*
  Copyright (c) 2015 Arduino LLC & Thibaut VIARD.  All right reserved.

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
#include "core_delay.h"
#include "core_hooks.h"

#define __SYSTEM_CLOCK_4MHZ   (4000000UL)
#define __SYSTEM_CLOCK_84MHZ (84000000UL)

/* Clock Settings (4MHz) using Internal Fast RC */
uint32_t SystemCoreClock = __SYSTEM_CLOCK_4MHZ ;

/**
 * \brief Default interrupt handler for unused IRQs.
 */
static void __halt()
{
  // Halts
  while (1);
}

/* Peripherals handlers */
void SUPC_Handler   ( void ) __attribute__ ((weak, alias("__halt")));
void RSTC_Handler   ( void ) __attribute__ ((weak, alias("__halt")));
void RTC_Handler    ( void ) __attribute__ ((weak, alias("__halt")));
void RTT_Handler    ( void ) __attribute__ ((weak, alias("__halt")));
void WDT_Handler    ( void ) __attribute__ ((weak, alias("__halt")));
void PMC_Handler    ( void ) __attribute__ ((weak, alias("__halt")));
void EFC0_Handler   ( void ) __attribute__ ((weak, alias("__halt")));
void EFC1_Handler   ( void ) __attribute__ ((weak, alias("__halt")));
void UART_Handler   ( void ) __attribute__ ((weak, alias("__halt")));
#ifdef SMC
void SMC_Handler    ( void ) __attribute__ ((weak, alias("__halt")));
#endif /* SMC */
void PIOA_Handler   ( void ) __attribute__ ((weak, alias("__halt")));
void PIOB_Handler   ( void ) __attribute__ ((weak, alias("__halt")));
#ifdef PIOC
void PIOC_Handler   ( void ) __attribute__ ((weak, alias("__halt")));
#endif /* PIOC */
#ifdef PIOD
void PIOD_Handler   ( void ) __attribute__ ((weak, alias("__halt")));
#endif /* PIOD */
#ifdef PIOE
void PIOE_Handler   ( void ) __attribute__ ((weak, alias("__halt")));
#endif /* PIOE */
void USART0_Handler ( void ) __attribute__ ((weak, alias("__halt")));
void USART1_Handler ( void ) __attribute__ ((weak, alias("__halt")));
void USART2_Handler ( void ) __attribute__ ((weak, alias("__halt")));
#ifdef USART3
void USART3_Handler ( void ) __attribute__ ((weak, alias("__halt")));
#endif /* USART3 */
void HSMCI_Handler  ( void ) __attribute__ ((weak, alias("__halt")));
void TWI0_Handler   ( void ) __attribute__ ((weak, alias("__halt")));
void TWI1_Handler   ( void ) __attribute__ ((weak, alias("__halt")));
void SPI0_Handler   ( void ) __attribute__ ((weak, alias("__halt")));
#ifdef SPI1
void SPI1_Handler   ( void ) __attribute__ ((weak, alias("__halt")));
#endif /* SPI1 */
void SSC_Handler    ( void ) __attribute__ ((weak, alias("__halt")));
void TC0_Handler    ( void ) __attribute__ ((weak, alias("__halt")));
void TC1_Handler    ( void ) __attribute__ ((weak, alias("__halt")));
void TC2_Handler    ( void ) __attribute__ ((weak, alias("__halt")));
void TC3_Handler    ( void ) __attribute__ ((weak, alias("__halt")));
void TC4_Handler    ( void ) __attribute__ ((weak, alias("__halt")));
void TC5_Handler    ( void ) __attribute__ ((weak, alias("__halt")));
#ifdef TC2
void TC6_Handler    ( void ) __attribute__ ((weak, alias("__halt")));
void TC7_Handler    ( void ) __attribute__ ((weak, alias("__halt")));
void TC8_Handler    ( void ) __attribute__ ((weak, alias("__halt")));
#endif /* TC2 */
void PWM_Handler    ( void ) __attribute__ ((weak, alias("__halt")));
void ADC_Handler    ( void ) __attribute__ ((weak, alias("__halt")));
void DACC_Handler   ( void ) __attribute__ ((weak, alias("__halt")));
void DMAC_Handler   ( void ) __attribute__ ((weak, alias("__halt")));
void UOTGHS_Handler ( void ) __attribute__ ((weak, alias("__halt")));
void TRNG_Handler   ( void ) __attribute__ ((weak, alias("__halt")));
#ifdef EMAC
void EMAC_Handler   ( void ) __attribute__ ((weak, alias("__halt")));
#endif /* EMAC */
void CAN0_Handler   ( void ) __attribute__ ((weak, alias("__halt")));
void CAN1_Handler   ( void ) __attribute__ ((weak, alias("__halt")));

/* Exception Table */
//__attribute__ ((section(".isr_vector")))
DeviceVectors exception_table=
{
  /* Configure Initial Stack Pointer, using linker-generated symbols */
  .pvStack = 0ul, // not used (void*) (&__StackTop),

  .pfnReset_Handler      = (void*) Reset_Handler,
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
  .pfnEFC1_Handler   = (void*) EFC1_Handler,   /* 7  Enhanced Embedded Flash Controller 1 */
  .pfnUART_Handler   = (void*) UART_Handler,   /* 8  Universal Asynchronous Receiver Transceiver */
#ifdef SMC
  .pfnSMC_Handler    = (void*) SMC_Handler,    /* 9  Static Memory Controller */
#else
  .pvReserved9       = (void*) (0UL),          /* 9  Reserved */
#endif /* SMC */
  .pvReserved10      = (void*) (0UL),          /* 10 Reserved */
  .pfnPIOA_Handler   = (void*) PIOA_Handler,   /* 11 Parallel I/O Controller A, */
  .pfnPIOB_Handler   = (void*) PIOB_Handler,   /* 12 Parallel I/O Controller B */
#ifdef PIOC
  .pfnPIOC_Handler   = (void*) PIOC_Handler,   /* 13 Parallel I/O Controller C */
#else
  .pvReserved13      = (void*) (0UL),          /* 13 Reserved */
#endif /* PIOC */
#ifdef PIOD
  .pfnPIOD_Handler   = (void*) PIOD_Handler,   /* 14 Parallel I/O Controller D */
#else
  .pvReserved14      = (void*) (0UL),          /* 14 Reserved */
#endif /* PIOD */
#ifdef PIOE
  .pfnPIOE_Handler   = (void*) PIOE_Handler,   /* 15 Parallel I/O Controller E */
#else
  .pvReserved15      = (void*) (0UL),          /* 15 Reserved */
#endif /* PIOE */
  .pvReserved16      = (void*) (0UL),          /* 16 Reserved */
  .pfnUSART0_Handler = (void*) USART0_Handler, /* 17 USART 0 */
  .pfnUSART1_Handler = (void*) USART1_Handler, /* 18 USART 1 */
  .pfnUSART2_Handler = (void*) USART2_Handler, /* 19 USART 2 */
#ifdef USART3
  .pfnUSART3_Handler = (void*) USART3_Handler, /* 20 USART 3 */
#else
  .pvReserved20      = (void*) (0UL),          /* 20 Reserved */
#endif /* USART3 */
  .pfnHSMCI_Handler  = (void*) HSMCI_Handler,  /* 21 Multimedia Card Interface */
  .pfnTWI0_Handler   = (void*) TWI0_Handler,   /* 22 Two-Wire Interface 0 */
  .pfnTWI1_Handler   = (void*) TWI1_Handler,   /* 23 Two-Wire Interface 1 */
  .pfnSPI0_Handler   = (void*) SPI0_Handler,   /* 24 Serial Peripheral Interface */
#ifdef SPI1
  .pfnSPI1_Handler   = (void*) SPI1_Handler,   /* 25 Serial Peripheral Interface */
#else
  .pvReserved25      = (void*) (0UL),          /* 25 Reserved */
#endif /* SPI1 */
  .pfnSSC_Handler    = (void*) SSC_Handler,    /* 26 Synchronous Serial Controller */
  .pfnTC0_Handler    = (void*) TC0_Handler,    /* 27 Timer Counter 0 */
  .pfnTC1_Handler    = (void*) TC1_Handler,    /* 28 Timer Counter 1 */
  .pfnTC2_Handler    = (void*) TC2_Handler,    /* 29 Timer Counter 2 */
  .pfnTC3_Handler    = (void*) TC3_Handler,    /* 30 Timer Counter 3 */
  .pfnTC4_Handler    = (void*) TC4_Handler,    /* 31 Timer Counter 4 */
  .pfnTC5_Handler    = (void*) TC5_Handler,    /* 32 Timer Counter 5 */
#ifdef TC2
  .pfnTC6_Handler    = (void*) TC6_Handler,    /* 33 Timer Counter 6 */
  .pfnTC7_Handler    = (void*) TC7_Handler,    /* 34 Timer Counter 7 */
  .pfnTC8_Handler    = (void*) TC8_Handler,    /* 35 Timer Counter 8 */
#else
  .pvReserved33      = (void*) (0UL),          /* 33 Reserved */
  .pvReserved34      = (void*) (0UL),          /* 34 Reserved */
  .pvReserved35      = (void*) (0UL),          /* 35 Reserved */
#endif /* TC2 */
  .pfnPWM_Handler    = (void*) PWM_Handler,    /* 36 Pulse Width Modulation Controller */
  .pfnADC_Handler    = (void*) ADC_Handler,    /* 37 ADC Controller */
  .pfnDACC_Handler   = (void*) DACC_Handler,   /* 38 DAC Controller */
  .pfnDMAC_Handler   = (void*) DMAC_Handler,   /* 39 DMA Controller */
  .pfnUOTGHS_Handler = (void*) UOTGHS_Handler, /* 40 USB OTG High Speed */
  .pfnTRNG_Handler   = (void*) TRNG_Handler,   /* 41 True Random Number Generator */
#ifdef EMAC
  .pfnEMAC_Handler   = (void*) EMAC_Handler,   /* 42 Ethernet MAC */
#else
  .pvReserved42      = (void*) (0UL),          /* 42 Reserved */
#endif /* EMAC */
  .pfnCAN0_Handler   = (void*) CAN0_Handler,   /* 43 CAN Controller 0 */
  .pfnCAN1_Handler   = (void*) CAN1_Handler    /* 44 CAN Controller 1 */
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

