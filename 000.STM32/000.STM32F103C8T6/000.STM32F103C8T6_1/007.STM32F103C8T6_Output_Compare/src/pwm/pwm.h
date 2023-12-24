#ifndef PWM_H_
#define PWM_H_

#include "stm32f10x.h"

void pwm_init();

void pwm_setCompare1(uint16_t compareVal);

#endif