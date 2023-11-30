#include "stm32f10x.h"
#include "stm32f10x_conf.h"

int main(int argc, char **argv)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    while (1)
    {
    }

    return 0;
}
