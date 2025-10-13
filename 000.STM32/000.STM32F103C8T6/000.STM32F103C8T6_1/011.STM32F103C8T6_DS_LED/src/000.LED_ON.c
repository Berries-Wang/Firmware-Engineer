#include "stm32f10x.h"

/**
 * 低电平启动
 */
int main(int argc, char **argv)
{
    // 启用或禁用高速APB（APB2）外设时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef gpioInitTypeDef;
    gpioInitTypeDef.GPIO_Pin = GPIO_Pin_0;
    gpioInitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
    gpioInitTypeDef.GPIO_Mode = GPIO_Mode_Out_PP;

    // 初始化GPIOA
    GPIO_Init(GPIOA, &gpioInitTypeDef);
    while (1)
    {
        // 置为高电平
        // GPIO_SetBits(GPIOA, GPIO_Pin_0);

        // 置为低电平启动
        GPIO_ResetBits(GPIOA, GPIO_Pin_0);
    }

    return 0;
}