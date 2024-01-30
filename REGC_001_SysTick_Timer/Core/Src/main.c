#include "stm32g0xx.h"

#include "SysTick.h"
#include "onboard_led.h"

#define LEDDELAY 1000

int main(void) {
    LedInit();
    SysTickInit();

    while (1) {
        delay_ms(LEDDELAY);
        ToggleLed();
    }
    return 0;
}

