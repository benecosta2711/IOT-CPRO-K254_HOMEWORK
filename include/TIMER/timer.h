#ifndef TIMER_H_
#define TIMER_H_

#include "COMMON/common.h"

/**
 * @typedef TaskFn
 * @brief   Định nghĩa hàm task callback.
 */
typedef void (*TaskFn)(void*);

/**
 * @struct SchedTask
 * @brief  Cấu trúc mô tả một task trong scheduler.
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
 */
void SCH_Init(uint32_t tick_ms);

/**
 * @brief  Thêm một task vào scheduler.
 */
int SCH_Add(TaskFn fn, void* arg, uint32_t period_ms);

/**
 * @brief  Hàm tick của scheduler.
 */
void SCH_Tick(void);

/**
 * @brief  Thực thi các task đến hạn.
 */
void SCH_RunPending(void);

#endif /* TIMER_H_ */
