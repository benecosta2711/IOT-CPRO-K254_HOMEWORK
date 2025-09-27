/**
 * @file    sensor.c
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

#include "sensor.h"
#include <stdio.h>

#define TIME_WRITE_SENSOR 1000000
static int count_emulator_sensor = 0;

void EMULATOR_Sensor(void *arg)
{
    (void)arg;
    EMULATOR_SoilMoisture(SOILMOISTURE_PORT, SOILMOITURE_PIN);
    EMULATOR_Temperature(TEMPERATURE_PORT, TEMPERATURE_PIN);
}

void EMULATOR_SoilMoisture(GPIO_Type *gpio, uint8_t gpio_pin)
{
    if (count_emulator_sensor < 20 || count_emulator_sensor > 40)
    {
        count_emulator_sensor++;
        uint8_t current_soil = CURRENT_SOILMOISTURE;
        for (int i = TIME_WRITE_SENSOR; i > 0; i--)
        {
            if (i % (TIME_WRITE_SENSOR) == 0)
            {
                current_soil++;
                if (gpio->PIN_SET[gpio_pin] == 1)
                {
                    gpio->DATA[gpio_pin] = current_soil;
                }
                printf("Sensor Soil Moisture sent data %d%% \n", current_soil);
            }
        }
    }
    else
    {
        count_emulator_sensor++;
        if (gpio->PIN_SET[gpio_pin] == 1)
        {
            gpio->DATA[gpio_pin] = 50;
        }
        printf("Sensor Soil Moisture sent data %d%% \n", 50);
    }
}

void EMULATOR_Temperature(GPIO_Type *gpio, uint8_t gpio_pin)
{
    if (count_emulator_sensor < 20 || count_emulator_sensor > 40)
    {
        count_emulator_sensor++;
        uint8_t current_temp = CURRENT_TEMPERATURE;
        for (int i = TIME_WRITE_SENSOR; i > 0; i--)
        {
            if (i % (TIME_WRITE_SENSOR) == 0)
            {
                current_temp++;
                if (gpio->PIN_SET[gpio_pin] == 1)
                {
                    gpio->DATA[gpio_pin] = current_temp;
                }
                printf("Sensor Temperature sent data  %d C \n", current_temp);
            }
        }
    }
    else
    {
        count_emulator_sensor++;
        if (gpio->PIN_SET[gpio_pin] == 1)
        {
            gpio->DATA[gpio_pin] = 24;
        }
        printf("Sensor Temperature sent data  %d C \n", 24);
    }
}

void READ_SoilMoisture(SENSOR_Data *data_sensor, GPIO_Type *gpio, uint8_t gpio_pin)
{
    data_sensor->soilMoisture = gpio->DATA[gpio_pin];
}

void READ_Temperature(SENSOR_Data *data_sensor, GPIO_Type *gpio, uint8_t gpio_pin)
{
    data_sensor->temperature = gpio->DATA[gpio_pin];
}
