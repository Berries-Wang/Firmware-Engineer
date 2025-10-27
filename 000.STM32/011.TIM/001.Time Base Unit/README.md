# Time Base Unit (时基单元)
学习 [[STM32 HAL库][定时器]时基单元，最佳教程，没有之一~](../999.IMG/1593167269-1-192.mp4)  & [[定时器]时基单元(补充)，最佳教程，没有之一~](../999.IMG/1597015420-1-192.mp4)

![wechat_2025-10-27_230508_269.png](../999.IMG/wechat_2025-10-27_230508_269.png)
- 分频(降频): 分频后频率 = 输入频率 / (${PSC} + 1); <sub>为什么+1,因为计数是从0开始的</sub>
- 计数器： 对输入脉冲进行计数，每计满一个定时周期就溢出一次
- 重复计数（RCR）： 每当计数器CNT溢出一次，重复计数RCR就会+1,当重复计数值达到(${RCR}+1)<sub>为什么+1,因为计数是从0开始的</sub>，那么就会产生update事件。 
- 图中阴影是“shadow register”(影子寄存器)<sub>视频中详细说明了其功能</sub>,其功能是寄存器的预加载功能,在某个事件中替换活动寄存器的值--防止跑飞


## 手册中的时基单元
> [Figure 52. Advanced-control timer block diagram](../../../002.REF_DOCS/rm0008-stm32f101xx-stm32f102xx-stm32f103xx-stm32f105xx-and-stm32f107xx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)

![wechat_2025-10-28_070506_108.png](./../999.IMG/wechat_2025-10-28_070506_108.png)