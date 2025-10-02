#ifndef COMMON_H_
#define COMMON_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

// --- Common Definitions and Enumerations ---
#define MAX_SOIL_MOISTURE 100
#define MIN_SOIL_MOISTURE 30
#define MAX_TIME_BESPROEI 60
#define SENSOR_CYCLE    10
#define MIN_TEMPERATURE -10

// --- SYSTEM ---
#define GPIO_OUTPUT 1
#define GPIO_INPUT 0
#define TIME_TICKS 1000

// --- Data Sensor ---
#define CURRENT_SOILMOISTURE 10
#define CURRENT_TEMPERATURE 20

/**
 * @enum struct_operation_mode
 * @brief Enumeration for operation modes: automatic and manual.
 */
typedef enum{
    MODE_AUTO,
    MODE_MANUAL
} struct_operation_mode;

extern struct_operation_mode g_operation_mode;

/**
 * @enum struct_pump_state
 * @brief Enumeration for pump states: on and off.
 */
typedef enum{
    PUMP_OFF,
    PUMP_ON
} struct_pump_state;

extern struct_pump_state g_pump_sate;

/**
 * @enum struct_led_state
 * @brief Enumeration for LED states: normal, warning, low moisture alert, and error.
 */
typedef enum{
    LED_NORMAL,
    LED_WATERING,
    LED_LOW_MOISTURE_ALERT,
    LED_ERROR
} struct_led_state;

extern struct_led_state g_led_state;

/**
 * @struct struct_sensor_data
 * @brief Structure to hold sensor data: soil moisture and temperature.
 */
typedef struct{
    float soil_moisture;
    float temperature;
}struct_sensor_data;

extern struct_sensor_data g_sensor_data;

#endif /* COMMON_H_ */