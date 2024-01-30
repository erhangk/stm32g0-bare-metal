/*
 * exti.c
 *
 *  Created on: Jan 30, 2024
 *      Author: erhangok
 */
#include "exti.h"

void EXTI_Init(void)
{
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN_Msk;
	GPIOA->MODER &= ~GPIO_MODER_MODE0_Msk;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD0_Msk;
	GPIOA->PUPDR |=  (1U<<0); //GPIO port pull-up/pull-down register

	RCC->APBENR2 |= (1U<<0); //APB peripheral clock enable register
	EXTI->RTSR1 |= (1U<<0); //NOT NECESSARY
	EXTI->IMR1 |= (1U<<0);  //EXTI CPU wakeup with interrupt mask register

    EXTI->FTSR1 |= (1U<<0);        // Enable EXTI on Falling edge
	EXTI->RTSR1 &= ~(1U<<0);       // Disable EXTI on Rising edge

	NVIC_SetPriority(EXTI0_1_IRQn,0);
	NVIC_EnableIRQ(EXTI0_1_IRQn);
}
