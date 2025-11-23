#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "Delay.h"

/**
 * 同putty相互传输数据
 *
 * 1. 发送数据
 * 2. 接收数据
 * 3. 硬件流控
 * 4. 中断接收
 * 5. 总结
 *
 */

/**
 * 初始化RCC
 */
void init_RCC();

/**
 * 初始化USART1
 */
void init_USART();

/**
 * 发送数据
 */
void send_data(u16 cur_data);

u16 receive_data();

int main(int argc, char **argv)
{
    // 初始化RCC时钟
    init_RCC();

    init_USART();

    const char hello_world[] = "Hello World! \n";

    // 间隔一段时间就发送一个Hello World
    for (;;)
    {
        for (u32 idx = 0; idx < (sizeof(hello_world) / (sizeof(char))) - 1; idx++)
        {
            send_data(hello_world[idx]);
        }
        Delay_ms(1000);
    }

    return 0;
}

/**
 * 使用USART1
 *
 * PA9:  USART1_TX
 * PA10: USART_RX
 */
void init_USART()
{
    // 开启时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);

    // 初始化PA9
    GPIO_InitTypeDef PA9_Init_Conf = {
        .GPIO_Pin = GPIO_Pin_9,
        .GPIO_Speed = GPIO_Speed_50MHz,
        .GPIO_Mode = GPIO_Mode_AF_PP};
    GPIO_Init(GPIOA, &PA9_Init_Conf);

    // 初始化PA10
    GPIO_InitTypeDef PA10_Init_Conf = {
        .GPIO_Pin = GPIO_Pin_10,
        .GPIO_Speed = GPIO_Speed_50MHz,
        .GPIO_Mode = GPIO_Mode_IPU};
    GPIO_Init(GPIOA, &PA10_Init_Conf);

    // 初始化USART1
    USART_InitTypeDef USART1_Init_Conf = {
        .USART_BaudRate = 9600,                  // 参考:'Table 192. Error calculation for programmed baud rates'
        .USART_WordLength = USART_WordLength_9b, // 使用9位数据位,1位校验位
        .USART_StopBits = 2,
        .USART_Parity = USART_Parity_Odd, // 校验规则: 奇校验
        .USART_Mode = USART_Mode_Rx | USART_Mode_Tx,
        .USART_HardwareFlowControl = USART_HardwareFlowControl_None // 暂时不开启硬件流控
    };
    USART_Init(USART1, &USART1_Init_Conf);

    // 打开USART1
    USART_Cmd(USART1, ENABLE);
}

/**
 * From FreeRTOS Demo
 */
void init_RCC()
{
    /* RCC system reset(for debug purpose). */
    RCC_DeInit();

    /* Enable HSE. */
    RCC_HSEConfig(RCC_HSE_ON);

    /* Wait till HSE is ready. */
    while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET)
    {
    }

    /* HCLK = SYSCLK. */
    RCC_HCLKConfig(RCC_SYSCLK_Div1);

    /* PCLK2  = HCLK. */
    RCC_PCLK2Config(RCC_HCLK_Div1);

    /* PCLK1  = HCLK/2. */
    RCC_PCLK1Config(RCC_HCLK_Div2);

    /* ADCCLK = PCLK2/4. */
    RCC_ADCCLKConfig(RCC_PCLK2_Div4);

    /* Flash 2 wait state. */
    *(volatile unsigned long *)0x40022000 = 0x01;

    /* PLLCLK = 8MHz * 9 = 72 MHz */
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

    /* Enable PLL. */
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready. */
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    /* Select PLL as system clock source. */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source. */
    while (RCC_GetSYSCLKSource() != 0x08)
    {
    }

    /* Enable GPIOA, GPIOB, GPIOC, GPIOD, GPIOE and AFIO clocks */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO, ENABLE);

    /* Set the Vector Table base address at 0x08000000. */
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

    /* Configure HCLK clock as SysTick clock source. */
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);

    /* SPI2 Periph clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
}

void send_data(u16 cur_data)
{
    // 如果TDR不为空,那说明数据还没有发送完,等待发送完成
    while ((USART_GetFlagStatus(USART1, USART_FLAG_TXE)) == RESET)
        ;

    USART_SendData(USART1, cur_data);
}

u16 receive_data()
{
}