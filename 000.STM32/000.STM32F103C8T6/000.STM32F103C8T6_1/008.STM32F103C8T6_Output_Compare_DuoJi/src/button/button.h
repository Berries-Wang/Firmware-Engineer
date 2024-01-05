#ifndef BUTTON_H_
#define BUTTON_H_

#include "stm32f10x.h"

/**
 * 按键是接在B1口
 */
void button_init();
u8 key_getNum();

#endif