#include "COMMON/common.h"
#include "PERIPHERAL/peripheral.h"
#include "SENSOR/sensor.h"
#include "PUMP/pump_control.h"
#include "LED_DISPLAY/led_display.h"
#include "TIMER/timer.h"
#include "BUTTON/button.h"
#include "FSM_SYSTEM/fsm_system.h"
#include "NOTIFICATION/notification.h"

void SYSTEM_Init(void);

int main(void)
{
    SYSTEM_Init();

    g_operation_mode = MODE_AUTO;
    g_pump_sate = PUMP_OFF;
    g_led_state = LED_NORMAL;

    SCH_Init(10);

    // Đăng ký các task
    SCH_Add(EMULATOR_Sensor,  NULL, 50);
    SCH_Add(FSM_System,       NULL, 50);
    SCH_Add(EMULATOR_Pump,    NULL, 50);
    SCH_Add(EMULATOR_Led,     NULL, 50);
    SCH_Add(EMULATOR_Button,  NULL, 50);
    SCH_Add(EMULATOR_Notification, NULL, 500);
    
    while (1)
    {
        SCH_Tick();
        SCH_RunPending();
        for(int i = 0; i <= 1000000000; i++){}
        GPIO_Enable();
        LED_Control();
    }
}

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
    PUMP_TurnOff(PUMP_PORT, PUMP_PIN);
}
