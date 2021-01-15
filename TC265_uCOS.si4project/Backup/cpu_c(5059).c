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
*
*                                            CPU PORT FILE
*
*                                            ARM-Cortex-M3
*                                      RealView Development Suite
*                            RealView Microcontroller Development Kit (MDK)
*                                       ARM Developer Suite (ADS)
*                                            Keil uVision
*
* Filename      : cpu_c.c
* Version       : V1.29.01.00
* Programmer(s) : JJL
*                 BAN
*                 FT
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


/*$PAGE*/
/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define  CPU_INT_SRC_POS_MAX                  ((((CPU_REG_NVIC_NVIC + 1) & 0x1F) * 32) + 16)

#define  CPU_BIT_BAND_SRAM_REG_LO                 0x20000000
#define  CPU_BIT_BAND_SRAM_REG_HI                 0x200FFFFF
#define  CPU_BIT_BAND_SRAM_BASE                   0x22000000


#define  CPU_BIT_BAND_PERIPH_REG_LO               0x40000000
#define  CPU_BIT_BAND_PERIPH_REG_HI               0x400FFFFF
#define  CPU_BIT_BAND_PERIPH_BASE                 0x42000000
////
////
/////*
////*********************************************************************************************************
////*                                           LOCAL CONSTANTS
////*********************************************************************************************************
////*/
////
////
/////*
////*********************************************************************************************************
////*                                          LOCAL DATA TYPES
////*********************************************************************************************************
////*/
////
////
/////*
////*********************************************************************************************************
////*                                            LOCAL TABLES
////*********************************************************************************************************
////*/
////
////
/////*
////*********************************************************************************************************
////*                                       LOCAL GLOBAL VARIABLES
////*********************************************************************************************************
////*/
////
////
/////*
////*********************************************************************************************************
////*                                      LOCAL FUNCTION PROTOTYPES
////*********************************************************************************************************
////*/
////
////
/////*
////*********************************************************************************************************
////*                                     LOCAL CONFIGURATION ERRORS
////*********************************************************************************************************
////*/
////
////
/////*$PAGE*/
/////*
////*********************************************************************************************************
////*                                          CPU_BitBandClr()
////*
////* Description : Clear bit in bit-band region.
////*
////* Argument(s) : addr            Byte address in memory space.
////*
////*               bit_nbr         Bit number in byte.
////*
////* Return(s)   : none.
////*
////* Caller(s)   : Application.
////*
////* Note(s)     : none.
////*********************************************************************************************************
////*/
////
////void  CPU_BitBandClr (CPU_ADDR    addr,
////                      CPU_INT08U  bit_nbr)
////{
////    CPU_ADDR  bit_word_off;
////    CPU_ADDR  bit_word_addr;
////
////
////    if ((addr >= CPU_BIT_BAND_SRAM_REG_LO) &&
////        (addr <= CPU_BIT_BAND_SRAM_REG_HI)) {
////        bit_word_off  = ((addr - CPU_BIT_BAND_SRAM_REG_LO  ) * 32) + (bit_nbr * 4);
////        bit_word_addr = CPU_BIT_BAND_SRAM_BASE   + bit_word_off;
////
////      *(volatile CPU_INT32U *)(bit_word_addr) = 0;
////
////    } else if ((addr >= CPU_BIT_BAND_PERIPH_REG_LO) &&
////               (addr <= CPU_BIT_BAND_PERIPH_REG_HI)) {
////        bit_word_off  = ((addr - CPU_BIT_BAND_PERIPH_REG_LO) * 32) + (bit_nbr * 4);
////        bit_word_addr = CPU_BIT_BAND_PERIPH_BASE + bit_word_off;
////
////      *(volatile CPU_INT32U *)(bit_word_addr) = 0;
////    }
////}
//
//
///*$PAGE*/
///*
//*********************************************************************************************************
//*                                          CPU_BitBandSet()
//*
//* Description : Set bit in bit-band region.
//*
//* Argument(s) : addr            Byte address in memory space.
//*
//*               bit_nbr         Bit number in byte.
//*
//* Return(s)   : none.
//*
//* Caller(s)   : Application.
//*
//* Note(s)     : none.
//*********************************************************************************************************
//*/
//
//void  CPU_BitBandSet (CPU_ADDR    addr,
//                      CPU_INT08U  bit_nbr)
//{
//    CPU_ADDR  bit_word_off;
//    CPU_ADDR  bit_word_addr;
//
//
//    if ((addr >= CPU_BIT_BAND_SRAM_REG_LO) &&
//        (addr <= CPU_BIT_BAND_SRAM_REG_HI)) {
//        bit_word_off  = ((addr - CPU_BIT_BAND_SRAM_REG_LO  ) * 32) + (bit_nbr * 4);
//        bit_word_addr = CPU_BIT_BAND_SRAM_BASE   + bit_word_off;
//
//      *(volatile CPU_INT32U *)(bit_word_addr) = 1;
//
//    } else if ((addr >= CPU_BIT_BAND_PERIPH_REG_LO) &&
//               (addr <= CPU_BIT_BAND_PERIPH_REG_HI)) {
//        bit_word_off  = ((addr - CPU_BIT_BAND_PERIPH_REG_LO) * 32) + (bit_nbr * 4);
//        bit_word_addr = CPU_BIT_BAND_PERIPH_BASE + bit_word_off;
//
//      *(volatile CPU_INT32U *)(bit_word_addr) = 1;
//    }
//}



/*$PAGE*/
/*
*********************************************************************************************************
*                                           CPU_IntSrcDis()
*
* Description : Disable an interrupt source.
*
* Argument(s) : pos     Position of interrupt vector in interrupt table :
*
*                           0       Invalid (see Note #1a).
*                           1       Invalid (see Note #1b).
*                           2       Non-maskable interrupt.
*                           3       Hard Fault.
*                           4       Memory Management.
*                           5       Bus Fault.
*                           6       Usage Fault.
*                           7-10    Reserved.
*                           11      SVCall
*                           12      Debug monitor.
*                           13      Reserved
*                           14      PendSV.
*                           15      SysTick.
*                           16+     External Interrupt.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) Several table positions do not contain interrupt sources :
*
*                   (a) Position 0 contains the stack pointer.
*                   (b) Positions 7-10, 13 are reserved.
*
*               (2) Several interrupts cannot be disabled/enabled :
*
*                   (a) Reset.
*                   (b) NMI.
*                   (c) Hard fault.
*                   (d) SVCall.
*                   (e) Debug monitor.
*                   (f) PendSV.
*
*               (3) The maximum Cortex-M3 table position is 256.  A particular Cortex-M3 may have fewer
*                   than 240 external exceptions and, consequently, fewer than 256 table positions.
*                   This function assumes that the specified table position is valid if the interrupt
*                   controller type register's INTLINESNUM field is large enough so that the position
*                   COULD be valid.
*********************************************************************************************************
*/
/*$PAGE*/
//void  CPU_IntSrcDis (CPU_INT08U  pos)
//{
//}
//void  CPU_IntSrcEn (CPU_INT08U  pos)
//{
//}
//void  CPU_IntSrcPendClr (CPU_INT08U  pos)
//{
//}
//void  CPU_IntSrcPrioSet (CPU_INT08U  pos,
//                         CPU_INT08U  prio)
//{
//}
//CPU_INT16S  CPU_IntSrcPrioGet (CPU_INT08U  pos)
//{
//}
//
//void        CPU_IntDis       ()
//{
//}
//void        CPU_IntEn        ()
//{
//}
//CPU_SR      CPU_SR_Save      (void)
//{
//}
//void        CPU_SR_Restore   (CPU_SR      cpu_sr)
//{
//}
//
//
//void        CPU_WaitForInt   (void)
//{
//}
//void        CPU_WaitForExcept(void)
//{
//}
//
//CPU_DATA    CPU_RevBits      (CPU_DATA    val)
//{
//}


