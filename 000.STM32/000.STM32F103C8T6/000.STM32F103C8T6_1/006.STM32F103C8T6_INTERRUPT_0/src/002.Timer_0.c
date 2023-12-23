#include "stm32f10x.h"
#include "OLED.h"
#include "timStu.h"

int main(int argc, char **argv)
{

    OLED_Init();
    // Timer_Init();
    Timer_External_Init();

    for (;;)
    {
        OLED_ShowSignedNum(1, 1, getNum(), 5);
    }

    return 0;
}