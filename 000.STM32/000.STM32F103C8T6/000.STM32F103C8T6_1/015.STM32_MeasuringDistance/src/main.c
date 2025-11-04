#include "stm32f10x.h"
#include "stm32f10x_exti.h"
#include "misc.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include <math.h>
#include "stm32f10x_rtc.h"
#include "stm32f10x_it.h"

void init_HSE_RCC();
void init_RCC_from_HSE();
/**
 * 使用定时器输出比较功能产生PWM波形，实现呼吸灯功能
 */
int main(int argc, char **argv)
{
    // 配置时钟树RCC
    init_HSE_RCC();

    {
        // 配置时钟来源: 这个还是得根据“Figure 8. Clock tree”来配置
        SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
        // 设置重载值 
        SysTick_Config(72*100);
        NVIC_SetPriority(SysTick_IRQn, -1);
    }

    // 通过阅读手册：[stm32f103c8.pdf]#`Figure 1. STM32F103xx performance line block diagram`，TIM1挂载在APB2总线上，因此需要使能APB2总线时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_TIM1, ENABLE);

    { // 配置定时器TIM
        // Step1. 配置时基单元
        TIM_TimeBaseInitTypeDef timeBaseInitConfig;
        /**
         * CK_CNT = 72MHZ/(720-1+1)=1KHZ 即 10000HZ，即时钟周期为1ms
         */
        timeBaseInitConfig.TIM_Prescaler = (720 - 1);
        timeBaseInitConfig.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数
        timeBaseInitConfig.TIM_Period = (100 - 1);               // 设置自动重装计数器
        timeBaseInitConfig.TIM_ClockDivision = TIM_CKD_DIV1;
        timeBaseInitConfig.TIM_RepetitionCounter = 0; // 重复计数器的值
        TIM_TimeBaseInit(TIM1, &timeBaseInitConfig);
    }

    { // 配置输入比较，需要针对于定时器的通道来进行配置
        TIM_OCInitTypeDef timeOCInitConfig;
        timeOCInitConfig.TIM_OCMode = TIM_OCMode_PWM1;               // 输出PWM波形
        timeOCInitConfig.TIM_OutputState = TIM_OutputState_Enable;   // 正常输出
        timeOCInitConfig.TIM_OutputNState = TIM_OutputNState_Enable; // 互补输出
        timeOCInitConfig.TIM_Pulse = 90;
        timeOCInitConfig.TIM_OCPolarity = TIM_OCPolarity_High;
        timeOCInitConfig.TIM_OCNPolarity = TIM_OCNPolarity_High;
        timeOCInitConfig.TIM_OCIdleState = TIM_OCIdleState_Reset;
        timeOCInitConfig.TIM_OCNIdleState = TIM_OCIdleState_Reset;
        TIM_OC1Init(TIM1, &timeOCInitConfig);
    }

    // 开启定时器
    TIM_Cmd(TIM1, ENABLE);

    for (;;)
    {
       
    }

    return 0;
}

void init_HSE_RCC()
{
    /**
     * 选择HSE作为时钟来源
     * 参考资料: 000.STM32/006.RCC/README.md
     */
    init_RCC_from_HSE();
}

/**
 * 选择HSE作为时钟来源
 * 参考资料: 000.STM32/006.RCC/README.md
 */
void init_RCC_from_HSE()
{
    { /**
       * 只有SYSCLK <= 8M 时才能设置FLASH,默认时钟来源就是HSI，恰好是8MHZ
       *
       * 为什么要设置FLASH： 程序是存储在FLASH中，CPU需要从FLASH中获取指令
       */
        /**
         * 打开FLASH预取
         */
        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

        /**
         * 当SYSCLK <= 72MHZ时，需要等待2个周期
         */
        FLASH_SetLatency(FLASH_Latency_2);
    }

    // 打开HSE
    {
        RCC_HSEConfig(RCC_HSE_ON);
        while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET)
            ;
    }

    // 配置锁相环: 配置之后，SYSCLK就是72MHZ
    {
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

        // 打开锁相环
        RCC_PLLCmd(ENABLE);

        // 锁相环开启需要时间，查询标志位，判断锁相环是否开启完成
        while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
            ;
    }

    // 配置SYSCLK，即配置系统时钟
    RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);

    // 配置AHB
    RCC_HCLKConfig(RCC_SYSCLK_Div1);

    // 配置APB1: 配置为36MHZ，因为APB1最大就是36MHZ
    RCC_PCLK1Config(RCC_HCLK_Div2);

    // 配置APB2 = SYSCLK = 72MHZ
    RCC_PCLK2Config(RCC_HCLK_Div1);

    // 关闭HSI,默认就是HSI
    RCC_HSICmd(DISABLE);
}