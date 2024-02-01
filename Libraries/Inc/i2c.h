/*
 * i2c.h
 *
 *  Created on: Jan 30, 2024
 *      Author: erhangok
 */

#ifndef I2C_H_
#define I2C_H_


#include "stm32g0xx.h"

void I2C_GPIO_Init(void);
void I2C_Init(void);
uint8_t I2C_Read(uint8_t devAddr, uint8_t regAddr);
void I2C_Write(uint8_t devAddr, uint16_t regAddr, uint8_t data);

#endif /* I2C_H_ */
