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

#ifdef __cplusplus
extern "C" {
#endif

#include "sam.h"
#include "core_hooks.h"
#include "core_cortex_vectors.h"
#include "core_variant.h"
#include "core_delay.h"           // for SysTick_DefaultHandler()
#include <stdint.h>

/* Symbols exported from linker script */
extern uint32_t __etext ;
extern uint32_t __data_start__ ;
extern uint32_t __data_end__ ;
extern uint32_t __bss_start__ ;
extern uint32_t __bss_end__ ;
extern uint32_t __StackTop;

extern int main( void ) ;
/* symbols from libc */
extern void __libc_init_array(void);


/**
 * \brief Default interrupt handler for unused IRQs.
 */
static void vector_halt(void)
{
  // Halts
  while (1);
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

#if defined DEBUG && (DEBUG == 1)
#warning "DEBUG handlers activated"

void HardFault_Handler (void)
{
  while (1);
}

void NMI_Handler(void)
{
  while (1);
}

void MemManage_Handler(void)
{
  while (1);
}

void BusFault_Handler(void)
{
  while (1);
}

void UsageFault_Handler(void)
{
  while (1);
}

void DebugMon_Handler(void)
{
  while (1);
}

#else

void HardFault_Handler (void) __attribute__ ((weak, alias("vector_halt")));
void NMI_Handler       (void) __attribute__ ((weak, alias("vector_halt")));
void MemManage_Handler (void) __attribute__ ((weak, alias("vector_halt")));
void BusFault_Handler  (void) __attribute__ ((weak, alias("vector_halt")));
void UsageFault_Handler(void) __attribute__ ((weak, alias("vector_halt")));
void DebugMon_Handler  (void) __attribute__ ((weak, alias("vector_halt")));

#endif // DEBUG=1

void SVC_Handler(void)
{
  svcHook();
}

void PendSV_Handler(void)
{
  pendSVHook();
}

void SysTick_Handler(void)
{
  if (sysTickHook())
    return;
  SysTick_DefaultHandler();
}

/* Exception Table */
__attribute__ ((section(".isr_vector")))
const CoreVectors startup_exception_table=
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
 };

void* vectorSetOrigin(DeviceVectors* pBase)
{
  void* p=(void*)(SCB->VTOR);

  /* relocate vector table
   * reference is http://www.keil.com/pack/doc/cmsis/core/html/_using__v_t_o_r_pg.html
   */
  __disable_irq();
  SCB->VTOR = (uint32_t)pBase;
  __DSB();
  __enable_irq();

  return p;
}

void* vectorAssign(IRQn_Type number, void (*isr)(void))
{
  uint32_t* pulTable=(uint32_t*)(SCB->VTOR);
  void *p=(void*)(pulTable+number+16);

  __disable_irq();
  pulTable[number+16]=(uint32_t)isr ;
  __DSB();
  __enable_irq();

  return p;
}

void* vectorReset(IRQn_Type number)
{
  uint32_t* pulTable=(uint32_t*)(SCB->VTOR);
  void *p=(void*)(pulTable+number+16);

  __disable_irq();
  pulTable[number+16]=(uint32_t)vector_halt ;
  __DSB();
  __enable_irq();

  return p;
}

#ifdef __cplusplus
}
#endif
