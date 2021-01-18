#include "Ifx_Types.h"
#include "IfxCpu_Intrinsics.h"
#include "IfxPort_Io.h"
#include "os_cpu.h"

IFX_INLINE void SysCallExtensionHook(IfxCpu_Trap trapInfo)
{
    switch (trapInfo.tId)
    {
        case 0:     //�л�����Trap
        {
            /*__svlcx();    lower context was stored in the trap vector */
            OSCtxSw();
            break;
        }
        default:
        {
            break;
        }
    }
}
#define IFX_CFG_CPU_TRAP_SYSCALL_CPU0_HOOK(trapInfo)  SysCallExtensionHook(trapInfo)


