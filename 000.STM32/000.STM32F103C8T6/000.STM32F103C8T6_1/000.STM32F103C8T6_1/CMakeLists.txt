cmake_minimum_required(VERSION 3.16)

project(000.STM32F103C8T6_1)

# 设置交叉编译工具链
set(CMAKE_C_COMPILER "/home/wei/WorkSpace/apps/arm-gnu-toolchain-13.2.Rel1-x86_64-arm-none-eabi/bin/arm-none-eabi-gcc")
# CMAKE_C_FLAGS 设置C编译选项;CMAKE_CXX_FLAGS 设置C++编译选项
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --specs=nosys.specs")

add_compile_definitions(STM32F10X_MD)

# 为了引入'stm32f10x_conf.h' 头文件，见: stm32f10x.h
add_compile_definitions(USE_STDPERIPH_DRIVER)

include_directories(libs/device_libs libs/STM32_Driver src/headers)

add_executable(main src/main.c)
