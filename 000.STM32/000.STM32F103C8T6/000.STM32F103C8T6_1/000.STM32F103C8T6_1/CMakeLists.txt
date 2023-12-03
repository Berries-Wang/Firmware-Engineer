cmake_minimum_required(VERSION 3.16)

project(000.STM32F103C8T6_1 VERSION 0.0.1)

SET(PATH_WORKSPACE_ROOT ${CMAKE_SOURCE_DIR})
message("PATH_WORKSPACE_ROOT: ${PATH_WORKSPACE_ROOT}")

# 日志有颜色
SET(CMAKE_COLOR_DIAGNOSTICS True)

# 指定启动文件
SET(STARTUP_ASM ${PATH_WORKSPACE_ROOT}/libs/startup_stm32f10x_hd.s)

# 是否开启更详细的编译过程信息显示
SET(CMAKE_VERBOSE_MAKEFILE ON)

# 设置交叉编译工具链
SET(TOOLCHAIN_PATH "/home/wei/WorkSpace/apps/gcc-arm-11.2-2022.02-x86_64-arm-none-eabi/bin/")
SET(CMAKE_ASM_COMPILER "${TOOLCHAIN_PATH}arm-none-eabi-gcc" )
SET(CMAKE_C_COMPILER "${TOOLCHAIN_PATH}arm-none-eabi-gcc" )
SET(CMAKE_CXX_COMPILER "${TOOLCHAIN_PATH}arm-none-eabi-c++" )
SET(CMAKE_C_AR "${TOOLCHAIN_PATH}arm-none-eabi-ar" )
SET(CMAKE_C_LINKER "${TOOLCHAIN_PATH}arm-none-eabi-ld" )
SET(CMAKE_OBJCOPY "${TOOLCHAIN_PATH}arm-none-eabi-objcopy" )
SET(CMAKE_OBJDUMP "${TOOLCHAIN_PATH}arm-none-eabi-objdump" )
SET(CMAKE_SIZE "${TOOLCHAIN_PATH}arm-none-eabi-size" )

# CMAKE_C_FLAGS 设置C编译选项;CMAKE_CXX_FLAGS 设置C++编译选项
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --specs=nosys.specs -mcpu=cortex-m3 -march=armv7-m")
#ASMFLAGS
set ( CMAKE_ASM_FLAGS "-x assembler-with-cpp ${CMAKE_C_FLAGS}")

add_compile_definitions(STM32F10X_MD)
# 为了引入'stm32f10x_conf.h' 头文件，见: stm32f10x.h
add_compile_definitions(USE_STDPERIPH_DRIVER)

# 平台基础文件
file (GLOB_RECURSE DeviceH ${PATH_WORKSPACE_ROOT}/libs/device_libs/*.h )
file (GLOB_RECURSE DeviceC ${PATH_WORKSPACE_ROOT}/libs/device_libs/*.c )
file (GLOB_RECURSE DriverH ${PATH_WORKSPACE_ROOT}/libs/STM32_Driver/*.h )
file (GLOB_RECURSE DriverC ${PATH_WORKSPACE_ROOT}/libs/STM32_Driver/*.c )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/device_libs ${CMAKE_CURRENT_SOURCE_DIR}/libs/STM32_Driver)

add_executable(main src/main.c  ${DeviceH} ${DeviceC} ${DriverH} ${DriverC})
