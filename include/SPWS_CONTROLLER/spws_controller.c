#include "spws_controller.h"
#include "hal_sensors.h"
#include "hal_actuators.h"
#include "hal_buttons.h"

static void ApplyLedByState(void)
{
    HAL_ACT_SetLed(g_system_state.ledState);
}

static void PumpOn(void)
{
    g_system_state.pumpState = PUMP_ON;
    g_system_state.ledState = LED_WATERING;
    HAL_ACT_TurnPumpOn();
    ApplyLedByState();
    LOGF("[SYS] Start watering");
}

static void PumpOff(const char *reason)
{
    g_system_state.pumpState = PUMP_OFF;
    g_system_state.ledState = LED_NORMAL;
    HAL_ACT_TurnPumpOff();
    ApplyLedByState();
    LOGF("[SYS] Stop watering (%s)", reason ? reason : "done");
}

static void OnModeChanged(void)
{
    const char *m = (g_system_state.currentMode == MODE_AUTO) ? "AUTO" : "MANUAL";
    LOGF("[SYS] Mode -> %s", m);
    if (g_system_state.currentMode == MODE_MANUAL && g_system_state.pumpState == PUMP_ON)
    {
        PumpOff("switch to MANUAL");
    }
}

static void CheckButtons(void)
{
    if (HAL_BTN_ReadToggleMode())
    {
        g_system_state.currentMode = (g_system_state.currentMode == MODE_AUTO) ? MODE_MANUAL : MODE_AUTO;
        OnModeChanged();
    }
    if (g_system_state.currentMode == MODE_MANUAL && HAL_BTN_ReadManualWater())
    {
        g_system_state.manualWateringCounter = g_system_config.manualWateringDuration_s;
        if (g_system_state.pumpState == PUMP_OFF)
            PumpOn();
    }
}

static void RunAutoLogic(void)
{
    if (g_last_sensor.soilMoisturePercent < g_system_config.minMoistureThreshold)
    {
        if (g_system_state.pumpState == PUMP_OFF)
            PumpOn();
    }
    if (g_system_state.pumpState == PUMP_ON)
    {
        if (g_last_sensor.soilMoisturePercent > g_system_config.maxMoistureThreshold)
        {
            PumpOff("reached max moisture");
        }
        else 
        {
            // do not thing
        }
    }
}

static void RunManualLogic(void)
{
    if (g_system_state.manualWateringCounter == 0 && g_system_state.pumpState == PUMP_ON)
    {
        PumpOff("manual done");
    }
}

void SYSTEM_Fsm(void)
{
    // 1) Mô phỏng cảm biến theo trạng thái bơm
    HAL_SENS_SimulateTick(g_system_state.pumpState);

    // 2) Đếm thời gian tưới nước 
    if (g_system_state.manualWateringCounter > 0)
        g_system_state.manualWateringCounter--;

    // 3) đọc nút giá trị nút nhấn
    CheckButtons();

    // 4) đọc sensor theo chu kỳ
    if (g_system_state.sensorCheckCounter == 0)
    {
        HAL_SENS_Read(&g_last_sensor);
        LOGF("[SENS] Soil=%.1f%%, Temp=%.1f°C",
             g_last_sensor.soilMoisturePercent, g_last_sensor.airTemperatureCelsius);

        // cảnh báo độ ẩm thấp nếu đang ở AUTO và chưa tưới
        if (g_system_state.currentMode == MODE_AUTO &&
            g_last_sensor.soilMoisturePercent < g_system_config.minMoistureThreshold &&
            g_system_state.pumpState == PUMP_OFF)
        {
            g_system_state.ledState = LED_LOW_MOISTURE_ALERT;
            ApplyLedByState();
        }
        else if (g_system_state.pumpState == PUMP_OFF)
        {
            g_system_state.ledState = LED_NORMAL;
            ApplyLedByState();
        }
    }

    // 5) chạy logic theo mode
    if (g_system_state.currentMode == MODE_AUTO)
        RunAutoLogic();
    else
        RunManualLogic();

    // 6) reset chu kỳ sensor
    g_system_state.sensorCheckCounter++;
    if (g_system_state.sensorCheckCounter >= g_system_config.sensorReadInterval_s)
        g_system_state.sensorCheckCounter = 0;
}
