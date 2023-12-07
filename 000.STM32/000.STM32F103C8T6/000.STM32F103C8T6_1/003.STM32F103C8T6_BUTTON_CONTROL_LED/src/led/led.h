#ifndef LED_H_
#define LED_H_

/**
 * LED 初始化
 */
void led_init();

/**
 * 点亮LED
 */
void led_on();

/**
 * 关闭LED
 */
void led_off();

/**
 * 如果灯是灭的,则按下灯开;若灯是开的，则按下灯灭;
 */
void led_turn();

#endif