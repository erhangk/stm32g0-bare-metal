/*
 * iwdg.h
 *
 *  Created on: Jan 30, 2024
 *      Author: erhangok
 */

#ifndef IWDG_H_
#define IWDG_H_

#endif /* IWDG_H_ */

#include "stm32g0xx.h"

void IWDGInit(uint32_t reload, uint32_t prescaler);
void IWDG_Refresh(void);
void IWDG_Start(void);
