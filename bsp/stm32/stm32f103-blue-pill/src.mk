SRC_FILES :=
SRC_FILES +=$(RTT_ROOT)/bsp/stm32/libraries/HAL_Drivers/drv_common.c
SRC_FILES +=$(RTT_ROOT)/bsp/stm32/libraries/HAL_Drivers/drv_gpio.c
SRC_FILES +=$(RTT_ROOT)/bsp/stm32/libraries/HAL_Drivers/drv_usart.c
SRC_FILES +=$(RTT_ROOT)/bsp/stm32/libraries/STM32F1xx_HAL/CMSIS/Device/ST/STM32F1xx/Source/Templates/gcc/startup_stm32f103xb.s
SRC_FILES +=$(RTT_ROOT)/bsp/stm32/libraries/STM32F1xx_HAL/CMSIS/Device/ST/STM32F1xx/Source/Templates/system_stm32f1xx.c
SRC_FILES +=$(RTT_ROOT)/bsp/stm32/libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c
SRC_FILES +=$(RTT_ROOT)/bsp/stm32/libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cec.c
SRC_FILES +=$(RTT_ROOT)/bsp/stm32/libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c
SRC_FILES +=$(RTT_ROOT)/bsp/stm32/libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_crc.c
SRC_FILES +=$(RTT_ROOT)/bsp/stm32/libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c
SRC_FILES +=$(RTT_ROOT)/bsp/stm32/libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c
SRC_FILES +=$(RTT_ROOT)/bsp/stm32/libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c
SRC_FILES +=$(RTT_ROOT)/bsp/stm32/libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c
SRC_FILES +=$(RTT_ROOT)/bsp/stm32/libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c
SRC_FILES +=$(RTT_ROOT)/bsp/stm32/libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c
SRC_FILES +=$(RTT_ROOT)/bsp/stm32/libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c
SRC_FILES +=$(RTT_ROOT)/bsp/stm32/libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_usart.c
SRC_FILES +=$(BSP_ROOT)/applications/main.c
SRC_FILES +=$(BSP_ROOT)/board/CubeMX_Config/Src/stm32f1xx_hal_msp.c
SRC_FILES +=$(BSP_ROOT)/board/board.c
SRC_FILES +=$(BSP_ROOT)/packages/SystemView-latest/SystemView_Src/Config/SEGGER_RTT_Device.c
SRC_FILES +=$(BSP_ROOT)/packages/SystemView-latest/SystemView_Src/Config/SEGGER_SYSVIEW_Config_RTThread.c
SRC_FILES +=$(BSP_ROOT)/packages/SystemView-latest/SystemView_Src/Config/SEGGER_SYSVIEW_RTThread.c
SRC_FILES +=$(BSP_ROOT)/packages/SystemView-latest/SystemView_Src/SEGGER/SEGGER_RTT.c
SRC_FILES +=$(BSP_ROOT)/packages/SystemView-latest/SystemView_Src/SEGGER/SEGGER_SYSVIEW.c
SRC_FILES +=$(RTT_ROOT)/components/drivers/ipc/completion.c
SRC_FILES +=$(RTT_ROOT)/components/drivers/ipc/dataqueue.c
SRC_FILES +=$(RTT_ROOT)/components/drivers/ipc/pipe.c
SRC_FILES +=$(RTT_ROOT)/components/drivers/ipc/ringblk_buf.c
SRC_FILES +=$(RTT_ROOT)/components/drivers/ipc/ringbuffer.c
SRC_FILES +=$(RTT_ROOT)/components/drivers/ipc/waitqueue.c
SRC_FILES +=$(RTT_ROOT)/components/drivers/ipc/workqueue.c
SRC_FILES +=$(RTT_ROOT)/components/drivers/misc/pin.c
SRC_FILES +=$(RTT_ROOT)/components/drivers/serial/serial.c
SRC_FILES +=$(RTT_ROOT)/components/finsh/cmd.c
SRC_FILES +=$(RTT_ROOT)/components/finsh/msh.c
SRC_FILES +=$(RTT_ROOT)/components/finsh/msh_parse.c
SRC_FILES +=$(RTT_ROOT)/components/finsh/shell.c
SRC_FILES +=$(RTT_ROOT)/components/libc/compilers/common/cctype.c
SRC_FILES +=$(RTT_ROOT)/components/libc/compilers/common/cstdio.c
SRC_FILES +=$(RTT_ROOT)/components/libc/compilers/common/cstdlib.c
SRC_FILES +=$(RTT_ROOT)/components/libc/compilers/common/cstring.c
SRC_FILES +=$(RTT_ROOT)/components/libc/compilers/common/ctime.c
SRC_FILES +=$(RTT_ROOT)/components/libc/compilers/common/cwchar.c
SRC_FILES +=$(RTT_ROOT)/components/libc/compilers/newlib/syscalls.c
SRC_FILES +=$(RTT_ROOT)/libcpu/arm/common/backtrace.c
SRC_FILES +=$(RTT_ROOT)/libcpu/arm/common/div0.c
SRC_FILES +=$(RTT_ROOT)/libcpu/arm/common/showmem.c
SRC_FILES +=$(RTT_ROOT)/libcpu/arm/cortex-m3/context_gcc.S
SRC_FILES +=$(RTT_ROOT)/libcpu/arm/cortex-m3/cpuport.c
SRC_FILES +=$(RTT_ROOT)/src/clock.c
SRC_FILES +=$(RTT_ROOT)/src/components.c
SRC_FILES +=$(RTT_ROOT)/src/device.c
SRC_FILES +=$(RTT_ROOT)/src/idle.c
SRC_FILES +=$(RTT_ROOT)/src/ipc.c
SRC_FILES +=$(RTT_ROOT)/src/irq.c
SRC_FILES +=$(RTT_ROOT)/src/kservice.c
SRC_FILES +=$(RTT_ROOT)/src/mem.c
SRC_FILES +=$(RTT_ROOT)/src/mempool.c
SRC_FILES +=$(RTT_ROOT)/src/object.c
SRC_FILES +=$(RTT_ROOT)/src/scheduler.c
SRC_FILES +=$(RTT_ROOT)/src/thread.c
SRC_FILES +=$(RTT_ROOT)/src/timer.c
