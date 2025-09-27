/**
 * @file    pump_control.h
 * @author  [Tên bạn/nhóm]
 * @date    [yyyy-mm-dd]
 * @brief   Pump control driver header
 *
 * @details 
 *  - Cung cấp API để điều khiển bật/tắt bơm thông qua GPIO.
 *  - Có hàm giả lập `EMULATOR_Pump()` để mô phỏng trạng thái bơm trong môi trường test.
 *  - Được thiết kế để hoạt động dựa trên cấu trúc `GPIO_Type` định nghĩa trong peripheral.h.
 *
 * @note 
 *  - Trong ứng dụng thực tế, cần cấu hình chân GPIO trước khi sử dụng các hàm này.
 *  - Bơm được ánh xạ tới `PUMP_PORT` và `PUMP_PIN` trong peripheral.h.
 */

#ifndef PUMPCONTROL_H_
#define PUMPCONTROL_H_

#include "common.h"
#include "peripheral.h"
#include "stdbool.h"

/**
 * @brief Bật bơm bằng cách set GPIO pin ở mức cao.
 * @param port       Con trỏ đến GPIO_Type (ví dụ GPIOB).
 * @param gpio_port  Số thứ tự pin gán cho bơm.
 */
void turn_pump_on(GPIO_Type *port, int gpio_port);

/**
 * @brief Tắt bơm bằng cách clear GPIO pin.
 * @param port       Con trỏ đến GPIO_Type.
 * @param gpio_port  Số thứ tự pin gán cho bơm.
 */
void turn_pump_off(GPIO_Type *port, int gpio_port);

/**
 * @brief Giả lập bơm (in trạng thái bơm ra console).
 * @param gpio       Con trỏ đến GPIO_Type.
 * @param gpio_pin   Số thứ tự pin của bơm.
 * @note  Sử dụng cho mục đích mô phỏng khi không có phần cứng thật.
 */

bool get_pump_mode(GPIO_Type *gpio, int gpio_pin);

void EMULATOR_PumpControl(GPIO_Type *gpio, int gpio_pin);

/**
 * @brief Gọi giả lập máy bơm
 */
void EMULATOR_Pump(void *arg);


#endif /* PUMPCONTROL_H_ */
