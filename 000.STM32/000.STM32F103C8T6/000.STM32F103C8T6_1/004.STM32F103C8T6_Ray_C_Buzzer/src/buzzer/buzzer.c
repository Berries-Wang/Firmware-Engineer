#include "buzzer.h"

void init_buzzer()
{
    GPIO_InitTypeDef GPIOB_InitStructure;
    GPIOB_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIOB_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIOB_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIOB_InitStructure);
}

void buzzer_on()
{
    GPIO_ResetBits(GPIOB, GPIO_Pin_12);
}

void buzzer_off()
{
    GPIO_SetBits(GPIOB, GPIO_Pin_12);
}