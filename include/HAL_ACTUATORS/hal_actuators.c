#include "hal_actuators.h"

static LedState_t s_led = LED_NORMAL;
static PumpState_t s_pump = PUMP_OFF;

void HAL_ACT_Init(void)
{
    s_led = LED_NORMAL;
    s_pump = PUMP_OFF;
}

void HAL_ACT_TurnPumpOn(void)
{
    if (s_pump != PUMP_ON)
    {
        s_pump = PUMP_ON;
        LOGF("[ACT] PUMP ON");
    }
    else 
    {
        //do not thing
    }
}

void HAL_ACT_TurnPumpOff(void)
{
    if (s_pump != PUMP_OFF)
    {
        s_pump = PUMP_OFF;
        LOGF("[ACT] PUMP OFF");
    }
    else 
    {
        //do not thing
    }
}

void HAL_ACT_SetLed(LedState_t st)
{
    if (st != s_led)
    {
        s_led = st;
        const char *name =
            (st == LED_NORMAL) ? "LED_NORMAL" : (st == LED_WATERING)         ? "LED_WATERING"
                                            : (st == LED_LOW_MOISTURE_ALERT) ? "LED_LOW_MOISTURE_ALERT"
                                                                             : "LED_ERROR";
        LOGF("[ACT] LED -> %s", name);
    }
    else 
    {
        //do not thing
    }
}
