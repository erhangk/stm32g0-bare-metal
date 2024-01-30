/*
 * onboard_led.c
 *
 *  Created on: Jan 30, 2024
 *      Author: erhangok
 */
#include "onboard_led.h"

void LedInit(void)
{
    /* Enable GPIOC clock */
    RCC->IOPENR |= (1U << 2);

    /* Setup PC6 as output */
    GPIOC->MODER &= ~(3U << 2*6);
    GPIOC->MODER |= (1U << 2*6);

    /* Turn on LED */
    GPIOC->ODR |= (1U << 6);
}

void ToggleLed(void)
{
	GPIOC->ODR ^= GPIO_ODR_OD6;
}

void EnableLed(void)
{
	GPIOC->ODR &= ~GPIO_ODR_OD6;
}

void DisableLed(void)
{
	GPIOC->ODR |= GPIO_ODR_OD6;
}
