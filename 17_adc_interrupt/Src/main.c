#include <stdio.h>
#include <stdint.h>
#include "uart.h"
#include "adc.h"

static void adc_callback(void);

uint32_t sensor_value;
int main(void) {

	uart2_tx_init();
	pa1_adc_interrupt_init();
	start_conversion();


	while(1) {
		adc_callback();
	}
}

static void adc_callback(void)
{
	sensor_value = adc_read();
	printf("Sensor value: %d\n\r", (int)sensor_value);
}

void ADC_IRQHandler(void)
{
	if(ADC1->SR & (1U<<1))
	{
		ADC1-> SR &=~ (1U<<1);
	}

}
