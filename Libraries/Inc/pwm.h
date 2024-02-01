/*
 * pwm.h
 *
 *  Created on: Jan 30, 2024
 *      Author: erhangok
 */

#ifndef PWM_H_
#define PWM_H_

#include "stm32g0xx.h"

void PWM_Init_CH2();
void PWM_Init_CH3();
void setDutyCycle(TIM_TypeDef* TIM, uint16_t dutyCycle, uint8_t channel);

#endif /* PWM_H_ */
