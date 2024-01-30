/*
 * keypad.h
 *
 *  Created on: Jan 30, 2024
 *      Author: erhangok
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_
#endif /* KEYPAD_H_ */

#include "stm32g0xx.h"

// Constants for keypad
#define A 50
#define B A
#define C A
#define D A
#define clear 10 // "*" sign is for clearing the keypad
#define send 11 // "#" confirms the entered value.

// 4x4 matrix for keypad
extern const int matrix[4][4];

void init_keypad(void);
uint16_t scan_keypad(uint8_t row); // Function to scan the keypad
uint8_t updateStatus(void); // Function to update status of GPIO

