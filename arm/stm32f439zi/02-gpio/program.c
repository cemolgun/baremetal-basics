#include "stm32f439zi.h"
#include "gpio.h"

void irq_default();
void reset();
int  main();

/*
    Vector table is the structure that contains pointers to special handlers

    Fill the vector table with
    
    0. Initial Stack Pointer 
    1. Reset
    2. Non Maskable Interrupt
    ...
    16. IRQ0
    17. IRQ1
    ...

    Use section attribute to generate a section called .vector_table in order to
    link the vector table to correct adress
*/
__attribute__((section(".vector_table"))) 
void (*const vector_table[VECTOR_TABLE_SZ])(void) = {
    [0 ... VECTOR_TABLE_SZ - 1] = irq_default,

    [0]                         = (void* )STACK_INIT,
    [1]                         = reset,
    [7 ... 10]                  = 0,
    [13]                        = 0,
};

/* Reset is the entry point to the program */
void reset()
{
    /* Copy .data into SRAM */
    uint32_t len = (uint32_t)&_data_end - (uint32_t)&_data_start;
    int8_t* dest = (int8_t* )&_data_start;
    int8_t* source = (int8_t* )&_text_end;
    for (uint32_t i = 0; i < len; i++)
        *dest++ = *source++;

    /* Initialize .bss to 0 in SRAM */
    for (int8_t* p = (int8_t* )&_bss_start; p != (int8_t* )&_bss_end; *p++=0);

    /* Call main */
    main();
}

/* Default interrupt routine that does nothing */
void irq_default() { return; }

const GpioPin green_led = GPIO_PIN('B', 0); 
const GpioPin blue_led  = GPIO_PIN('B', 7); 
const GpioPin red_led   = GPIO_PIN('B', 14);
const GpioPin button    = GPIO_PIN('C', 13);

/* Read, write, toggle */
int main()
{
    volatile Rcc* rcc = (Rcc* )0x40023800;
    rcc->ahb1enr |= 0b110;   // Enable gpio b, c

    gpio_set_mode(green_led, GPIO_MODE_OUTPUT);
    gpio_set_mode(blue_led, GPIO_MODE_OUTPUT);
    gpio_set_mode(red_led,  GPIO_MODE_OUTPUT);
    gpio_set_mode(button,   GPIO_MODE_INPUT);

    bool button_prev = 0;
    bool button_now  = 0;
    for(;;)
    {
        button_prev = button_now;
        button_now  = gpio_read(button);

        if (button_now)
        {
            gpio_write(red_led, 1);
            gpio_write(green_led, 0);
        }

        else
        {
            gpio_write(red_led, 0);
            gpio_write(green_led, 1);
        }

        if ((button_now != button_prev) && button_now)
            gpio_toggle(blue_led);
    }
}
