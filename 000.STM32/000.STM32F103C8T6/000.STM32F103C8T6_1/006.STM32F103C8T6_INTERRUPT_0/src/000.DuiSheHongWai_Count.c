// 红外计数
#include "stm32f10x.h"
#include "OLED.h"

static uint16_t oled_show_count = 0;

int main(int argc, char **argv)
{
    OLED_Init();
    DuiSheHongWai_Count_init();

    OLED_ShowString(1, 1, "COUNT:");

    for (;;)
    {
        OLED_ShowNum(1, 7, oled_show_count, 5);
    }

    return 0;
}

void DuiSheHongWai_Count_init()
{
    // 打开RCC
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    // 配置GPIO
    {
        GPIO_InitTypeDef GPIO_InitStru;
        GPIO_InitStru.GPIO_Mode = GPIO_Mode_IPU;
        GPIO_InitStru.GPIO_Pin = GPIO_Pin_14;
        GPIO_InitStru.GPIO_Speed = GPIO_Speed_50MHz;

        GPIO_Init(GPIOB, &GPIO_InitStru);
    }
    // 配置AFIO
    {
        GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);
    }

    // 配置EXTI
    {
        EXTI_InitTypeDef EXTI_InitStructure;
        EXTI_InitStructure.EXTI_Line = EXTI_Line14;
        EXTI_InitStructure.EXTI_LineCmd = ENABLE;
        EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
        // 下降沿
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
        EXTI_Init(&EXTI_InitStructure);
    }

    // 配置NVIC
    {
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
        NVIC_InitTypeDef NVIC_InitTypeDef;
        NVIC_InitTypeDef.NVIC_IRQChannel = EXTI15_10_IRQn;
        NVIC_InitTypeDef.NVIC_IRQChannelPreemptionPriority = 1;
        NVIC_InitTypeDef.NVIC_IRQChannelSubPriority = 1;
        NVIC_InitTypeDef.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitTypeDef);
    }
}

// 中断函数: 函数名是固定的，见文件:000.STM32/000.STM32F103C8T6/000.STM32F103C8T6_1/002.BASE_LIBS/device_libs/startup_stm32f10x_md.s
void EXTI15_10_IRQHandler()
{
    if (EXTI_GetITStatus(EXTI_Line14) == SET)
    {
        oled_show_count++;
        // 中断标识位清除
        EXTI_ClearITPendingBit(EXTI_Line14);
    }
}