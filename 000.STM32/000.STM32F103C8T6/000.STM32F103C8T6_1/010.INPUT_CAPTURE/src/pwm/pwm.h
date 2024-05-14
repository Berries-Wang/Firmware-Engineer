#ifndef PWM_IC_MEASURING_FREQUENCY_H_
#define PWM_IC_MEASURING_FREQUENCY_H_

#include "stm32f10x.h"

void pwm_init();

void pwm_setCompare2(uint16_t compareVal);

#endif