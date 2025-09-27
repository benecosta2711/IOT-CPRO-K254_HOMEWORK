/**
 * @file    led_dispaly.c
 * @author  [Tên bạn/nhóm]
 * @date    [yyyy-mm-dd]
 * @brief   Button driver implementation
 *
 * @details
 *  -
 *
 * @note
 *  .
 */

#include "led_display.h"

void LED_On(GPIO_Type *gpio, int gpio_pin) { gpio->DATA[gpio_pin] = 1; }
void LED_Off(GPIO_Type *gpio, int gpio_pin) { gpio->DATA[gpio_pin] = 0; }
void LED_Toggle(GPIO_Type *gpio, int gpio_pin) { gpio->DATA[gpio_pin] ^= 1; }

void LED_Control(void)
{
    switch (g_led_state)
    {
    case LED_NORMAL:
        LED_Off(LED_RED_PORT, LED_RED_PIN);
        LED_Off(LED_YELLOW_PORT, LED_YELLOW_PIN);
        LED_On(LED_GREEN_PORT, LED_GREEN_PIN);
        break;

    case LED_LOW_MOISTURE_ALERT:
        LED_On(LED_RED_PORT, LED_RED_PIN);
        LED_Off(LED_YELLOW_PORT, LED_YELLOW_PIN);
        LED_Off(LED_GREEN_PORT, LED_GREEN_PIN);
        break;

    case LED_WATERING:
        // LED_Off(LED_RED_PORT, LED_RED_PIN);
        LED_On(LED_YELLOW_PORT, LED_YELLOW_PIN);
        //LED_Off(LED_GREEN_PORT, LED_GREEN_PIN);
        break;

    case LED_ERROR:
        LED_Toggle(LED_RED_PORT, LED_RED_PIN);
        LED_Off(LED_YELLOW_PORT, LED_YELLOW_PIN);
        LED_Off(LED_GREEN_PORT, LED_GREEN_PIN);
        break;
    default:
        break;
    }
}

void EMULATOR_LedUpdate(GPIO_Type *gpio, int gpio_pin);

void EMULATOR_Led(void *arg)
{
    (void)arg;
    EMULATOR_LedUpdate(LED_RED_PORT, LED_RED_PIN);
    EMULATOR_LedUpdate(LED_YELLOW_PORT, LED_YELLOW_PIN);
    EMULATOR_LedUpdate(LED_GREEN_PORT, LED_GREEN_PIN);
}

void EMULATOR_LedUpdate(GPIO_Type *gpio, int gpio_pin)
{
    if (gpio->PIN_SET[gpio_pin] == 1 && gpio->MODE == 1 && gpio->DATA[gpio_pin] == 1)
    {
        if (gpio_pin == 1)
            printf("LED RED ON\n");
        else if (gpio_pin == 2)
            printf("LED YELLOW ON\n");
        else if (gpio_pin == 3)
            printf("LED GREEN ON\n");
    }
    else
    {
        if (gpio_pin == 1)
            printf("LED RED OFF\n");
        else if (gpio_pin == 2)
            printf("LED YELLOW OFF\n");
        else if (gpio_pin == 3)
            printf("LED GREEN OFF\n");
    }
}