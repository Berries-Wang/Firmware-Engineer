#include "stm32f10x.h"

int main(int argc, char **argv)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    for (int index = 0; index < 10; index++)
    {
    }

    return 0;
}
