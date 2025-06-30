#include "stm32f4xx.h"

#define GPIOAEN			(1U<<0)
#define ADC1EN			(1U<<8)
#define ADC_CH1			(1U<<0)
#define ADC_SEQ_LEN_1	(0x00)


/*ADC configured with 3 channels */
/* ch2, 3, 5*/
/*first = ch5*/
/*second = ch2*/
/*third = ch3*/

void pa1_adc_init(void) {
	/***Configure the ADC GPIO pin***/

	/*Enable clock access to GPIOA*/
	RCC->AHB1ENR |= GPIOAEN;
	/*Set the mode of PA1 to analog*/
	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER |= (1U<<3);

	/***Configure the ADC module***/
	/*Enable clock access to the ADC*/
	RCC->APB2ENR |= ADC1EN;

	/*Configure adc parameters*/
	/*Conversion sequence start*/
	ADC1->SQR3 |= ADC_CH1;
	/*Conversion sequence length*/
	ADC1->SQR1 = ADC_SEQ_LEN_1;

	/*Enable ADC module*/

}

