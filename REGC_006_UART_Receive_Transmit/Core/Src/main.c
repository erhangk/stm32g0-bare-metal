#include "stm32g0xx.h"
#include "uart.h"

int main()
{
	UART_Init();
	print("Hello World!");
	while(1)
	{
		uart_tx(uart_rx());
	}
}







