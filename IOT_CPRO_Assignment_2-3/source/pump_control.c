/**
 * @file    pump_control.c
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

#include "pump_control.h"

void turn_pump_on(GPIO_Type *gpio, int gpio_pin)
{
    gpio->DATA[gpio_pin] = 1;
}

void turn_pump_off(GPIO_Type *gpio, int gpio_pin)
{
    gpio->DATA[gpio_pin] = 0;
}

bool get_pump_mode(GPIO_Type *gpio, int gpio_pin)
{
    if (gpio->DATA[gpio_pin] == 1)
    {
        return true;
    }
    else if (gpio->DATA[gpio_pin] == 0)
    {
        return false;
    }
    else
    {
        printf("error");
    }
}

void EMULATOR_PumpControl(GPIO_Type *gpio, int gpio_pin)
{
    if (gpio_pin == 3 && gpio->PIN_SET[gpio_pin] == 1 && gpio->MODE == 1)
    {
        if (gpio->DATA[gpio_pin] == 1)
        {
            printf("TURN PUMP ON \n");
        }
        else if (gpio->DATA[gpio_pin] == 0)
        {
            printf("TURN PUMP OFF \n");
        }
    }
}

void EMULATOR_Pump(void *arg)
{
    (void)arg;
    EMULATOR_PumpControl(PUMP_PORT, PUMP_PIN);
}
