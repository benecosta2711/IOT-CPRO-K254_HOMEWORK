#include "fsm_system.h"

static uint32_t s_manual_water_ms = 0;
static int g_count_pump_time = 0;

void PUMP_OffCallback(void)
{
    turn_pump_off(PUMP_PORT, PUMP_PIN);
    g_pump_sate = PUMP_OFF;
    g_count_pump_time = 0;
}

void FSM_System(void *arg)
{
    (void)arg;

    g_led_state = LED_WATERING;
    //
    if (g_count_pump_time > 0)
    {
        printf("time of pump: %d\n", g_count_pump_time--);
        if (g_count_pump_time == 0)
        {
            PUMP_OffCallback();
        }
        else
        {
            //
        }
    }

    READ_SoilMoisture(&g_sensor_data, SOILMOISTURE_PORT, SOILMOITURE_PIN);
    READ_Temperature(&g_sensor_data, TEMPERATURE_PORT, TEMPERATURE_PIN);

    //
    if (g_pump_sate == PUMP_ON)
    {
        g_led_state = LED_WATERING;
    }
    else
    {
        if (g_sensor_data.soil_moisture < MIN_SOIL_MOISTURE)
        {
            g_led_state = LED_LOW_MOISTURE_ALERT;
        }
        else
        {
            g_led_state = LED_NORMAL;
        }
    }

    //
    if (BUTTON1_IsPressed())
    {
        if (g_operation_mode == MODE_AUTO)
        {
            g_operation_mode = MODE_MANUAL;
            if (g_pump_sate == PUMP_ON)
            {
                PUMP_OffCallback();
            }
        }
        else
        {
            g_operation_mode = MODE_AUTO;
            s_manual_water_ms = 0;
        }
    }

    switch (g_operation_mode)
    {
    case MODE_AUTO:
    {
        printf("AUTO MODE \n");
        BUTTON2_IsPressed();
        if (g_pump_sate == PUMP_OFF)
        {
            if (g_sensor_data.soil_moisture < MIN_SOIL_MOISTURE)
            {
                turn_pump_on(PUMP_PORT, PUMP_PIN);
                g_count_pump_time = 3;
                g_pump_sate = PUMP_ON;
            }
        }
        else
        {
            if (g_sensor_data.soil_moisture >= MAX_SOIL_MOISTURE)
            {
                PUMP_OffCallback();
            }
        }
    }
    break;

    case MODE_MANUAL:
    {
        printf("MANUAL MODE \n");
        if (BUTTON2_IsPressed())
        {
            if (g_pump_sate == PUMP_OFF)
            {
                turn_pump_on(PUMP_PORT, PUMP_PIN);
                g_pump_sate = PUMP_ON;
                g_count_pump_time = 3;
            }
            else
            {
                /* Nếu đang ON mà người dùng bấm nữa, có thể tắt ngay (tuỳ yêu cầu):
                   PUMP_OffCallback();
                   s_manual_water_ms = 0;
                */
            }
        }
        if (s_manual_water_ms > 0)
        {
            const uint32_t step_ms = 50;
            if (s_manual_water_ms > step_ms)
            {
                s_manual_water_ms -= step_ms;
            }
            else
            {
                s_manual_water_ms = 0;
            }
            if (s_manual_water_ms == 0 && g_pump_sate == PUMP_ON)
            {
                PUMP_OffCallback();
            }
        }
    }
    break;

    default:
    {
        if (g_pump_sate == PUMP_ON)
        {
            PUMP_OffCallback();
        }
        g_operation_mode = MODE_AUTO;
        break;
    }
    }
}
