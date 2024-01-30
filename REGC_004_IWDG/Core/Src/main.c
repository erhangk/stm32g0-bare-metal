#include "stm32g0xx.h"
#include "iwdg.h"
#include "onboard_led.h"
#include "SysTick.h"

#define LEDDELAY 1000
#define WDG_RELOAD_VAL 1000 //working for 1000, resets for 100

int main(void) {
    LedInit();
    SysTickInit();
    IWDGInit(WDG_RELOAD_VAL, IWDG_PR_PR_2); //Prescaler=4
    IWDG_Start();

    while (1) {
        delay_ms(LEDDELAY);
        /* Toggle LED */
        ToggleLed();
        IWDG_Refresh();
    }
    return 0;
}
