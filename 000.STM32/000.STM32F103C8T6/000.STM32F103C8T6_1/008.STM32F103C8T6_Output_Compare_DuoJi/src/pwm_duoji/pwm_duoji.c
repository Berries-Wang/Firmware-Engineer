#include "pwm_duoji.h"

void pwm_init()
{
    // 1. 开启时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    // 2. 使用内部时钟
    TIM_InternalClockConfig(TIM2);

    // 3. 配置时基单元
    TIM_TimeBaseInitTypeDef tim_TimeBaseInitStru;
    tim_TimeBaseInitStru.TIM_ClockDivision = TIM_CKD_DIV1;
    tim_TimeBaseInitStru.TIM_CounterMode = TIM_CounterMode_Up; /*计数器模式*/
    // CK_CNT_OV = CK_CNT / (ARR + 1) = CK_PSC / (PSC + 1) / (ARR + 1)
    // CK_PSC = 72MHZ , ARR = ${TIM_Period} , PSC = ${TIM_Prescaler} = 72MHZ / 7200 / 10000 = 10KHZ   (HZ，即 次/s) , 即，在10KHZ的频率下计10000个数，那就是每秒计一次数
    tim_TimeBaseInitStru.TIM_Period = 20000 - 1;
    tim_TimeBaseInitStru.TIM_Prescaler = 72 - 1;
    tim_TimeBaseInitStru.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &tim_TimeBaseInitStru);

    // 初始化输出比较单元
    TIM_OCInitTypeDef timOCInitType;
    TIM_OCStructInit(&timOCInitType);
    timOCInitType.TIM_OCMode = TIM_OCMode_PWM1;
    timOCInitType.TIM_OCPolarity = TIM_OCPolarity_High;
    timOCInitType.TIM_OutputState = TIM_OutputState_Enable;
    timOCInitType.TIM_Pulse = 0; // 设置CCR 值，占空比: 计算公式见: 001.嵌入式知识库/003.INTERRUPT/000.STM32F103C8T6/001.TIM中断.md
    TIM_OC2Init(TIM2, &timOCInitType);

    // 初始化GPIO
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef gpioInit;
    gpioInit.GPIO_Mode = GPIO_Mode_AF_PP;
    gpioInit.GPIO_Pin = GPIO_Pin_1;
    gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &gpioInit);

    // 6.启动定时器
    TIM_Cmd(TIM2, ENABLE);
}

void pwm_setCompare2(uint16_t compareVal)
{
    TIM_SetCompare2(TIM2, compareVal);
}