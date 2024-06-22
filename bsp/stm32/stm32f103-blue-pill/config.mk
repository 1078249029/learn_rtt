BSP_ROOT ?= D:/Programes/RT-Thread/rtt/rt-thread/bsp/stm32/stm32f103-blue-pill
RTT_ROOT ?= D:/Programes/RT-Thread/rtt/rt-thread

CROSS_COMPILE ?=D:\\Programes\\RT-Thread\\env-windows-1.5.0\\tools\\gnu_gcc\\arm_gcc\\mingw\\bin\\arm-none-eabi-

CFLAGS := -mcpu=cortex-m3 -mthumb -ffunction-sections -fdata-sections -Dgcc -O2 -gdwarf-2 -g
AFLAGS := -c -mcpu=cortex-m3 -mthumb -ffunction-sections -fdata-sections -x assembler-with-cpp -Wa,-mimplicit-it=thumb  -gdwarf-2
LFLAGS := -mcpu=cortex-m3 -mthumb -ffunction-sections -fdata-sections -Wl,--gc-sections,-Map=rt-thread.map,-cref,-u,Reset_Handler -T board/linker_scripts/link.lds
CXXFLAGS := -mcpu=cortex-m3 -mthumb -ffunction-sections -fdata-sections -Dgcc -O2 -gdwarf-2 -g
EXTERN_LIB := -lc -lm 

CPPPATHS :=-I$(BSP_ROOT)\applications \
	-I$(RTT_ROOT)\components\libc\compilers\common\include \
	-I$(RTT_ROOT)\components\libc\compilers\newlib \
	-I$(RTT_ROOT)\libcpu\arm\common \
	-I$(RTT_ROOT)\libcpu\arm\cortex-m3 \
	-I$(RTT_ROOT)\components\drivers\include \
	-I$(BSP_ROOT)\board \
	-I$(BSP_ROOT)\board\CubeMX_Config\Inc \
	-I$(RTT_ROOT)\bsp\stm32\libraries\HAL_Drivers \
	-I$(RTT_ROOT)\bsp\stm32\libraries\HAL_Drivers\config \
	-I$(RTT_ROOT)\bsp\stm32\libraries\HAL_Drivers\CMSIS\Include \
	-I$(RTT_ROOT)\components\finsh \
	-I$(BSP_ROOT) \
	-I$(RTT_ROOT)\include \
	-I$(RTT_ROOT)\bsp\stm32\libraries\STM32F1xx_HAL\CMSIS\Device\ST\STM32F1xx\Include \
	-I$(RTT_ROOT)\bsp\stm32\libraries\STM32F1xx_HAL\STM32F1xx_HAL_Driver\Inc \
	-I$(RTT_ROOT)\components\libc\posix\io\poll \
	-I$(RTT_ROOT)\components\libc\posix\io\stdio \
	-I$(RTT_ROOT)\components\libc\posix\ipc \
	-I$(BSP_ROOT)\packages\SEGGER_RTT-latest \
	-I$(BSP_ROOT)\packages\SEGGER_RTT-latest\RTT \
	-I$(BSP_ROOT)\packages\SystemView-latest \
	-I$(BSP_ROOT)\packages\SystemView-latest\SystemView_Src\Config \
	-I$(BSP_ROOT)\packages\SystemView-latest\SystemView_Src\SEGGER 

DEFINES := -DHAVE_CCONFIG_H -DRT_USING_LIBC -DRT_USING_NEWLIB -DSTM32F103xB -DUSE_HAL_DRIVER -D_POSIX_C_SOURCE=1 -D__RTTHREAD__
