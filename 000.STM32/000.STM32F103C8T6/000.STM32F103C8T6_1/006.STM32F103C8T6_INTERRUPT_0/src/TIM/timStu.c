#include "timStu.h"

static uint16_t NUM = 0;

/**
 * 使用内部时钟中断
 */
void Timer_Init()
{
    // 1. 开启时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    // 2. 使用内部时钟
    TIM_InternalClockConfig(TIM2);

    // 3. 配置时基单元
    TIM_TimeBaseInitTypeDef tim_TimeBaseInitStru;
    tim_TimeBaseInitStru.TIM_ClockDivision = TIM_CKD_DIV1;
    tim_TimeBaseInitStru.TIM_CounterMode = TIM_CounterMode_Up; /*计数器模式*/
    // 计数器溢出频率: CK_CNT_OV = CK_CNT / (ARR + 1) = CK_PSC / (PSC + 1) / (ARR + 1)
    // CK_PSC = 72MHZ , ARR = ${TIM_Period} , PSC = ${TIM_Prescaler} = 72MHZ / 7200 / 10000 = 1HZ   (HZ，即 1次/s) , 即，在10KHZ的频率下计10000(${TIM_Period})个数，那就是每秒计一次数
    // 对72MHZ进行7200分频，得到10K的计数频率
    tim_TimeBaseInitStru.TIM_Period = 10000 - 1;    // ARR 自动重装器的值
    tim_TimeBaseInitStru.TIM_Prescaler = 7200 - 1;  // PSC预分频器的值
    tim_TimeBaseInitStru.TIM_RepetitionCounter = 0; // 重复计数器的值
    TIM_TimeBaseInit(TIM2, &tim_TimeBaseInitStru);

    // 4. 使能更新中断
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    // 5. 配置NVIC
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_Init1;
    NVIC_Init1.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_Init1.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_Init1.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init1.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_Init1);

    // 6.启动定时器
    TIM_Cmd(TIM2, ENABLE);
}

/**
 * 外部中断: 使用对射式红外触发中断
 */
void Timer_External_Init()
{
    // 1. 开启时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // 初始化GPIO
    GPIO_InitTypeDef gpioInit;
    gpioInit.GPIO_Mode = GPIO_Mode_IPU;
    gpioInit.GPIO_Pin = GPIO_Pin_0;
    gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &gpioInit);

    // 2. 通过ETR引脚的外部时钟模式2配置
    TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0x00);

    // 3. 配置时基单元
    TIM_TimeBaseInitTypeDef tim_TimeBaseInitStru;
    tim_TimeBaseInitStru.TIM_ClockDivision = TIM_CKD_DIV1;
    tim_TimeBaseInitStru.TIM_CounterMode = TIM_CounterMode_Up; /*计数器模式*/
 tim_TimeBaseInitStru.TIM_Period = 10 - 1;
    // 关闭分频器,那就遮挡一下就会触发一次中断
    tim_TimeBaseInitStru.TIM_Prescaler = 1 - 1;
    tim_TimeBaseInitStru.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &tim_TimeBaseInitStru);

    // 4. 使能更新中断
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    // 5. 配置NVIC
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_Init1;
    NVIC_Init1.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_Init1.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_Init1.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init1.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_Init1);

    // 6.启动定时器
    TIM_Cmd(TIM2, ENABLE);
}

void TIM2_IRQHandler()
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET) /*检查中断位置*/
    {
        NUM++;
        // 清除中断位
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}

uint16_t getNum()
{
    return NUM;
}