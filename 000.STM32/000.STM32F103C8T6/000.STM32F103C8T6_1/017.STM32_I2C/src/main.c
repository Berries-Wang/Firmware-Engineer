#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "Delay.h"

/**
 * I2C
 */

/**
 * 初始化RCC
 */
void init_RCC();

int main(int argc, char **argv)
{

    return 0;
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

    /* Configure HCLK clock as SysTick clock source. */
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);

    /* SPI2 Periph clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

    // 关闭HSI,默认就是HSI
    RCC_HSICmd(DISABLE);
}