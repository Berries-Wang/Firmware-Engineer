#include "stm32f10x.h"
#include "Delay.h"
#include "stm32f10x_exti.h"
#include "misc.h"

/**
 *
 */
int main(int argc, char **argv)
{
    // 开启GPIOB RCC时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    // 开启AFIO时钟: 因为中断线的映射
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    {
        /**
         * 红外传感器 PB0 ， 上拉输入，那么就是下降沿触发
         */
        GPIO_InitTypeDef gpioInitTypeDef;
        gpioInitTypeDef.GPIO_Pin = GPIO_Pin_0;
        gpioInitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
        gpioInitTypeDef.GPIO_Mode = GPIO_Mode_IPU; // 使用上拉输入

        GPIO_Init(GPIOB, &gpioInitTypeDef);
    }

    { /**
       * 蜂鸣器输出: 低电平触发
       */
        GPIO_InitTypeDef gpioInitTypeDef;
        gpioInitTypeDef.GPIO_Pin = GPIO_Pin_1;
        gpioInitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
        gpioInitTypeDef.GPIO_Mode = GPIO_Mode_Out_PP; // 推挽输出
        GPIO_Init(GPIOB, &gpioInitTypeDef);
        GPIO_SetBits(GPIOB, GPIO_Pin_1);
    }
    // 配置AFIO
    {
        GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);
    }


    { // EXTI Line映射
        EXTI_InitTypeDef exti_init_config;
        exti_init_config.EXTI_Line = EXTI_Line0; // 这个得查阅资料了: 000.STM32/008.STM32-异常/003.STM32异常之EXTI.md#0.2.5 External interrupt/event line mapping
        exti_init_config.EXTI_Mode = EXTI_Mode_Interrupt;
        exti_init_config.EXTI_Trigger = EXTI_Trigger_Rising_Falling; // 上升沿和下降沿都触发
        exti_init_config.EXTI_LineCmd = ENABLE; // 连通中断源与NVIC之间的通道，只有连通了，中断才能传递到NVIC
        EXTI_Init(&exti_init_config);
    }

    { // 配置NVIC: 中断管理，优先级，路由
        // 在NVIC中打开EXTI1
        NVIC_InitTypeDef nvic_init_config;
        nvic_init_config.NVIC_IRQChannel = EXTI0_IRQn;
        /**
         * 参考: 000.STM32/008.STM32-异常/002.Cortex-M之NVIC.md ## Priority grouping
         * 
         * nvic_init_config.NVIC_IRQChannelPreemptionPriority 设置抢占优先级
         */
        nvic_init_config.NVIC_IRQChannelPreemptionPriority = 1;
        nvic_init_config.NVIC_IRQChannelSubPriority = 1;
        nvic_init_config.NVIC_IRQChannelCmd = ENABLE;
        NVIC_SetPriorityGrouping(NVIC_PriorityGroup_2);
        NVIC_Init(&nvic_init_config);
    }


    while (1)
        ;

    return 0;
}

// 中断处理函数
void EXTI0_IRQHandler()
{

    if ((GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0)) == Bit_RESET)
    {
       
         GPIO_SetBits(GPIOB, GPIO_Pin_1);
    }
    else
    {
        // 中断触发，则蜂鸣器工作
        GPIO_ResetBits(GPIOB, GPIO_Pin_1);
    }
    // 中断重置
    EXTI_ClearITPendingBit(EXTI0_IRQn);
}