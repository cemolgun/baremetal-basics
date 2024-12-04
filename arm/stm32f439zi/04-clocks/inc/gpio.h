#pragma once

#include "stm32f439xx.h"
#include <stdbool.h>

typedef struct GpioPin
{
    GPIO_TypeDef*  port;
    uint8_t        num;
} GpioPin;

enum GPIO_MODER_MODE 
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
