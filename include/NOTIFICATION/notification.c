#include "notification.h"

static float s_sensor_moisture = 0;
static float s_sensor_temp = 0;
static SystemMode_t s_system_mode = 0;
static PumpState_t s_pump_state = 0;

void EMULATOR_Notification(void *arg)
{
    printf("Send data about System \n");
    NOTIFICATION_GetData(g_sensor_data, g_operation_mode, g_pump_sate);
    printf("Độ ẩm đất:%.2f \n Nhiệt độ: %.2f\n", s_sensor_moisture, s_sensor_temp);
    if(s_system_mode == MODE_AUTO)
    {
        printf("Chế độ từ động\n");
    }
    else 
    {
        printf("Chế độ thủ công\n");
    }
    if(s_pump_state == PUMP_OFF)
    {
        printf("Máy bơm đang tắt\n");
    }
    else
    {
        printf("Máy bơm đã được bật\n");
    }
}

void NOTIFICATION_GetData(SensorData_t sensor_data, SystemMode_t system_mode, PumpState_t pump_state)
{
    s_sensor_moisture = sensor_data.soilMoisturePercent;
    s_sensor_temp     = sensor_data.airTemperatureCelsius;
    s_system_mode     = system_mode;
    s_pump_state      = pump_state;
}