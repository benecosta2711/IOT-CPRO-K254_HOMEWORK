#ifndef HAL_ACTUATORS_H
#define HAL_ACTUATORS_H

#include "CONFIG/config.h"

void HAL_ACT_Init(void);
void HAL_ACT_TurnPumpOn(void);
void HAL_ACT_TurnPumpOff(void);
void HAL_ACT_SetLed(LedState_t st);

#endif
