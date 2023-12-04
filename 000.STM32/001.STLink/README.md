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
## 参考资料
1. [github: stlink-org/stlink](https://github.com/stlink-org/stlink)