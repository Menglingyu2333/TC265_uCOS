################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/iLLD/TC26B/Tricore/Gtm/Tom/PwmHl/IfxGtm_Tom_PwmHl.c 

OBJS += \
./Libraries/iLLD/TC26B/Tricore/Gtm/Tom/PwmHl/IfxGtm_Tom_PwmHl.o 

COMPILED_SRCS += \
./Libraries/iLLD/TC26B/Tricore/Gtm/Tom/PwmHl/IfxGtm_Tom_PwmHl.src 

C_DEPS += \
./Libraries/iLLD/TC26B/Tricore/Gtm/Tom/PwmHl/IfxGtm_Tom_PwmHl.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/iLLD/TC26B/Tricore/Gtm/Tom/PwmHl/%.src: ../Libraries/iLLD/TC26B/Tricore/Gtm/Tom/PwmHl/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C Compiler'
	ctc -D__CPU__=tc26xb -I"C:\000Files\Infineon\TC265\AurixDS\TC265_uCOS_v2\OS\EvalBoards\Infineon\Tricore\TC265" -I"C:\000Files\Infineon\TC265\AurixDS\TC265_uCOS_v2\OS\uCOS-III\Ports\Tricore\Generic\Tasking" -I"C:\000Files\Infineon\TC265\AurixDS\TC265_uCOS_v2\OS\uC-CPU\Tricore\Tasking" -I"C:\000Files\Infineon\TC265\AurixDS\TC265_uCOS_v2\OS" -I"C:\000Files\Infineon\TC265\AurixDS\TC265_uCOS_v2" -I"C:\000Files\Infineon\TC265\AurixDS\TC265_uCOS_v2\OS\uC-CPU" -I"C:\000Files\Infineon\TC265\AurixDS\TC265_uCOS_v2\OS\uC-LIB" -I"C:\000Files\Infineon\TC265\AurixDS\TC265_uCOS_v2\OS\uCOS-III\Source" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Gpt12" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/Infra/Platform/Tricore/Compilers" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Multican/Std" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/Infra/Platform" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Cif/Std" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Hssl/Std" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Cpu/Trap" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/Service/CpuGeneric/If/Ccu6If" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Dsadc/Dsadc" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Port" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Stm/Timer" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Dts/Dts" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Eth" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Flash" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Vadc" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Msc" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Qspi/SpiMaster" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Scu/Std" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/Service/CpuGeneric/SysSe/Comm" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/Service/CpuGeneric/SysSe/Math" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/Infra/Platform/Tricore" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Gtm/Trig" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Gtm/Tim" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Ccu6/TimerWithTrigger" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Emem" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Mtu" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/Infra" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Fft" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/I2c/I2c" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Asclin/Asc" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/Service/CpuGeneric/SysSe" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Flash/Std" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/Service/CpuGeneric/If" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Psi5" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Cpu" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Fce/Std" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Stm/Std" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Msc/Msc" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Vadc/Adc" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Asclin" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Gtm/Tom/Pwm" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Gtm/Atom" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Port/Std" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Psi5/Psi5" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Eray" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Qspi/SpiSlave" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Ccu6/Icu" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Cpu/CStart" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Hssl" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Cif" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Eth/Phy_Pef7071" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Hssl/Hssl" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Iom/Driver" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Multican/Can" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Psi5s/Psi5s" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Fft/Fft" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Ccu6/PwmHl" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Iom/Std" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/_Lib" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Gtm/Tom/Timer" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Sent" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Eray/Eray" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Gpt12/Std" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Dma" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Fce/Crc" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Qspi" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/Infra/Sfr" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/Infra/Sfr/TC26B" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/Service/CpuGeneric/SysSe/Bsp" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/Service/CpuGeneric/SysSe/General" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Cpu/Std" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Dts" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Src" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Dma/Std" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Cif/Cam" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Src/Std" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Asclin/Std" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/I2c/Std" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Configurations" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/_Lib/DataHandling" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Sent/Sent" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Ccu6/Timer" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Psi5/Std" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Psi5s" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Emem/Std" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Ccu6/PwmBc" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Iom" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Ccu6/TPwm" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/Service/CpuGeneric" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Multican" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Mtu/Std" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/Infra/Sfr/TC26B/_Reg" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Gtm/Tom/PwmHl" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Dma/Dma" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Gtm/Atom/Timer" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Ccu6/Std" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/Service/CpuGeneric/SysSe/Time" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Dsadc/Std" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Cpu/Irq" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Gtm" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Ccu6" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Gpt12/IncrEnc" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Psi5s/Std" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Scu" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/_Lib/InternalMux" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Stm" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Dsadc/Rdc" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Vadc/Std" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Dts/Std" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/Service" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Eth/Std" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Smu" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/_PinMap" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Asclin/Lin" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/Service/CpuGeneric/StdIf" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Dsadc" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Fce" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Gtm/Atom/PwmHl" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Qspi/Std" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Gtm/Tom" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Gtm/Tim/In" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Msc/Std" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Configurations/Debug" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Fft/Std" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Gtm/Atom/Pwm" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/Service/CpuGeneric/_Utilities" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Gtm/Std" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Smu/Std" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/I2c" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Asclin/Spi" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Eray/Std" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Port/Io" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/_Impl" -I"C:/000Files/Infineon/TC265/AurixDS/TC265_uCOS_v2/Libraries/iLLD/TC26B/Tricore/Sent/Std" --iso=99 --language=+volatile --fp-model=3 --fp-model=+contract --fp-model=f --fp-model=l --fp-model=n --fp-model=r --fp-model=z -O0 --tradeoff=4 --compact-max-size=200 -g --no-warnings=544,557 -o "$@"  "$<"  --core=tc1.6.x --dep-file=$(@:.src=.d) --misrac-version=2012 -N0 -Z0 -Y0 2>&1; sed -i -e '/ctc\\include/d' -e '/Libraries\\iLLD/d' -e '/Libraries\\Infra/d' -e 's/\(.*\)".*\\TC265_uCOS_v2\(\\.*\)"/\1\.\.\2/g' -e 's/\\/\//g' $(@:.src=.d) && \
	echo $(@:.src=.d) generated
	@echo 'Finished building: $<'
	@echo ' '

Libraries/iLLD/TC26B/Tricore/Gtm/Tom/PwmHl/%.o: ./Libraries/iLLD/TC26B/Tricore/Gtm/Tom/PwmHl/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


