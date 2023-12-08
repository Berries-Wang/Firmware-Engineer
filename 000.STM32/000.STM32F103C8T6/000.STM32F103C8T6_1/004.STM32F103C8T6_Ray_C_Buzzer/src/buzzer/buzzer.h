#ifndef BUZZER_H_
#define BUZZER_H_

#include "stm32f10x.h"

/**
 * 初始化蜂鸣器
 */
void init_buzzer();

/**
 * 蜂鸣器响
 */
void buzzer_on();

/**
 * 蜂鸣器静
 */
void buzzer_off();

#endif