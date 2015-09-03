#ifndef _ARDUINO_CORE_CORTEX_M_VECTORS_H_
#define _ARDUINO_CORE_CORTEX_M_VECTORS_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _CoreVectors
{
  /* Stack pointer */
  void* pvStack;

  /* Cortex-M handlers */
  void* pfnReset_Handler;
  void* pfnNMI_Handler;
  void* pfnHardFault_Handler;
  void* pfnMemManage_Handler;
  void* pfnBusFault_Handler;
  void* pfnUsageFault_Handler;
  void* pfnReserved1_Handler;
  void* pfnReserved2_Handler;
  void* pfnReserved3_Handler;
  void* pfnReserved4_Handler;
  void* pfnSVC_Handler;
  void* pfnDebugMon_Handler;
  void* pfnReserved5_Handler;
  void* pfnPendSV_Handler;
  void* pfnSysTick_Handler;
} CoreVectors;

#ifdef __cplusplus
}
#endif

#endif // _ARDUINO_CORE_CORTEX_M_VECTORS_H_
