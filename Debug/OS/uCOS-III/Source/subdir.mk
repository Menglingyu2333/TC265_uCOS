################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../OS/uCOS-III/Source/os_cfg_app.c \
../OS/uCOS-III/Source/os_core.c \
../OS/uCOS-III/Source/os_dbg.c \
../OS/uCOS-III/Source/os_flag.c \
../OS/uCOS-III/Source/os_int.c \
../OS/uCOS-III/Source/os_mem.c \
../OS/uCOS-III/Source/os_msg.c \
../OS/uCOS-III/Source/os_mutex.c \
../OS/uCOS-III/Source/os_pend_multi.c \
../OS/uCOS-III/Source/os_prio.c \
../OS/uCOS-III/Source/os_q.c \
../OS/uCOS-III/Source/os_sem.c \
../OS/uCOS-III/Source/os_stat.c \
../OS/uCOS-III/Source/os_task.c \
../OS/uCOS-III/Source/os_tick.c \
../OS/uCOS-III/Source/os_time.c \
../OS/uCOS-III/Source/os_tmr.c \
../OS/uCOS-III/Source/os_var.c 

OBJS += \
./OS/uCOS-III/Source/os_cfg_app.o \
./OS/uCOS-III/Source/os_core.o \
./OS/uCOS-III/Source/os_dbg.o \
./OS/uCOS-III/Source/os_flag.o \
./OS/uCOS-III/Source/os_int.o \
./OS/uCOS-III/Source/os_mem.o \
./OS/uCOS-III/Source/os_msg.o \
./OS/uCOS-III/Source/os_mutex.o \
./OS/uCOS-III/Source/os_pend_multi.o \
./OS/uCOS-III/Source/os_prio.o \
./OS/uCOS-III/Source/os_q.o \
./OS/uCOS-III/Source/os_sem.o \
./OS/uCOS-III/Source/os_stat.o \
./OS/uCOS-III/Source/os_task.o \
./OS/uCOS-III/Source/os_tick.o \
./OS/uCOS-III/Source/os_time.o \
./OS/uCOS-III/Source/os_tmr.o \
./OS/uCOS-III/Source/os_var.o 

COMPILED_SRCS += \
./OS/uCOS-III/Source/os_cfg_app.src \
./OS/uCOS-III/Source/os_core.src \
./OS/uCOS-III/Source/os_dbg.src \
./OS/uCOS-III/Source/os_flag.src \
./OS/uCOS-III/Source/os_int.src \
./OS/uCOS-III/Source/os_mem.src \
./OS/uCOS-III/Source/os_msg.src \
./OS/uCOS-III/Source/os_mutex.src \
./OS/uCOS-III/Source/os_pend_multi.src \
./OS/uCOS-III/Source/os_prio.src \
./OS/uCOS-III/Source/os_q.src \
./OS/uCOS-III/Source/os_sem.src \
./OS/uCOS-III/Source/os_stat.src \
./OS/uCOS-III/Source/os_task.src \
./OS/uCOS-III/Source/os_tick.src \
./OS/uCOS-III/Source/os_time.src \
./OS/uCOS-III/Source/os_tmr.src \
./OS/uCOS-III/Source/os_var.src 

C_DEPS += \
./OS/uCOS-III/Source/os_cfg_app.d \
./OS/uCOS-III/Source/os_core.d \
./OS/uCOS-III/Source/os_dbg.d \
./OS/uCOS-III/Source/os_flag.d \
./OS/uCOS-III/Source/os_int.d \
./OS/uCOS-III/Source/os_mem.d \
./OS/uCOS-III/Source/os_msg.d \
./OS/uCOS-III/Source/os_mutex.d \
./OS/uCOS-III/Source/os_pend_multi.d \
./OS/uCOS-III/Source/os_prio.d \
./OS/uCOS-III/Source/os_q.d \
./OS/uCOS-III/Source/os_sem.d \
./OS/uCOS-III/Source/os_stat.d \
./OS/uCOS-III/Source/os_task.d \
./OS/uCOS-III/Source/os_tick.d \
./OS/uCOS-III/Source/os_time.d \
./OS/uCOS-III/Source/os_tmr.d \
./OS/uCOS-III/Source/os_var.d 


# Each subdirectory must supply rules for building sources it contributes
OS/uCOS-III/Source/%.src: ../OS/uCOS-III/Source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C Compiler'
	ctc -D__CPU__=tc26xb -I"D:\000Files\Infineon\TC265\AurixDS\TC265_uCOS_v2\OS\EvalBoards\Infineon\Tricore\TC265" -I"D:\000Files\Infineon\TC265\AurixDS\TC265_uCOS_v2\OS\uCOS-III\Ports\Tricore\Generic\Tasking" -I"D:\000Files\Infineon\TC265\AurixDS\TC265_uCOS_v2\OS\uC-CPU\Tricore\Tasking" -I"D:\000Files\Infineon\TC265\AurixDS\TC265_uCOS_v2\OS" -I"D:\000Files\Infineon\TC265\AurixDS\TC265_uCOS_v2" -I"D:\000Files\Infineon\TC265\AurixDS\TC265_uCOS_v2\OS\uC-CPU" -I"D:\000Files\Infineon\TC265\AurixDS\TC265_uCOS_v2\OS\uC-LIB" -I"D:\000Files\Infineon\TC265\AurixDS\TC265_uCOS_v2\OS\uCOS-III\Source" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Gpt12" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/Infra/Platform/Tricore/Compilers" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Multican/Std" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/Infra/Platform" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Cif/Std" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Hssl/Std" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Cpu/Trap" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/Service/CpuGeneric/If/Ccu6If" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Dsadc/Dsadc" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Port" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Stm/Timer" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Dts/Dts" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Eth" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Flash" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Vadc" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Msc" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Qspi/SpiMaster" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Scu/Std" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/Service/CpuGeneric/SysSe/Comm" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/Service/CpuGeneric/SysSe/Math" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/Infra/Platform/Tricore" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Gtm/Trig" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Gtm/Tim" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Ccu6/TimerWithTrigger" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Emem" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Mtu" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/Infra" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Fft" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/I2c/I2c" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Asclin/Asc" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/Service/CpuGeneric/SysSe" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Flash/Std" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/Service/CpuGeneric/If" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Psi5" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Cpu" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Fce/Std" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Stm/Std" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Msc/Msc" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Vadc/Adc" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Asclin" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Gtm/Tom/Pwm" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Gtm/Atom" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Port/Std" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Psi5/Psi5" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Eray" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Qspi/SpiSlave" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Ccu6/Icu" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Cpu/CStart" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Hssl" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Cif" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Eth/Phy_Pef7071" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Hssl/Hssl" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Iom/Driver" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Multican/Can" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Psi5s/Psi5s" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Fft/Fft" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Ccu6/PwmHl" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Iom/Std" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/_Lib" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Gtm/Tom/Timer" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Sent" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Eray/Eray" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Gpt12/Std" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Dma" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Fce/Crc" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Qspi" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/Infra/Sfr" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/Infra/Sfr/TC26B" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/Service/CpuGeneric/SysSe/Bsp" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/Service/CpuGeneric/SysSe/General" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Cpu/Std" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Dts" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Src" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Dma/Std" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Cif/Cam" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Src/Std" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Asclin/Std" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/I2c/Std" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Configurations" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/_Lib/DataHandling" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Sent/Sent" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Ccu6/Timer" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Psi5/Std" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Psi5s" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Emem/Std" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Ccu6/PwmBc" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Iom" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Ccu6/TPwm" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/Service/CpuGeneric" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Multican" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Mtu/Std" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/Infra/Sfr/TC26B/_Reg" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Gtm/Tom/PwmHl" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Dma/Dma" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Gtm/Atom/Timer" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Ccu6/Std" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/Service/CpuGeneric/SysSe/Time" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Dsadc/Std" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Cpu/Irq" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Gtm" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Ccu6" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Gpt12/IncrEnc" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Psi5s/Std" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Scu" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/_Lib/InternalMux" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Stm" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Dsadc/Rdc" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Vadc/Std" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Dts/Std" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/Service" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Eth/Std" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Smu" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/_PinMap" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Asclin/Lin" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/Service/CpuGeneric/StdIf" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Dsadc" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Fce" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Gtm/Atom/PwmHl" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Qspi/Std" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Gtm/Tom" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Gtm/Tim/In" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Msc/Std" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Configurations/Debug" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Fft/Std" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Gtm/Atom/Pwm" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/Service/CpuGeneric/_Utilities" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Gtm/Std" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Smu/Std" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/I2c" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Asclin/Spi" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Eray/Std" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Port/Io" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/_Impl" -I"D:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Sent/Std" --iso=99 --language=+volatile --fp-model=3 --fp-model=+contract --fp-model=f --fp-model=l --fp-model=n --fp-model=r --fp-model=z -O0 --tradeoff=4 --compact-max-size=200 -g --no-warnings=544,557 -o "$@"  "$<"  --core=tc1.6.x --dep-file=$(@:.src=.d) --misrac-version=2012 -N0 -Z0 -Y0 2>&1; sed -i -e '/ctc\\include/d' -e '/Libraries\\iLLD/d' -e '/Libraries\\Infra/d' -e 's/\(.*\)".*\\TC265_uCOS_v2\(\\.*\)"/\1\.\.\2/g' -e 's/\\/\//g' $(@:.src=.d) && \
	echo $(@:.src=.d) generated
	@echo 'Finished building: $<'
	@echo ' '

OS/uCOS-III/Source/%.o: ./OS/uCOS-III/Source/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


