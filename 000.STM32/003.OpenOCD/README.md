# STMicroelectronics/OpenOCD
&nbsp;&nbsp;目的是为了调试STM32,所以使用 STMicroelectronics/OpenOCD
> 请阅读:[000.STM32/003.OpenOCD/000.OpenOCD_SOURCE_CODE/README.md](./000.OpenOCD_SOURCE_CODE/README.md)
## 从源码安装
```txt
   1. 获取源码:
        git clone git@github.com:STMicroelectronics/OpenOCD.git
   2. 切换到发布分支/标签: 通过github下release可以查看到发布分支/标签
        git checkout v0.12.0  # 通过项目主页(github) Releases可以发现，最近发布分支/标签: v0.12.0
   3. 使用如下命令进行构建
      3.1 ./bootstrap (when building from the git repository)
      # 指定安装目录： ./configure --help 即可输出手册，内含指定安装目录的方式.
      3.2 ./configure --prefix=/home/wei/WorkSpace/open_source/Firmware-Engineer/000.STM32/003.OpenOCD/000.OpenOCD_SOURCE_CODE/000.OpenOCD_v0.12.0/OpenOCD-INSTALL-DIR/000.PREFIX  --exec-prefix=/home/wei/WorkSpace/open_source/Firmware-Engineer/000.STM32/003.OpenOCD/000.OpenOCD_SOURCE_CODE/000.OpenOCD_v0.12.0/OpenOCD-INSTALL-DIR/001.EPREFIX 
      3.3  make
      3.4 sudo make install 
```

### 编译问题
1. jimtcl not found, run git submodule init and git submodule update.
   + 原因: 代码clone下来后，不能将项目中.git目录删除.

2. 点击调试，卡在: Launching GDB: arm-none-eabi-gdb -q --interpreter=mi2
1-gdb-version
   ```txt
      执行一下命令: arm-none-eabi-gdb -q --interpreter=mi2,就能看到问题。
      arm-none-eabi-gdb -q --interpreter=mi2
      arm-none-eabi-gdb: error while loading shared libraries: libncursesw.so.5: cannot open shared object file: No such file or directory

      安装库: sudo apt install libncursesw5

      再执行一下:  Launching GDB: arm-none-eabi-gdb -q --interpreter=mi2 可以发现缺少 libpython3.6m.so.1.0 库，
      arm-none-eabi-gdb -q --interpreter=mi2
      arm-none-eabi-gdb: error while loading shared libraries: libpython3.6m.so.1.0: cannot open shared object file: No such file or directory
      处理: 
      cd /usr/lib/x86_64-linux-gnu/
      $ sudo ln -s libpython3.8.so.1.0 libpython3.6m.so.1.0
   ```