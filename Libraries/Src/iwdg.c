/*
 * iwdg.c
 *
 *  Created on: Jan 30, 2024
 *      Author: erhangok
 */
#include "iwdg.h"

void IWDGInit(uint32_t reload, uint32_t prescaler) {
    IWDG->KR = IWDG_KEY_WRITE_ACCESS_ENABLE; //Enable access
    IWDG->PR = prescaler;    //Prescaler: 4

    IWDG->RLR = reload; //Reload value: 1000

    IWDG_Refresh(); //Refresh watchdog counter
}

void IWDG_Refresh(void)
{
    IWDG->KR = IWDG_KEY_RELOAD;
}

void IWDG_Start(void)
{
    IWDG->KR = IWDG_KEY_ENABLE;
}
