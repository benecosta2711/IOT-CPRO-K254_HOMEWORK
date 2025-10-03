
#ifndef BUTTON_H_
#define BUTTON_H_

#include "stdbool.h"
#include "common.h"
#include "peripheral.h"

/**
 * @brief Callback xử lý khi nút nhấn số 1 được phát hiện và set flag
 */
void EXCEPTION1_Callback(void);

/**
 * @brief Callback xử lý khi nút nhấn số 2 được phát hiện và set flag
 */
void EXCEPTION2_Callback(void);

/**
 * @brief Kiểm tra trạng thái nút số 1.
 */
bool BUTTON1_IsPressed(void);

/**
 * @brief Kiểm tra trạng thái nút số 2.
 */
bool BUTTON2_IsPressed(void);

/**
 * @brief Giả lập việc nhấn nút tại một GPIO pin cụ thể.
 */
void EMULATOR_ButtonSetOn(GPIO_Type *gpio, int gpio_pin);

/**
 * @brief Gọi hàm giả lập nút nhấn.
 */
void EMULATOR_Button(void *arg);

#endif /* BUTTON_H_ */
