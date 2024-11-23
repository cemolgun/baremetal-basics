#include "gpio.h"

inline void gpio_set_mode(GpioPin pin, int mode)
{
    pin.port->moder &= ~(0b11 << (pin.num * 2));
    pin.port->moder |= (mode << (pin.num * 2));
}

inline void gpio_write(GpioPin pin, bool value)
{
    pin.port->bsrr = ((1 << 16) << pin.num) >> (16*value);
}

inline bool gpio_read(GpioPin pin)
{
    return pin.port->idr & (1 << pin.num);
}

inline void gpio_toggle(GpioPin pin)
{
    pin.port->odr ^= (1 << pin.num);
}
