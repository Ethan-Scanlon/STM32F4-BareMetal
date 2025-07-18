#include <stdio.h>
#include <stdint.h>
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"
#include "exti.h"

#define GPIOAEN				(1U<<0)
#define PIN5				(1U<<5)
#define LED					PIN5

static void exti_callback(void);

int main(void) 
{

	RCC->AHB1ENR |= GPIOAEN;
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~ (1U<<11);

	pc13_exti_init();
	uart2_tx_init();

	while(1) 
	{
	
	}
}

static void exti_callback(void)
{
	printf("BTN Pressed...");
	GPIOA->ODR ^= LED;
}

void EXTI15_10_IRQHandler(void) 
{
	if(EXTI->PR & LINE13)
	{
		/*Clear PR flag to rearm it*/
		EXTI->PR |= LINE13
		/*Do something*/
		exti_callback();
	}
}