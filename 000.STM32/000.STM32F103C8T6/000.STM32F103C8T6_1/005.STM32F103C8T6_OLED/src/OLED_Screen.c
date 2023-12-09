#include "OLED.h"

int main(int argc, char **argv)
{

    OLED_Init();

    OLED_ShowString(1, 1, "STM32");

    for (;;)
    {
    }

    return 0;
}