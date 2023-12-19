// 旋转编码器触发中断
#include "stm32f10x.h"
#include "OLED.h"

// 其实是正负脉冲数量
static int16_t COUNT = 0;

int16_t getCount();
void init_Encoder();

/**
 * 变量,编码器正向转做加法;反向转做减法;
 */

int main(int argc, char **argv)
{
    // 初始化OLED
    OLED_Init();
    init_Encoder();
    int16_t num_count = 0;
    OLED_ShowString(1, 1, "Num:");
    for (;;)
    {
        num_count += getCount();
        OLED_ShowSignedNum(1, 5, num_count, 5);
    }

    return 0;
}

/**
 * 初始化编码器
 * 通过文档:001.嵌入式知识库/003.INTERRUPT/000.STM32F103C8T6/000.EXTI中断.md , 需要打通GPIO输入、AFIO 、 EXTI 、 NVIC
 */
void init_Encoder()
{
    { /*初始化GPIO*/
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
        GPIO_InitTypeDef GPIO_InitStru;
        GPIO_InitStru.GPIO_Mode = GPIO_Mode_IPU;
        GPIO_InitStru.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
        GPIO_InitStru.GPIO_Speed = GPIO_Speed_50MHz;

        GPIO_Init(GPIOB, &GPIO_InitStru);
    }
    { /*AFIO初始化*/
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
        GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);
        GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);
    }

    // 配置EXTI
    {
        EXTI_InitTypeDef EXTI_InitStructure;
        EXTI_InitStructure.EXTI_Line = EXTI_Line1 | EXTI_Line0;
        EXTI_InitStructure.EXTI_LineCmd = ENABLE;
        EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
        // 下降沿
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
        EXTI_Init(&EXTI_InitStructure);
    }

    // 配置NVIC
    {
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

        NVIC_InitTypeDef NVIC_InitTypeDef0;
        NVIC_InitTypeDef0.NVIC_IRQChannel = EXTI0_IRQn;
        NVIC_InitTypeDef0.NVIC_IRQChannelPreemptionPriority = 1;
        NVIC_InitTypeDef0.NVIC_IRQChannelSubPriority = 1;
        NVIC_InitTypeDef0.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitTypeDef0);

        NVIC_InitTypeDef NVIC_InitTypeDef1;
        NVIC_InitTypeDef1.NVIC_IRQChannel = EXTI1_IRQn;
        NVIC_InitTypeDef1.NVIC_IRQChannelPreemptionPriority = 1;
        NVIC_InitTypeDef1.NVIC_IRQChannelSubPriority = 2;
        NVIC_InitTypeDef1.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitTypeDef1);
    }
}

int16_t getCount()
{
    int16_t temp = COUNT;
    COUNT = 0;
    return temp;
}

void EXTI0_IRQHandler()
{
    if (EXTI_GetITStatus(EXTI_Line0) == SET)
    {
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
        {
            COUNT--;
        }
        // 中断标识位清除
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}

void EXTI1_IRQHandler()
{
    if (EXTI_GetITStatus(EXTI_Line1) == SET)
    {
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0)
        {
            COUNT++;
        }
        // 中断标识位清除
        EXTI_ClearITPendingBit(EXTI_Line1);
    }
}