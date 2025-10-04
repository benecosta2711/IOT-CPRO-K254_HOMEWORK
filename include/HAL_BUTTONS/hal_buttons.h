#ifndef HAL_BUTTONS_H
#define HAL_BUTTONS_H

#include "config.h"

void HAL_BTN_Init(void);
int  HAL_BTN_ReadToggleMode(void);    
int  HAL_BTN_ReadManualWater(void);   

#endif
