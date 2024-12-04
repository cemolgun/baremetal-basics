#include <stm32f439xx.h>

#define VECTOR_TABLE_SZ 107

extern void* _text_start;
extern void* _text_end;
extern void* _data_start;
extern void* _data_end;
extern void* _bss_start;
extern void* _bss_end;
extern void* _stack_init;

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

    [0]                         = (void* )&_stack_init,
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
