#include <stdio.h>
#include <stdint.h>
#include "uart.h"
#include "adc.h"
#include "systick.h"

#define GPIOAEN				(1U<<0)
#define PIN5				(1U<<5)
#define LED_PIN				PIN5

void systick_callback(void);

int main(void) {

	RCC->AHB1ENR |= GPIOAEN;
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~ (1U<<11);

	uart2_tx_init();
	systick_1hz_interrupt();

	while(1) {

	}
}

void systick_callback(void)
{
	printf("A second passed!! \n\r");
	GPIOA->ODR ^= LED_PIN;
}

void SysTick_Handler(void)
{
	systick_callback();
}

