// 按钮控制舵机
#include "pwm_duoji.h"
#include "button.h"
#include "OLED.h"

int main(int argc, char **argv)
{

    pwm_init();
    button_init();
    OLED_Init();

    uint16_t angle = 0;
    for (;;)
    {
        uint8_t keyNum = key_getNum();
        if (keyNum == 1) // 按键按下
        {
            angle += 30;
            if (angle > 180)
            {
                angle = 0;
            }
            pwm_setCompare2(angle * 2000 / 180 + 500);
            OLED_ShowNum(1, 1, angle, 3);
        }
    }

    return 0;
}