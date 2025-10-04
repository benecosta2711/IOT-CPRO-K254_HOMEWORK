#include "peripheral.h"

PORT_Type PORTA_BASE = {0};
PORT_Type PORTB_BASE = {0};
PORT_Type PORTC_BASE = {0};

GPIO_Type GPIOA_BASE = {0};
GPIO_Type GPIOB_BASE = {0};
GPIO_Type GPIOC_BASE = {0};

void GPIO_Enable(void)
{
    for (int i = 0; i < NUM_PIN; i++)
    {
        // Check PORTA
        if (PORTA->PIN_REG[i] == 1)
            GPIOA->PIN_SET[i] = 1;
        else
            GPIOA->PIN_SET[i] = 0;
            
        // Check PORTB
        if (PORTB->PIN_REG[i] == 1)
            GPIOB->PIN_SET[i] = 1;
        else
            GPIOB->PIN_SET[i] = 0;

        // Check PORTC
        if (PORTC->PIN_REG[i] == 1)
            GPIOC->PIN_SET[i] = 1;
        else
            GPIOC->PIN_SET[i] = 0;
    }
}

void GPIO_Init(PORT_Type *port, GPIO_Type *gpio_port, uint8_t port_index, uint8_t gpio_set_mode)
{
    port->PIN_REG[port_index] = 1;
    gpio_port->MODE = gpio_set_mode;
}
