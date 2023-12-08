#include "ray.h"

void init_ray()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    // 配置为上拉输入模式
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;

    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

uint8_t ray_light()
{
    return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13);
}
