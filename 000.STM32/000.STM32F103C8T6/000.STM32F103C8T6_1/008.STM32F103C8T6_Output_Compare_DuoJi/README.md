# 008.STM32F103C8T6_Output_Compare_DuoJi
&nbsp;&nbsp;PWM 实验

## PWM 控制舵机
&nbsp;&nbsp;舵机是一种根据输入PWM信号占空比来控制输出角度的装置。

&nbsp;&nbsp;输入PWM信号要求: 周期为20ms,高电平宽度为0.5ms ~ 2.5ms
```txt

   周期与频率的关系: 频率 = 1 / 周期 
   若周期为20ms,则频率=1/周期 = 1/20ms = 50/s = 50HZ
    HZ: 次/s

```

### 舵机输出角度与输入信号脉冲关系
<img src="./REF_IMGs/duoji_shuchu_jiaodu-01.png"/>