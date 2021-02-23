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


/*$PAGE*/
/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/


