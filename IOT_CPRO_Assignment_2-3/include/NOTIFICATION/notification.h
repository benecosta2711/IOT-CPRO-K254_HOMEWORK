#ifndef NOTIFICATION_H_
#define NOTIFICATION_H_

#include "common.h"
#include "sensor.h"

/**
 * @brief Hàm giả lập việc gửi/thể hiện thông báo.
 */
void EMULATOR_Notification(void *arg);

/**
 * @brief Lấy dữ liệu hiện tại để phục vụ việc thông báo.
 */
void NOTIFICATION_GetData(struct_sensor_data sensor_data, struct_operation_mode system_mode, struct_pump_state pump_state);

#endif /* NOTIFICATION_H_ */
