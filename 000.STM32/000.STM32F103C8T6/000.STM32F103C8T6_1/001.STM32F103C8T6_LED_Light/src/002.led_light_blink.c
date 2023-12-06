#include "stm32f10x.h"
#include "Delay.h"

/**
 * 通过README.md 可以知晓接，A0接的是负极，那么只有是低电平时才有电流通过，灯才会亮。
 * 测试：
 *    A0接LED正极，预测: 只有A0为高电平时才会亮灯. 测试结果: 当LED的正极接入到A0,LED另一端接入到负极,那么此时只有A0是高电平时灯才会亮.
 */
int main(void)
{
    // 开启GPIOA的时钟,使用各个外设前必须开启时钟，否则对外设的操作无效
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_InitStructure);

    while (1)
    {
        // 设置低电平，亮灯
        GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);

        // 延迟300ms
        Delay_ms(300);

        // 设置高电平，灭灯
        GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);

        // 延迟300ms
        Delay_ms(300);
    }
    return 0;
}
