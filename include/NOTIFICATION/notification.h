#ifndef NOTIFICATION_H_
#define NOTIFICATION_H_

#include "COMMON/common.h"
#include "SENSOR/sensor.h"

/**
 * @brief Hàm giả lập việc gửi/thể hiện thông báo.
 */
void EMULATOR_Notification(void *arg);

/**
 * @brief Lấy dữ liệu hiện tại để phục vụ việc thông báo.
 */
void NOTIFICATION_GetData(SensorData_t sensor_data, SystemMode_t system_mode, PumpState_t pump_state);

#endif /* NOTIFICATION_H_ */
