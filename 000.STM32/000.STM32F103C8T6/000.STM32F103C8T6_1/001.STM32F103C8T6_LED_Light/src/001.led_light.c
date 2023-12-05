#include "stm32f10x.h"

int main(void)
{
    // 开启GPIOC的时钟,使用各个外设前必须开启时钟，否则对外设的操作无效
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // GPIO_SetBits(GPIOC, GPIO_Pin_13);
    //GPIO_ResetBits(GPIOC, GPIO_Pin_13);

    // 设置低电平，亮灯
    GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);

    while (1)
    {
        // do nothing
    }
    return 0;
}