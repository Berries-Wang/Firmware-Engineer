cmake_minimum_required(VERSION 3.16)

project(000.STM32F103C8T6_1 VERSION 0.0.1 LANGUAGES C CXX ASM)

SET(PATH_WORKSPACE_ROOT ${CMAKE_SOURCE_DIR})
message("PATH_WORKSPACE_ROOT: ${PATH_WORKSPACE_ROOT}")

# 日志有颜色
SET(CMAKE_COLOR_DIAGNOSTICS True)

# 指定启动文件,类似于引导，否则程序不会执行: 需要选择 gcc_ride7下面的，不能选择arm目录下的，是否和编译平台有关?
set(STARTUP_FILE ${PATH_WORKSPACE_ROOT}/libs/device_libs/startup_stm32f10x_md.s)
# 指定链接文件，这个是从STM32cubemx创建的项目里面拷贝来的
SET(LINKER_SCRIPT ${PATH_WORKSPACE_ROOT}/libs/device_libs/STM32F103C8Tx_FLASH.ld)

# 是否开启更详细的编译过程信息显示
SET(CMAKE_VERBOSE_MAKEFILE ON)

# 设置交叉编译工具链
SET(TOOLCHAIN_PATH "/home/wei/WorkSpace/apps/gcc-arm-11.2-2022.02-x86_64-arm-none-eabi/bin/")
SET(CMAKE_ASM_COMPILER "${TOOLCHAIN_PATH}arm-none-eabi-gcc")
SET(CMAKE_C_COMPILER "${TOOLCHAIN_PATH}arm-none-eabi-gcc")
SET(CMAKE_CXX_COMPILER "${TOOLCHAIN_PATH}arm-none-eabi-c++")
SET(CMAKE_C_AR "${TOOLCHAIN_PATH}arm-none-eabi-ar")
SET(CMAKE_C_AS "${TOOLCHAIN_PATH}arm-none-eabi-as")
SET(CMAKE_C_LINKER "${TOOLCHAIN_PATH}arm-none-eabi-ld")
SET(CMAKE_OBJCOPY "${TOOLCHAIN_PATH}arm-none-eabi-objcopy")
SET(CMAKE_OBJDUMP "${TOOLCHAIN_PATH}arm-none-eabi-objdump")
SET(CMAKE_SIZE "${TOOLCHAIN_PATH}arm-none-eabi-size")
SET(AS "${TOOLCHAIN_PATH}arm-none-eabi-as")
SET(AR "${TOOLCHAIN_PATH}arm-none-eabi-ar")

# CMAKE_C_FLAGS 设置C编译选项;CMAKE_CXX_FLAGS 设置C++编译选项
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --specs=nano.specs -specs=rdimon.specs --specs=nosys.specs  -mcpu=cortex-m3 -march=armv7-m -mthumb -Wall -fdata-sections -ffunction-sections")

# ASMFLAGS
set(CMAKE_ASM_FLAGS " -x assembler-with-cpp ${CMAKE_C_FLAGS}")

SET(CMAKE_EXE_LINKER_FLAGS
    "${CMAKE_EXE_LINKER_FLAGS} -T ${LINKER_SCRIPT}  -Wl,--gc-sections,--print-memory-usage"
)

# 为了引入'stm32f10x_conf.h' 头文件，见: stm32f10x.h
add_compile_definitions(STM32F10X_MD USE_STDPERIPH_DRIVER)

# 平台基础文件
file(GLOB_RECURSE DeviceH ${PATH_WORKSPACE_ROOT}/libs/device_libs/*.h)
file(GLOB_RECURSE DeviceC ${PATH_WORKSPACE_ROOT}/libs/device_libs/*.c)
file(GLOB_RECURSE DriverH ${PATH_WORKSPACE_ROOT}/libs/STM32_Driver/*.h)
file(GLOB_RECURSE DriverC ${PATH_WORKSPACE_ROOT}/libs/STM32_Driver/*.c)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/device_libs ${CMAKE_CURRENT_SOURCE_DIR}/libs/STM32_Driver)

SET(LED_LIGHT "LED_LIGHT")
SET(OUTPUT_EXE_NAME "LED_LIGHT_EXE")

add_executable(${LED_LIGHT} src/000.led_light.c ${DeviceH} ${DeviceC} ${DriverH} ${DriverC} ${STARTUP_FILE} ${LINKR_SCRIPT})

# 通过st-flash烧录，是要将.bin文件烧录到STM32中
ADD_CUSTOM_COMMAND(
  TARGET "${LED_LIGHT}"
  POST_BUILD
  # Build .bin files
  COMMAND ${CMAKE_OBJCOPY} -Obinary "${LED_LIGHT}" "${OUTPUT_EXE_NAME}.bin"
  COMMENT "Building ${OUTPUT_EXE_NAME}.bin"
  # Display sizes
  COMMAND ${CMAKE_SIZE} --format=berkeley ${LED_LIGHT}
  COMMENT "Invoking: Cross ARM GNU Print Size"
  )
