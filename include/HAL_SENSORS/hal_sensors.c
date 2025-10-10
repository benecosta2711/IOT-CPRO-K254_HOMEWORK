#include "hal_sensors.h"

// moisture 50%, temp 27°
static SensorData_t g_sensor;

void HAL_SENS_Init(void)
{
    g_sensor = (SensorData_t){50.0f, 27.0f};
}

void HAL_SENS_Read(SensorData_t *out)
{
    if (out)
        *out = g_sensor;
}

// Mô phỏng mỗi giây nếu không tưới độ ẩm giảm; nếu tưới tăng
void HAL_SENS_SimulateTick(PumpState_t pump)
{
    const float dryRate = 0.9f;
    const float wetRate = 2.5f;

    if(pump == PUMP_ON)
    {
        g_sensor.soilMoisturePercent += wetRate;
    }
    else
    {
        g_sensor.soilMoisturePercent -= dryRate;
    }

    if(g_sensor.soilMoisturePercent < 0)
    {
        g_sensor.soilMoisturePercent = 0;
    }
    if(g_sensor.soilMoisturePercent > 100)
    {
        g_sensor.soilMoisturePercent = 100;
    }
}
