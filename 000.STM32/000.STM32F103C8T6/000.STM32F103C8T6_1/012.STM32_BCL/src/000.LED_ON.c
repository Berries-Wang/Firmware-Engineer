#include "stm32f10x.h"
#include "Delay.h"

/**
 * 低电平启动
 */
int main(int argc, char **argv)
{

    { // 初始化按钮
      // 启用或禁用高速APB（APB2）外设时钟
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA, ENABLE);

        GPIO_InitTypeDef gpioInitTypeDef;
        gpioInitTypeDef.GPIO_Pin = GPIO_Pin_0;
        gpioInitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
        gpioInitTypeDef.GPIO_Mode = GPIO_Mode_IPU; // 使用上拉输入

        // 初始化GPIOA
        GPIO_Init(GPIOB, &gpioInitTypeDef);
    }

    { // 初始化LED

        GPIO_InitTypeDef gpioInitTypeDef_LED;
        gpioInitTypeDef_LED.GPIO_Pin = GPIO_Pin_0;
        gpioInitTypeDef_LED.GPIO_Speed = GPIO_Speed_50MHz;
        gpioInitTypeDef_LED.GPIO_Mode = GPIO_Mode_Out_PP; // 推挽输出

        // 初始化GPIOA
        GPIO_Init(GPIOA, &gpioInitTypeDef_LED);
        GPIO_SetBits(GPIOA, GPIO_Pin_0);
    }

    while (1)
    {
      //  读取按钮状态
        if (0 == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0))
        {
            Delay_ms(20);
            // 若按键一直按下
            while (0 == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0));
            Delay_ms(20);
            
            if (0 == GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0))
            {
                GPIO_SetBits(GPIOA, GPIO_Pin_0);
            }
            else
            {
                GPIO_ResetBits(GPIOA, GPIO_Pin_0);
            }
        }
    }

    return 0;
}