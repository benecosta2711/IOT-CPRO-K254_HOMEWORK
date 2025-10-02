#ifndef SENSOR_H_
#define SENSOR_H_

#include "common.h"
#include "peripheral.h"

// --- Function Prototypes ---
/**
 * @brief Giả lập cảm biến độ ẩm load data vào chân gpio pin
 * @param gpio  Con trỏ đến GPIO_Type
 * @param gpio_pin Số thứ tự pin trong port
 */
void EMULATOR_SoilMoisture(GPIO_Type *gpio, uint8_t gpio_pin);

/**
 * @brief Giả lập cảm biến độ ẩm load data vào chân gpio pin
 * @param gpio  Con trỏ đến GPIO_Type
 * @param gpio_pin Số thứ tự pin trong port
 */
void EMULATOR_Temperature(GPIO_Type *gpio, uint8_t gpio_pin);

/**
 * @brief Gọi giả lập cảm biến 
 */
void EMULATOR_Sensor(void *arg);

/**
 * @brief Đọc dữ liệu của cảm biến độ ẩm
 * @param data_sensor Chứ dữ liệu đọc đựa từ cảm biến
 * @param gpio con trỏ đến GPIO_Type
 * @param gpio_pin số thứ tự của pin trong port
 */
void READ_SoilMoisture(struct_sensor_data *data_sensor, GPIO_Type *gpio, uint8_t gpio_pin);

/**
 * @brief Đọc dữ liệu của cảm biến nhiệt độ
 * @param data_sensor Chứ dữ liệu đọc đựa từ cảm biến
 * @param gpio con trỏ đến GPIO_Type
 * @param gpio_pin số thứ tự của pin trong port
 */
void READ_Temperature(struct_sensor_data *data_sensor, GPIO_Type *gpio, uint8_t gpio_pin);

#endif /* SENSOR_H_ */