#ifndef RAY_H_
#define RAY_H_

#include "stm32f10x.h"

/**
 * 初始化光敏电阻传感器
 */
void init_ray();

/**
 * 读取光敏电阻传感器的值:
 * 1: 暗
 * 0: 亮
 */
uint8_t ray_light();

#endif