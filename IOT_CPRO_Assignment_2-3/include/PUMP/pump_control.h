#ifndef PUMPCONTROL_H_
#define PUMPCONTROL_H_

#include "common.h"
#include "peripheral.h"
#include "stdbool.h"

/**
 * @brief Bật bơm bằng cách set GPIO pin ở mức cao.
 * @param port       Con trỏ đến GPIO_Type (ví dụ: GPIOB).
 * @param gpio_pin   Số thứ tự pin được gán cho bơm.
 * @note Trong chế độ giả lập, hành vi này chỉ thay đổi giá trị trong struct GPIO_Type.
 */
void PUMP_TurnOn(GPIO_Type *port, int gpio_pin);

/**
 * @brief Tắt bơm bằng cách clear GPIO pin.
 * @param port       Con trỏ đến GPIO_Type.
 * @param gpio_pin   Số thứ tự pin được gán cho bơm.
 */
void PUMP_TurnOff(GPIO_Type *port, int gpio_pin);

/**
 * @brief Lấy trạng thái hiện tại của bơm.
 * @param gpio       Con trỏ đến GPIO_Type.
 * @param gpio_pin   Số thứ tự pin của bơm.
 * @retval true      Nếu bơm đang bật (pin ở mức high).
 * @retval false     Nếu bơm đang tắt (pin ở mức low).
 */
bool PUMP_GetMode(GPIO_Type *gpio, int gpio_pin);

/**
 * @brief Giả lập trạng thái bơm (in/log ra trạng thái hiện tại).
 */
void EMULATOR_PumpControl(GPIO_Type *gpio, int gpio_pin);

/**
 * @brief Task giả lập bơm để chạy trong scheduler.
 */
void EMULATOR_Pump(void *arg);

#endif /* PUMPCONTROL_H_ */
