#include "notification.h"

static float s_sensor_moisture = 0;
static float s_sensor_temp = 0;
static struct_operation_mode s_system_mode = 0;
static struct_pump_state s_pump_state = 0;

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

void NOTIFICATION_GetData(struct_sensor_data sensor_data, struct_operation_mode system_mode, struct_pump_state pump_state)
{
    s_sensor_moisture = sensor_data.soil_moisture;
    s_sensor_temp     = sensor_data.temperature;
    s_system_mode     = system_mode;
    s_pump_state      = pump_state;
}