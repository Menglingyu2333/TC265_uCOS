/**********************************************************************************************************************
 * \file Cpu0_Main.c
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
#include <includes.h>

#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "Port/Io/IfxPort_Io.h"
#include "Bsp.h"
#include "Multican/Can/IfxMultican_Can.h"

IfxCpu_syncEvent g_cpuSyncEvent = 0;

// CAN handle
IfxMultican_Can can;
// Nodes handles
IfxMultican_Can_Node canNode1;
IfxMultican_Can_Node canNode2;
IfxMultican_Can_Node canNode3;
IfxMultican_Can_Node canNode0;

// Message Object handles
IfxMultican_Can_MsgObj canMsgObj0;
IfxMultican_Can_MsgObj canMsgObj1;
IfxMultican_Can_MsgObj canMsgObj2;
IfxMultican_Can_MsgObj canMsgObj3;
static void CanApp_init(void)
{
    // Init STD
    IfxPort_setPinMode(&MODULE_P11, 11, IfxPort_Mode_outputPushPullGeneral);
    IfxPort_setPinMode(&MODULE_P02,  8, IfxPort_Mode_outputPushPullGeneral);
    IfxPort_setPinMode(&MODULE_P00,  7, IfxPort_Mode_outputPushPullGeneral);
    IfxPort_setPinMode(&MODULE_P02,  4, IfxPort_Mode_outputPushPullGeneral);

    // create configuration
    IfxMultican_Can_Config canConfig;
    IfxMultican_Can_initModuleConfig(&canConfig, &MODULE_CAN);
    // initialize interrupt priority
//    canConfig.nodePointer[TX_INTERRUPT_SRC_ID].priority = ISR_PRIORITY_CAN_TX;
    // initialize module
    IfxMultican_Can_initModule(&can, &canConfig);

    // create CAN node config
    IfxMultican_Can_NodeConfig canNodeConfig;
    IfxMultican_Can_Node_initConfig(&canNodeConfig, &can);
    canNodeConfig.baudrate = 500000; // 1 MBaud
    canNodeConfig.nodeId = IfxMultican_NodeId_0;
    canNodeConfig.rxPin = &IfxMultican_RXD0A_P02_1_IN;
    canNodeConfig.txPin = &IfxMultican_TXD0_P02_0_OUT;
    IfxMultican_Can_Node_init(&canNode0, &canNodeConfig);
    //CAN node1 configuration
    canNodeConfig.nodeId = IfxMultican_NodeId_1;
    canNodeConfig.rxPin = &IfxMultican_RXD1D_P00_1_IN;
    canNodeConfig.txPin = &IfxMultican_TXD1_P00_0_OUT;
    IfxMultican_Can_Node_init(&canNode1, &canNodeConfig);
    //CAN node2 configuration
    canNodeConfig.nodeId = IfxMultican_NodeId_2;
    canNodeConfig.rxPin = &IfxMultican_RXD2B_P02_3_IN;
    canNodeConfig.txPin = &IfxMultican_TXD2_P02_2_OUT;
    IfxMultican_Can_Node_init(&canNode2, &canNodeConfig);
    //CAN node3 configuration
    canNodeConfig.nodeId = IfxMultican_NodeId_3;
    canNodeConfig.rxPin = &IfxMultican_RXD3A_P00_3_IN;
    canNodeConfig.txPin = &IfxMultican_TXD3_P00_2_OUT;
    IfxMultican_Can_Node_init(&canNode3, &canNodeConfig);

    // create message object config
    IfxMultican_Can_MsgObjConfig canMsgObjConfig;
    IfxMultican_Can_MsgObj_initConfig(&canMsgObjConfig, &canNode0);
    // assigned message object:
    canMsgObjConfig.msgObjId = 0;
    canMsgObjConfig.frame = IfxMultican_Frame_transmit;
    canMsgObjConfig.control.messageLen = IfxMultican_DataLengthCode_8;
    IfxMultican_Can_MsgObj_init(&canMsgObj0, &canMsgObjConfig);

    IfxMultican_Can_MsgObj_initConfig(&canMsgObjConfig, &canNode1);
    canMsgObjConfig.msgObjId = 1;
    canMsgObjConfig.frame = IfxMultican_Frame_transmit;
    canMsgObjConfig.control.messageLen = IfxMultican_DataLengthCode_8;
    IfxMultican_Can_MsgObj_init(&canMsgObj1, &canMsgObjConfig);

    IfxMultican_Can_MsgObj_initConfig(&canMsgObjConfig, &canNode2);
    canMsgObjConfig.msgObjId = 2;
    canMsgObjConfig.frame = IfxMultican_Frame_transmit;
    canMsgObjConfig.control.messageLen = IfxMultican_DataLengthCode_8;
    IfxMultican_Can_MsgObj_init(&canMsgObj2, &canMsgObjConfig);

    IfxMultican_Can_MsgObj_initConfig(&canMsgObjConfig, &canNode3);
    canMsgObjConfig.msgObjId = 3;
    canMsgObjConfig.frame = IfxMultican_Frame_transmit;
    canMsgObjConfig.control.messageLen = IfxMultican_DataLengthCode_8;
    IfxMultican_Can_MsgObj_init(&canMsgObj3, &canMsgObjConfig);

}

void CAN_SendSingle(IfxMultican_Can_MsgObj *MO, uint32 id, uint32 high, uint32 low)
{
    // Initialise the message strcture
    IfxMultican_Message txMsg;
    IfxMultican_Message_init(&txMsg, id, high, low, IfxMultican_DataLengthCode_8);
    IfxMultican_Can_MsgObj_sendMessage(MO, &txMsg);
}


//OS
static  OS_TCB          AppTaskStartTCB;
static  CPU_STK         AppTaskStartStk[APP_TASK_START_STK_SIZE];
static  OS_TCB          AppTask1TCB;
static  CPU_STK         AppTask1Stk[APP_TASK_1_STK_SIZE];
static  OS_TCB          AppTask2TCB;
static  CPU_STK         AppTask2Stk[APP_TASK_2_STK_SIZE];



static  void    AppTaskCreate (void);
static  void    AppObjCreate  (void);
static  void    AppTaskStart  (void *p_arg);
static  void    BSP_Init(void);
void    PeriodicTimerTask(OS_TMR *p_tmr, void *p_arg);
OS_TMR  TaskTimer1;
OS_SEM  Sem1;

CPU_INT32U SyncFlag = 0;

int core0_main(void)
{
    OS_ERR  err;
    IfxCpu_enableInterrupts();

    /* !!WATCHDOG0 AND SAFETY WATCHDOG ARE DISABLED HERE!!
     * Enable the watchdogs and service them periodically if it is required
     */
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());

    BSP_Init();

    /* Wait for CPU sync event */
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 1);
    SyncFlag = 1;
//    while(SyncFlag == 1);
//    IfxCpu_disableInterrupts();     //BSP_IntDisAll();          /* Disable all interrupts.                              */
    OSTaskSwIntInit();

    OS_CPU_SysTickInit((CPU_INT32U)(TimeConst_1s)/OSCfg_TickRate_Hz);                                   /* Init uC/OS periodic time src (SysTick).              */

    OSInit(&err);                                               /* Init uC/OS-III.                                      */

    OSTaskCreate((OS_TCB     *)&AppTaskStartTCB,                /* Create the start task                                */
                 (CPU_CHAR   *)"App Task Start",
                 (OS_TASK_PTR ) AppTaskStart,
                 (void       *) 0,
                 (OS_PRIO     ) APP_TASK_START_PRIO,
                 (CPU_STK    *)&AppTaskStartStk[0],
                 (CPU_STK_SIZE) APP_TASK_START_STK_SIZE / 10,
                 (CPU_STK_SIZE) APP_TASK_START_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);
    OSStart(&err);                                              /* Start multitasking (i.e. give control to uC/OS-III). */
    while(1);
    return (1);
}
static  void    BSP_Init()
{
    initTime();
    CanApp_init();
    IfxPort_setPinMode(&MODULE_P14, 9, IfxPort_Mode_outputPushPullGeneral);


    CAN_SendSingle(&canMsgObj0, 0x001, 0x0000, 0x0000);
}


/*
*********************************************************************************************************
*                                          STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Arguments   : p_arg   is the argument passed to 'AppTaskStart()' by 'OSTaskCreate()'.
*
* Returns     : none
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/

static  void  AppTaskStart (void *p_arg)
{
    OS_ERR      err;

   (void)p_arg;

    CPU_Init();

    Mem_Init();                                                 /* Initialize Memory Management Module                  */

#if OS_CFG_STAT_TASK_EN > 0u
    OSStatTaskCPUUsageInit(&err);                               /* Compute CPU capacity with no task running            */
#endif

    CPU_IntDisMeasMaxCurReset();

#if (APP_CFG_SERIAL_EN == DEF_ENABLED)
    BSP_Ser_Init(115200);                                       /* Enable Serial Interface                              */
#endif

//    APP_TRACE_INFO(("Creating Application Tasks...\n\r"));
    AppTaskCreate();                                            /* Create Application Tasks                             */

//    APP_TRACE_INFO(("Creating Application Events...\n\r"));
    AppObjCreate();                                             /* Create Application Objects                           */

//    BSP_LED_Off(0);

    while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop.       */
        OSTimeDlyHMSM(0, 0, 1, 0,
                      OS_OPT_TIME_HMSM_STRICT,
                      &err);
        CAN_SendSingle(&canMsgObj0, 0x002, 0x0000, 0x0000);
    }
}

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
void AppTask1 ()
{
    OS_ERR       err;
    IfxCpu_Id   CpuID;


    OSTimeDlyHMSM(0, 0, 0, 100,
                  OS_OPT_TIME_HMSM_STRICT,
                  &err);
    CAN_SendSingle(&canMsgObj0, 0x101, 0x0000, 0x0000);

    while (TRUE) {
        OSTimeDlyHMSM(0, 0, 0, 100,
                      OS_OPT_TIME_HMSM_STRICT,
                      &err);
        IfxPort_togglePin(&MODULE_P14, 9);
        CpuID = IfxCpu_getCoreId();
        CAN_SendSingle(&canMsgObj0, 0x102, (0x0000 | CpuID), 0x0000);
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
void AppTask2 ()
{
    OS_ERR       err;
    IfxCpu_Id   CpuID;
    OSTimeDlyHMSM(0, 0, 0, 230,
                  OS_OPT_TIME_HMSM_STRICT,
                  &err);
    CAN_SendSingle(&canMsgObj0, 0x201, 0x0000, 0x0000);

    while (TRUE) {
        OSTimeDlyHMSM(0, 0, 0, 203,
                      OS_OPT_TIME_HMSM_STRICT,
                      &err);
//        OSSemPend(&Sem1, 0, OS_OPT_PEND_BLOCKING, NULL_PTR, &err);
        CpuID = IfxCpu_getCoreId();
        CAN_SendSingle(&canMsgObj1, 0x202, (0x0000 | CpuID), 0x0000);
    }
}

void PeriodicTimerTask(OS_TMR *p_tmr, void *p_arg)
{
    IfxCpu_Id   CpuID;
    CpuID = IfxCpu_getCoreId();
    CAN_SendSingle(&canMsgObj1, 0x301, (0x0000 | CpuID), 0x0000);
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

static  void  AppTaskCreate (void)
{
    OS_ERR       err;
    OSTaskCreate((OS_TCB     *)&AppTask1TCB,                /* Create the start task                                */
                 (CPU_CHAR   *)"App Task 1",
                 (OS_TASK_PTR ) AppTask1,
                 (void       *) 0,
                 (OS_PRIO     ) APP_TASK_1_PRIO,
                 (CPU_STK    *)&AppTask1Stk[0],
                 (CPU_STK_SIZE) APP_TASK_1_STK_SIZE / 10,
                 (CPU_STK_SIZE) APP_TASK_1_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);

    OSTaskCreate((OS_TCB     *)&AppTask2TCB,                /* Create the start task                                */
                 (CPU_CHAR   *)"App Task 2",
                 (OS_TASK_PTR ) AppTask2,
                 (void       *) 0,
                 (OS_PRIO     ) APP_TASK_2_PRIO,
                 (CPU_STK    *)&AppTask2Stk[0],
                 (CPU_STK_SIZE) APP_TASK_2_STK_SIZE / 10,
                 (CPU_STK_SIZE) APP_TASK_2_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);
}



/*
*********************************************************************************************************
*                                      CREATE APPLICATION EVENTS
*
* Description:  This function creates the application kernel objects.
*
* Arguments  :  none
*
* Returns    :  none
*********************************************************************************************************
*/

static  void  AppObjCreate (void)
{
    OS_ERR err;
    OSTmrCreate(&TaskTimer1, &"Timer 1", 0, 7, OS_OPT_TMR_PERIODIC, PeriodicTimerTask, (void *)0, &err);
    OSTmrStart(&TaskTimer1, &err);

    OSSemCreate(&Sem1, &"Sem1", 1, &err);
}
