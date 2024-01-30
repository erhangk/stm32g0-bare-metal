#include "stm32g0xx.h"
#include "SysTick.h"
#include "exti.h"
#include "onboard_led.h"
#include "ssd.h"
#include "timer.h"
#include "iwdg.h"

#define WDG_RELOAD_VAL 10000
#define IWDG_PR 7
//For 12 seconds(To observe it resets if the timer does not stop after 10 seconds

#define TIM_PSC 160
#define TIM_ARR 25

uint16_t counter = 0;
int D1;
int D2;
int D3;
int D4;

void Timer2Init();

int main(void) {
	IWDGInit(WDG_RELOAD_VAL, IWDG_PR);
	LedInit();

	Timer2Init(TIM_PSC, TIM_ARR);

	EXTI_Init();
	PanelInit();
	setDigit(GPIO_ODR_OD6,0);
    while(1) {
    }
    return 0;
}

void TIM2_IRQHandler(){
	TIM2->SR &= ~(1<<0); // Clear UIF update interrupt flag
	counter++;
	/*
	if(counter>=40000)
	{
		DisableTimer(TIM2);
		GPIOC->ODR ^= (1U << 6);
		counter = 0;
	}
	*/

	int number_counter = counter/4;
	D1 = number_counter/1000;
	D2 = (number_counter%1000)/100;
	D3 = (number_counter%100)/10;
	D4 = number_counter%10;
	if (counter%4 == 0){
		setDigit(GPIO_ODR_OD6,D4);
	}else if(counter%3 == 0){
		setDigit(GPIO_ODR_OD5,D3);
	}else if(counter%2 == 0){
		setDigit(GPIO_ODR_OD4,D2);
	}else if(counter%1 == 0){
		setDigit(GPIO_ODR_OD1,D1);
	}
}

void EXTI0_1_IRQHandler(void){
	EXTI->FPR1 |= (1<<0);
	counter = 0;
	ToggleLed();
	EnableTimer(TIM2);
	IWDG_Start();
	IWDG_Refresh();
}
