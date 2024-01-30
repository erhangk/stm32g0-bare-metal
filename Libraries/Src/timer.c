/*
 * timer.c
 *
 *  Created on: Jan 30, 2024
 *      Author: erhangok
 */

#include "timer.h"

void Timer2Init(uint32_t PSC, uint32_t ARR)
{
	RCC->APBENR1 |= RCC_APBENR1_TIM2EN_Msk;

	TIM2->CNT = 0;
	TIM2->PSC = PSC;
	TIM2->ARR = ARR;//1600
	TIM2->DIER |= (1U<<0);

	NVIC_EnableIRQ(TIM2_IRQn);
	NVIC_SetPriority(TIM2_IRQn,3);
	TIM2->SR &= ~(1U<<0);

	TIM2->EGR |= (1U<<0); // Reset timer

	DisableTimer(TIM2);
}

void EnableTimer(TIM_TypeDef* TIM)
{
	TIM->CR1 |= (1U<<0);
}

void DisableTimer(TIM_TypeDef* TIM)
{
	TIM->CR1 &= ~(1U<<0);
}
