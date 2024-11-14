#pragma once

#include <stdint.h>
#include <stdbool.h>

#define FLASH_START     0x08000000
#define FLASH_SZ        ((2)*(1024)*(1024)) /* 2M */

#define SRAM_START      0x20000000
#define SRAM_SZ         ((192)*(1024))      /* 192K */

#define STACK_INIT      ((SRAM_START)+(SRAM_SZ)) 
#define VECTOR_TABLE_SZ 107

extern void* _text_start;
extern void* _text_end;
extern void* _data_start;
extern void* _data_end;
extern void* _bss_start;
extern void* _bss_end;

typedef struct Rcc                  /* Reset and clock control */
{
    volatile uint32_t cr;
    volatile uint32_t pllcfgr;
    volatile uint32_t cfgr;
    volatile uint32_t cir;
    volatile uint32_t ahb1rstr;
    volatile uint32_t ahb2rstr;
    volatile uint32_t ahb3rstr;

    volatile uint32_t _res1[1];
    
    volatile uint32_t apb1rstr;
    volatile uint32_t apb2rstr;

    volatile uint32_t _res2[2];
    
    volatile uint32_t ahb1enr;
    volatile uint32_t ahb2enr;
    volatile uint32_t ahb3enr;

    volatile uint32_t _res3[1];

    volatile uint32_t apb1enr;
    volatile uint32_t apb2enr;

    volatile uint32_t _res4[2];

    volatile uint32_t ahb1lpenr;
    volatile uint32_t ahb2lpenr;
    volatile uint32_t ahb3lpenr;

    volatile uint32_t _res5[1];

    volatile uint32_t apb1lpenr;
    volatile uint32_t apb2lpenr;

    volatile uint32_t _res6[2];

    volatile uint32_t bdcr;
    volatile uint32_t csr;

    volatile uint32_t _res7[2];

    volatile uint32_t sscgr;
    volatile uint32_t plli2scfgr;
    volatile uint32_t pllsaicfgr;
    volatile uint32_t dckcfgr;
} Rcc;

typedef struct Gpio             /* General Purpose IO */
{
    volatile uint32_t moder;    // Port mode register
    volatile uint32_t otyper;   // Output type register
    volatile uint32_t ospeedr;  // Output speed register
    volatile uint32_t pupdr;    // Pull-up/pull-down register
    volatile uint32_t idr;      // Input data register
    volatile uint32_t odr;      // Output data register
    volatile uint32_t bsrr;     // Bit set/reset register
    volatile uint32_t lckr;     // Configuration lock register
    volatile uint32_t afr[2];   // Alternate function low + high register
} Gpio;


