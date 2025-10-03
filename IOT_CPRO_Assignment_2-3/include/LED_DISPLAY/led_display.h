#ifndef LED_DISPLAY_H_
#define LED_DISPLAY_H_

#include "common.h"
#include "peripheral.h"

/**
 * @brief Bật LED tại một GPIO pin.
 * @param gpio     Con trỏ đến GPIO_Type (ví dụ GPIOC).
 * @param gpio_pin Vị trí pin được gán cho LED.
 */
void LED_On(GPIO_Type *gpio, int gpio_pin);

/**
 * @brief Tắt LED tại một GPIO pin.
 * @param gpio     Con trỏ đến GPIO_Type (ví dụ GPIOC).
 * @param gpio_pin Vị trí pin được gán cho LED.
 */
void LED_Off(GPIO_Type *gpio, int gpio_pin);

/**
 * @brief Đảo trạng thái LED (nếu đang bật thì tắt, đang tắt thì bật).
 * @param gpio     Con trỏ đến GPIO_Type.
 * @param gpio_pin Vị trí pin của LED.
 */
void LED_Toggle(GPIO_Type *gpio, int gpio_pin);

/**
 * @brief Điều khiển LED theo trạng thái hệ thống.
 * @note  Hàm này phụ thuộc vào biến trạng thái toàn cục (ví dụ g_pump_state).
 */
void LED_Control(void);

/**
 * @brief Giả lập LED (in trạng thái LED ra console).
 */
void EMULATOR_LedUpdate(GPIO_Type *gpio, int gpio_pin);

/**
 * @brief Gọi hàm Giả lập LED (in trạng thái LED ra console).
 */
void EMULATOR_Led(void *arg);

#endif /* DISPLAYLED_H_ */
