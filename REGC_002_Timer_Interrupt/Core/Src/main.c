#include "stm32g0xx.h"
#include "exti.h"
#include "onboard_led.h"
#include "timer.h"

#define TIM_PSC 0
#define TIM_ARR 16000000

volatile int counter = 0;
volatile int delay; //declared for observing on debug, otherwise not necessary
int incrementing = 1;

int main(void) {

	LedInit();
	Timer2Init(TIM_PSC, TIM_ARR);
	EXTI_Init();

	EnableTimer(TIM2);
    while(1) {
    }
    return 0;
}

void TIM2_IRQHandler(void){
	TIM2->SR &= ~(1<<0); // Clear UIF update interrupt flag
	ToggleLed();
}

void EXTI0_1_IRQHandler(void){
	EXTI->FPR1 |= (1<<0);

	if(incrementing)
	{
		counter++;
		TIM2->PSC++;

		if(counter>=9)
		{
			incrementing = 0;
		}
	}
	else
	{
		counter--;
		TIM2->PSC--;
		if(counter <= 0)
		{
			incrementing = 1;
		}
	}
	delay = counter + 1;
}

