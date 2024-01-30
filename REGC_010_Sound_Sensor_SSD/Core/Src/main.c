#include "stm32g0xx.h"
#include "ssd.h"
#include "SysTick.h"
#include "timer.h"
#include "exti.h"
#include "MicrophoneModule.h"

uint16_t counter = 0;

int D1, D2, D3, D4;

int main(void) {
	EXTI_Init(); //For button
	PanelInit();
	SysTickInit();
	initMic();

	setDigit(GPIO_ODR_OD6,0);
    while(1) {
    	D1 = counter/1000;
    	D2 = (counter%1000)/100;
    	D3 = (counter%100)/10;
    	D4 = counter%10;

    	setDigit(GPIO_ODR_OD6,D4);
    	delay_ms(1);
    	setDigit(GPIO_ODR_OD5,D3);
    	delay_ms(1);
    	setDigit(GPIO_ODR_OD4,D2);
    	delay_ms(1);
    	setDigit(GPIO_ODR_OD1,D1);
    	delay_ms(1);
    }
    return 0;
}

void EXTI0_1_IRQHandler(void){
	counter = 0;
	GPIOC->ODR &= ~(1U << 6);
	EXTI->FPR1 |= (1<<0); //EXTI falling edge pending register 1 (EXTI_FPR1)
}

void EXTI4_15_IRQHandler(){
	counter++;
	delay_ms(100); // Delay for debouncing
	EXTI->RPR1 = EXTI_RPR1_RPIF9;  // Clear the pending bit for EXTI line 2
}
