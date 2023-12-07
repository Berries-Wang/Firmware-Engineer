#include "led.h"
#include "button.h"

int main(int argc, char **argv)
{

    button_init();
    led_init();

    for (;;)
    {
        uint8_t keyNum = key_getNum();
        if (keyNum == 1) // 按键按下
        {
            // led_on(); // 点亮LED
            led_turn();
        }
    }

    return 0;
}