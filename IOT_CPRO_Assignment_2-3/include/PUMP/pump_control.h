#ifndef PUMPCONTROL_H_
#define PUMPCONTROL_H_

#include "common.h"
#include "peripheral.h"
#include "stdbool.h"

/**
 * @brief Bật bơm bằng cách set GPIO pin ở mức cao.
 *
 * @param port       Con trỏ đến GPIO_Type (ví dụ: GPIOB).
 * @param gpio_pin   Số thứ tự pin được gán cho bơm.
 *
 * @note Trong chế độ giả lập, hành vi này chỉ thay đổi giá trị trong struct GPIO_Type.
 */
void turn_pump_on(GPIO_Type *port, int gpio_pin);

/**
 * @brief Tắt bơm bằng cách clear GPIO pin.
 *
 * @param port       Con trỏ đến GPIO_Type.
 * @param gpio_pin   Số thứ tự pin được gán cho bơm.
 */
void turn_pump_off(GPIO_Type *port, int gpio_pin);

/**
 * @brief Lấy trạng thái hiện tại của bơm.
 *
 * @param gpio       Con trỏ đến GPIO_Type.
 * @param gpio_pin   Số thứ tự pin của bơm.
 *
 * @retval true      Nếu bơm đang bật (pin ở mức high).
 * @retval false     Nếu bơm đang tắt (pin ở mức low).
 */
bool get_pump_mode(GPIO_Type *gpio, int gpio_pin);

/**
 * @brief Giả lập trạng thái bơm (in/log ra trạng thái hiện tại).
 *
 * @param gpio       Con trỏ đến GPIO_Type.
 * @param gpio_pin   Số thứ tự pin của bơm.
 *
 * @note Chỉ sử dụng trong môi trường test khi không có phần cứng thật.
 */
void EMULATOR_PumpControl(GPIO_Type *gpio, int gpio_pin);

/**
 * @brief Task giả lập bơm để chạy trong scheduler.
 *
 * @param arg  Tham số tùy chọn (có thể là NULL).
 *
 * @details
 *  - Hàm này có thể được đăng ký vào scheduler để tự động log trạng thái bơm định kỳ.
 */
void EMULATOR_Pump(void *arg);

#endif /* PUMPCONTROL_H_ */
