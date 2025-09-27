/**
 * @file    common.h
 * @author  [Tên bạn/nhóm]
 * @date    [yyyy-mm-dd]
 * @brief   Button driver header
 *
 * @details 
 *  - 
 *
 * @note 
 *  - 
 */

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
 * @enum OPERATION_Mode
 * @brief Enumeration for operation modes: automatic and manual.
 * define the operation mode of the device
 */
typedef enum{
    MODE_IDLE,
    MODE_AUTO,
    MODE_MANUAL
} OPERATION_Mode;

extern OPERATION_Mode g_operation_mode;

/**
 * @enum PUMP_State
 * @brief Enumeration for pump states: on and off.
 * define the state of the pump
 */
typedef enum{
    PUMP_OFF,
    PUMP_ON
} PUMP_State;

extern PUMP_State g_pump_sate;

/**
 * @enum LED_State
 * @brief Enumeration for LED states: normal, warning, low moisture alert, and error.
 * define the state of the LED
 */
typedef enum{
    LED_NORMAL,
    LED_WATERING,
    LED_LOW_MOISTURE_ALERT,
    LED_ERROR
} LED_State;

extern LED_State g_led_state;

/***
 * @struct SYSTEM_Config
 * @brief Structure to hold system configuration parameters.
 * define the structure to hold system configuration parameters
*/
typedef struct{
    float soilMoisture_besproei;
    float soilMoisture_unbesproei;
    int time_besproei;
    int cycle_sensor;
    int system_mode;
} SYSTEM_Config;

/**
 * @struct SENSOR_Data
 * @brief Structure to hold sensor data: soil moisture and temperature.
 * define the structure to hold sensor data
 */
typedef struct{
    float soilMoisture;
    float temperature;
}SENSOR_Data;

extern SENSOR_Data g_sensor_data;

#endif /* COMMON_H_ */