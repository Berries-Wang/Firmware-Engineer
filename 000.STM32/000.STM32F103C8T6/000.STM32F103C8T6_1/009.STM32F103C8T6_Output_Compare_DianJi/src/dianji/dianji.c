#include "dianji.h"

void dianji_init()
{

    // 点击方向控制
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef gpioInitData;
    gpioInitData.GPIO_Mode = GPIO_Mode_Out_PP;
    gpioInitData.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
    gpioInitData.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &gpioInitData);

    pwm_init();
}

/**
 * speed > 0 正向转;反之，反向转;
*/
void set_dianji_speed(int8_t speed)
{
    if (speed > 0)
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_4);
        GPIO_ResetBits(GPIOA, GPIO_Pin_5);

        pwm_setCompare3(speed);
    }
    else 
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_5);
        GPIO_ResetBits(GPIOA, GPIO_Pin_4);

        pwm_setCompare3(-speed);
    }
}