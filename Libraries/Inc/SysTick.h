/*
 * SysTick.h
 *
 *  Created on: Jan 30, 2024
 *      Author: erhangok
 */

#ifndef MODULES_SYSTICK_H_
#define MODULES_SYSTICK_H_

#endif /* MODULES_SYSTICK_H_ */

#include "stm32g0xx.h"

static volatile uint32_t millis;

void SysTickInit(void);
void delay_ms(uint32_t delay);
void SysTick_Handler(void);
