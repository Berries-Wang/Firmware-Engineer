#!/bin/bash
CUR_DIR=`pwd`
STFlashDir="${CUR_DIR}/../../../../000.STM32/001.STLink/000.v1.17.0/stlink/build/bin"

echo `${STFlashDir}/st-flash write ${CUR_DIR}/build/LED_LIGHT.bin 0x08000000` 