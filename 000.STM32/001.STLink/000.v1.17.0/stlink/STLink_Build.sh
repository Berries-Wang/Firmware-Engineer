#!/bin/bash

# 开始之前得安装 libusb 库

CUR_DIR=`pwd`
cd "${CUR_DIR}/build"
cmake -DCMAKE_BUILD_TYPE=Debug ..
make