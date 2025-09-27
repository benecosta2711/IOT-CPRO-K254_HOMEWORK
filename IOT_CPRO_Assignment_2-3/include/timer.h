/**
 * @file    timer.h
 * @author  [Tên bạn/nhóm]
 * @date    [yyyy-mm-dd]
 * @brief   Simple timer scheduler emulation
 *
 * @details
 *  - Cung cấp scheduler đơn giản dựa trên tick định kỳ.
 *  - Cho phép đăng ký nhiều task chạy theo chu kỳ (periodic task).
 *  - Các task được gọi tuần tự trong vòng lặp chính (cooperative scheduling).
 *
 * @note
 *  - Đây là phiên bản mô phỏng, không chính xác tuyệt đối như hardware timer.
 *  - Dùng để test logic hoặc giả lập hành vi thời gian thực trong môi trường phần mềm.
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "common.h"

/**
 * @typedef TaskFn
 * @brief   Định nghĩa hàm task callback.
 *
 * @param arg  Tham số truyền vào task (có thể là NULL).
 */
typedef void (*TaskFn)(void*);

/**
 * @struct SchedTask
 * @brief  Cấu trúc mô tả một task trong scheduler.
 *
 * @details
 *  - fn: con trỏ đến hàm callback.
 *  - arg: tham số truyền cho callback.
 *  - period_ms: chu kỳ chạy task (ms).
 *  - elapsed_ms: thời gian đã trôi (ms).
 *  - enabled: cờ bật/tắt task (1 = enable, 0 = disable).
 */
typedef struct {
    TaskFn   fn;
    void*    arg;
    uint32_t period_ms;
    uint32_t elapsed_ms;
    uint8_t  enabled;
} SchedTask;

/**
 * @brief  Khởi tạo scheduler.
 *
 * @param  tick_ms  Đơn vị tick (ms). Ví dụ: tick_ms = 10 → mỗi tick tương ứng 10ms.
 *
 * @note   Nên gọi một lần trong hàm main() trước khi thêm task.
 */
void SCH_Init(uint32_t tick_ms);

/**
 * @brief  Thêm một task vào scheduler.
 *
 * @param  fn         Con trỏ hàm task callback.
 * @param  arg        Tham số truyền vào callback (có thể NULL).
 * @param  period_ms  Chu kỳ chạy task (tính bằng ms).
 *
 * @retval >= 0   ID của task nếu thêm thành công.
 * @retval -1     Nếu không còn slot trống hoặc tham số không hợp lệ.
 *
 * @note   Tối đa số task = SCH_MAX_TASKS (định nghĩa trong timer.c).
 */
int SCH_Add(TaskFn fn, void* arg, uint32_t period_ms);

/**
 * @brief  Hàm tick của scheduler.
 *
 * @details
 *  - Gọi định kỳ trong vòng lặp chính hoặc từ ngắt timer (nếu có).
 *  - Cập nhật bộ đếm thời gian cho tất cả các task đã được thêm.
 */
void SCH_Tick(void);

/**
 * @brief  Thực thi các task đến hạn.
 *
 * @details
 *  - Kiểm tra tất cả các task trong danh sách.
 *  - Nếu task đủ thời gian (elapsed_ms >= period_ms), callback sẽ được gọi.
 *  - Sau khi chạy, elapsed_ms được reset lại (theo period_ms).
 */
void SCH_RunPending(void);

#endif /* TIMER_H_ */
