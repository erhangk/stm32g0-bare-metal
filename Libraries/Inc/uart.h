/*
 * uart.h
 *
 *  Created on: Jan 30, 2024
 *      Author: erhangok
 */

#ifndef UART_H_
#define UART_H_

#include "stm32g0xx.h"

void UART_Init();
void printChar(uint8_t c);
int _print(int f,char *ptr, int len);
void print(char *s);
void println(char *s);
uint8_t uart_rx(void);
void uart_tx(uint8_t c);

#endif /* UART_H_ */
