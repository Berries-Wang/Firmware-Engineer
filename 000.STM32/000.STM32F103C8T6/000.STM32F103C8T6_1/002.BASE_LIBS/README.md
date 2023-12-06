# BASE_LIBS
&nbsp;&nbsp;存储基础工具，如基础函数库,文件说明如下:
```txt
&nbsp;&nbsp;项目文件说明（000.STM32/000.STM32F103C8T6/000.STM32F103C8T6_1/002.BASE_LIBS）
```txt
.
├── CMakeLists.txt
├── device_libs
│   ├── CMakeLists.txt
│   ├── core_cm3.c # 内核寄存器描述文件
│   ├── core_cm3.h
│   ├── startup_stm32f10x_md.s # STM32启动文件，STM32就是从启动文件开始执行的
│   ├── startup_stm32f10x_md_vl.s
│   ├── STM32F103C8Tx_FLASH.ld 链接文件，从STM32cubemx创建的项目里面拷贝来的
│   ├── stm32f10x.h  # STM32外设寄存器描述文件，描述STM32有哪些寄存器以及对应地址
│   ├── system_stm32f10x.c # STM32外设寄存器描述文件 ， 主要用于配置时钟，STM32主频72MHZ，就是system文件里的函数配置的
│   └── system_stm32f10x.h # STM32外设寄存器描述文件 ， 主要用于配置时钟
└── STM32_Driver
    ├── CMakeLists.txt
    ├── misc.c  # 内核库函数文件,其他的(STM32_Driver目录下其他文件)都是外设库库函数文件
    ├── misc.h  # 内核寄存器描述文件
    ├── stm32f10x_adc.c
    ├── stm32f10x_adc.h
    ├── stm32f10x_bkp.c
    ├── stm32f10x_bkp.h
    ├── stm32f10x_can.c
    ├── stm32f10x_can.h
    ├── stm32f10x_cec.c
    ├── stm32f10x_cec.h
    ├── stm32f10x_conf.h # 配置库函数头文件包含关系
    ├── stm32f10x_crc.c
    ├── stm32f10x_crc.h
    ├── stm32f10x_dac.c
    ├── stm32f10x_dac.h
    ├── stm32f10x_dbgmcu.c
    ├── stm32f10x_dbgmcu.h
    ├── stm32f10x_dma.c
    ├── stm32f10x_dma.h
    ├── stm32f10x_exti.c
    ├── stm32f10x_exti.h
    ├── stm32f10x_flash.c
    ├── stm32f10x_flash.h
    ├── stm32f10x_fsmc.c
    ├── stm32f10x_fsmc.h
    ├── stm32f10x_gpio.c
    ├── stm32f10x_gpio.h
    ├── stm32f10x_i2c.c
    ├── stm32f10x_i2c.h
    ├── stm32f10x_it.c  # 存放中断函数
    ├── stm32f10x_it.h  # 存放中断函数
    ├── stm32f10x_iwdg.c
    ├── stm32f10x_iwdg.h
    ├── stm32f10x_pwr.c
    ├── stm32f10x_pwr.h
    ├── stm32f10x_rcc.c
    ├── stm32f10x_rcc.h
    ├── stm32f10x_rtc.c
    ├── stm32f10x_rtc.h
    ├── stm32f10x_sdio.c
    ├── stm32f10x_sdio.h
    ├── stm32f10x_spi.c
    ├── stm32f10x_spi.h
    ├── stm32f10x_tim.c
    ├── stm32f10x_tim.h
    ├── stm32f10x_usart.c
    ├── stm32f10x_usart.h
    ├── stm32f10x_wwdg.c
    └── stm32f10x_wwdg.h
```
