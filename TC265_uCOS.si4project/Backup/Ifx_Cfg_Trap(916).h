#include "Cpu/Std/Ifx_Types.h"
#include "Cpu/Std/IfxCpu_Intrinsics.h"
#include "Port/Io/IfxPort_Io.h"
#include "SysSe/Bsp/Bsp.h"

IFX_INLINE SysCallExtensionHook(IfxCpu_Trap trapInfo)
{
    switch (trapInfo.tId)
    {
        case 0:     //«–ªª»ŒŒÒTrap
        {
            __svlcx();
            OSCtxSw();
            __rslcx();
            __nop();
            break;
        }
        default:
        {
            break;
        }
    }
}
#define IFX_CFG_CPU_TRAP_SYSCALL_CPU0_HOOK(trapInfo)  SysCallExtensionHook(trapInfo)


