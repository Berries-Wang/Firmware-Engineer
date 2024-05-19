# Stlink
## lsusb 命令
```txt
   # 插上最小系统板到USB上时：
   wei@Wang:~/WorkSpace/apps/gcc-arm-11.2-2022.02-x86_64-arm-none-eabi/bin$ lsusb 
   Bus 002 Device 001: ID 1d6b:0003 Linux Foundation 3.0 root hub
   Bus 001 Device 007: ID 13d3:3362 IMC Networks Atheros AR3012 Bluetooth 4.0 Adapter
   Bus 001 Device 008: ID 0483:3748 STMicroelectronics ST-LINK/V2   # 检测到了ST-Link-V2 调试器
   Bus 001 Device 004: ID 1a81:2039 Holtek Semiconductor, Inc. USB Keyboard
   Bus 001 Device 003: ID 04f2:b547 Chicony Electronics Co., Ltd USB2.0 VGA UVC WebCam
   Bus 001 Device 002: ID 18f8:0f97 [Maxxter] USB OPTICAL MOUSE 
   Bus 001 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub
```

## 需要将二进制可执行文件通过STLink烧录到STM32中.
> 请参考:[000.STM32/000.STM32F103C8T6/000.STM32F103C8T6_1/000.STM32F103C8T6_1/CMakeLists.txt](../000.STM32/000.STM32F103C8T6/000.STM32F103C8T6_1/000.STM32F103C8T6_1/CMakeLists.txt) & [001.嵌入式知识库/001.文件格式](001.嵌入式知识库/001.文件格式/README.md)

&nbsp;&nbsp;如果不是将二进制可执行文件烧录到STM32中，则STM32不会开始执行.
```cmake 
     # 来源于: 000.STM32/000.STM32F103C8T6/000.STM32F103C8T6_1/000.STM32F103C8T6_1/CMakeLists.txt , 截取部分。

     # 此时生成的是ELF格式文件,烧录到STM32中，STM32也无法执行
     add_executable(${HELLO_WORLD} src/000.Hello_World.c ${DeviceH} ${DeviceC} ${DriverH} ${DriverC} ${STARTUP_FILE} ${LINKR_SCRIPT})
     
     # 通过st-flash烧录，是要将.bin文件烧录到STM32中
     ADD_CUSTOM_COMMAND(
       TARGET "${HELLO_WORLD}"
       POST_BUILD
       # Build .bin files , 构建BIN格式文件，烧录到STM32后，STM32可执行
       COMMAND ${CMAKE_OBJCOPY} -Obinary "${HELLO_WORLD}" "${OUTPUT_EXE_NAME}.bin"
       COMMENT "Building ${OUTPUT_EXE_NAME}.bin"
       # Display sizes
       COMMAND ${CMAKE_SIZE} --format=berkeley ${HELLO_WORLD}
       COMMENT "Invoking: Cross ARM GNU Print Size"
       )
```

## 编译&&安装
### STlink1.17.0 (学习STM32时所用)


## 参考资料
1. [github: stlink-org/stlink](https://github.com/stlink-org/stlink)