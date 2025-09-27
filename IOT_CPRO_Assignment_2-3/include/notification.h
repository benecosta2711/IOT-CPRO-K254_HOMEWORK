/**
 * @file    notification.h
 * @author  [Tên bạn/nhóm]
 * @date    [yyyy-mm-dd]
 * @brief   Notification (thông báo trạng thái) driver header
 *
 * @details
 *  - Cung cấp API để hiển thị hoặc gửi thông báo dựa trên dữ liệu cảm biến, 
 *    chế độ hệ thống và trạng thái bơm.
 *  - Hỗ trợ cả chế độ giả lập (emulation) để kiểm thử mà không cần phần cứng thực tế.
 *
 * @note
 *  - Module này chỉ thu thập dữ liệu và hiển thị/gửi thông báo, 
 *    không thực hiện điều khiển trực tiếp phần cứng.
 *  - Trong chế độ giả lập, hàm EMULATOR_Notification cho phép test logic báo hiệu 
 *    trên môi trường phần mềm.
 */

#ifndef NOTIFICATION_H_
#define NOTIFICATION_H_

#include "common.h"
#include "sensor.h"

/**
 * @brief Hàm giả lập việc gửi/thể hiện thông báo.
 *
 * @param arg  Tham số tuỳ chọn (có thể là NULL hoặc struct dữ liệu giả lập).
 *
 * @note
 *  - Được thiết kế để chạy như một task trong scheduler.
 *  - Cho phép mô phỏng hành vi thông báo (bật LED, in console, ...).
 */
void EMULATOR_Notification(void *arg);

/**
 * @brief Lấy dữ liệu hiện tại để phục vụ việc thông báo.
 *
 * @param sensor_data  Cấu trúc dữ liệu cảm biến (độ ẩm, nhiệt độ, v.v.).
 * @param system_mode  Chế độ hoạt động của hệ thống (ví dụ: MODE_AUTO, MODE_MANUAL).
 * @param pump_state   Trạng thái bơm hiện tại (ON/OFF).
 *
 * @details
 *  - Hàm này thường được gọi trong vòng lặp chính hoặc scheduler 
 *    để cập nhật thông tin hiển thị/gửi đi.
 *  - Có thể dùng để hiển thị thông tin lên LCD, gửi qua UART, hoặc log ra console.
 */
void Notification_GetData(SENSOR_Data sensor_data, OPERATION_Mode system_mode, PUMP_State pump_state);

#endif /* NOTIFICATION_H_ */
