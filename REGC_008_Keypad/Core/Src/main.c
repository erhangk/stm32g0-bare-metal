#include "stm32g0xx.h"
#include "stdlib.h"
#include "pwm.h"
#include "SysTick.h"
#include "uart.h"
#include "keypad.h"

void EXTI0_1_IRQHandler(void);
void EXTI2_3_IRQHandler(void);
void EXTI4_15_IRQHandler(void);

volatile uint8_t dutycycle; // Processed duty cycle value

int main(){
    // Initialize UART, keypad, SysTick, and PWM
	UART_Init();
	init_keypad();
	SysTickInit();
    PWM_Init_CH3();

	char str_dutycycle[4]; // String to hold duty cycle

	while(1){
		utoa(dutycycle,str_dutycycle, 10); // Convert duty cycle to string
		print("Current Duty Cycle: %");
		/*
		for(int i=0;i<4;i++)
		{
			uart_tx(str_dutycycle[i]); // Transmit duty cycle character by character
		}
		*/
		print(str_dutycycle);//If this does not work, use the code commented above
		print("\n\r");

		delay_ms(2000);
	}
	return 0;
}

// Interrupt handler for EXTI0_1
void EXTI0_1_IRQHandler(void) {
    dutycycle = scan_keypad(1); // Scan keypad for row 2
    delay_ms(500); // Delay for debouncing
    EXTI->RPR1 = EXTI_RPR1_RPIF0;  // Clear the pending bit for EXTI line 0
}

// Interrupt handler for EXTI2_3
void EXTI2_3_IRQHandler(void) {
	dutycycle = scan_keypad(2); // Scan keypad for row 3
    delay_ms(500); // Delay for debouncing
    EXTI->RPR1 = EXTI_RPR1_RPIF2;  // Clear the pending bit for EXTI line 2
}

// Interrupt handler for EXTI4_15
void EXTI4_15_IRQHandler(void) {
    // Determine which key was pressed and scan accordingly
    if((EXTI->RPR1&EXTI_RPR1_RPIF8))
    {
    	dutycycle = scan_keypad(3); // Scan keypad for row 4
    }
    if((EXTI->RPR1&EXTI_RPR1_RPIF9))
    {
    	dutycycle = scan_keypad(0); // Scan keypad for row 1
    }
    delay_ms(500); // Delay for debouncing
    EXTI->RPR1 |= EXTI_RPR1_RPIF8; // Clear the pending bit for EXTI line 8
    EXTI->RPR1 |= EXTI_RPR1_RPIF9; // Clear the pending bit for EXTI line 9
}
