# Advanced-control timers (高级定时器)
The advanced-control timers (TIM1 and TIM8) consist of a 16-bit auto-reload counter driven by a programmable prescaler.(高级控制定时器（TIM1和TIM8）由可编程预分频器驱动的16位自动重载计数器组成)

It may be used for a variety of purposes, including measuring the pulse lengths of input signals (input capture) or generating output waveforms (output compare, PWM, complementary PWM with dead-time insertion)（其用途广泛，既可测量输入信号的脉冲宽度（输入捕获），也能生成输出波形（输出比较、PWM、带死区插入的互补PWM））

Pulse lengths and waveform periods can be modulated from a few microseconds to several milliseconds using the timer prescaler and the RCC clock controller prescalers (通过定时器预分频器和RCC时钟控制器预分频器，可将脉冲宽度与波形周期调制范围从数微秒至数毫秒。)