#include "pwm.h"
#include "Delay.h"

int main(int argc, char **argv)
{

    pwm_init();

    for (;;)
    {
        for (uint16_t i = 0; i <= 100; i++)
        {
            pwm_setCompare1(i);
            Delay_ms(10);
        }

        for (uint16_t i = 100; i >= 1; i--)
        {
            pwm_setCompare1(i);
            Delay_ms(10);

            // 注意，i的类型是uint16_t是无符号整数，不会存在小于0的情况,即 0-1 = 65535
        }
    }

    return 0;
}