/*
 * pwm.c
 *
 *  Created on: Jan 30, 2024
 *      Author: erhangok
 */

#include "pwm.h"

void setDutyCycle(TIM_TypeDef* TIM, uint16_t dutyCycle, uint8_t channel)
{
	switch (channel){
		case 1:
			TIM->CCR1 = dutyCycle;
			break;
		case 2:
			TIM->CCR2 = dutyCycle;
			break;
		case 3:
			TIM->CCR3 = dutyCycle;
			break;
		case 4:
			TIM->CCR4 = dutyCycle;
			break;
	}
}

void PWM_Init_CH3() {
    RCC->IOPENR |= RCC_IOPENR_GPIOAEN;   // Enable GPIOA clock
    RCC->APBENR2 |= RCC_APBENR2_TIM1EN;  // Enable TIM1 clock

    GPIOA->MODER &= ~GPIO_MODER_MODE10;   // Clear mode bits for PA10
    GPIOA->MODER |= GPIO_MODER_MODE10_1;  // Set PA10 to Alternate Function mode

    GPIOA->AFR[1] &= ~(0xF << ((10 - 8) * 4));  // Clear the current AF setting for PA10
    GPIOA->AFR[1] |= (2 << ((10 - 8) * 4));    // Set the AF (AF2) for TIM1_CH3 for PA10

    TIM1->PSC = 1600 - 1;  // Prescaler for 1kHz PWM frequency
    TIM1->ARR = 100;       // Auto-reload value for 100 steps, this is for 1% increments
    TIM1->CCMR2 |= TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2; // PWM mode 1 on Channel 3
    TIM1->CCER |= TIM_CCER_CC3E;        // Enable capture/compare for channel 3
    TIM1->BDTR |= TIM_BDTR_MOE;         // Main output enable (needed for TIM1)
	TIM1->CR1 |= TIM_CR1_CEN;           // Enable timer

    //for interrupts
    TIM1->DIER |= TIM_DIER_CC1IE;

    // Enable TIM1 interrupt in NVIC
    NVIC_EnableIRQ(TIM1_CC_IRQn);
    NVIC_SetPriority(TIM1_CC_IRQn, 0);

    setDutyCycle(TIM1, 0, 3); //set initial duty cycle to 0
}

void PWM_Init_CH2() {

    GPIOA->MODER &= ~GPIO_MODER_MODE9;   // Clear mode bits for PA09
	GPIOA->MODER |= GPIO_MODER_MODE9_1;  // Set PA9 to Alternate Function mode

	GPIOA->AFR[1] &= ~(0xF << ((9 - 8) * 4));  // Clear the current AF setting for PA9
	GPIOA->AFR[1] |= (2 << ((9 - 8) * 4));    // Set the AF (AF2) for TIM1_CH2 for PA9

	TIM1->PSC = 1600 - 1;  // Prescaler for 1kHz PWM frequency
	TIM1->ARR = 100;       // Auto-reload value for 100 steps, this is for 1% increments
    TIM1->CCMR1 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2; // PWM mode 1 on Channel 2
    TIM1->CCER |= TIM_CCER_CC2E;        // Enable capture/compare for channel 3
    TIM1->BDTR |= TIM_BDTR_MOE;         // Main output enable (needed for TIM1)
	TIM1->CR1 |= TIM_CR1_CEN;           // Enable timer

    //for interrupts
    TIM1->DIER |= TIM_DIER_CC1IE;

    // Enable TIM1 interrupt in NVIC
    NVIC_EnableIRQ(TIM1_CC_IRQn);
    NVIC_SetPriority(TIM1_CC_IRQn, 0);

    setDutyCycle(TIM1, 0, 2); //set initial duty cycle to 0
}
