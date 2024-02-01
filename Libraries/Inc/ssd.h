/*
 * ssd.h
 *
 *  Created on: Jan 30, 2024
 *      Author: erhangok
 */

#ifndef SSD_H_
#define SSD_H_

#include "stm32g0xx.h"

static const uint8_t digitPins[16];

void PanelInit(void);
void setDigit(uint32_t mask,int digit);

#endif /* SSD_H_ */
