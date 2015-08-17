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

/* Initialize segments */
extern uint32_t __etext ;
extern uint32_t __data_start__ ;
extern uint32_t __data_end__ ;
extern uint32_t __bss_start__ ;
extern uint32_t __bss_end__ ;
extern uint32_t __StackTop;

extern int main( void ) ;
extern void __libc_init_array(void);


extern void svcHook(void);
extern void pendSVHook(void);
extern int sysTickHook(void);

#define __SYSTEM_CLOCK_8MHZ   (8000000UL)
#define __SYSTEM_CLOCK_120MHZ (120000000UL)

/* Clock Settings (4MHz) using Internal Fast RC */
uint32_t SystemCoreClock = __SYSTEM_CLOCK_8MHZ ;

/**
 * \brief Default interrupt handler for unused IRQs.
 */
static void __halt() {
	// Halts
	while (1)
		;
}

/* Cortex-M3 core handlers */
void NMI_Handler       (void) __attribute__ ((weak, alias("__halt")));
void HardFault_Handler (void) __attribute__ ((weak, alias("__halt")));
void MemManage_Handler (void) __attribute__ ((weak, alias("__halt")));
void BusFault_Handler  (void) __attribute__ ((weak, alias("__halt")));
void UsageFault_Handler(void) __attribute__ ((weak, alias("__halt")));
void DebugMon_Handler  (void) __attribute__ ((weak, alias("__halt")));
void SVC_Handler       (void) { svcHook(); }
void PendSV_Handler    (void) {	pendSVHook(); }


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
};

/**
 * \brief Setup the microcontroller system.
 *
 * Initialize the System and update the SystemFrequency variable.
 */
void SystemInit( void )
{
}

/**
 * \brief This is the code that gets called on processor reset.
 * Initializes the device and call the main() routine.
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
  if ( &__bss_start__ != &__bss_end__ )
  {
    for ( pDest = &__bss_start__ ; pDest < &__bss_end__ ; pDest++ )
    {
      *pDest = 0ul ;
    }
  }

  /* Initialize the C library */
//  __libc_init_array();

  /* Initialize the system */
  SystemInit() ;

  /* Branch to main function */
  main() ;

  /* Infinite loop */
  while ( 1 )
  {
  }
}

void SysTick_Handler(void)
{
  if (sysTickHook())
    return;
  SysTick_DefaultHandler();
}
