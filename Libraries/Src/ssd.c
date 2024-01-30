/*
 * ssd.c
 *
 *  Created on: Jan 30, 2024
 *      Author: erhangok
 */

#include "ssd.h"

static const uint8_t digitPins[16] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F, // 9
    0x77, // A
    0x7C, // B
    0x39, // C
    0x5E, // D
    0x79, // E
    0x71  // F
};

void PanelInit(void)
{
	RCC->IOPENR |= RCC_IOPENR_GPIOBEN_Msk;
    GPIOB->MODER &= ~0xFFFF;
    GPIOB->MODER |= 0x5555;
    GPIOB->ODR |= digitPins[0];


    GPIOA->MODER &= ~GPIO_MODER_MODE1_Msk;
    GPIOA->MODER |= GPIO_MODER_MODE1_0;

    GPIOA->MODER &= ~GPIO_MODER_MODE4_Msk;
    GPIOA->MODER |= GPIO_MODER_MODE4_0;

    GPIOA->MODER &= ~GPIO_MODER_MODE5_Msk;
    GPIOA->MODER |= GPIO_MODER_MODE5_0;

    GPIOA->MODER &= ~GPIO_MODER_MODE6_Msk;
    GPIOA->MODER |= GPIO_MODER_MODE6_0; //pa1 pa4 pa5 pa6

    //Disable D1,D2,D3,D4
    GPIOA->ODR |= GPIO_ODR_OD1;
	GPIOA->ODR |= GPIO_ODR_OD4;
	GPIOA->ODR |= GPIO_ODR_OD5;
	GPIOA->ODR |= GPIO_ODR_OD6;
}

void setDigit(uint32_t mask,int digit)
{
    //Disable D1,D2,D3,D4
    GPIOA->ODR |= GPIO_ODR_OD1;
	GPIOA->ODR |= GPIO_ODR_OD4;
	GPIOA->ODR |= GPIO_ODR_OD5;
	GPIOA->ODR |= GPIO_ODR_OD6;

    GPIOA->ODR &= ~mask; //Enable mask2
    GPIOB->ODR |= digitPins[digit];
    GPIOB->ODR &= digitPins[digit];
}
