/**
 * @file    fsm_system.h
 * @author  [Tên bạn/nhóm]
 * @date    [yyyy-mm-dd]
 * @brief   Finite State Machine (FSM) system header
 *
 * @details
 *  - Định nghĩa API cho hệ thống FSM điều khiển chế độ vận hành.
 *  - FSM_System() đóng vai trò như bộ điều khiển trung tâm, 
 *    xử lý logic dựa trên dữ liệu cảm biến, trạng thái bơm, 
 *    và sự kiện nút nhấn.
 *  - Hệ thống sử dụng các module con: sensor, LED display, button, timer, pump_control.
 *
 * @note
 *  - FSM chỉ điều phối luồng hoạt động, không trực tiếp điều khiển phần cứng.
 *  - Cần đảm bảo các module phụ trợ (sensor, button, pump_control) 
 *    đã được khởi tạo trước khi gọi FSM_System().
 */

#ifndef FSM_SYSTEM_H_
#define FSM_SYSTEM_H_

#include "common.h"
#include "sensor.h"
#include "led_display.h"
#include "button.h"
#include "timer.h"
#include "pump_control.h"

/**
 * @brief Hàm chính của FSM hệ thống.
 *
 * @param arg  Tham số tuỳ chọn (có thể là NULL hoặc con trỏ tới struct context).
 *
 * @details
 *  - Được gọi định kỳ trong vòng lặp chính hoặc scheduler.
 *  - Quản lý các chế độ hoạt động (MODE_IDLE, MODE_AUTO, MODE_MANUAL, ...).
 *  - Xử lý sự kiện từ cảm biến và nút nhấn để điều khiển bơm và hiển thị LED.
 */
void FSM_System(void *arg);

#endif /* FSM_SYSTEM_H_ */
