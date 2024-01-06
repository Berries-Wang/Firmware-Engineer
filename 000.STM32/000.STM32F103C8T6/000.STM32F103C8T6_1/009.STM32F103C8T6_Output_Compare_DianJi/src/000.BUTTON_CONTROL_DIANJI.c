// 按钮控制舵机
#include "dianji.h"
#include "button.h"
#include "OLED.h"

int main(int argc, char **argv)
{

    dianji_init();
    button_init();
    OLED_Init();

    int8_t speed = 0;
    int8_t step = 10;
    for (;;)
    {
        uint8_t keyNum = key_getNum();
        if (keyNum == 1) // 按键按下
        {
            speed += step;
            if (speed >= 100)
            {
                step = -10;
            }
            else if (speed <= -100)
            {
                step = 10;
            }
            set_dianji_speed(speed);
            OLED_ShowNum(1, 1, speed, 4);
        }
    }

    return 0;
}