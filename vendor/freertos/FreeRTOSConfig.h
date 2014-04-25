#ifndef __FREERTOS_CONFIG__H
#define __FREERTOS_CONFIG__H

#ifndef __IASMARM__
// IAR assembler "compile" portarm.s need to include this file but cannot understand many other headers.
#include "hal/hal.h"
#include "common/assertion.h"
#endif

//--------------------------------------------------------------------+
// See http://www.freertos.org/a00110.html.
//--------------------------------------------------------------------+
#define configUSE_PREEMPTION                   1
#define configCPU_CLOCK_HZ                     ( SystemCoreClock )
//#define configCPU_CLOCK_HZ                   ( CGU_GetPCLKFrequency(CGU_PERIPHERAL_M4CORE))
#define configTICK_RATE_HZ                     ( ( portTickType ) 1000 )
#define configMAX_PRIORITIES                   ( ( unsigned portBASE_TYPE ) 8 )
#define configMINIMAL_STACK_SIZE               ( ( unsigned short ) 128 )
#define configTOTAL_HEAP_SIZE                  ( ( size_t ) ( 16*1024 ) )
#define configMAX_TASK_NAME_LEN                32
#define configUSE_16_BIT_TICKS      		       0
#define configIDLE_SHOULD_YIELD                1
#define configUSE_MUTEXES                      1
#define configUSE_RECURSIVE_MUTEXES            0
#define configUSE_COUNTING_SEMAPHORES          0
#define configQUEUE_REGISTRY_SIZE              10 // used to name queue/semaphore with debugger

/* Hook function related definitions. */
#define configUSE_IDLE_HOOK                    1
#define configUSE_TICK_HOOK                    0
#define configUSE_MALLOC_FAILED_HOOK           1
#define configCHECK_FOR_STACK_OVERFLOW         2

/* Run time and task stats gathering related definitions. */
#define configGENERATE_RUN_TIME_STATS          0
#define configUSE_TRACE_FACILITY               1 // legacy trace
#define configUSE_STATS_FORMATTING_FUNCTIONS   0

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES                  0
#define configMAX_CO_ROUTINE_PRIORITIES        2

/* Software timer related definitions. */
#define configUSE_TIMERS                       0
#define configTIMER_TASK_PRIORITY              ( configMAX_PRIORITIES - 3 )
#define configTIMER_QUEUE_LENGTH               10
#define configTIMER_TASK_STACK_DEPTH	         configMINIMAL_STACK_SIZE

/* Optional functions - most linkers will remove unused functions anyway. */
#define INCLUDE_vTaskPrioritySet               0
#define INCLUDE_uxTaskPriorityGet              0
#define INCLUDE_vTaskDelete                    0
#define INCLUDE_vTaskSuspend                   1 // required for queue, semaphore, mutex to be blocked indefinitely with portMAX_DELAY
#define INCLUDE_xResumeFromISR                 0
#define INCLUDE_vTaskDelayUntil                1
#define INCLUDE_vTaskDelay                     1
#define INCLUDE_xTaskGetSchedulerState         0
#define INCLUDE_xTaskGetCurrentTaskHandle      0
#define INCLUDE_uxTaskGetStackHighWaterMark    0
#define INCLUDE_xTaskGetIdleTaskHandle         0
#define INCLUDE_xTimerGetTimerDaemonTaskHandle 0
#define INCLUDE_pcTaskGetTaskName              0
#define INCLUDE_eTaskGetState                  0
#define INCLUDE_xEventGroupSetBitFromISR       0
#define INCLUDE_xTimerPendFunctionCall         0

/* Define to trap errors during development. */
#define configASSERT( x )                      if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); hal_debugger_breakpoint(); }

/* FreeRTOS hooks to NVIC vectors */
#define xPortPendSVHandler    PendSV_Handler
#define xPortSysTickHandler   SysTick_Handler
#define vPortSVCHandler       SVC_Handler

//--------------------------------------------------------------------+
// Interrupt nesting behaviour configuration.
//--------------------------------------------------------------------+
/* Cortex-M specific definitions. */
#ifdef __NVIC_PRIO_BITS
	#define configPRIO_BITS       __NVIC_PRIO_BITS
#else
	#define configPRIO_BITS       5        /* 32 priority levels */
#endif

/* The lowest interrupt priority that can be used in a call to a "set priority"
function. */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY			  0x1f

/* The highest interrupt priority that can be used by any interrupt service
routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
PRIORITY THAN THIS! (higher priorities are lower numeric values. */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY	5

/* Interrupt priorities used by the kernel port layer itself.  These are generic
to all Cortex-M ports, and do not rely on any particular library functions. */
#define configKERNEL_INTERRUPT_PRIORITY 		          ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	        ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

#if 0
#if __CORTEX_M == 4

#elif __CORTEX_M == 3

#elif __CORTEX_M == 0

#else
	#error "not yet supported MCU"
#endif
#endif

#endif /* __FREERTOS_CONFIG__H */
