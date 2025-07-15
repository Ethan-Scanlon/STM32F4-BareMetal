#include <stdio.h>
#include <stdint.h>
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"

#define GPIOAEN				(1U<<0)
#define PIN5				(1U<<5)
#define LED_PIN				PIN5

int main(void) {

	tim2_pa5_output_compare();
	while(1) {

	}
}

