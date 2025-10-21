# STM32 异常
STM32 是基于 Arm® 32-bit Cortex®-M3 CPU core  , 因此，先了解Cortex®-M3的异常模型，再了解STM32的异常



## 参与资料
https://developer.arm.com/documentation/107706/0100/Exceptions-and-interrupts-overview/Stack-frames?lang=en
https://developer.arm.com/documentation/107706/0100/Floating-point-and-MVE-support/Floating-point-context-handling-mechanisms?lang=en#md543-floating-point-context-handling-mechanisms__exc_return-1
https://developer.arm.com/documentation/107706/0100/Use-case-examples/context-switch-fp?lang=en
https://github.com/ARM-software/m-profile-user-guide-examples/blob/main/Exception_model/context-switch-fp/scheduler.c
https://developer.arm.com/documentation/107655/100/Armv8-M-exception-model-with-Security-Extension/Stack-frames?lang=en
https://community.arm.com/cfs-file/__key/telligent-evolution-components-attachments/01-2057-00-00-00-01-28-19/Cortex_2D00_M-for-Beginners-_2D00_-2017_5F00_CN_5F00_v3.pdf
https://developer.arm.com/documentation/ddi0553/by/?lang=en
https://github.com/Berries-Wang/Berries-Kernel/blob/release/001.UNIX-DOCS/005.syscall-%E5%8F%91%E8%B5%B7%E7%B3%BB%E7%BB%9F%E8%B0%83%E7%94%A8.md
Page37: https://github.com/Berries-Wang/Berries-Kernel/blob/release/006.REFS/learn_the_architecture_-_aarch64_exception_model_102412_0103_02_en.pdf 
Page37: https://github.com/Berries-Wang/Berries-Kernel/blob/release/006.REFS/learn_the_architecture_-_aarch64_exception_model_102412_0103_02_en.pdf
https://github.com/Berries-Wang/Berries-Kernel-NOTE/blob/master/000.LINUX_KERNEL/003.%E8%BF%9B%E7%A8%8B%E8%B0%83%E5%BA%A6/001.Linux-Kernel-%E4%B8%AD%E6%96%AD-Interrupt.md