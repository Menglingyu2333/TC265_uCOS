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

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief                      INITIAL TASK PSW
*
*           This define holds the initial PSW value for a new created task:
*           (PRS=0, IO privilege = USER1, CDE=0,  CDC=0)
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
#define SYS_TASKS_MAX_NUM   5
static volatile OS_TCB_CTX_EXT SysTaskExt[SYS_TASKS_MAX_NUM];  /* TCB Extensions for all tasks           */
static OS_TCB                  OSTCBDummy;              /* dummy TCB for 1st task switch          */
static volatile OS_TCB_CTX_EXT OSTCBDummyExt;           /* dummy TCB extension                    */

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

//static inline void*   OSCTXToAddr       (CPU_INT32U ctx);
static inline OS_UCX* OSCreateUCX       (void);
static inline OS_LCX* OSCreateLCX       (void);
static inline CPU_INT32U  OSRemoveContext   (CPU_INT32U removePCXI);
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

    /*if (OS_AppTaskCreateHookPtr != (OS_APP_HOOK_TCB)0) {
        (*OS_AppTaskCreateHookPtr)(p_tcb);
    }*/

    volatile OS_TCB_CTX_EXT *ext;                           /* Pointer to TCB extension                   */
    if(p_tcb->ExtPtr == (void *)0){
        ext = SysTaskExt;                                   /* search for free TCB extension              */
        while ((ext < &SysTaskExt[SYS_TASKS_MAX_NUM]) &&    /* Loop through TCB extension list            */
               ((ext->TaskPCXI) != 0)) {                    /* PCXI = 0 indicates unused extension        */
            ext++;                                          /* switch to next TCB extension               */
        }                                                   /*--------------------------------------------*/
        if (ext < &SysTaskExt[SYS_TASKS_MAX_NUM]) {         /* see, if valid TCB extension is found:      */
            ext->TaskPCXI = *(p_tcb->StkPtr);               /* PCXI -> Link to Task Lower Context         */
            p_tcb->ExtPtr = (void *)ext;                    /* Link extension to TCB                      */
        }
    }
    else{
        ext = p_tcb->ExtPtr;
        ext->TaskPCXI = *(p_tcb->StkPtr);                   /* Link extension to TCB                      */
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
    /*if (OS_AppTaskDelHookPtr != (OS_APP_HOOK_TCB)0) {
        (*OS_AppTaskDelHookPtr)(p_tcb);
    }*/
    volatile OS_TCB_CTX_EXT *ext;                     /* Pointer to TCB extension                   */
                                                      /*--------------------------------------------*/
    ext=(volatile OS_TCB_CTX_EXT *)p_tcb->ExtPtr;     /* get pointer to TCB extension               */
    if (ext != 0) {                                   /* see, if valid TCB extension is linked:     */
        ext->TaskPCXI     = 0;                        /* free TCB extension -> unlink task context  */
        p_tcb->ExtPtr = (void *)0;                    /* Remove extension link from TCB             */
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

    p_stk = &p_stk_base[stk_size - 1];                          /* Load stack pointer                                     */


    /* Unlink next two context's */
    UpperCtxLink = __mfcr(CPU_FCX);
    UpperCtx = (OS_UCX*)GET_PHYS_ADDRESS(UpperCtxLink);

    LowerCtxLink = UpperCtx->_PCXI;
    LowerCtx = (OS_LCX*)GET_PHYS_ADDRESS(LowerCtxLink);

    __mtcr(CPU_FCX, LowerCtx->_PCXI);

    /* Update context links */
    UpperCtx->_PCXI = FALSE;  /* Last context of the task => report error if returns */
    UpperCtx->_A10 = (CPU_INT32U*)p_stk;;
    UpperCtx->_A11 = OS_TaskReturn;
    UpperCtx->_PSW = OS_INIT_TASK_PSW;

    LowerCtx->_PCXI = GET_UPPER_CTX_LINK(UpperCtxLink);
    LowerCtx->_PC   = (CPU_INT32U*)p_task;
    LowerCtx->_A4   = (CPU_INT32U*)p_arg;

    *p_stk = GET_LOWER_CTX_LINK(LowerCtxLink);

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



#if OS_CFG_APP_HOOKS_EN > 0u
    if (OS_AppTaskSwHookPtr != (OS_APP_HOOK_VOID)0) {
        (*OS_AppTaskSwHookPtr)();
    }
#endif

#if OS_CFG_TASK_PROFILE_EN > 0u
    ts = OS_TS_GET();
    if (OSTCBCurPtr != OSTCBHighRdyPtr) {
        OSTCBCurPtr->CyclesDelta  = ts - OSTCBCurPtr->CyclesStart;
        OSTCBCurPtr->CyclesTotal += (OS_CYCLES)OSTCBCurPtr->CyclesDelta;
    }

    OSTCBHighRdyPtr->CyclesStart = ts;
#endif

#ifdef  CPU_CFG_INT_DIS_MEAS_EN
    int_dis_time = CPU_IntDisMeasMaxCurReset();             /* Keep track of per-task interrupt disable time          */
    if (OSTCBCurPtr->IntDisTimeMax < int_dis_time) {
        OSTCBCurPtr->IntDisTimeMax = int_dis_time;
    }
#endif

#if OS_CFG_SCHED_LOCK_TIME_MEAS_EN > 0u
                                                            /* Keep track of per-task scheduler lock time             */
    if (OSTCBCurPtr->SchedLockTimeMax < OSSchedLockTimeMaxCur) {
        OSTCBCurPtr->SchedLockTimeMax = OSSchedLockTimeMaxCur;
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
/*! \brief    remove upper/lower context from previous context list
*
*   \param    RemovePCXI PCXI pointer to context to be removed
*
*   \return   PCXI pointer to next context
*/
/*------------------------------------------------------------------------------------------------*/
//static inline CPU_INT32U OSRemoveContext(CPU_INT32U removePCXI)
//{
//    CPU_INT32U nextPCXI;
//
//    __asm ("   mfcr    d14, #PCXI                     ; store current PCXI in D14               \n"\
//           "   mtcr    #(PCXI), %1                    ; PCXI register = RemovePCXI              \n"\
//           "   extr.u  d15, %1, #16, #4               ; calc. physical address                  \n"\
//           "   sh      d15, d15, #28                  ; from RemovePCXI                         \n"\
//           "   insert  d15, d15, %1, #6, #16          ; store PCXI address in D15               \n"\
//           "   mov.a   a15, d15                       ; store PCXI address in A15               \n"\
//           "   ld.w    d13, [a15]0                    ; store next PCXI in D13                  \n"\
//           "   jz.t    %1:22, a                       ; if lower context, jump to label 1:      \n"\
//           "   stucx   [a15]0                         ; copy ucx registers to remove PCX        \n"\
//           "   st.w    [a15]0, d13                    ; restore next PCXI                       \n"\
//           "   movh.a  a11, #@his(b)                  ; setup return address                    \n"\
//           "   lea     a11, [a11]@los(b)              ; in A11 (label 2:)                       \n"\
//           "   ret                                    ; restore upper context                   \n"\
//           "a: stlcx   [a15]0                         ; copy lcx registers to remove PCX        \n"\
//           "   st.a    [a15]4, a11                    ; workaround CPU TC.067                   \n"\
//           "   st.w    [a15]0, d13                    ; restore next PCXI                       \n"\
//           "   rslcx                                  ; restore lower context                   \n"\
//           "b: mtcr    #(PCXI), d14                   ; restore PCXI register                   \n"\
//           "   mov     %0, d13                        ; return next PCXI                        \n"\
//           : "=d" (nextPCXI) : "d" (removePCXI) : "a15", "d13", "d14", "d15");
//
//   return nextPCXI;
//}

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
    OSRunning = TRUE;                                 /* OS is now running                        */

    OSTCBDummy.ExtPtr = (void*)&OSTCBDummyExt;          /* setup dummy TCB                          */
    OSTCBCurPtr = &OSTCBDummy;                          /* dummy TCB for 1st context switch         */

    OS_TASK_SW();                                     /* request a task switch to highest prio    */
}

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
    volatile OS_TCB_CTX_EXT *ext;                     /* pointer to TCB extension                 */
                                                      /*------------------------------------------*/
    __dsync();                                        /* synchronize all data accesses            */

    /* get pointer to previous context (= current task context)                                   */
    /* because OSCtxSw is reached via a call command from ISR vector / trap handler               */
    /* current PCXI register points to one additional upper context where we can find the         */
    /* current task context pointer:                                                              */
    OS_UCX* ptUpperCTX = (OS_UCX*)GET_PHYS_ADDRESS((__mfcr(CPU_PCXI)));

    ext = (volatile OS_TCB_CTX_EXT*)OSTCBCurPtr->ExtPtr;

    if (ext == (volatile OS_TCB_CTX_EXT*)0) {         /* no TCB extension; task has been deleted  */
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
    } else {                                          /* store current context pointer in TCB     */
        ext->TaskPCXI = ptUpperCTX->_PCXI;
    }

    OSTaskSwHook();                                   /* call user funktion for any task switch   */

    OSTCBCurPtr = OSTCBHighRdyPtr;                    /* new highest prio task is current task    */
    OSPrioCur = OSPrioHighRdy;                        /* new highest prio is now current prio     */

    ext = (volatile OS_TCB_CTX_EXT*)OSTCBCurPtr->ExtPtr;
    ptUpperCTX->_PCXI = ext->TaskPCXI;                /* restore new task context pointer         */
    OSResumeExecution();                              /* resume execution of highest prio. task   */

}

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
void OSIntCtxSw(void)
{
    __asm ("    movh.a  a11,#@his(j1)                  ; setup return address (label j1:)        \n"\
           "    lea     a11,[a11]@los(j1)              ; in A11                                  \n"\
           "    ret                                    ; remove context from call to OSIntCtxSw  \n"\
           "j1: movh.a  a11,#@his(j2)                  ; setup return address (label j2:)        \n"\
           "    lea     a11,[a11]@los(j2)              ; in A11                                  \n"\
           "    ret                                    ; remove context from call to OSIntExit   \n"\
           "j2: j       OSCtxSw                        ; jump to OSCtxSw()                       \n"\
           : /* no outputs */ : /* no inputs */ : "a11");
}


