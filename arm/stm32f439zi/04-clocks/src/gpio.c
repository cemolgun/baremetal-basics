#include "stm32f439xx.h"
#include "gpio.h"

inline void gpio_set_mode(GpioPin pin, int mode)
{
    pin.port->MODER &= ~(0b11 << (pin.num * 2));
    pin.port->MODER |= (mode << (pin.num * 2));
}

inline void gpio_write(GpioPin pin, bool value)
{
    pin.port->BSRR = ((1 << 16) << pin.num) >> (16*value);
}

inline bool gpio_read(GpioPin pin)
{
    return pin.port->IDR & (1 << pin.num);
}

inline void gpio_toggle(GpioPin pin)
{
    pin.port->ODR ^= (1 << pin.num);
}
