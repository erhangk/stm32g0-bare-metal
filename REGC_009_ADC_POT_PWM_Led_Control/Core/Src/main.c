#include "stm32g0xx.h"
#include "SysTick.h"
#include "adc.h"
#include "pwm.h"


int main(){
    uint16_t dutyCycle;

    SysTickInit();
    PWM_Init_CH2();
    PWM_Init_CH3();
    ADC_Init();
    while(1)
    {
    	dutyCycle = (uint16_t) readADC()*100/4095;
    	setDutyCycle(TIM1, dutyCycle, 2);
    	setDutyCycle(TIM1, 100-dutyCycle, 3);
    }
    return 0;
}
