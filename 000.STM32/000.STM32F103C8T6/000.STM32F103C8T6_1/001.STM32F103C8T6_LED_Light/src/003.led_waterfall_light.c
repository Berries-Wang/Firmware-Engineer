#include "stm32f10x.h"
#include "Delay.h"

/**
 * LED 流水灯实验
 */
int main(void)
{
    // 开启GPIOA的时钟,使用各个外设前必须开启时钟，否则对外设的操作无效: 因为连接的都是GPIOA端口(A0~A7)，所以需要打开GPIOA的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_InitStructure);

    for (;;)
    {
        for (uint16_t i = 0; i <= 7; i++)
        {
            // 低电平点亮，所以需要取反
            GPIO_Write(GPIOA, ~(0x0001 << i));

            // 延迟300ms
            Delay_ms(300);
        }
    }

    return 0;
}
