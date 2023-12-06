#include "stm32f10x.h"
#include "Delay.h"

/**
 * LED 流水灯实验 + 蜂鸣器(低电平触发)
 */
int main(void)
{
    /**
     * 开启GPIOA的时钟,使用各个外设前必须开启时钟，否则对外设的操作无效: 因为LED连接的都是GPIOA端口(A0~A7)，所以需要打开GPIOA的时钟
     * 蜂鸣器接在PB12号口,所以GPIOB也要初始化
     */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);

    /**
     * 初始化GPIOA
     */
    GPIO_InitTypeDef GPIOA_InitStructure;
    GPIOA_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIOA_InitStructure.GPIO_Pin = (GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_12);
    GPIOA_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIOA_InitStructure);

    /**
     * 初始化GPIOB
     */
    GPIO_InitTypeDef GPIOB_InitStructure;
    GPIOB_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIOB_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIOB_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIOB_InitStructure);

    for (;;)
    {
        for (uint16_t i = 0; i <= 7; i++)
        {
            // 低电平点亮，所以需要取反
            GPIO_Write(GPIOA, ~(0x0001 << i));
            if ((i >> 2) == 0)
            {
                // 低电平触发蜂鸣器，此时蜂鸣器会响
                GPIO_ResetBits(GPIOB, GPIO_Pin_12);
            }
            else
            {
                // 低电平触发蜂鸣器，此时蜂鸣器不会响
                GPIO_SetBits(GPIOB, GPIO_Pin_12);
            }

            // 延迟300ms
            Delay_ms(100);
        }
    }

    return 0;
}
