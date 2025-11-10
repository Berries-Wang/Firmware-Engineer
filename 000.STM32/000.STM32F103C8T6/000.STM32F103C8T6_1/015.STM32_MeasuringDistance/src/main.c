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
 *
 * PA8: TIM1_CH1
 * PA9: TIM1_CH2
 */
int main(int argc, char **argv)
{
    // 配置时钟树RCC
    init_HSE_RCC();

    {
        // 配置时钟来源: 这个还是得根据“Figure 8. Clock tree”来配置
        SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
        // 设置重载值
        SysTick_Config(72 * 100);
        NVIC_SetPriority(SysTick_IRQn, -1);
    }

    // 通过阅读手册：[stm32f103c8.pdf]#`Figure 1. STM32F103xx performance line block diagram`，TIM1挂载在APB2总线上，因此需要使能APB2总线时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_TIM1 | RCC_APB2Periph_AFIO, ENABLE);

    { // channel 初始化
        GPIO_InitTypeDef gpioBInitConfig;
        gpioBInitConfig.GPIO_Pin = GPIO_Pin_8;
        gpioBInitConfig.GPIO_Speed = GPIO_Speed_50MHz;
        gpioBInitConfig.GPIO_Mode = GPIO_Mode_IPD;
        GPIO_Init(GPIOA, &gpioBInitConfig);
        // 禁用霍尔模式
        TIM_SelectHallSensor(TIM1, DISABLE);
    }

    // 初始化GPIO
    { // PB9 接LED PB8接Trig
        GPIO_InitTypeDef gpioInitConfig;
        gpioInitConfig.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_8;
        gpioInitConfig.GPIO_Mode = GPIO_Mode_Out_PP;
        gpioInitConfig.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOB, &gpioInitConfig);
        // 先把灯点亮
        GPIO_SetBits(GPIOB, GPIO_Pin_9);
    }

    { // 配置定时器TIM
        TIM_SetClockDivision(TIM1, TIM_CKD_DIV1);
        // Step1. 配置时基单元
        TIM_TimeBaseInitTypeDef timeBaseInitConfig;
        /**
         * CK_CNT = 72MHZ/(72-1+1)=1KHZ 即 1000000HZ，即时钟周期为1us
         */
        timeBaseInitConfig.TIM_Prescaler = (72 - 1);
        timeBaseInitConfig.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数
        timeBaseInitConfig.TIM_Period = (65535 - 1);             // 设置自动重装计数器
        timeBaseInitConfig.TIM_ClockDivision = TIM_CKD_DIV1;
        timeBaseInitConfig.TIM_RepetitionCounter = 0; // 重复计数器的值
        TIM_TimeBaseInit(TIM1, &timeBaseInitConfig);
        // 打开ARR寄存器的预加载功能
        TIM_ARRPreloadConfig(TIM1, ENABLE);
    }

    { // 配置输入捕获，需要针对于定时器的通道来进行配置
        TIM_ICInitTypeDef icInitConfig;
        icInitConfig.TIM_Channel = TIM_Channel_1;
        icInitConfig.TIM_ICPolarity = TIM_ICPolarity_Rising;
        icInitConfig.TIM_ICSelection = TIM_ICSelection_DirectTI;
        icInitConfig.TIM_ICPrescaler = TIM_ICPSC_DIV1;
        icInitConfig.TIM_ICFilter = 0x0C;
        // 初始化通道1
        TIM_ICInit(TIM1, &icInitConfig);

        // 初始化与通道1相互引用的通道2,但是通道2需要设置为间接
        icInitConfig.TIM_Channel = TIM_Channel_2;
        icInitConfig.TIM_ICPolarity = TIM_ICPolarity_Falling; // 记录反射回来的时候的值
        icInitConfig.TIM_ICSelection = TIM_ICSelection_IndirectTI;
        TIM_ICInit(TIM1, &icInitConfig);
    }

    TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Enable);
    TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Enable);

    // 开启定时器
    TIM_Cmd(TIM1, ENABLE);

    for (;;)
    {
        // 重置CCR寄存器(俩都要)
        TIM_SetCompare1(TIM1, 0);
        TIM_SetCompare2(TIM1, 0);

        // 发射10us的脉冲
        GPIO_SetBits(GPIOB, GPIO_Pin_8);
        /**
         * for执行一次，需要消耗8个指令周期
         */
        for (uint8_t i = 0; i < 10; i++)
            ;
        // 脉冲发射完毕
        GPIO_ResetBits(GPIOB, GPIO_Pin_8);

        // 等待发射&回应
        uint8_t success = 0;
        uint16_t ccr1_val = 0, ccr2_val = 0;
        for (;;)
        {
            // 获取ccr1 ccr2的值
            ccr1_val = TIM_GetCapture1(TIM1);
            ccr2_val = TIM_GetCapture2(TIM1);
            if (ccr1_val > 0 && ccr2_val > 0)
            {
                success = 1;
            }
            if (success)
            {
                // 距离(cm) = (ccr2_val - ccr1_val) * (脉宽) * 340*100 /2 , 脉宽为1us
                uint16_t distance_cm = (ccr2_val - ccr1_val) * (1 / 1000 / 1000) * 340 * 100 / 2;
                // 如果距离小于20cm，则亮灯
                if (distance_cm <= 30)
                {
                    GPIO_SetBits(GPIOB, GPIO_Pin_9);
                }
                else
                { // 超过了，那么不亮了
                    GPIO_ResetBits(GPIOB, GPIO_Pin_9);
                }
            }
        }
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