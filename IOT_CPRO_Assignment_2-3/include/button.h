/**
 * @file    button.h
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


#ifndef BUTTON_H_
#define BUTTON_H_

#include "stdbool.h"
#include "common.h"
#include "peripheral.h"

/**
 * @brief Callback xử lý khi nút nhấn được phát hiện.
 * @note  Hàm này chỉ set flag, không xử lý trực tiếp logic.
 */
void EXCEPTION1_Callback(void);
void EXCEPTION2_Callback(void);


bool BUTTON1_IsPressed(void);
bool BUTTON2_IsPressed(void);


/**
 * @brief Giả lập việc nhấn nút tại một GPIO pin.
 * @param gpio     Con trỏ đến GPIO_Type (ví dụ GPIOB).
 * @param gpio_pin Vị trí pin cần giả lập.
 */
void EMULATOR_ButtonSetOn(GPIO_Type *gpio, int gpio_pin);

/**
 * @brief Gọi hàm giả lập Button
 */
void EMULATOR_Button(void *arg);

#endif