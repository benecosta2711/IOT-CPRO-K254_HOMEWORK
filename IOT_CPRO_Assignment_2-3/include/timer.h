/**
 * @file    timer.h
 * @author  [Tên bạn/nhóm]
 * @date    [yyyy-mm-dd]
 * @brief   Header for simple timer emulation
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <common.h>

// /**
//  * @brief Khởi tạo timer giả lập
//  * @param period    Số tick để hết hạn (ví dụ 100 tick = 100 ms giả lập)
//  * @param callback  Hàm callback sẽ được gọi khi timer hết hạn
//  */
// void TIMER_Init(uint32_t period, void (*callback)(void));

// /**
//  * @brief Gọi hàm này trong vòng lặp chính để giả lập timer tick
//  */
// void TIMER_Tick(void);







typedef void (*TaskFn)(void*);
typedef struct {
    TaskFn fn; void* arg;
    uint32_t period_ms, elapsed_ms;
    uint8_t enabled;
} SchedTask;

void SCH_Init(uint32_t tick_ms);          // vd tick=10ms
int  SCH_Add(TaskFn fn, void* arg, uint32_t period_ms);
void SCH_Tick(void);                      // gọi ở vòng lặp
void SCH_RunPending(void);                // dispatch task đủ hạn

#endif /* TIMER_H_ */