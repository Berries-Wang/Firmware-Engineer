#include "button.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "Delay.h"

/**
 * 按键是接在B1口
 */
void button_init()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    // 配置为上拉输入模式
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;

    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

uint8_t key_getNum()
{
    uint8_t keyNum = 0;

    if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0) // 如果输出的是低电平
    {
        Delay_ms(20); // 消除按键抖动
        while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
            ;
        Delay_ms(20); // 消除按键抖动
        keyNum = 1;
    }

    return keyNum;
}