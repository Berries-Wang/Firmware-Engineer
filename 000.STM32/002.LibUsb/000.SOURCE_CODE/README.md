# Libusb
## 编译问题
### 编译
```txt
   1. ./autogen.sh 
   2. make 
   3. sudo make install 
```

### 编译问题
#### error: Libtool library used but 'LIBTOOL' is undefined
```txt
wei@Wang:~/WorkSpace/open_source/Firmware-Engineer/000.STM32/002.LibUsb/000.LibUsb/libusb$ ./autogen.sh 
autoreconf: Entering directory `.'
autoreconf: configure.ac: not using Gettext
autoreconf: running: aclocal --force -I m4
autoreconf: configure.ac: tracing
autoreconf: configure.ac: not using Libtool
autoreconf: running: /usr/bin/autoconf --force
autoreconf: running: /usr/bin/autoheader --force
autoreconf: running: automake --add-missing --copy --force-missing
libusb/Makefile.am:5: error: Libtool library used but 'LIBTOOL' is undefined
libusb/Makefile.am:5:   The usual way to define 'LIBTOOL' is to add 'LT_INIT'
libusb/Makefile.am:5:   to 'configure.ac' and run 'aclocal' and 'autoconf' again.
libusb/Makefile.am:5:   If 'LT_INIT' is in 'configure.ac', make sure
libusb/Makefile.am:5:   its definition is in aclocal's search path.
autoreconf: automake failed with exit status: 1

> 解决:  sudo apt-get install libtool
```

#### configure: error: udev support requested but libudev header not installed
```txt
   .....
   checking for inline... inline
   checking operating system... Linux
   checking for library containing clock_gettime2... no
   checking libudev.h usability... no
   checking libudev.h presence... no
   checking for libudev.h... no
   configure: error: udev support requested but libudev header not installed

   # 解决: sudo apt-get install libudev-dev
```

## 参考资料
1. 源码获取:[https://github.com/libusb/libusb](https://github.com/libusb/libusb)