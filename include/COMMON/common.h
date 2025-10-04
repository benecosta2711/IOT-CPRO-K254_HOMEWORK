#ifndef COMMON_H_
#define COMMON_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

// --- Common Definitions and Enumerations ---
#define MAX_SOIL_MOISTURE 100
#define MIN_SOIL_MOISTURE 30
#define MAX_TIME_BESPROEI 60
#define SENSOR_CYCLE 10
#define MIN_TEMPERATURE -10

// --- SYSTEM ---
#define GPIO_OUTPUT 1
#define GPIO_INPUT 0
#define TIME_TICKS 1000

// --- Data Sensor ---
#define CURRENT_SOILMOISTURE 10
#define CURRENT_TEMPERATURE 20

/**
 * @enum system_mode_t
 * @brief Enumeration for operation modes: automatic and manual.
 */
typedef enum
{
    MODE_AUTO,
    MODE_MANUAL
} SystemMode_t;

extern SystemMode_t g_operation_mode;

/**
 * @enum PumpState_t
 * @brief Enumeration for pump states: on and off.
 */
typedef enum
{
    PUMP_OFF,
    PUMP_ON
} PumpState_t;

extern PumpState_t g_pump_sate;

/**
 * @enum LedState_t
 * @brief Enumeration for LED states: normal, warning, low moisture alert, and error.
 */
typedef enum
{
    LED_NORMAL,
    LED_WATERING,
    LED_LOW_MOISTURE_ALERT,
    LED_ERROR
} LedState_t;

extern LedState_t g_led_state;

/**
 * @struct SensorData_t
 * @brief Structure to hold sensor data: soil moisture and temperature.
 */
typedef struct
{
    float soilMoisturePercent;
    float airTemperatureCelsius;
} SensorData_t;

extern SensorData_t g_sensor_data;

typedef struct
{
    float minMoistureThresHold;
    float maxMoistureThresHold;
    unsigned int maxWateringDuration_s;
    unsigned int sensorReadInterval_s;
    unsigned int manualWateringDuration_t;
} SystemSettings_t;

typedef struct 
{
    SystemMode_t currentMode;
    PumpState_t pumpState;
    LedState_t ledState;
    unsigned int wateringTimeCounter;
    unsigned int sensorCheckCounter;
} SystemState_t;

#endif /* COMMON_H_ */