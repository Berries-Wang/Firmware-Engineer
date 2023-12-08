#include "buzzer.h"
#include "ray.h"

int main(int argc, char **argv)
{

    init_ray();
    init_buzzer();

    for (;;)
    {
        if (ray_light() == 1) // 若灯暗了
        {
            buzzer_on();
        }
        else
        {
            buzzer_off();
        }
    }

    return 0;
}