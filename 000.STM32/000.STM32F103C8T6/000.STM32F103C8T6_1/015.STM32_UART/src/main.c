#include "stm32f10x.h"

int main(int argc, char **argv)
{

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

     
        GPIO_InitTypeDef gpioInitConfigPB = {
            .GPIO_Pin = GPIO_Pin_12,
            .GPIO_Speed = GPIO_Speed_50MHz,
            .GPIO_Mode = GPIO_Mode_Out_PP,
        };
        GPIO_Init(GPIOB, &gpioInitConfigPB);
    

    GPIO_SetBits(GPIOB, GPIO_Pin_12);

    for (;;)
        ;

    return 0;
}