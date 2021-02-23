/*
*********************************************************************************************************
*                                                uC/CPU
*                                    CPU CONFIGURATION & PORT LAYER
*
*                          (c) Copyright 2004-2011; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*
*               uC/CPU is provided in source form to registered licensees ONLY.  It is
*               illegal to distribute this source code to any third party unless you receive
*               written permission by an authorized Micrium representative.  Knowledge of
*               the source code may NOT be used to develop a similar product.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*
*               You can contact us at www.micrium.com.
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#define    MICRIUM_SOURCE
#include  <cpu.h>
#include  <cpu_core.h>

#include  <lib_def.h>
#include  "Bsp.h"
CPU_DATA  CPU_CntLeadZeros (CPU_DATA  val)
{
    CPU_DATA ret;
    __asm ("clz %0, %1" : "=d" (ret) : "d" (val));
    return ret;
}

IfxCpu_mutexLock  MultiCoreMutex;

Ifx_TickTime TimeConst[TIMER_COUNT];

/** \brief Initialize the time constants.
 *
 * Initialize the time constants TimeConst_0s, TimeConst_100ns, TimeConst_1us,
 * TimeConst_10us, TimeConst_100us, TimeConst_1ms, TimeConst_10ms, TimeConst_100ms,
 * TimeConst_1s, TimeConst_10s
 * \return None.
 */
void initTime(void)
{
    sint32 Fsys = IfxStm_getFrequency(BSP_DEFAULT_TIMER);

    TimeConst[TIMER_INDEX_10NS]  = Fsys / (1000000000 / 10);
    TimeConst[TIMER_INDEX_100NS] = Fsys / (1000000000 / 100);
    TimeConst[TIMER_INDEX_1US]   = Fsys / (1000000 / 1);
    TimeConst[TIMER_INDEX_10US]  = Fsys / (1000000 / 10);
    TimeConst[TIMER_INDEX_100US] = Fsys / (1000000 / 100);
    TimeConst[TIMER_INDEX_1MS]   = Fsys / (1000 / 1);
    TimeConst[TIMER_INDEX_10MS]  = Fsys / (1000 / 10);
    TimeConst[TIMER_INDEX_100MS] = Fsys / (1000 / 100);
    TimeConst[TIMER_INDEX_1S]    = Fsys * (1);
    TimeConst[TIMER_INDEX_10S]   = Fsys * (10);
    TimeConst[TIMER_INDEX_100S]  = Fsys * (100);
}


/** \brief Wait function.
 *
 * This is an empty function that just spend some time waiting.
 *
 * \return None.
 */
void waitPoll(void)
{}

/** \brief Wait time function.
 *
 * This is an empty function that that returns after the timeout elapsed. The
 * minimal time spend in the function is guaranteed, but not the max time.
 *
 * \param timeout Specifies the time the function waits for before returning
 *
 * \return None.
 */
void waitTime(Ifx_TickTime timeout)
{
    wait(timeout);
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/


