/**
 * @file    fsm_system.c
 * @author  [Tên bạn/nhóm]
 * @date    [yyyy-mm-dd]
 * @brief   Button driver implementation
 *
 * @details
 *  -
 *
 * @note
 *  -
 */
#include "fsm_system.h"

/* Manual watering countdown (ms). Với SCH_Init(10), mỗi lần FSM chạy giả sử 50ms */
static uint32_t s_manual_water_ms = 0;


static int g_count_pump_time = 0;

void PUMP_OffCallback(void)
{
    turn_pump_off(PUMP_PORT, PUMP_PIN);
    g_pump_sate = PUMP_OFF;
    g_count_pump_time = 0;
}

/* Gợi ý: đăng ký FSM_System vào scheduler:
   SCH_Add(FSM_System, NULL, 50); // 50ms một lần
*/
void FSM_System(void *arg)
{
    (void)arg;
    g_led_state = LED_WATERING;

    /* 0) Kiểm tra biến đếm thời gian tưới nước có đàn tồn tại không nếu có thì--*/
    if(g_count_pump_time > 0)
    {
        printf("time of pump: %d\n", g_count_pump_time--);
        if(g_count_pump_time == 0)
        {
            PUMP_OffCallback();
        }
    }

    /* 1) Đọc cảm biến */
    READ_SoilMoisture(&g_sensor_data, SOILMOISTURE_PORT, SOILMOITURE_PIN);
    READ_Temperature(&g_sensor_data, TEMPERATURE_PORT, TEMPERATURE_PIN);

    /* 2) Cập nhật LED theo trạng thái tổng quát */
    if (g_pump_sate == PUMP_ON)
    {
        g_led_state = LED_WATERING;
    }
    else
    {
        if (g_sensor_data.soilMoisture < MIN_SOIL_MOISTURE)
        {
            g_led_state = LED_LOW_MOISTURE_ALERT;
        }
        else
        {
            g_led_state = LED_NORMAL;
        }
    }

    /* 3) Xử lý nút chuyển chế độ (Button1): toggle AUTO <-> MANUAL */
    if (BUTTON1_IsPressed())
    {
        if (g_operation_mode == MODE_AUTO)
        {
            g_operation_mode = MODE_MANUAL;
            /* Sang MANUAL phải đảm bảo bơm tắt */
            if (g_pump_sate == PUMP_ON)
            {
                PUMP_OffCallback();
            }
        }
        else
        { /* MODE_MANUAL -> MODE_AUTO */
            g_operation_mode = MODE_AUTO;
            /* Reset manual countdown khi quay lại AUTO */
            s_manual_water_ms = 0;
        }
    }

    switch (g_operation_mode)
    {
    case MODE_IDLE:
        /* Khởi động mặc định vào AUTO */
        g_operation_mode = MODE_AUTO;
        break;

    case MODE_AUTO:
    {
        printf("AUTO MODE \n");
        BUTTON2_IsPressed();
        /* Logic AUTO theo ngưỡng cấu hình */
        if (g_pump_sate == PUMP_OFF)
        {
            if (g_sensor_data.soilMoisture < MIN_SOIL_MOISTURE)
            {
                /* Bắt đầu tưới */
                turn_pump_on(PUMP_PORT, PUMP_PIN);
                g_count_pump_time = 3;
                g_pump_sate = PUMP_ON;
                /* Không dùng timer one-shot, nên bỏ qua ở bản tối giản này */
            }
        }
        else
        { /* PUMP_ON */
            if (g_sensor_data.soilMoisture >= MAX_SOIL_MOISTURE)
            {
                PUMP_OffCallback();
            }
            /* Nếu muốn giới hạn tối đa tưới mỗi lần:
               có thể thêm 1 counter ms giống s_manual_water_ms để auto dừng */
        }
    } 
    break;

    case MODE_MANUAL:
    {
        printf("MANUAL MODE \n");
        /* Nút 2: tưới tay 10s */
        if (BUTTON2_IsPressed())
        {
            if (g_pump_sate == PUMP_OFF)
            {
                turn_pump_on(PUMP_PORT, PUMP_PIN);
                g_pump_sate = PUMP_ON;
                g_count_pump_time = 3;
                //s_manual_water_ms = 10000; /* 10 giây */
            }
            else
            {
                /* Nếu đang ON mà người dùng bấm nữa, có thể tắt ngay (tuỳ yêu cầu):
                   PUMP_OffCallback();
                   s_manual_water_ms = 0;
                */
            }
        }

        /* Đếm lùi manual watering (nếu đang tưới tay) */
        if (s_manual_water_ms > 0)
        {
            /* Giả sử FSM_System chạy mỗi 50ms (period khi SCH_Add) */
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
        /* Bảo vệ */
        if (g_pump_sate == PUMP_ON)
        {
            PUMP_OffCallback();
        }
        g_operation_mode = MODE_AUTO;
        break;
    }
}
