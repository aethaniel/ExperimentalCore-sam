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
#include "core_delay.h"
#include "core_hooks.h"

#define __SYSTEM_CLOCK_8MHZ   (8000000UL)
#define __SYSTEM_CLOCK_120MHZ (120000000UL)

/* Clock Settings (4MHz) using Internal Fast RC */
uint32_t SystemCoreClock = __SYSTEM_CLOCK_8MHZ ;

/**
 * \brief Default interrupt handler for unused IRQs.
 */
static void __halt()
{
  // Halts
  while (1);
}

/* Peripherals handlers */
void SUPC_Handler      ( void ) __attribute__ ((weak, alias("__halt")));
void RSTC_Handler      ( void ) __attribute__ ((weak, alias("__halt")));
void RTC_Handler       ( void ) __attribute__ ((weak, alias("__halt")));
void RTT_Handler       ( void ) __attribute__ ((weak, alias("__halt")));
void WDT_Handler       ( void ) __attribute__ ((weak, alias("__halt")));
void PMC_Handler       ( void ) __attribute__ ((weak, alias("__halt")));
void EFC_Handler       ( void ) __attribute__ ((weak, alias("__halt")));
#ifdef FLEXCOM7
void FLEXCOM7_Handler  ( void ) __attribute__ ((weak, alias("__halt")));
#endif /* FLEXCOM7*/
void FLEXCOM0_Handler  ( void ) __attribute__ ((weak, alias("__halt")));
void FLEXCOM1_Handler  ( void ) __attribute__ ((weak, alias("__halt")));
void PIOA_Handler      ( void ) __attribute__ ((weak, alias("__halt")));
void PIOB_Handler      ( void ) __attribute__ ((weak, alias("__halt")));
void PDMIC0_Handler    ( void ) __attribute__ ((weak, alias("__halt")));
void FLEXCOM2_Handler  ( void ) __attribute__ ((weak, alias("__halt")));
void MEM2MEM_Handler   ( void ) __attribute__ ((weak, alias("__halt")));
void I2SC0_Handler     ( void ) __attribute__ ((weak, alias("__halt")));
void I2SC1_Handler     ( void ) __attribute__ ((weak, alias("__halt")));
void PDMIC1_Handler    ( void ) __attribute__ ((weak, alias("__halt")));
void FLEXCOM3_Handler  ( void ) __attribute__ ((weak, alias("__halt")));
void FLEXCOM4_Handler  ( void ) __attribute__ ((weak, alias("__halt")));
void FLEXCOM5_Handler  ( void ) __attribute__ ((weak, alias("__halt")));
void FLEXCOM6_Handler  ( void ) __attribute__ ((weak, alias("__halt")));
void TC0_Handler       ( void ) __attribute__ ((weak, alias("__halt")));
void TC1_Handler       ( void ) __attribute__ ((weak, alias("__halt")));
void TC2_Handler       ( void ) __attribute__ ((weak, alias("__halt")));
void TC3_Handler       ( void ) __attribute__ ((weak, alias("__halt")));
void TC4_Handler       ( void ) __attribute__ ((weak, alias("__halt")));
void TC5_Handler       ( void ) __attribute__ ((weak, alias("__halt")));
void ADC_Handler       ( void ) __attribute__ ((weak, alias("__halt")));
void ARM_Handler       ( void ) __attribute__ ((weak, alias("__halt")));
void UHP_Handler       ( void ) __attribute__ ((weak, alias("__halt")));
void UDP_Handler       ( void ) __attribute__ ((weak, alias("__halt")));
void CRCCU_Handler     ( void ) __attribute__ ((weak, alias("__halt")));

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
  .pfnSUPC_Handler      = (void*) SUPC_Handler,      /* 0  Supply Controller */
  .pfnRSTC_Handler      = (void*) RSTC_Handler,      /* 1  Reset Controller */
  .pfnRTC_Handler       = (void*) RTC_Handler,       /* 2  Real Time Clock */
  .pfnRTT_Handler       = (void*) RTT_Handler,       /* 3  Real Time Timer */
  .pfnWDT_Handler       = (void*) WDT_Handler,       /* 4  Watchdog Timer */
  .pfnPMC_Handler       = (void*) PMC_Handler,       /* 5  Power Management Controller */
  .pfnEFC_Handler       = (void*) EFC_Handler,       /* 6  Enhanced Flash Controller */
#ifdef FLEXCOM7
  .pfnFLEXCOM7_Handler  = (void*) FLEXCOM7_Handler,  /* 7  FLEXCOM 7 */
#else
  .pvReserved7          = (void*) (0UL),             /* 7  Reserved */
#endif  /* FLEXCOM7 */
  .pfnFLEXCOM0_Handler  = (void*) FLEXCOM0_Handler,  /* 8  FLEXCOM 0 */
  .pfnFLEXCOM1_Handler  = (void*) FLEXCOM1_Handler,  /* 9  FLEXCOM 1 */
  .pvReserved10         = (void*) (0UL),             /* 10 Reserved */
  .pfnPIOA_Handler      = (void*) PIOA_Handler,      /* 11 Parallel I/O Controller A */
  .pfnPIOB_Handler      = (void*) PIOB_Handler,      /* 12 Parallel I/O Controller B */
  .pfnPDMIC0_Handler    = (void*) PDMIC0_Handler,    /* 13 PDM 0 */
  .pfnFLEXCOM2_Handler  = (void*) FLEXCOM2_Handler,  /* 14 FLEXCOM2 */
  .pfnMEM2MEM_Handler   = (void*) MEM2MEM_Handler,   /* 15 MEM2MEM */
  .pfnI2SC0_Handler     = (void*) I2SC0_Handler,    /* 16 I2SC0 */
  .pfnI2SC1_Handler     = (void*) I2SC1_Handler,     /* 17 I2SC1 */
  .pfnPDMIC1_Handler    = (void*) PDMIC1_Handler,    /* 18 PDM 1 */
  .pfnFLEXCOM3_Handler  = (void*) FLEXCOM3_Handler,  /* 19 FLEXCOM3 */
  .pfnFLEXCOM4_Handler  = (void*) FLEXCOM4_Handler,  /* 20 FLEXCOM4 */
  .pfnFLEXCOM5_Handler  = (void*) FLEXCOM5_Handler,  /* 21 FLEXCOM5 */
  .pfnFLEXCOM6_Handler  = (void*) FLEXCOM6_Handler,  /* 22 FLEXCOM6 */
  .pfnTC0_Handler       = (void*) TC0_Handler,       /* 23 Timer/Counter 0 */
  .pfnTC1_Handler       = (void*) TC1_Handler,       /* 24 Timer/Counter 1 */
  .pfnTC2_Handler       = (void*) TC2_Handler,       /* 25 Timer/Counter 2 */
  .pfnTC3_Handler       = (void*) TC3_Handler,       /* 26 Timer/Counter 3 */
  .pfnTC4_Handler       = (void*) TC4_Handler,       /* 27 Timer/Counter 4 */
  .pfnTC5_Handler       = (void*) TC5_Handler,       /* 28 Timer/Counter 5 */
  .pfnADC_Handler       = (void*) ADC_Handler,       /* 29 Analog To Digital Converter */
  .pfnARM_Handler       = (void*) ARM_Handler,       /* 30 FPU */
  .pvReserved31         = (void*) (0UL),             /* 31 Reserved */
  .pvReserved32         = (void*) (0UL),             /* 32 Reserved */
  .pvReserved33         = (void*) (0UL),             /* 33 Reserved */
  .pvReserved34         = (void*) (0UL),             /* 34 Reserved */
  .pvReserved35         = (void*) (0UL),             /* 35 Reserved */
  .pvReserved36         = (void*) (0UL),             /* 36 Reserved */
  .pvReserved37         = (void*) (0UL),             /* 37 Reserved */
  .pvReserved38         = (void*) (0UL),             /* 38 Reserved */
  .pvReserved39         = (void*) (0UL),             /* 39 Reserved */
  .pvReserved40         = (void*) (0UL),             /* 40 Reserved */
  .pvReserved41         = (void*) (0UL),             /* 41 Reserved */
  .pvReserved42         = (void*) (0UL),             /* 42 Reserved */
  .pvReserved43         = (void*) (0UL),             /* 43 Reserved */
  .pvReserved44         = (void*) (0UL),             /* 44 Reserved */
  .pvReserved45         = (void*) (0UL),             /* 45 Reserved */
  .pvReserved46         = (void*) (0UL),             /* 46 Reserved */
  .pfnUHP_Handler       = (void*) UHP_Handler,       /* 47 USB OHCI */
  .pfnUDP_Handler       = (void*) UDP_Handler,       /* 48 USB Device FS */
  .pfnCRCCU_Handler     = (void*) CRCCU_Handler      /* 49 CRCCU */
};

/**
 * \brief Setup the microcontroller system.
 *
 * Initialize the System and update the System Frequency variable.
 */
void SystemInit( void )
{
}

