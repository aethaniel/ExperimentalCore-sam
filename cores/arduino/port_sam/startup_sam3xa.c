/*
  Copyright (c) 2014 Arduino.  All right reserved.

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

/* Initialize segments */
extern uint32_t __etext ;
extern uint32_t __data_start__ ;
extern uint32_t __data_end__ ;
extern uint32_t __bss_start__ ;
extern uint32_t __bss_end__ ;
extern uint32_t __StackTop;

extern int main( void ) ;
extern void __libc_init_array(void);

#if 0 // see cortex_handlers.c
/* Default empty handler */
void Dummy_Handler(void);

/* Cortex-M3 core handlers */
#if defined DEBUG
void NMI_Handler( void )
{
  while ( 1 )
  {
  }
}

void HardFault_Handler( void )
{
  while ( 1 )
  {
  }
}

void SVC_Handler( void )
{
  while ( 1 )
  {
  }
}

void PendSV_Handler( void )
{
  while ( 1 )
  {
  }
}

void SysTick_Handler         ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#else
void NMI_Handler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void HardFault_Handler  ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void MemManage_Handler  ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void BusFault_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void UsageFault_Handler ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SVC_Handler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void DebugMon_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void PendSV_Handler     ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SysTick_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif //DEBUG

/* Peripherals handlers */
void SUPC_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void RSTC_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void RTC_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void RTT_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void WDT_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void PMC_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void EFC0_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void EFC1_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void UART_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#ifdef _SAM3XA_SMC_INSTANCE_
void SMC_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAM3XA_SMC_INSTANCE_ */
#ifdef _SAM3XA_SDRAMC_INSTANCE_
void SDRAMC_Handler ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAM3XA_SDRAMC_INSTANCE_ */
void PIOA_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void PIOB_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#ifdef _SAM3XA_PIOC_INSTANCE_
void PIOC_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAM3XA_PIOC_INSTANCE_ */
#ifdef _SAM3XA_PIOD_INSTANCE_
void PIOD_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAM3XA_PIOD_INSTANCE_ */
#ifdef _SAM3XA_PIOE_INSTANCE_
void PIOE_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAM3XA_PIOE_INSTANCE_ */
#ifdef _SAM3XA_PIOF_INSTANCE_
void PIOF_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAM3XA_PIOF_INSTANCE_ */
void USART0_Handler ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void USART1_Handler ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void USART2_Handler ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#ifdef _SAM3XA_USART3_INSTANCE_
void USART3_Handler ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAM3XA_USART3_INSTANCE_ */
void HSMCI_Handler  ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TWI0_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TWI1_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SPI0_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#ifdef _SAM3XA_SPI1_INSTANCE_
void SPI1_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAM3XA_SPI1_INSTANCE_ */
void SSC_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC0_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC1_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC2_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC3_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC4_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC5_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#ifdef _SAM3XA_TC2_INSTANCE_
void TC6_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAM3XA_TC2_INSTANCE_ */
#ifdef _SAM3XA_TC2_INSTANCE_
void TC7_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAM3XA_TC2_INSTANCE_ */
#ifdef _SAM3XA_TC2_INSTANCE_
void TC8_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAM3XA_TC2_INSTANCE_ */
void PWM_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void ADC_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void DACC_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void DMAC_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void UOTGHS_Handler ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TRNG_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#ifdef _SAM3XA_EMAC_INSTANCE_
void EMAC_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAM3XA_EMAC_INSTANCE_ */
void CAN0_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void CAN1_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif // 0

/* Exception Table */
__attribute__ ((section(".isr_vector")))
const DeviceVectors exception_table=
{
    /* Configure Initial Stack Pointer, using linker-generated symbols */
    .pvStack = (void*) (&__StackTop),

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
    .pfnEFC0_Handler   = (void*) EFC0_Handler,   /* 6  Enhanced Flash Controller 0 */
    .pfnEFC1_Handler   = (void*) EFC1_Handler,   /* 7  Enhanced Flash Controller 1 */
    .pfnUART_Handler   = (void*) UART_Handler,   /* 8  Universal Asynchronous Receiver Transceiver */
#ifdef _SAM3XA_SMC_INSTANCE_
    .pfnSMC_Handler    = (void*) SMC_Handler,    /* 9  Static Memory Controller */
#else
    .pvReserved9       = (void*) (0UL),          /* 9  Reserved */
#endif /* _SAM3XA_SMC_INSTANCE_ */
#ifdef _SAM3XA_SDRAMC_INSTANCE_
    .pfnSDRAMC_Handler = (void*) SDRAMC_Handler, /* 10 Synchronous Dynamic RAM Controller */
#else
    .pvReserved10      = (void*) (0UL),          /* 10 Reserved */
#endif /* _SAM3XA_SDRAMC_INSTANCE_ */
    .pfnPIOA_Handler   = (void*) PIOA_Handler,   /* 11 Parallel I/O Controller A, */
    .pfnPIOB_Handler   = (void*) PIOB_Handler,   /* 12 Parallel I/O Controller B */
#ifdef _SAM3XA_PIOC_INSTANCE_
    .pfnPIOC_Handler   = (void*) PIOC_Handler,   /* 13 Parallel I/O Controller C */
#else
    .pvReserved13      = (void*) (0UL),          /* 13 Reserved */
#endif /* _SAM3XA_PIOC_INSTANCE_ */
#ifdef _SAM3XA_PIOD_INSTANCE_
    .pfnPIOD_Handler   = (void*) PIOD_Handler,   /* 14 Parallel I/O Controller D */
#else
    .pvReserved14      = (void*) (0UL),          /* 14 Reserved */
#endif /* _SAM3XA_PIOD_INSTANCE_ */
#ifdef _SAM3XA_PIOE_INSTANCE_
    .pfnPIOE_Handler   = (void*) PIOE_Handler,   /* 15 Parallel I/O Controller E */
#else
    .pvReserved15      = (void*) (0UL),          /* 15 Reserved */
#endif /* _SAM3XA_PIOE_INSTANCE_ */
#ifdef _SAM3XA_PIOF_INSTANCE_
    .pfnPIOF_Handler   = (void*) PIOF_Handler,   /* 16 Parallel I/O Controller F */
#else
    .pvReserved16      = (void*) (0UL),          /* 16 Reserved */
#endif /* _SAM3XA_PIOF_INSTANCE_ */
    .pfnUSART0_Handler = (void*) USART0_Handler, /* 17 USART 0 */
    .pfnUSART1_Handler = (void*) USART1_Handler, /* 18 USART 1 */
    .pfnUSART2_Handler = (void*) USART2_Handler, /* 19 USART 2 */
#ifdef _SAM3XA_USART3_INSTANCE_
    .pfnUSART3_Handler = (void*) USART3_Handler, /* 20 USART 3 */
#else
    .pvReserved20      = (void*) (0UL),          /* 20 Reserved */
#endif /* _SAM3XA_USART3_INSTANCE_ */
    .pfnHSMCI_Handler  = (void*) HSMCI_Handler,  /* 21 Multimedia Card Interface */
    .pfnTWI0_Handler   = (void*) TWI0_Handler,   /* 22 Two-Wire Interface 0 */
    .pfnTWI1_Handler   = (void*) TWI1_Handler,   /* 23 Two-Wire Interface 1 */
    .pfnSPI0_Handler   = (void*) SPI0_Handler,   /* 24 Serial Peripheral Interface */
#ifdef _SAM3XA_SPI1_INSTANCE_
    .pfnSPI1_Handler   = (void*) SPI1_Handler,   /* 25 Serial Peripheral Interface */
#else
    .pvReserved25      = (void*) (0UL),          /* 25 Reserved */
#endif /* _SAM3XA_SPI1_INSTANCE_ */
    .pfnSSC_Handler    = (void*) SSC_Handler,    /* 26 Synchronous Serial Controller */
    .pfnTC0_Handler    = (void*) TC0_Handler,    /* 27 Timer Counter 0 */
    .pfnTC1_Handler    = (void*) TC1_Handler,    /* 28 Timer Counter 1 */
    .pfnTC2_Handler    = (void*) TC2_Handler,    /* 29 Timer Counter 2 */
    .pfnTC3_Handler    = (void*) TC3_Handler,    /* 30 Timer Counter 3 */
    .pfnTC4_Handler    = (void*) TC4_Handler,    /* 31 Timer Counter 4 */
    .pfnTC5_Handler    = (void*) TC5_Handler,    /* 32 Timer Counter 5 */
#ifdef _SAM3XA_TC2_INSTANCE_
    .pfnTC6_Handler    = (void*) TC6_Handler,    /* 33 Timer Counter 6 */
#else
    .pvReserved33      = (void*) (0UL),          /* 33 Reserved */
#endif /* _SAM3XA_TC2_INSTANCE_ */
#ifdef _SAM3XA_TC2_INSTANCE_
    .pfnTC7_Handler    = (void*) TC7_Handler,    /* 34 Timer Counter 7 */
#else
    .pvReserved34      = (void*) (0UL),          /* 34 Reserved */
#endif /* _SAM3XA_TC2_INSTANCE_ */
#ifdef _SAM3XA_TC2_INSTANCE_
    .pfnTC8_Handler    = (void*) TC8_Handler,    /* 35 Timer Counter 8 */
#else
    .pvReserved35      = (void*) (0UL),          /* 35 Reserved */
#endif /* _SAM3XA_TC2_INSTANCE_ */
    .pfnPWM_Handler    = (void*) PWM_Handler,    /* 36 Pulse Width Modulation Controller */
    .pfnADC_Handler    = (void*) ADC_Handler,    /* 37 ADC Controller */
    .pfnDACC_Handler   = (void*) DACC_Handler,   /* 38 DAC Controller */
    .pfnDMAC_Handler   = (void*) DMAC_Handler,   /* 39 DMA Controller */
    .pfnUOTGHS_Handler = (void*) UOTGHS_Handler, /* 40 USB OTG High Speed */
    .pfnTRNG_Handler   = (void*) TRNG_Handler,   /* 41 True Random Number Generator */
#ifdef _SAM3XA_EMAC_INSTANCE_
    .pfnEMAC_Handler   = (void*) EMAC_Handler,   /* 42 Ethernet MAC */
#else
    .pvReserved42      = (void*) (0UL),          /* 42 Reserved */
#endif /* _SAM3XA_EMAC_INSTANCE_ */
    .pfnCAN0_Handler   = (void*) CAN0_Handler,   /* 43 CAN Controller 0 */
    .pfnCAN1_Handler   = (void*) CAN1_Handler    /* 44 CAN Controller 1 */
} ;

/**
 * \brief This is the code that gets called on processor reset.
 * \brief This is the code that gets called on processor reset.
 * To initialize the device, and call the main() routine.
 */
void Reset_Handler( void )
{
  uint32_t *pSrc, *pDest;

  /* Initialize the initialized data section */
  pSrc = &__etext;
  pDest = &__data_start__;

  if ( (&__data_start__ != &__data_end__) && (pSrc != pDest) )
  {
    for (; pDest < &__data_end__ ; pDest++, pSrc++ )
    {
      *pDest = *pSrc ;
    }
  }

  /* Clear the zero section */
  if ( (&__data_start__ != &__data_end__) && (pSrc != pDest) )
  {
    for ( pDest = &__bss_start__ ; pDest < &__bss_end__ ; pDest++ )
    {
      *pDest = 0 ;
    }
  }

  /* Initialize the C library */
  __libc_init_array();

  SystemInit() ;

  /* Branch to main function */
  main() ;

  /* Infinite loop */
  while ( 1 )
  {
  }
}

/**
 * \brief Default interrupt handler for unused IRQs.
 */
void Dummy_Handler( void )
{
  while ( 1 )
  {
  }
}
