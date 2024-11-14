#include "stm32f439zi.h"

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

/* Turn on the onboard leds of nucleo f439zi */
int main()
{
    volatile Rcc* rcc = (Rcc* )0x40023800;
    rcc->ahb1enr |= 0b10;   // Enable gpio b

    volatile Gpio* gpio_b  = (Gpio* )0x40020400;
    gpio_b->moder = ((1 << 0*2) | (1 << 7*2) | (1 << 14*2)); // Pin mode
    gpio_b->odr = ((1 << 0) | (1<<7) | (1<<14));             // Pin value

    for(;;);
}
