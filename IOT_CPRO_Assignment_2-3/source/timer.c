/**
 * @file    timer.c
 * @author  [Tên bạn/nhóm]
 * @date    [yyyy-mm-dd]
 * @brief   Simple timer emulation
 *
 * @details
* API khớp với timers.h tối giản:
 *   - SCH_Init(tick_ms)
 *   - SCH_Add(fn, arg, period_ms)
 *   - SCH_Tick()
 *   - SCH_RunPending()
 *
 * @note
 *  - Đây chỉ là mô phỏng, không có độ chính xác như hardware timer.
 *  - Có thể dùng để test logic (ví dụ: nút nhấn sau 100 tick).
 */

#include "timer.h"
#include <string.h> 
#include <stddef.h> 

#ifndef SCH_MAX_TASKS
#define SCH_MAX_TASKS 12
#endif

static SchedTask g_tasks[SCH_MAX_TASKS];
static uint32_t g_tick_ms = 1; 

static int sch_find_free_slot(void)
{
    for (int i = 0; i < SCH_MAX_TASKS; ++i)
    {
        if (g_tasks[i].fn == NULL)
            return i;
    }
    return -1;
}

void SCH_Init(uint32_t tick_ms)
{
    if (tick_ms == 0)
        tick_ms = 1;
    g_tick_ms = tick_ms;
    memset(g_tasks, 0, sizeof(g_tasks));
}

int SCH_Add(TaskFn fn, void *arg, uint32_t period_ms)
{
    if (!fn || period_ms == 0)
        return -1;
    int id = sch_find_free_slot();
    if (id < 0)
        return -1;

    g_tasks[id].fn = fn;
    g_tasks[id].arg = arg;
    g_tasks[id].period_ms = period_ms;
    g_tasks[id].elapsed_ms = 0;
    g_tasks[id].enabled = 1;
    return id;
}

void SCH_Tick(void)
{
    for (int i = 0; i < SCH_MAX_TASKS; ++i)
    {
        if (g_tasks[i].fn && g_tasks[i].enabled)
        {
            g_tasks[i].elapsed_ms += g_tick_ms;
        }
    }
}

void SCH_RunPending(void)
{
    for (int i = 0; i < SCH_MAX_TASKS; ++i)
    {
        SchedTask *t = &g_tasks[i];
        if (!t->fn || !t->enabled)
            continue;

        if (t->elapsed_ms >= t->period_ms)
        {
            t->elapsed_ms -= t->period_ms;
            t->fn(t->arg);
        }
    }
}
