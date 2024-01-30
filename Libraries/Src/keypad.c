/*
 * keypad.c
 *
 *  Created on: Jan 30, 2024
 *      Author: erhangok
 */

#include "keypad.h"
#include "pwm.h"

// 4x4 matrix for keypad
const int matrix[4][4] = {{1,2,3,A},
						  {4,5,6,B},
						  {7,8,9,C},
						  {clear,0,send,D}};

// Initialize all the inputs and interrupts needed for keypad
void init_keypad(void){
    // Enable clock for GPIOA and GPIOB
    RCC->IOPENR |= RCC_IOPENR_GPIOAEN | RCC_IOPENR_GPIOBEN;

    // Configure GPIO pins for keypad
    GPIOA->MODER &= ~(GPIO_MODER_MODE9_Msk | GPIO_MODER_MODE8_Msk);
    GPIOA->MODER |= GPIO_MODER_MODE8_0;

    GPIOB->MODER &= ~(GPIO_MODER_MODE0_Msk |
                      GPIO_MODER_MODE2_Msk |
                      GPIO_MODER_MODE4_Msk |
                      GPIO_MODER_MODE5_Msk |
                      GPIO_MODER_MODE8_Msk |
                      GPIO_MODER_MODE9_Msk);

    GPIOB->MODER |= GPIO_MODER_MODE4_0 |
                    GPIO_MODER_MODE5_0 |
                    GPIO_MODER_MODE9_0;

    // Set initial output levels for GPIO pins to HIGH
    GPIOA->ODR |= GPIO_ODR_OD8;
    GPIOB->ODR |= GPIO_ODR_OD9 | GPIO_ODR_OD5 | GPIO_ODR_OD4;

    // Setup pins as Pullup
    GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD9_Msk;
    GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD0_Msk | GPIO_PUPDR_PUPD2_Msk | GPIO_PUPDR_PUPD8_Msk;

    GPIOA->PUPDR |= GPIO_PUPDR_PUPD9_1;
    GPIOB->PUPDR |= GPIO_PUPDR_PUPD0_1 | GPIO_PUPDR_PUPD2_1 | GPIO_PUPDR_PUPD8_1;

    // Enable APB peripheral clock
    RCC->APBENR2 |= (1U<<0);

    // Configure external interrupt lines for keypad
    EXTI->EXTICR[2] |= (0U << 8*1);
    EXTI->EXTICR[0] |= (1U << 8*0);
    EXTI->EXTICR[0] |= (1U << 8*2);
    EXTI->EXTICR[2] |= (1U << 8*0);

    // Configure rising edge trigger for external interrupts
    EXTI->RTSR1 |= (1U << 9);
    EXTI->RTSR1 |= (1U << 0);
    EXTI->RTSR1 |= (1U << 2);
    EXTI->RTSR1 |= (1U << 8);

    // Enable external interrupts
    EXTI->IMR1 |= (1U<<9);
    EXTI->IMR1 |= (1U<<0);
    EXTI->IMR1 |= (1U<<2);
    EXTI->IMR1 |= (1U<<8);

    // Enable NVIC interrupts
    NVIC_SetPriority(EXTI0_1_IRQn, 2);
    NVIC_EnableIRQ(EXTI0_1_IRQn);

    NVIC_SetPriority(EXTI2_3_IRQn, 2);
    NVIC_EnableIRQ(EXTI2_3_IRQn);

    NVIC_SetPriority(EXTI4_15_IRQn, 2);
    NVIC_EnableIRQ(EXTI4_15_IRQn);
}

// This function is for the logic for when keypad is pressed
uint16_t scan_keypad(uint8_t row)
{
	static uint16_t raw_stroke; // Raw keypad strokes
	uint16_t dutycycle;

    uint8_t column;

    // Check each column to identify the pressed key
    // This turns off each row and checks if any of the rows turned off.
    GPIOA->ODR &= ~GPIO_ODR_OD8;
    if (!updateStatus()){
        column = 0;
    }
    GPIOA->ODR |= GPIO_ODR_OD8; //then turns them on again.

    GPIOB->ODR &= ~GPIO_ODR_OD9;
    if (!updateStatus()){
        column = 1;
    }
    GPIOB->ODR |= GPIO_ODR_OD9;

    GPIOB->ODR &= ~GPIO_ODR_OD5;
    if (!updateStatus()){
        column = 2;
    }
    GPIOB->ODR |= GPIO_ODR_OD5;

    GPIOB->ODR &= ~GPIO_ODR_OD4;
    if (!updateStatus()){
        column = 3;
    }
    GPIOB->ODR |= GPIO_ODR_OD4;

    // Lookup the matrix for what value is in that position
    uint8_t current_num = matrix[row][column];
    if(current_num == send)
    {
        setDutyCycle(TIM1, raw_stroke, 3); // Set PWM duty cycle
        dutycycle = raw_stroke;   // Update duty cycle since raw duty cycle gets reset.
        raw_stroke = 0;           // Reset raw duty cycle
    }
    else if(current_num == clear)// if clear is pressed, reset raw duty cycle
    {
        raw_stroke = 0;
    }
    else if(current_num < 10) //if a normal number is pressed, update the raw duty cycle
    {
        raw_stroke = 10*raw_stroke + current_num; // Update raw duty cycle
        if(raw_stroke > 100)
        {
            raw_stroke=100; // Limit duty cycle to 100
        }
    }
    return dutycycle;
}

// Read the status of the rows
uint8_t updateStatus(void)
{
    return (GPIOA->IDR & GPIO_IDR_ID9) ||
           (GPIOB->IDR & GPIO_IDR_ID0) ||
           (GPIOB->IDR & GPIO_IDR_ID2) ||
           (GPIOB->IDR & GPIO_IDR_ID8);
}

