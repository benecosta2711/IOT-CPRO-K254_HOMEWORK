#include "hal_buttons.h"
#include <stdio.h>

#define TIME_COUNT 20

static int s_toggle = 0;
static int s_manual = 0;

// Mô phỏng button bằng bàn phím, chương trình bị chặn
static void ReadLine(void)
{
    char buf[64];
    if (fgets(buf, sizeof(buf), stdin))
    {
        for (char *p = buf; *p; ++p)
        {
            if (*p == 'a' || *p == 'A')
                s_toggle = 1;
            if (*p == 'm' || *p == 'M')
                s_manual = 1;
        }
    }
}

void HAL_BTN_Init(void) {}

static int count_random = 0;

int HAL_BTN_ReadToggleMode(void)
{
    // ReadLine();
    // int v = s_toggle;
    // s_toggle = 0;
    // return v;

    int button_toggle;
    //Chặn thời gian để nút nhấn được đọc từ từ
    for (int i = TIME_COUNT; i > 0; i--){}

    if (count_random++ %5 == 0)
    {
        s_toggle = 1;
        button_toggle = s_toggle;
        s_toggle = 0;
    }
    else
    {
        // do not thing
    }

    return button_toggle;
}

int HAL_BTN_ReadManualWater(void)
{
    // int v = s_manual;
    // s_manual = 0;
    // return v;

    int button_manual;
    //Chặn thời gian để nút nhấn được đọc từ từ
    for (int i = TIME_COUNT; i > 0; i--){}

    if (count_random++ %6 == 0)
    {
        s_manual = 1;
        button_manual = s_manual;
        s_manual = 0;
    }
    else
    {
        // do not thing
    }
    return button_manual;
}
