#pragma once

#include "stm32f439zi.h"

#define GPIO_BASE   0x40020000U
#define GPIO_OFFSET 0x400U
#define GPIO_PIN(LABEL, NUM) {(Gpio*)(GPIO_BASE + ((LABEL-'A')*GPIO_OFFSET)), LABEL, NUM}

typedef struct GpioPin
{
    Gpio*  port;
    char   label;
    int8_t num;
} GpioPin;

enum GPIO_MODES 
{
    GPIO_MODE_INPUT,
    GPIO_MODE_OUTPUT,
    GPIO_MODE_ALTERNATE_FUNCTION,
    GPIO_MODE_ANALOG 
};

void gpio_set_mode(GpioPin pin, int mode);
void gpio_write(GpioPin pin, bool value);
bool gpio_read(GpioPin pin);
void gpio_toggle(GpioPin pin);
