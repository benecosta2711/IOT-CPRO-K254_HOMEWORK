/**
 * @file    button.c
 * @author  [Tên bạn/nhóm]
 * @date    [yyyy-mm-dd]
 * @brief   Button driver implementation
 *
 * @details
 *  - Cài đặt hàm callback `BUTTON_Callback()`.
 *  - Cài đặt hàm `EMULATOR_Button()` để mô phỏng nút nhấn.
 *  - Sử dụng biến `button_pressed_flag` để báo hiệu sự kiện.
 *
 * @note
 *  - Trong ứng dụng thực tế, callback chỉ nên set flag,
 *    còn xử lý logic thực hiện ở main loop hoặc FreeRTOS task.
 */

#include "button.h"
#include <stdio.h>

#define TIME_WRITE_BUTTON 2000000000

static int button1_is_pressed = 0;
static int button2_is_pressed = 0;

volatile uint8_t button1_pressed_flag = 0;
volatile uint8_t button2_pressed_flag = 0;

void EXCEPTION1_Callback(void) { button1_pressed_flag = 1; }
void EXCEPTION2_Callback(void) { button2_pressed_flag = 1; }

bool BUTTON1_IsPressed(void)
{
    if (button1_pressed_flag)
    {
        button1_pressed_flag = 0;
        return true;
    }
    return false;
}

bool BUTTON2_IsPressed(void)
{
    if (button2_pressed_flag)
    {
        button2_pressed_flag = 0;
        return true;
    }
    return false;
}

void EMULATOR_Button(void *arg)
{
    (void)arg;
    static int i = 0;
    if(i++%4)
    {
    EMULATOR_ButtonSetOn(BUTTON2_PORT, BUTTON2_PIN);
    }
    else
    {
    EMULATOR_ButtonSetOn(BUTTON1_PORT, BUTTON1_PIN);
    }
}

void EMULATOR_ButtonSetOn(GPIO_Type *gpio, int gpio_pin)
{
    //for (int i = TIME_WRITE_BUTTON; i >= 0; i--){}
    if(button1_is_pressed % 10 == 0 || button2_is_pressed % 25 == 0)
    {
    if (gpio == GPIOA)
    {
        gpio->DATA[gpio_pin] = 1;
        printf("\n=======BUTTON 1 PRESSED=======\n");

        if (gpio == BUTTON1_PORT && gpio_pin == BUTTON1_PIN)
            EXCEPTION1_Callback();

        gpio->DATA[gpio_pin] = 0;
    }
    else if (gpio == GPIOB)
    {
        gpio->DATA[gpio_pin] = 1;
        printf("=======BUTTON 2 PRESSED=======\n");

        if (gpio == BUTTON2_PORT && gpio_pin == BUTTON2_PIN)
            EXCEPTION2_Callback();

        gpio->DATA[gpio_pin] = 0;
    }
    }
    if (gpio == GPIOA)
    button1_is_pressed++;
    if (gpio == GPIOB)
    button2_is_pressed++;
}
