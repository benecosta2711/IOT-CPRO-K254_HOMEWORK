
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
 * @param gpio     Con trỏ đến GPIO_Type (ví dụ: GPIOB).
 * @param gpio_pin Vị trí pin cần giả lập.
 * @note 
 *  - Dùng trong test software khi không có phần cứng thật.
 *  - Có thể set nhiều lần để mô phỏng nhiều nút khác nhau.
 */
void EMULATOR_ButtonSetOn(GPIO_Type *gpio, int gpio_pin);

/**
 * @brief Gọi hàm giả lập nút nhấn.
 * @param arg  Tham số tuỳ chọn (có thể là NULL hoặc struct mô phỏng).
 * @note 
 *  - Được thiết kế để chạy như một task trong scheduler.
 *  - Khi gọi sẽ tự động cập nhật trạng thái nút theo giả lập.
 */
void EMULATOR_Button(void *arg);

#endif /* BUTTON_H_ */
