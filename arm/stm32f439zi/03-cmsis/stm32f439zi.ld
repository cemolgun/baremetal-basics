ENTRY(reset)

MEMORY
{
    FLASH(rx) : ORIGIN =0x08000000, LENGTH =2M
    SRAM(rwx) : ORIGIN =0x20000000, LENGTH =192K
}

SECTIONS
{
    .text :
    {
        _text_start = .;
        *(.vector_table)
        *(.text)
        *(.rodata)
        . = ALIGN(4);
        _text_end = .;
    } >FLASH 

    .data :
    {
        _data_start = .;
        *(.data)
        . = ALIGN(4);
        _data_end = .;
    } >SRAM AT>FLASH

    .bss :
    {
        _bss_start = .;
        *(.bss)
        *(COMMON)
        . = ALIGN(4);
        _bss_end = .;
    } >SRAM
}

_stack_init = ORIGIN(SRAM) + LENGTH(SRAM);
