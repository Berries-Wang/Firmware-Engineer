#include "led.h"
#include "stm32f10x.h"

/**
 * LED 接在A0口，则需要初始化GPIOA
 */
void led_init()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
 * 低电平触发模式，所以，将A0置为低电平灯亮
 */
void led_on()
{
    GPIO_ResetBits(GPIOA, GPIO_Pin_0);
}

/**
 * 低电平触发模式，所以，将A0置为高电平灯灭
 */
void led_off()
{
    GPIO_SetBits(GPIOA, GPIO_Pin_0);
}

void led_turn()
{
    if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0) == 0) // 如果灯亮
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_0); // 关灯
    }
    else
    {
        GPIO_ResetBits(GPIOA, GPIO_Pin_0); // 开灯
    }
}