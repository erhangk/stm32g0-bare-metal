/*
 * onboard_led.h
 *
 *  Created on: Jan 30, 2024
 *      Author: erhangok
 */

#ifndef ONBOARD_LED_H_
#define ONBOARD_LED_H_

#include "stm32g0xx.h"

void LedInit(void);
void ToggleLed(void);
void EnableLed(void);
void DisableLed(void);


#endif /* ONBOARD_LED_H_ */
