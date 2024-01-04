// 按钮控制舵机
#include "pwm_duoji.h"

int main(int argc, char **argv)
{

    pwm_init();

    pwm_setCompare2(2500);
    for (;;)
    {
    }

    return 0;
}