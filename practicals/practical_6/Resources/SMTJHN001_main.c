/**
 * @file: main.c
 * @author: 
 * @student-number:
 * @ps-no:
 *
 * Student solution for practical 6.
 */

//Macros
#define STM32F051  //define target for header files, must be def'd before includes

//Includes
#include "stm32f0xx.h"											   
#include "lcd_stm32f0.h"
#include <stdint.h>

//Global Variables
uint8_t SW0_PRESSED = 0;

//Function Declerations
void ResetClockTo48Mhz(void);
void init_student(void);
void init_ADC(void);
void init_GPIOB(void);
void init_GPIOA(void);
void init_TIM3 (void);

//Main Function
int main (void){
    ResetClockTo48Mhz();
    init_student();
    init_GPIOB();
    init_GPIOA();
    init_ADC();
    while (1){}
}						

//Function Definitions
/**
 * Function resets the STM32 Clocks to 48 MHz
 */
void ResetClockTo48Mhz(void)
{
    if ((RCC->CFGR & RCC_CFGR_SWS) == RCC_CFGR_SWS_PLL)
    {
        RCC->CFGR &= (uint32_t) (~RCC_CFGR_SW);
        while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI);
    }
    RCC->CR &= (uint32_t)(~RCC_CR_PLLON);
    while ((RCC->CR & RCC_CR_PLLRDY) != 0);
    RCC->CFGR = ((RCC->CFGR & (~0x003C0000)) | 0x00280000);
    RCC->CR |= RCC_CR_PLLON;
    while ((RCC->CR & RCC_CR_PLLRDY) == 0);
    RCC->CFGR |= (uint32_t) (RCC_CFGR_SW_PLL);
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
}

void init_student(void){
}

void init_ADC(void){
}

void init_GPIOB(void){
}

void init_GPIOA(void){
}

void init_TIM3 (void) {
}

void ADC1_COMP_IRQHandler(void){
}

