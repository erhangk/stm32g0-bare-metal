/*
 * i2c.c
 *
 *  Created on: Jan 30, 2024
 *      Author: erhangok
 */

#include "i2c.h"

void I2C_GPIO_Init(void)
{
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN;

	GPIOA->MODER &= ~(GPIO_MODER_MODE9|
					  GPIO_MODER_MODE10);
	GPIOA->MODER |= (GPIO_MODER_MODE9_1|
					 GPIO_MODER_MODE10_1); //Set for alternate function

	GPIOA->OTYPER |= (GPIO_OTYPER_OT9|
				 	  GPIO_OTYPER_OT10);

	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED9_Msk; // high speed
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED10_Msk; // high speed

	GPIOA->PUPDR |= GPIO_PUPDR_PUPD9_0;
	GPIOA->PUPDR |= GPIO_PUPDR_PUPD10_0;

	GPIOA->AFR[1] |= (6U << 4); // for PA9,PA10 AF6(I2C)
	GPIOA->AFR[1] |= (6U << 8); // for PA9,PA10 AF6(I2C)
}

void I2C_Init(void)
{
	I2C_GPIO_Init();
	RCC->APBENR1 |= RCC_APBENR1_I2C1EN;

	I2C1->CR1 = 0;
	I2C1->CR1 |= I2C_CR1_ERRIE;

	I2C1->TIMINGR |= (3<<28);   // PRESC
	I2C1->TIMINGR |= (0x13<<0); // SCLL
	I2C1->TIMINGR |= (0xF<<8);  // SCLH
	I2C1->TIMINGR |= (0x2<<16); // SDADEL
	I2C1->TIMINGR |= (0x4<<20); // SCLDEL

	I2C1->CR1 = I2C_CR1_PE;

	NVIC_SetPriority(I2C1_IRQn, 1);
	NVIC_EnableIRQ(I2C1_IRQn);
}

uint8_t I2C_Read(uint8_t devAddr, uint8_t regAddr)
{
	I2C1->CR2 = 0; //Clear
	I2C1->CR2 |= (uint32_t)devAddr << 1; //Slave adress
	I2C1->CR2 |= 1U << 16; // Number of bytes
	I2C1->CR2 |= I2C_CR2_START;

	while(!(I2C1->ISR & I2C_ISR_TXIS)); //Wait till TXIS is empty

	I2C1->TXDR = (uint32_t)regAddr;
	while(!(I2C1->ISR & I2C_ISR_TC));   //Wait till transfer complete

	// READ OPERATION(read data)
	I2C1->CR2 = 0;
	I2C1->CR2 |= ((uint32_t)devAddr << 1); //Slave adresss | 7 bit addressing mode
	I2C1->CR2 |= I2C_CR2_RD_WRN; //Read mode
	I2C1->CR2 |= (1U << 16); // Number of bytes
	I2C1->CR2 |= I2C_CR2_NACK; // NACK
	I2C1->CR2 |= I2C_CR2_AUTOEND; // AUTOEND
	I2C1->CR2 |= I2C_CR2_START; // Generate Start

	while(!(I2C1->ISR & I2C_ISR_RXNE));
	return (uint8_t)I2C1->RXDR;
}

void I2C_Write(uint8_t devAddr, uint16_t regAddr, uint8_t data)
{
	I2C1->CR2 = 0;
	I2C1->CR2 |= ((uint32_t)devAddr << 1); // slave adress
	I2C1->CR2 |= (3U << 16);
	I2C1->CR2 |= I2C_CR2_AUTOEND;
	I2C1->CR2 |= I2C_CR2_START;

	while(!(I2C1->ISR & I2C_ISR_TXIS));
	I2C1->TXDR = (uint32_t)regAddr;

	while(!(I2C1->ISR & I2C_ISR_TXIS));
	I2C1->TXDR = (uint32_t)data;
}
