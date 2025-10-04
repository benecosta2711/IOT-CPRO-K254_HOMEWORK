#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>
#include <stdio.h>

typedef enum {
    MODE_AUTO = 0,
    MODE_MANUAL
} SystemMode_t;

typedef enum {
    PUMP_OFF = 0,
    PUMP_ON
} PumpState_t;

typedef enum {
    LED_NORMAL = 0,          
    LED_WATERING,            
    LED_LOW_MOISTURE_ALERT,  
    LED_ERROR                
} LedState_t;

typedef struct {
    float soilMoisturePercent;     
    float airTemperatureCelsius;   
} SensorData_t;

typedef struct {
    float minMoistureThreshold;    
    float maxMoistureThreshold;    
    unsigned manualWateringDuration_s; 
    unsigned sensorReadInterval_s;     
    unsigned maxWateringDuration_s;    
} SystemSettings_t;

typedef struct {
    SystemMode_t currentMode;
    PumpState_t  pumpState;
    LedState_t   ledState;

    unsigned sensorCheckCounter;
    unsigned manualWateringCounter;
    unsigned wateringElapsed_s; 
} SystemState_t;

#define CFG_MIN_MOISTURE_DEFAULT        35.0f
#define CFG_MAX_MOISTURE_DEFAULT        55.0f
#define CFG_MANUAL_WATER_DUR_S_DEFAULT  10U
#define CFG_SENSOR_INTERVAL_S_DEFAULT   2U
#define CFG_MAX_WATER_DUR_S_DEFAULT     60U

#define LOGF(fmt, ...)  do { printf(fmt "\n", ##__VA_ARGS__); fflush(stdout); } while(0)

extern SystemSettings_t g_system_config;
extern SystemState_t g_system_state;
extern SensorData_t g_last_sensor;

#endif // CONFIG_H
