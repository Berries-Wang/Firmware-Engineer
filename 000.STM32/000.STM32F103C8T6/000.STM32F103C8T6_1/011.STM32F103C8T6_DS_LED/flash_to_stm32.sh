#!/bin/bash
CUR_DIR=`pwd`
STFlashDir="${CUR_DIR}/../../../../000.STM32/001.STLink/000.SOURCE_CODE/CODE/stlink-1.8.0/build/bin"
echo ${STFlashDir}
echo `${STFlashDir}/st-flash write ${CUR_DIR}/build-output/LED_ON_EXE.bin 0x08000000` 