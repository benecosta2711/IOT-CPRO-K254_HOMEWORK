/**
 * @file    main.c
 * @author  [Tên bạn/nhóm]
 * @date    [yyyy-mm-dd]
 * @brief   Button driver implementation
 *
 * @details
 *  -
 *
 * @note
 *  -
 */

#include "common.h"
#include "peripheral.h"
#include "sensor.h"
#include "pump_control.h"
#include "led_display.h"
#include "timer.h"
#include "button.h"
#include "fsm_system.h"

void SYSTEM_Init(void);

/* ================== Main Function ================== */
int main(void)
{
    // 1. Init hệ thống
    SYSTEM_Init();

    g_operation_mode = MODE_IDLE;
    g_pump_sate = PUMP_OFF;
    g_led_state = LED_NORMAL;

    // 2. Init Scheduler tick = 10ms
    SCH_Init(10);

    // 3. Đăng ký các task
    SCH_Add(EMULATOR_Button,  NULL, 50);
    SCH_Add(FSM_System,       NULL, 50);
    SCH_Add(EMULATOR_Pump,    NULL, 50);
    SCH_Add(EMULATOR_Led,     NULL, 50);
    SCH_Add(EMULATOR_Sensor,  NULL, 50);
    // 4. Main loop
    while (1)
    {
        SCH_Tick();
        SCH_RunPending();
        for(int i = 0; i <= 1000000000; i++){}
        //FSM_System();
        GPIO_Enable();
        LED_Control();
    }
}

/* ================== System Function ================== */
// --- System Init ---
void SYSTEM_Init(void)
{
    // --- Function Init ---
    GPIO_Init(PORTA, GPIOA, 2, GPIO_INPUT);
    GPIO_Init(PORTA, GPIOA, 3, GPIO_INPUT);
    GPIO_Init(PORTB, GPIOB, 2, GPIO_INPUT);
    GPIO_Init(PORTB, GPIOB, 3, GPIO_OUTPUT);
    GPIO_Init(PORTC, GPIOC, 1, GPIO_OUTPUT);
    GPIO_Init(PORTC, GPIOC, 2, GPIO_OUTPUT);
    GPIO_Init(PORTC, GPIOC, 3, GPIO_OUTPUT);

    // --- Set LED off ---
    LED_Off(LED_RED_PORT, LED_RED_PIN);
    LED_Off(LED_YELLOW_PORT, LED_YELLOW_PIN);
    LED_Off(LED_GREEN_PORT, LED_GREEN_PIN);

    // --- Set PUMP off ---
    turn_pump_off(PUMP_PORT, PUMP_PIN);
}
