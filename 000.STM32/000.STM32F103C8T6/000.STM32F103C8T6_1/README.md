# STM32F103C8T6 '基于函数库开发方式' 开发环境搭建



## 文件说明
&nbsp;&nbsp;项目文件说明
```txt
.
├── build
├── CMakeLists.txt
├── libs
│   ├── device_libs
│   │   ├── core_cm3.c  # 内核寄存器描述文件
│   │   ├── core_cm3.h  # 内核寄存器描述文件
│   │   ├── startup_stm32f10x_cl.s         # STM32启动文件，STM32就是从启动文件开始执行的
│   │   ├── startup_stm32f10x_hd.s         # STM32启动文件
│   │   ├── startup_stm32f10x_hd_vl.s      # STM32启动文件
│   │   ├── startup_stm32f10x_ld.s         # STM32启动文件
│   │   ├── startup_stm32f10x_ld_vl.s      # STM32启动文件
│   │   ├── startup_stm32f10x_md.s         # STM32启动文件
│   │   ├── startup_stm32f10x_md_vl.s      # STM32启动文件
│   │   ├── startup_stm32f10x_xl.s         # STM32启动文件
│   │   ├── stm32f10x.h # STM32外设寄存器描述文件，描述STM32有哪些寄存器以及对应地址
│   │   ├── system_stm32f10x.c # STM32外设寄存器描述文件 ， 主要用于配置时钟，STM32主频72MHZ，就是system文件里的函数配置的
│   │   └── system_stm32f10x.h # STM32外设寄存器描述文件 ， 主要用于配置时钟
│   └── STM32_Driver
│       ├── misc.c  # 内核库函数文件,其他的(STM32_Driver目录下其他文件)都是外设库库函数文件
│       ├── stm32f10x_adc.c
│       ├── stm32f10x_bkp.c
│       ├── stm32f10x_can.c
│       ├── stm32f10x_cec.c
│       ├── stm32f10x_crc.c
│       ├── stm32f10x_dac.c
│       ├── stm32f10x_dbgmcu.c
│       ├── stm32f10x_dma.c
│       ├── stm32f10x_exti.c
│       ├── stm32f10x_flash.c
│       ├── stm32f10x_fsmc.c
│       ├── stm32f10x_gpio.c
│       ├── stm32f10x_i2c.c
│       ├── stm32f10x_iwdg.c
│       ├── stm32f10x_pwr.c
│       ├── stm32f10x_rcc.c
│       ├── stm32f10x_rtc.c
│       ├── stm32f10x_sdio.c
│       ├── stm32f10x_spi.c
│       ├── stm32f10x_tim.c
│       ├── stm32f10x_usart.c
│       └── stm32f10x_wwdg.c
└── src
    ├── main.c  # main函数,启动函数
    ├── stm32f10x_conf.h # 配置库函数头文件包含关系
    ├── stm32f10x_it.c   # 存放中断函数
    └── stm32f10x_it.h   # 存放中断函数
```