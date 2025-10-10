#include "CONFIG/config.h"
#include "SPWS_CONTROLLER/spws_controller.h"
#include "HAL_SENSORS/hal_sensors.h"
#include "HAL_ACTUATORS/hal_actuators.h"
#include "HAL_BUTTONS/hal_buttons.h"
#include <unistd.h>
#include <stdlib.h>

// global
SystemSettings_t g_system_config;
SystemState_t g_system_state;
SensorData_t g_last_sensor;

void System_Init(SystemSettings_t setting);

void System_Init(SystemSettings_t setting)
{
    g_system_config = setting;

    HAL_SENS_Init();
    HAL_ACT_Init();
    HAL_BTN_Init();

    g_system_state.currentMode = MODE_AUTO;
    g_system_state.pumpState = PUMP_OFF;
    g_system_state.ledState = LED_NORMAL;
    g_system_state.sensorCheckCounter = 0;
    g_system_state.manualWateringCounter = 0;
    g_system_state.wateringElapsed_s = 0;

    HAL_ACT_SetLed(g_system_state.ledState);
    LOGF("[SYS] Init done. Mode=AUTO, Pump=OFF");
}

int main(int argc, char **argv)
{
    /*Cấu hình cho hệ thống các giá trị được truyền bào cho các giá trị 
    {minMoistureThreshold, maxMoistureThreshold, manualWateringDuration_s, sensorReadInterval_s, maxWateringDuration_s}*/
    SystemSettings_t cfg = {
        .minMoistureThreshold = (argc > 1) ? atof(argv[1]) : CFG_MIN_MOISTURE_DEFAULT,
        .maxMoistureThreshold = (argc > 2) ? atof(argv[2]) : CFG_MAX_MOISTURE_DEFAULT,
        .manualWateringDuration_s = (argc > 3) ? (unsigned)atoi(argv[3]) : CFG_MANUAL_WATER_DUR_S_DEFAULT,
        .sensorReadInterval_s = (argc > 4) ? (unsigned)atoi(argv[4]) : CFG_SENSOR_INTERVAL_S_DEFAULT,
        .maxWateringDuration_s = (argc > 5) ? (unsigned)atoi(argv[5]) : CFG_MAX_WATER_DUR_S_DEFAULT,
    };

    LOGF("CFG: min=%.1f max=%.1f manual=%us sensorInt=%us maxWater=%us",
         cfg.minMoistureThreshold, cfg.maxMoistureThreshold,
         cfg.manualWateringDuration_s, cfg.sensorReadInterval_s,
         cfg.maxWateringDuration_s);

    //LOGF("Controls: type 'a'+Enter to toggle AUTO/MANUAL, 'm'+Enter manual water, Ctrl+C to quit.");

    System_Init(cfg);

    while (1)
    {
        printf("//=================//\n");
        SYSTEM_Fsm();
        sleep(1);
    }
    return 0;
}