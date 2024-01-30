#include "stm32g0xx.h"
#include "pwm.h"

volatile int dutyCycle = 0;
volatile int direction = 1;

int main(void) {
    PWM_Init_CH3();

    while (1) {
    }
}

void TIM1_CC_IRQHandler(void) {
    if (TIM1->SR & TIM_SR_CC1IF) { // Check capture/compare 1 interrupt flag
        TIM1->SR &= ~TIM_SR_CC1IF; // Clear the interrupt flag

        // Update the duty cycle
        dutyCycle += direction;
        if (dutyCycle >= 100) {
            dutyCycle = 100;
            direction = -1;
        } else if (dutyCycle <= 0) {
            dutyCycle = 0;
            direction = 1;
        }

        setDutyCycle(TIM1, dutyCycle, 3); // Update TIM1 channel 3 duty cycle
    }
}
