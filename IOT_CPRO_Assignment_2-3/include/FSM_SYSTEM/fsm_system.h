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
 * @param arg  Tham số tuỳ chọn (có thể là NULL hoặc con trỏ tới struct context).
 * @details
 *  - Được gọi định kỳ trong vòng lặp chính hoặc scheduler.
 *  - Quản lý các chế độ hoạt động (MODE_IDLE, MODE_AUTO, MODE_MANUAL, ...).
 *  - Xử lý sự kiện từ cảm biến và nút nhấn để điều khiển bơm và hiển thị LED.
 */
void FSM_System(void *arg);

#endif /* FSM_SYSTEM_H_ */
