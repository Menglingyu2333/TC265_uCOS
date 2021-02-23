/*
*********************************************************************************************************
*                                                uC/OS-III
*                                          The Real-Time Kernel
*
*
*                           (c) Copyright 2009-2010; Micrium, Inc.; Weston, FL
*                    All rights reserved.  Protected by international copyright laws.
*
*                                           ARM Cortex-M3 Port
*
* File      : OS_CPU_C.C
* Version   : V3.01.2
* By        : JJL
*             BAN
*
* LICENSING TERMS:
* ---------------
*             uC/OS-III is provided in source form to registered licensees ONLY.  It is
*             illegal to distribute this source code to any third party unless you receive
*             written permission by an authorized Micrium representative.  Knowledge of
*             the source code may NOT be used to develop a similar product.
*
*             Please help us continue to provide the Embedded community with the finest
*             software available.  Your honesty is greatly appreciated.
*
*             You can contact us at www.micrium.com.
*
* For       : ARMv7M Cortex-M3
* Mode      : Thumb2
* Toolchain : RealView
*********************************************************************************************************
*/

#define   OS_CPU_GLOBALS

#ifdef VSC_INCLUDE_SOURCE_FILE_NAMES
const  CPU_CHAR  *os_cpu_c__c = "$Id: $";
#endif

/*$PAGE*/
/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include "includes.h"
#include "Bsp.h"
#include "IfxPort.h"
#include "IfxStm.h"
#include "IfxCpu_reg.h"
#include "SysSe/Bsp/Bsp.h"
#include "IfxCpu.h"

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief                      INITIAL TASK PSW
*
*           This define holds the initial PSW value for a new created task:
*           (PRS=0, IO privilege = Supervisor Mode, CDE=1,  CDC=0)
*/
/*------------------------------------------------------------------------------------------------*/
#define OS_INIT_TASK_PSW         0x00000880u

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief                      PCXI ADDRESS
*
*           This define holds the short address for PCXI register.
*/
/*------------------------------------------------------------------------------------------------*/
static OS_TCB                  OSTCBDummy;              /* dummy TCB for 1st task switch          */

typedef struct _OS_UCX          /* TC upper context structure */
{
  CPU_INT32U      _PCXI;            /* upper context PCXI         */
  CPU_INT32U      _PSW;             /* upper context PSW          */
  CPU_INT32U*     _A10;             /* upper context A10 (SP)     */
  CPU_INT32U*     _A11;             /* upper context A11 (RA)     */
  CPU_INT32U      _D8;              /* upper context D8           */
  CPU_INT32U      _D9;              /* upper context D9           */
  CPU_INT32U      _D10;             /* upper context D10          */
  CPU_INT32U      _D11;             /* upper context D11          */
  CPU_INT32U*     _A12;             /* upper context A12          */
  CPU_INT32U*     _A13;             /* upper context A13          */
  CPU_INT32U*     _A14;             /* upper context A14          */
  CPU_INT32U*     _A15;             /* upper context A15          */
  CPU_INT32U      _D12;             /* upper context D12          */
  CPU_INT32U      _D13;             /* upper context D13          */
  CPU_INT32U      _D14;             /* upper context D14          */
  CPU_INT32U      _D15;             /* upper context D15          */
} OS_UCX;

typedef struct _OS_LCX          /* TC lower context structure */
{
  CPU_INT32U      _PCXI;            /* lower context PCXI         */
  CPU_INT32U*     _PC;              /* lower context saved PC     */
  CPU_INT32U*     _A2;              /* lower context A2           */
  CPU_INT32U*     _A3;              /* lower context A3           */
  CPU_INT32U      _D0;              /* lower context D0           */
  CPU_INT32U      _D1;              /* lower context D1           */
  CPU_INT32U      _D2;              /* lower context D2           */
  CPU_INT32U      _D3;              /* lower context D3           */
  CPU_INT32U*     _A4;              /* lower context A4           */
  CPU_INT32U*     _A5;              /* lower context A5           */
  CPU_INT32U*     _A6;              /* lower context A6           */
  CPU_INT32U*     _A7;              /* lower context A7           */
  CPU_INT32U      _D4;              /* lower context D4           */
  CPU_INT32U      _D5;              /* lower context D5           */
  CPU_INT32U      _D6;              /* lower context D6           */
  CPU_INT32U      _D7;              /* lower context D7           */
} OS_LCX;

/*
****************************************************************************************************
*                                 MODULE INTERNAL PROTOTYPES
****************************************************************************************************
*/

static inline void    OSResumeExecution (void);


/*
****************************************************************************************************
*                                 MODULE INTERNAL FUNCTIONS
****************************************************************************************************
*/

/*------------------------------------------------------------------------------------------------*/
/*! \brief    convert TriCore context pointer (PCXI, FXC, LCX) into physical address
*
*   \param    ctx     TriCore context pointer
*
*   \return   Pointer to physical CTX address
*/
/*------------------------------------------------------------------------------------------------*/
//static inline void* OSCTXToAddr (CPU_INT32U ctx)
//{
//    void *ptrctx;                                     /* context address                          */
//
//    __asm(" extr.u d15, %1, #16, #4                   ; calc. physical address from para. ctx   \n"\
//          " sh     d15, d15, #28                                                                \n"\
//          " insert %1, d15, %1, #6, #16                                                         \n"\
//          " mov.a  %0, %1                             ; ptrctx = address                        \n"
//          : "=a" (ptrctx) : "d" (ctx) : "d15");
//
//    return ptrctx;                                    /* return CTX physical address              */
//}
#define GET_PHYS_ADDRESS(effectiveAddr)   ((uint32)((uint32)(effectiveAddr & 0xF0000u) << 12u) | \
                                           (uint32)((uint32)(effectiveAddr & 0xFFFFu) << 6u))

#define GET_EFFECTIVE_ADDRESS(physAddr)   ((uint32)((uint32)(physAddr & 0xF0000000u) >> 12u) | \
                                           (uint32)((uint32)(physAddr & 0x003FFFC0u) >> 6u))

#define PCXI_PCX_OFFSET       (0u)
#define PCXI_PCX_MASK         (0xFFFFFu << PCXI_PCX_OFFSET)

#define PCXI_UL_OFFSET        (20u)
#define PCXI_UL_MASK          (1u << PCXI_UL_OFFSET)
#define PCXI_UL_UPPER_CTX     (PCXI_UL_MASK)
#define PCXI_UL_LOWER_CTX     (0u)

#define PCXI_PIE_OFFSET       (21u)
#define PCXI_PIE_MASK         (1u << PCXI_PIE_OFFSET)
#define PCXI_PIE_ENABLED      (PCXI_PIE_MASK)
#define PCXI_PIE_DISABLED     (0u)

#define PCXI_PCPN_OFFSET      (22u)
#define PCXI_PCPN_MASK        (0xFFu << PCXI_PCPN_OFFSET)

/** \brief Create PCXI value for and upper task context */
#define GET_UPPER_CTX_LINK(link)  (((uint32)(link & PCXI_PCX_MASK)) | PCXI_UL_UPPER_CTX | PCXI_PIE_ENABLED)

/** \brief Create PCXI value for and lower task context */
#define GET_LOWER_CTX_LINK(link)  (((uint32)(link & PCXI_PCX_MASK)) | PCXI_UL_LOWER_CTX | PCXI_PIE_ENABLED)


/*
*********************************************************************************************************
*                                           IDLE TASK HOOK
*
* Description: This function is called by the idle task.  This hook has been added to allow you to do
*              such things as STOP the CPU to conserve power.
*
* Arguments  : None.
*
* Note(s)    : None.
*********************************************************************************************************
*/

void  OSIdleTaskHook (void)
{
#if OS_CFG_APP_HOOKS_EN > 0u
    if (OS_AppIdleTaskHookPtr != (OS_APP_HOOK_VOID)0) {
        (*OS_AppIdleTaskHookPtr)();
    }
#endif
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                       OS INITIALIZATION HOOK
*
* Description: This function is called by OSInit() at the beginning of OSInit().
*
* Arguments  : None.
*
* Note(s)    : None.
*********************************************************************************************************
*/

void  OSInitHook (void)
{
    CPU_STK_SIZE   i;
    CPU_STK       *p_stk;


    p_stk = OSCfg_ISRStkBasePtr;                            /* Clear the ISR stack                                    */
    for (i = 0u; i < OSCfg_ISRStkSize; i++) {
        *p_stk++ = (CPU_STK)0u;
    }
    OS_CPU_ExceptStkBase = (CPU_STK *)(OSCfg_ISRStkBasePtr + OSCfg_ISRStkSize - 1u);
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                         STATISTIC TASK HOOK
*
* Description: This function is called every second by uC/OS-III's statistics task.  This allows your
*              application to add functionality to the statistics task.
*
* Arguments  : None.
*
* Note(s)    : None.
*********************************************************************************************************
*/

void  OSStatTaskHook (void)
{
#if OS_CFG_APP_HOOKS_EN > 0u
    if (OS_AppStatTaskHookPtr != (OS_APP_HOOK_VOID)0) {
        (*OS_AppStatTaskHookPtr)();
    }
#endif
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                          TASK CREATION HOOK
*
* Description: This function is called when a task is created.
*
* Arguments  : p_tcb        Pointer to the task control block of the task being created.
*
* Note(s)    : None.
*********************************************************************************************************
*/

void  OSTaskCreateHook (OS_TCB  *p_tcb)
{
#if OS_CFG_APP_HOOKS_EN > 0u

    if (OS_AppTaskCreateHookPtr != (OS_APP_HOOK_TCB)0) {
        (*OS_AppTaskCreateHookPtr)(p_tcb);
    }

#else
    (void)p_tcb;                                      /* Prevent compiler warning                               */
#endif
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                           TASK DELETION HOOK
*
* Description: This function is called when a task is deleted.
*
* Arguments  : p_tcb        Pointer to the task control block of the task being deleted.
*
* Note(s)    : None.
*********************************************************************************************************
*/

void  OSTaskDelHook (OS_TCB  *p_tcb)
{
#if OS_CFG_APP_HOOKS_EN > 0u
    if (OS_AppTaskDelHookPtr != (OS_APP_HOOK_TCB)0) {
        (*OS_AppTaskDelHookPtr)(p_tcb);
    }

#else
    (void)p_tcb;                                            /* Prevent compiler warning                               */
#endif
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                            TASK RETURN HOOK
*
* Description: This function is called if a task accidentally returns.  In other words, a task should
*              either be an infinite loop or delete itself when done.
*
* Arguments  : p_tcb        Pointer to the task control block of the task that is returning.
*
* Note(s)    : None.
*********************************************************************************************************
*/

void  OSTaskReturnHook (OS_TCB  *p_tcb)
{
#if OS_CFG_APP_HOOKS_EN > 0u
    if (OS_AppTaskReturnHookPtr != (OS_APP_HOOK_TCB)0) {
        (*OS_AppTaskReturnHookPtr)(p_tcb);
    }
#else
    (void)p_tcb;                                            /* Prevent compiler warning                               */
#endif
}

/*$PAGE*/
/*
**********************************************************************************************************
*                                       INITIALIZE A TASK'S STACK
*
* Description: This function is called by OS_Task_Create() or OSTaskCreateExt() to initialize the stack
*              frame of the task being created. This function is highly processor specific.
*
* Arguments  : p_task       Pointer to the task entry point address.
*
*              p_arg        Pointer to a user supplied data area that will be passed to the task
*                               when the task first executes.
*
*              p_stk_base   Pointer to the base address of the stack.
*
*              stk_size     Size of the stack, in number of CPU_STK elements.
*
*              opt          Options used to alter the behavior of OS_Task_StkInit().
*                            (see OS.H for OS_TASK_OPT_xxx).
*
* Returns    : Always returns the location of the new top-of-stack' once the processor registers have
*              been placed on the stack in the proper order.
*
* Note(s)    : 1) Interrupts are enabled when task starts executing.
*
*              2) All tasks run in Thread mode, using process stack.
**********************************************************************************************************
*/

CPU_STK  *OSTaskStkInit (OS_TASK_PTR    p_task,
                         void          *p_arg,
                         CPU_STK       *p_stk_base,
                         CPU_STK       *p_stk_limit,
                         CPU_STK_SIZE   stk_size,
                         OS_OPT         opt)
{
    CPU_STK  *p_stk;
    OS_UCX* UpperCtx;
    CPU_INT32U UpperCtxLink;
    OS_LCX* LowerCtx;
    CPU_INT32U LowerCtxLink;

    CPU_INT32U tmpFCX;
    CPU_INT32U tmpLCX;
    CPU_SR_ALLOC();

    OS_CRITICAL_ENTER();

    tmpFCX = __mfcr(CPU_FCX);
    tmpLCX = __mfcr(CPU_LCX);

    //Init CSA
    IfxCpu_initCSA(&p_stk_base[stk_size - (TASK_CSA_NUM_DEFAULT * 16)], &p_stk_base[stk_size]);

    p_stk = &p_stk_base[stk_size - (TASK_CSA_NUM_DEFAULT * 16)];                          /* Load stack pointer                                     */

    /* Unlink next two context's */
    UpperCtxLink = __mfcr(CPU_FCX);
    UpperCtx = (OS_UCX*)GET_PHYS_ADDRESS(UpperCtxLink);

    LowerCtxLink = UpperCtx->_PCXI;
    LowerCtx = (OS_LCX*)GET_PHYS_ADDRESS(LowerCtxLink);

    __mtcr(CPU_FCX, LowerCtx->_PCXI);

    /* Update context links */
    UpperCtx->_PCXI = FALSE;  /* Last context of the task => report error if returns */
    UpperCtx->_A10 = (CPU_INT32U*)p_stk;;
    UpperCtx->_A11 = (CPU_STK)OS_TaskReturn;
    UpperCtx->_PSW = OS_INIT_TASK_PSW;

    LowerCtx->_PCXI = GET_UPPER_CTX_LINK(UpperCtxLink);
    LowerCtx->_PC   = (CPU_INT32U*)p_task;
    LowerCtx->_A4   = (CPU_INT32U*)p_arg;

    *--p_stk = __mfcr(CPU_LCX);
    *--p_stk = __mfcr(CPU_FCX);
    *--p_stk = GET_LOWER_CTX_LINK(LowerCtxLink);

    __mtcr(CPU_FCX, tmpFCX);
    __mtcr(CPU_LCX, tmpLCX);

    OS_CRITICAL_EXIT();

    return (p_stk);
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                           TASK SWITCH HOOK
*
* Description: This function is called when a task switch is performed.  This allows you to perform other
*              operations during a context switch.
*
* Arguments  : None.
*
* Note(s)    : 1) Interrupts are disabled during this call.
*              2) It is assumed that the global pointer 'OSTCBHighRdyPtr' points to the TCB of the task
*                 that will be 'switched in' (i.e. the highest priority task) and, 'OSTCBCurPtr' points
*                 to the task being switched out (i.e. the preempted task).
*********************************************************************************************************
*/

void  OSTaskSwHook (void)
{
#if OS_CFG_TASK_PROFILE_EN > 0u
    CPU_TS  ts;
#endif
#ifdef  CPU_CFG_INT_DIS_MEAS_EN
    CPU_TS  int_dis_time;
#endif
    IfxCpu_Id CpuID = IfxCpu_getCoreId();



#if OS_CFG_APP_HOOKS_EN > 0u
    if (OS_AppTaskSwHookPtr != (OS_APP_HOOK_VOID)0) {
        (*OS_AppTaskSwHookPtr)();
    }
#endif

#if OS_CFG_TASK_PROFILE_EN > 0u
    ts = OS_TS_GET();
    if (OSTCBCurPtr[CpuID] != OSTCBHighRdyPtr[CpuID]) {
        OSTCBCurPtr[CpuID]->CyclesDelta  = ts - OSTCBCurPtr[CpuID]->CyclesStart;
        OSTCBCurPtr[CpuID]->CyclesTotal += (OS_CYCLES)OSTCBCurPtr[CpuID]->CyclesDelta;
    }

    OSTCBHighRdyPtr[CpuID]->CyclesStart = ts;
#endif

#ifdef  CPU_CFG_INT_DIS_MEAS_EN
    int_dis_time = CPU_IntDisMeasMaxCurReset();             /* Keep track of per-task interrupt disable time          */
    if (OSTCBCurPtr[CpuID]->IntDisTimeMax < int_dis_time) {
        OSTCBCurPtr[CpuID]->IntDisTimeMax = int_dis_time;
    }
#endif

#if OS_CFG_SCHED_LOCK_TIME_MEAS_EN > 0u
                                                            /* Keep track of per-task scheduler lock time             */
    if (OSTCBCurPtr[CpuID]->SchedLockTimeMax < OSSchedLockTimeMaxCur) {
        OSTCBCurPtr[CpuID]->SchedLockTimeMax = OSSchedLockTimeMaxCur;
    }
    OSSchedLockTimeMaxCur = (CPU_TS)0;                      /* Reset the per-task value                               */
#endif
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                              TICK HOOK
*
* Description: This function is called every tick.
*
* Arguments  : None.
*
* Note(s)    : 1) This function is assumed to be called from the Tick ISR.
*********************************************************************************************************
*/

void  OSTimeTickHook (void)
{
#if OS_CFG_APP_HOOKS_EN > 0u
    if (OS_AppTimeTickHookPtr != (OS_APP_HOOK_VOID)0) {
        (*OS_AppTimeTickHookPtr)();
    }
#endif
}

/*------------------------------------------------------------------------------------------------*/
/*! \brief    resume execution of task
*
*   \note     the PCXI value of the previous context holds the new task PCXI context pointer
*/
/*------------------------------------------------------------------------------------------------*/
static inline void OSResumeExecution(void)
{
    __asm ("   movh.a  a11,#@his(d)                   ; setup return address (label d:)         \n"\
           "   lea     a11,[a11]@los(d)               ; in A11                                  \n"\
           "   ret                                    ; restore context from call to OSCtxSw    \n"\
           "d: rslcx                                  ; restore lower task context              \n"\
           "   nop                                    ; bugfix: TC.069                          \n"\
           "   rfe                                    ; restore upper context and run task      \n"\
           : /* no outputs */ : /* no inputs */ : "a11");
}
/*------------------------------------------------------------------------------------------------*/
/*! \brief             START OS AND ACTIVATE FIRST TASK
*
*          This function also installs the timer ISR and dispatcher trap \n
*/
/*------------------------------------------------------------------------------------------------*/
void OSStartHighRdy(void)
{
    CPU_INT08U i;
    for(i = 1; i < CPU_CORE_NUM; i++){
        OSTCBCurPtr[i] = &OSTCBDummy;                          /* dummy TCB for 1st context switch         */
        OS_TASK_SW(i);                                     /* request a task switch to highest prio    */
    }
    OSTCBCurPtr[0] = &OSTCBDummy;                          /* dummy TCB for 1st context switch         */
    OS_TASK_SW(0);                                     /* request a task switch to highest prio    */
}
#ifdef  SMP_EN
/*------------------------------------------------------------------------------------------------*/
/*! \brief             TASK CONTEXT SWITCH
*
*          In this uCOS implementation the dispatcher is invoked by a software trap or via
*          OSIntCtxSw from interrupt it can be requested with the macro OS_TASK_SW()
*
* \note    the interrupt / trap vector code has to save the upper and (!) lower context of the
*          interrupted task, then this function is invoked by a call (no jump or jump and link
*          instructions!)
*/
/*------------------------------------------------------------------------------------------------*/
void   __jump__   OSCtxSw(CPU_INT08U CpuID)
{
                                                      /*------------------------------------------*/
    __dsync();                                        /* synchronize all data accesses            */
//    IfxCpu_Id CpuID = IfxCpu_getCoreId();

    /* get pointer to previous context (= current task context)                                   */
    /* because OSCtxSw is reached via a call command from ISR vector / trap handler               */
    /* current PCXI register points to one additional upper context where we can find the         */
    /* current task context pointer:                                                              */
    OS_UCX* ptUpperCTX = (OS_UCX*)GET_PHYS_ADDRESS((__mfcr(CPU_PCXI)));

    if(OSTCBCurPtr[CpuID]->TaskState == (OS_STATE)OS_TASK_STATE_DEL){
        CPU_INT32U prevLink = __mfcr(CPU_FCX);
        CPU_INT32U currLink = __mfcr(CPU_PCXI);
        while (ptUpperCTX->_PCXI != 0u)
        {
          CPU_INT32U tmpLink = ptUpperCTX->_PCXI;
          ptUpperCTX->_PCXI = prevLink;
          prevLink = currLink;
          currLink = tmpLink;
          ptUpperCTX = (OS_UCX*)GET_PHYS_ADDRESS(currLink);
        }
        ptUpperCTX->_PCXI = prevLink;
        __mtcr(CPU_FCX, currLink);
    }
    else{
        OS_UCX* ptCurTaskUCX = (OS_UCX*)GET_PHYS_ADDRESS(ptUpperCTX->_PCXI);
        CPU_STK *CurTaskStk = (CPU_STK)ptCurTaskUCX->_A10;
        *--CurTaskStk = __mfcr(CPU_LCX);
        *--CurTaskStk = __mfcr(CPU_FCX);
        *--CurTaskStk = __mfcr(CPU_PCXI);
        OSTCBCurPtr[CpuID]->StkPtr = CurTaskStk;
//        *((typeTaskPCXI*)(OSTCBCurPtr[CpuID]->StkPtr)) = ptUpperCTX->_PCXI;
    }

    OSTaskSwHook();                                   /* call user funktion for any task switch   */

    OSTCBCurPtr[CpuID] = OSTCBHighRdyPtr[CpuID];      /* new highest prio task is current task    */
    OSPrioCur[CpuID] = OSPrioHighRdy[CpuID];          /* new highest prio is now current prio     */

    __mtcr(CPU_PCXI, *(typeTaskPCXI*)(OSTCBCurPtr[CpuID]->StkPtr++));
    __mtcr(CPU_FCX, *(typeTaskPCXI*)(OSTCBCurPtr[CpuID]->StkPtr++));
    __mtcr(CPU_LCX, *(typeTaskPCXI*)(OSTCBCurPtr[CpuID]->StkPtr++));
                                                      /* restore new task context pointer         */
//    OSResumeExecution();                              /* resume execution of highest prio. task   */
    __isync();                                        /* synchronize all data accesses            */

    __asm("rslcx");
    __asm("nop");
    __asm("rfe");

}
#else
/*------------------------------------------------------------------------------------------------*/
/*! \brief             TASK CONTEXT SWITCH
*
*          In this uCOS implementation the dispatcher is invoked by a software trap or via
*          OSIntCtxSw from interrupt it can be requested with the macro OS_TASK_SW()
*
* \note    the interrupt / trap vector code has to save the upper and (!) lower context of the
*          interrupted task, then this function is invoked by a call (no jump or jump and link
*          instructions!)
*/
/*------------------------------------------------------------------------------------------------*/
void OSCtxSw(void)
{
                                                      /*------------------------------------------*/
    __dsync();                                        /* synchronize all data accesses            */

    /* get pointer to previous context (= current task context)                                   */
    /* because OSCtxSw is reached via a call command from ISR vector / trap handler               */
    /* current PCXI register points to one additional upper context where we can find the         */
    /* current task context pointer:                                                              */
    OS_UCX* ptUpperCTX = (OS_UCX*)GET_PHYS_ADDRESS((__mfcr(CPU_PCXI)));

    if(OSTCBCurPtr->TaskState == (OS_STATE)OS_TASK_STATE_DEL){
        CPU_INT32U prevLink = __mfcr(CPU_FCX);
        CPU_INT32U currLink = __mfcr(CPU_PCXI);
        while (ptUpperCTX->_PCXI != 0u)
        {
          CPU_INT32U tmpLink = ptUpperCTX->_PCXI;
          ptUpperCTX->_PCXI = prevLink;
          prevLink = currLink;
          currLink = tmpLink;
          ptUpperCTX = (OS_UCX*)GET_PHYS_ADDRESS(currLink);
        }
    }
    else{
        OS_LCX* ptCurTaskLCX = (OS_LCX*)GET_PHYS_ADDRESS(ptUpperCTX->_PCXI);
        OS_UCX* ptCurTaskUCX = (OS_UCX*)GET_PHYS_ADDRESS(ptCurTaskLCX->_PCXI);
        CPU_STK CurTaskStk = (CPU_STK)ptCurTaskUCX->_A10;
        CurTaskStk -= 4;
        OSTCBCurPtr->StkPtr = CurTaskStk;
        *((typeTaskPCXI*)(OSTCBCurPtr->StkPtr)) = ptUpperCTX->_PCXI;
    }

    OSTaskSwHook();                                   /* call user funktion for any task switch   */

    OSTCBCurPtr = OSTCBHighRdyPtr;                    /* new highest prio task is current task    */
    OSPrioCur = OSPrioHighRdy;                        /* new highest prio is now current prio     */

    ptUpperCTX->_PCXI = *((typeTaskPCXI*)(OSTCBCurPtr->StkPtr));
                                                      /* restore new task context pointer         */
    OSResumeExecution();                              /* resume execution of highest prio. task   */

}
#endif
/*------------------------------------------------------------------------------------------------*/
/*! \brief             TASK SWITCH FROM INTERRUPT
*
*          This function restores the context from the previous calls and jumps to OSCtxSw().
*          OSCtxSw() is invoked by a jump because there is still one upper context left on
*          the previous context list from the call to the interrupt handler
*
* \note    This function is used only inside OSIntExit().
*          OSIntExit() is located at the very end of interrupt handlers.
*
* \note    Interrupt vector code has to save the upper and (!) lower context of the interrupted
*          task and invoke the interrupt handler via a call command.
*/
/*------------------------------------------------------------------------------------------------*/
void OSIntCtxSw(CPU_INT08U CpuID)
{
    __asm ("    movh.a  a11,#@his(j1)                  ; setup return address (label j1:)        \n"\
           "    lea     a11,[a11]@los(j1)              ; in A11                                  \n"\
           "    ret                                    ; remove context from call to OSIntCtxSw  \n"\
           "j1: movh.a  a11,#@his(j2)                  ; setup return address (label j2:)        \n"\
           "    lea     a11,[a11]@los(j2)              ; in A11                                  \n"\
           "    ret                                    ; remove context from call to OSIntExit   \n"\
           "j2: MOV     D4,%0                          ; Store CpuID to D4                       \n"\
           "    j       OSCtxSw                        ; jump to OSCtxSw()                       \n"\
           : /* no outputs */ : "d" (CpuID) : "a11");
}


