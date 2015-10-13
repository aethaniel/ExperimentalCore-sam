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

#define __SYSTEM_CLOCK_8MHZ   (8000000UL)
#define __SYSTEM_CLOCK_120MHZ (120000000UL)

/* Clock Settings (4MHz) using Internal Fast RC */
uint32_t SystemCoreClock = __SYSTEM_CLOCK_8MHZ ;

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
  .pfnSUPC_Handler      = (void*) vector_halt,  /* 0  Supply Controller */
  .pfnRSTC_Handler      = (void*) vector_halt,  /* 1  Reset Controller */
  .pfnRTC_Handler       = (void*) vector_halt,  /* 2  Real Time Clock */
  .pfnRTT_Handler       = (void*) vector_halt,  /* 3  Real Time Timer */
  .pfnWDT_Handler       = (void*) vector_halt,  /* 4  Watchdog Timer */
  .pfnPMC_Handler       = (void*) vector_halt,  /* 5  Power Management Controller */
  .pfnEFC0_Handler      = (void*) vector_halt,  /* 6  Enhanced Flash Controller */
#ifdef FLEXCOM7
  .pfnFLEXCOM7_Handler  = (void*) vector_halt,  /* 7  FLEXCOM 7 */
#else
  .pvReserved7          = (void*) (0UL),        /* 7  Reserved */
#endif  /* FLEXCOM7 */
  .pfnFLEXCOM0_Handler  = (void*) vector_halt,  /* 8  FLEXCOM 0 */
  .pfnFLEXCOM1_Handler  = (void*) vector_halt,  /* 9  FLEXCOM 1 */
  .pvReserved10         = (void*) (0UL),        /* 10 Reserved */
  .pfnPIOA_Handler      = (void*) vector_halt,  /* 11 Parallel I/O Controller A */
  .pfnPIOB_Handler      = (void*) vector_halt,  /* 12 Parallel I/O Controller B */
  .pfnPDMIC0_Handler    = (void*) vector_halt,  /* 13 PDM 0 */
  .pfnFLEXCOM2_Handler  = (void*) vector_halt,  /* 14 FLEXCOM2 */
  .pfnMEM2MEM_Handler   = (void*) vector_halt,  /* 15 MEM2MEM */
  .pfnI2SC0_Handler     = (void*) vector_halt,  /* 16 I2SC0 */
  .pfnI2SC1_Handler     = (void*) vector_halt,  /* 17 I2SC1 */
  .pfnPDMIC1_Handler    = (void*) vector_halt,  /* 18 PDM 1 */
  .pfnFLEXCOM3_Handler  = (void*) vector_halt,  /* 19 FLEXCOM3 */
  .pfnFLEXCOM4_Handler  = (void*) vector_halt,  /* 20 FLEXCOM4 */
  .pfnFLEXCOM5_Handler  = (void*) vector_halt,  /* 21 FLEXCOM5 */
  .pfnFLEXCOM6_Handler  = (void*) vector_halt,  /* 22 FLEXCOM6 */
  .pfnTC0_Handler       = (void*) vector_halt,  /* 23 Timer/Counter 0 */
  .pfnTC1_Handler       = (void*) vector_halt,  /* 24 Timer/Counter 1 */
  .pfnTC2_Handler       = (void*) vector_halt,  /* 25 Timer/Counter 2 */
  .pfnTC3_Handler       = (void*) vector_halt,  /* 26 Timer/Counter 3 */
  .pfnTC4_Handler       = (void*) vector_halt,  /* 27 Timer/Counter 4 */
  .pfnTC5_Handler       = (void*) vector_halt,  /* 28 Timer/Counter 5 */
  .pfnADC_Handler       = (void*) vector_halt,  /* 29 Analog To Digital Converter */
  .pfnFPU_Handler       = (void*) vector_halt,  /* 30 FPU */
  .pvReserved31         = (void*) (0UL),        /* 31 Reserved */
  .pvReserved32         = (void*) (0UL),        /* 32 Reserved */
  .pvReserved33         = (void*) (0UL),        /* 33 Reserved */
  .pvReserved34         = (void*) (0UL),        /* 34 Reserved */
  .pvReserved35         = (void*) (0UL),        /* 35 Reserved */
  .pvReserved36         = (void*) (0UL),        /* 36 Reserved */
  .pvReserved37         = (void*) (0UL),        /* 37 Reserved */
  .pvReserved38         = (void*) (0UL),        /* 38 Reserved */
  .pvReserved39         = (void*) (0UL),        /* 39 Reserved */
  .pvReserved40         = (void*) (0UL),        /* 40 Reserved */
  .pvReserved41         = (void*) (0UL),        /* 41 Reserved */
  .pvReserved42         = (void*) (0UL),        /* 42 Reserved */
  .pvReserved43         = (void*) (0UL),        /* 43 Reserved */
  .pvReserved44         = (void*) (0UL),        /* 44 Reserved */
  .pvReserved45         = (void*) (0UL),        /* 45 Reserved */
  .pvReserved46         = (void*) (0UL),        /* 46 Reserved */
  .pfnUHP_Handler       = (void*) vector_halt,  /* 47 USB OHCI */
  .pfnUSBDEV_Handler    = (void*) vector_halt,  /* 48 USB Device FS */
  .pfnCRCCU_Handler     = (void*) vector_halt   /* 49 CRCCU */
};

/**
 * \brief Setup the microcontroller system.
 *
 * Initialize the System and update the System Frequency variable.
 */
void SystemInit( void )
{
}

