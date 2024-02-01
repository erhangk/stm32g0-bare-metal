/*
 * timer.h
 *
 *  Created on: Jan 30, 2024
 *      Author: erhangok
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "stm32g0xx.h"

void Timer2Init();
void EnableTimer(TIM_TypeDef* TIM);
void DisableTimer(TIM_TypeDef* TIM);

#endif /* TIMER_H_ */
