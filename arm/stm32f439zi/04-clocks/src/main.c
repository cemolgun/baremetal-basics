#include "stm32f439xx.h"
#include "gpio.h"

const GpioPin button  = {GPIOC, 13};

const GpioPin leds[3] = {{GPIOB, 0},
                         {GPIOB, 7},
                         {GPIOB, 14}};

/* Visualisation of different system clocks with different frequencies */
int main()
{
    RCC->AHB1ENR |= 0b110;
    
    /* Enable HSE, wait untill ready */
    RCC->CR |= RCC_CR_HSEON;
    while (!(RCC->CR & RCC_CR_HSERDY));
    
    /* PLL F_sys = SRC/M*N/P */
    /* F = 16M/16*96/4 = 24Mhz */
    RCC->PLLCFGR = (2 << RCC_PLLCFGR_PLLQ_Pos)     |
                   RCC_PLLCFGR_PLLSRC_HSI          |
                   (0b01 << RCC_PLLCFGR_PLLP_Pos)  |
                   (96 << RCC_PLLCFGR_PLLN_Pos)    |
                   (16 << RCC_PLLCFGR_PLLM_Pos); 
   
    /* Enable PLL, wait untill ready */
    RCC->CR |= RCC_CR_PLLON;
    while (!(RCC->CR & RCC_CR_PLLRDY));
    
    gpio_set_mode(leds[0], GPIO_MODE_OUTPUT);
    gpio_set_mode(leds[1], GPIO_MODE_OUTPUT);
    gpio_set_mode(leds[2], GPIO_MODE_OUTPUT);
    gpio_set_mode(button, GPIO_MODE_INPUT);
    
    /* 0: HSI, 1: HSE, 2: PLL */
    int8_t clock_mode = 0;  
    for(;;)
    {
        gpio_toggle(leds[clock_mode]);
        for (int i = 0; i < 100000; i++);
        
        if (gpio_read(button))
        {
            clock_mode = (clock_mode + 1) % 3;
            switch (clock_mode) {
                case 0:
                    RCC->CFGR &= ~RCC_CFGR_SW;
                    RCC->CFGR |= RCC_CFGR_SW_HSI;
                    break;
                
                case 1:
                    RCC->CFGR &= ~RCC_CFGR_SW;
                    RCC->CFGR |= RCC_CFGR_SW_HSE;
                    break;
                
                case 2:
                    RCC->CFGR &= ~RCC_CFGR_SW;
                    RCC->CFGR |= RCC_CFGR_SW_PLL;
                    break;
            }
            
            gpio_write(leds[0], 0);
            gpio_write(leds[1], 0);
            gpio_write(leds[2], 0);
        }
    }
}
