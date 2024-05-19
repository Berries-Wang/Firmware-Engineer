# STLink 项目
&nbsp;&nbsp;编译教程： 在源码的doc目录下的compiling.md: doc/compiling.md

&nbsp;&nbsp;与源码略微不同的编译方式:

&nbsp;&nbsp;编译，不安装到系统。编译脚本：
```shell
  #!/bin/bash
  
  # 开始之前得安装 libusb 库
  
  CUR_DIR=`pwd`
  cd "${CUR_DIR}/build"
  cmake -DCMAKE_BUILD_TYPE=Debug ..
  make
```

## 参考资料
1. 源码下载:[https://github.com/stlink-org/stlink](https://github.com/stlink-org/stlink)