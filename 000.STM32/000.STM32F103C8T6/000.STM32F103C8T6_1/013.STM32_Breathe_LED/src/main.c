#include "stm32f10x.h"
#include "Delay.h"
#include "stm32f10x_exti.h"
#include "misc.h"
#include "stm32f10x_tim.h"

/**
 * 使用定时器输出比较功能产生PWM波形，实现呼吸灯功能
 */
int main(int argc, char **argv)
{
    // 通过阅读手册：[stm32f103c8.pdf]#`Figure 1. STM32F103xx performance line block diagram`，TIM1挂载在APB2总线上，因此需要使能APB2总线时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 | RCC_APB2Periph_GPIOA, ENABLE);
    {// 配置定时器TIM


    }

    while (1)
        ;

    return 0;
}