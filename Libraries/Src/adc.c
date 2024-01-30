/*
 * adc.c
 *
 *  Created on: Jan 30, 2024
 *      Author: erhangok
 */

#include "adc.h"

void ADC_Init()
{
	//PA7
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN;
	RCC->APBENR2 |= RCC_APBENR2_ADCEN;
	GPIOA->MODER |= GPIO_MODER_MODE7; //Set PA7 as analog

	//ADC1->CFGR1 &= ~ADC_CFGR1_CHSELRMOD;
	ADC1->CFGR1 |= ADC_CFGR1_CONT; //Enable continuous conversion mode
	ADC1->SMPR |= ADC_SMPR_SMPSEL7;
	ADC1->SMPR |= 0b111;
	ADC1->CHSELR |= ADC_CHSELR_CHSEL7;

	ADC1->CR |= ADC_CR_ADEN; //ADC enable
	ADC1->CR |= ADC_CR_ADSTART; //ADC start
}

uint32_t readADC()
{
	while(!(ADC1->ISR & ADC_ISR_EOC))
	{
	}
	return ADC1->DR;
}
