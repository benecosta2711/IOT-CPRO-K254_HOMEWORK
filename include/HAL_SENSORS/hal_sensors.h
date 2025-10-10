#ifndef HAL_SENSORS_H
#define HAL_SENSORS_H

#include "CONFIG/config.h"

void HAL_SENS_Init(void);

void HAL_SENS_Read(SensorData_t* out);

void HAL_SENS_SimulateTick(PumpState_t pump);

#endif
