/**********************************************************************************************************************
 * \file Cpu1_Main.c
 * \copyright Copyright (C) Infineon Technologies AG 2019
 *
 * Use of this file is subject to the terms of use agreed between (i) you or the company in which ordinary course of
 * business you are acting and (ii) Infineon Technologies AG or its licensees. If and as long as no such terms of use
 * are agreed, use of this file is subject to following:
 *
 * Boost Software License - Version 1.0 - August 17th, 2003
 *
 * Permission is hereby granted, free of charge, to any person or organization obtaining a copy of the software and
 * accompanying documentation covered by this license (the "Software") to use, reproduce, display, distribute, execute,
 * and transmit the Software, and to prepare derivative works of the Software, and to permit third-parties to whom the
 * Software is furnished to do so, all subject to the following:
 *
 * The copyright notices in the Software and this entire statement, including the above license grant, this restriction
 * and the following disclaimer, must be included in all copies of the Software, in whole or in part, and all
 * derivative works of the Software, unless such copies or derivative works are solely in the form of
 * machine-executable object code generated by a source language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *********************************************************************************************************************/
#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"

#include "Bsp.h"
#include "Multican/Can/IfxMultican_Can.h"

extern IfxCpu_syncEvent g_cpuSyncEvent;

// CAN handle
extern IfxMultican_Can can;
// Nodes handles
extern IfxMultican_Can_Node canNode1;
extern IfxMultican_Can_Node canNode2;
extern IfxMultican_Can_Node canNode3;
extern IfxMultican_Can_Node canNode0;

// Message Object handles
extern IfxMultican_Can_MsgObj canMsgObj0;
extern IfxMultican_Can_MsgObj canMsgObj1;
extern IfxMultican_Can_MsgObj canMsgObj2;
extern IfxMultican_Can_MsgObj canMsgObj3;
extern void CAN_SendSingle(IfxMultican_Can_MsgObj *MO, uint32 id, uint32 high, uint32 low);
static  void  Core1TaskCreate (void);
extern CPU_INT32U SyncFlag;
static  OS_TCB          AppTask3TCB;
static  CPU_STK         AppTask3Stk[APP_TASK_3_STK_SIZE];
static  OS_TCB_CTX_EXT  AppTask3Ext;
static  OS_TCB          AppTask4TCB;
static  CPU_STK         AppTask4Stk[APP_TASK_4_STK_SIZE];
static  OS_TCB_CTX_EXT  AppTask4Ext;

int core1_main(void)
{
    IfxCpu_enableInterrupts();

    /* !!WATCHDOG1 IS DISABLED HERE!!
     * Enable the watchdog and service it periodically if it is required
     */
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());

    /* Wait for CPU sync event */
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 1);
    while(SyncFlag == 0);
    Core1TaskCreate ();

    while(1)
    {
        CAN_SendSingle(&canMsgObj0, 0x511, 0x0000, 0x0000);
        waitTime(TimeConst_1s);
    }
    return (1);
}
/*
*********************************************************************************************************
*                                      CREATE APPLICATION TASKS
*
* Description:  This function creates the application tasks.
*
* Arguments  :  none
*
* Returns    :  none
*********************************************************************************************************
*/

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief                      TASK #1
*
*           This is an example of a task.
*
* \note     1) The first line of code is used to prevent a compiler warning because 'pdata' is not
*              used.  The compiler should not generate any code for this statement.
*
* \param    pdata             Is the argument passed to 'AppTask1()' by 'OSTaskCreate()'.
*/
/*------------------------------------------------------------------------------------------------*/
void AppTask3 ()
{
    OS_ERR       err;
    IfxCpu_Id   CpuID;


    OSTimeDlyHMSM(0, 0, 1, 210,
                  OS_OPT_TIME_HMSM_STRICT,
                  &err);
    CAN_SendSingle(&canMsgObj0, 0x210, 0x0000, 0x0000);

    while (TRUE) {
        OSTimeDlyHMSM(0, 0, 1, 211,
                      OS_OPT_TIME_HMSM_STRICT,
                      &err);
//        IfxPort_togglePin(&MODULE_P14, 9);
//        CpuID = IfxCpu_getCoreId();
        CAN_SendSingle(&canMsgObj0, 0x211, (0x0000 | 0), 0x0000);
//        OSSemPost(&Sem1, OS_OPT_POST_1, &err);
    }
}



/*------------------------------------------------------------------------------------------------*/
/*!
* \brief                      TASK #2
*
*           This is an example of a task.
*
* \note     1) The first line of code is used to prevent a compiler warning because 'pdata' is not
*              used.  The compiler should not generate any code for this statement.
*
* \param    pdata             Is the argument passed to 'AppTask1()' by 'OSTaskCreate()'.
*/
/*------------------------------------------------------------------------------------------------*/
void AppTask4 ()
{
    OS_ERR       err;
    IfxCpu_Id   CpuID;
    OSTimeDlyHMSM(0, 0, 0, 220,
                  OS_OPT_TIME_HMSM_STRICT,
                  &err);
    CAN_SendSingle(&canMsgObj0, 0x220, 0x0000, 0x0000);

    while (TRUE) {
        OSTimeDlyHMSM(0, 0, 1, 221,
                      OS_OPT_TIME_HMSM_STRICT,
                      &err);
//        OSSemPend(&Sem1, 0, OS_OPT_PEND_BLOCKING, NULL_PTR, &err);
        CpuID = IfxCpu_getCoreId();
        CAN_SendSingle(&canMsgObj1, 0x221, (0x0000 | CpuID), 0x0000);
    }
}
static  void  Core1TaskCreate (void)
{
    OS_ERR       err;
    AppTask3Ext.CoreID = 1;
    AppTask4Ext.CoreID = 1;
    OSTaskCreate((OS_TCB     *)&AppTask3TCB,                /* Create the start task                                */
                 (CPU_CHAR   *)"App Task 3",
                 (OS_TASK_PTR ) AppTask3,
                 (void       *) 0,
                 (OS_PRIO     ) APP_TASK_3_PRIO,
                 (CPU_STK    *)&AppTask3Stk[0],
                 (CPU_STK_SIZE) APP_TASK_3_STK_SIZE / 10,
                 (CPU_STK_SIZE) APP_TASK_3_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *)&AppTask3Ext,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);

    OSTaskCreate((OS_TCB     *)&AppTask4TCB,                /* Create the start task                                */
                 (CPU_CHAR   *)"App Task 4",
                 (OS_TASK_PTR ) AppTask4,
                 (void       *) 0,
                 (OS_PRIO     ) APP_TASK_4_PRIO,
                 (CPU_STK    *)&AppTask4Stk[0],
                 (CPU_STK_SIZE) APP_TASK_4_STK_SIZE / 10,
                 (CPU_STK_SIZE) APP_TASK_4_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *)&AppTask4Ext,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);
}

