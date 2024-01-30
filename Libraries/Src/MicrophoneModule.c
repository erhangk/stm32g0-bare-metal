/*
 * MicrophoneModule.c
 *
 *  Created on: Jan 30, 2024
 *      Author: erhangok
 */

#include "MicrophoneModule.h"

void initMic(){
	 // Enable the clock for GPIO port B
	    RCC->IOPENR |= RCC_IOPENR_GPIOBEN;

	    // Configure PB9 as input
	    GPIOB->MODER &= ~GPIO_MODER_MODE9_Msk;  // Clear mode bits for PB9


		EXTI->EXTICR[2]|= (1U << 8*1);

	    // Enable SYSCFG clock
	    RCC->APBENR2 |= RCC_APBENR2_SYSCFGEN;

	    EXTI->IMR1 |= (1U<<9);
	    EXTI->RTSR1 |= (1U << 9);

	    NVIC_SetPriority(EXTI4_15_IRQn, 2);
	    NVIC_EnableIRQ(EXTI4_15_IRQn);
}
