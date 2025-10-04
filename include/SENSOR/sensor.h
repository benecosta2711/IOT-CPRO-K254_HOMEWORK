#ifndef SENSOR_H_
#define SENSOR_H_

#include "COMMON/common.h"
#include "PERIPHERAL/peripheral.h"

// --- Function Prototypes ---
/**
 * @brief Giả lập cảm biến độ ẩm load data vào chân gpio pin
 */
void EMULATOR_SoilMoisture(GPIO_Type *gpio, uint8_t gpio_pin);

/**
 * @brief Giả lập cảm biến độ ẩm load data vào chân gpio pin
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
void READ_SoilMoisture(SensorData_t *data_sensor, GPIO_Type *gpio, uint8_t gpio_pin);

/**
 * @brief Đọc dữ liệu của cảm biến nhiệt độ
 * @param data_sensor Chứ dữ liệu đọc đựa từ cảm biến
 * @param gpio con trỏ đến GPIO_Type
 * @param gpio_pin số thứ tự của pin trong port
 */
void READ_Temperature(SensorData_t *data_sensor, GPIO_Type *gpio, uint8_t gpio_pin);

#endif /* SENSOR_H_ */