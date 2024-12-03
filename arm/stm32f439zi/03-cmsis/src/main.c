#include "stm32f439xx.h"
#include "gpio.h"

const GpioPin red_led = {GPIOB, 14};

int main()
{
    RCC->AHB1ENR |= 0b110;
    gpio_set_mode(red_led, GPIO_MODE_OUTPUT);

    for(;;)
    {
        gpio_toggle(red_led);
        for (int i = 0; i < 500000; i++);
    }
}
