#include "stm32f10x.h"
#include "stm32f10x_exti.h"
#include "misc.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include <math.h>
#include "stm32f10x_rtc.h"
#include "stm32f10x_it.h"
#include "Delay.h"

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

    { // 初始化GPIO口: 灯
        GPIO_InitTypeDef gpioInitConfigPB = {
            .GPIO_Pin = GPIO_Pin_12,
            .GPIO_Speed = GPIO_Speed_50MHz,
            .GPIO_Mode = GPIO_Mode_IPD,
        };
        GPIO_Init(GPIOB, &gpioInitConfigPB);
    }

    { //  看手册，TIM1_CH1 对应PA8

        TIM_TimeBaseInitTypeDef timeBaseInitConfig = {
            .TIM_Prescaler = 72 - 1,               // PSC： 预分频器,降频 , 1MHZ
            .TIM_CounterMode = TIM_CounterMode_Up, //
            .TIM_Period = 0xFFFF,                  // ARR
            .TIM_ClockDivision = TIM_CKD_DIV1,     //
            .TIM_RepetitionCounter = 0             // RCR ,目前配置输入捕获,应该不用配置吧
        };
        TIM_TimeBaseStructInit(&timeBaseInitConfig);
        // 配置自动重装寄存器(ARR)的预加载功能
        TIM_ARRPreloadConfig(TIM1, ENABLE);

        GPIO_InitTypeDef gpioInitConfigPA7 = {
            // trig
            .GPIO_Pin = GPIO_Pin_7,
            .GPIO_Speed = GPIO_Speed_50MHz,
            .GPIO_Mode = GPIO_Mode_Out_PP,
        };
        GPIO_Init(GPIOA, &gpioInitConfigPA7);

        GPIO_InitTypeDef gpioInitConfigPA8 = {
            // echo
            .GPIO_Pin = GPIO_Pin_8,
            .GPIO_Speed = GPIO_Speed_50MHz,
            .GPIO_Mode = GPIO_Mode_IN_FLOATING,
        };
        GPIO_Init(GPIOA, &gpioInitConfigPA8);
    }

    { // 输入滤波: 过滤掉信号中的毛刺 -> 边沿检测 -> 信号选择 -> 分频 -> 事件(ICPS)

        // 定时器1的配置: 配置为输入捕获


        // 配置通道1
        TIM_ICInitTypeDef icInitConfig = {
            .TIM_Channel = TIM_Channel_1,                // 配置输入渠道
            .TIM_ICPolarity = TIM_ICPolarity_Rising,     // 配置边沿检测
            .TIM_ICSelection = TIM_ICSelection_DirectTI, // 配置信号选择
            .TIM_ICPrescaler = TIM_ICPSC_DIV1,           // 配置预分频系数
            .TIM_ICFilter = 0x0};                        // 配置输入滤波器,不滤波
        TIM_ICInit(TIM1, &icInitConfig);

        // 其实还是配置通道1
        TIM_ICInitTypeDef icInitConfig_2 = {
            .TIM_Channel = TIM_Channel_2,                  // 配置输入渠道
            .TIM_ICPolarity = TIM_ICPolarity_Falling,      // 配置边沿检测
            .TIM_ICSelection = TIM_ICSelection_IndirectTI, // 配置信号选择
            .TIM_ICPrescaler = TIM_ICPSC_DIV1,             // 配置预分频系数
            .TIM_ICFilter = 0x0};                          // 配置输入滤波器
        TIM_ICInit(TIM1, &icInitConfig_2);
    }

    for (;;)
    {
        // 向CNT值设置为0
        TIM_SetCounter(TIM1, 0);

        // 清除cc1 cc2标志位
        TIM_ClearFlag(TIM1, TIM_FLAG_CC1);
        TIM_ClearFlag(TIM1, TIM_FLAG_CC2);
        // 启动定时器
        TIM_Cmd(TIM1, ENABLE);
        TIM_ITConfig(TIM1, TIM_IT_CC1, ENABLE);
        TIM_ITConfig(TIM1, TIM_IT_CC2, ENABLE);
        {
            // 打开捕获比较功能
            TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Enable);
            TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Enable);
        }

        // 发射10us的脉冲
        GPIO_SetBits(GPIOA, GPIO_Pin_7);
        Delay_us(15);
        // 脉冲发射完毕
        GPIO_ResetBits(GPIOA, GPIO_Pin_7);

        // 等待发射&回应
        uint8_t success = 0;
        for (;;)
        {
            /**
             * 获取标识位: TIMx_SR 寄存器, 查看手册: "14.3.6  Input capture mode"
             */
            FlagStatus ccr1_flag = TIM_GetFlagStatus(TIM1, TIM_FLAG_CC1);
            FlagStatus ccr2_flag = TIM_GetFlagStatus(TIM1, TIM_FLAG_CC2);
            // 都测量成功
            if (ccr1_flag == SET && ccr2_flag == SET)
            {
                success = 1;
                break;
            }
        }

        // 打开捕获比较功能
        TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Disable);
        TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Disable);
        TIM_Cmd(TIM1, DISABLE);

        // 如果测量成功
        if (success)
        {
            uint16_t ccr1_val = TIM_GetCapture1(TIM1);
            uint16_t ccr2_val = TIM_GetCapture2(TIM1);
            // 距离(cm) = (ccr2_val - ccr1_val) * (脉宽) * 340*100 /2 , 脉宽为1us
            float pulse_width = (ccr2_val - ccr1_val) * 1e-6f;
            float distance_cm = 340.0f * 100 * pulse_width / 2.0f;
            // 如果距离小于20cm，则亮灯
            if (distance_cm <= 20)
            {
                GPIO_SetBits(GPIOB, GPIO_Pin_12);
            }
            else
            { // 超过了，那么不亮了
                GPIO_ResetBits(GPIOB, GPIO_Pin_12);
            }
        } 
        // 置位
        success = 0;
        Delay_ms(60);
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