#include "spi.h"

#define SPI1EN			(1U<<12)
#define GPIOAEN			(1U<<0)

#define SR_TXE			(1U<<1)
#define SR_RXNE			(1U<<0)

#define SR_BSY			(1U<<7)

/*
 * PA5 IS CLK
 * PA6 IS MISO
 * PA7 IS MOSI
 * PA9 IS SS
 */

void spi_gpio_init(void)
{
	/*Enable clock access*/
	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER &=~ (1U<<10);
	GPIOA->MODER |= (1U<<11);

	GPIOA->MODER &=~ (1U<<12);
	GPIOA->MODER |= (1U<<13);

	GPIOA->MODER &=~ (1U<<14);
	GPIOA->MODER |= (1U<<15);

	//Set PA9 as GPIO Out
	GPIOA->MODER |= (1U<<18);
	GPIOA->MODER &=~ (1U<<19);

	GPIOA->AFR[0] |= (1U<<20);
	GPIOA->AFR[0] &=~ (1U<<21);
	GPIOA->AFR[0] |= (1U<<22);
	GPIOA->AFR[0] &=~ (1U<<23);

	GPIOA->AFR[0] |= (1U<<24);
	GPIOA->AFR[0] &=~ (1U<<25);
	GPIOA->AFR[0] |= (1U<<26);
	GPIOA->AFR[0] &=~ (1U<<27);

	GPIOA->AFR[0] |= (1U<<28);
	GPIOA->AFR[0] &=~ (1U<<29);
	GPIOA->AFR[0] |= (1U<<30);
	GPIOA->AFR[0] &=~ (1U<<31);

}

void spi1_config(void)
{
	RCC->APB2ENR |= SPI1EN;

	//fPLCK/4
	SPI1->CR1 |= (1U<<3);
	SPI1->CR1 &=~ (1U<<4);
	SPI1->CR1 &=~ (1U<<5);

	/*Set CPOL to 1 and CPHA to 1*/
	SPI1->CR1 |= (1U<<0);
	SPI1->CR1 |= (1U<<1);

	/*Enable full duplex*/
	SPI1->CR1 &=~ (1U<<10);

	/*Set MSB first*/
	SPI1->CR1 &=~ (1U<<7);

	/*Set mode to master*/
	SPI1->CR1 |= (1U<<2);

	/*Set 8 bit data mode*/
	SPI1->CR1 &=~ (1U<<11);

	/*Select software slave management by setting SSM=1 and SSI=1*/
	SPI1->CR1 |= (1U<<8);
	SPI1->CR1 |= (1U<<9);

	/*Enable SPI module*/
	SPI1->CR1 |= (1U<<6);

}

void spi1_transmit(uint8_t *data, uint32_t size)
{
	uint32_t i=0;
	uint8_t temp;

	while(i<size)
	{
		/*Wait until transmit buffer is empty (until TXE is set)*/
		while(!(SPI1->SR & (SR_TXE))) {}
		/*Write the data to the data register*/
		SPI1->DR = data[i];
		i++;

	}
	/*Wait until TXE is set*/
	while(!(SPI1->SR & (SR_TXE))) {}

	/*Wait for busy flag*/
	while(SPI1->SR & (SR_BSY)) {}

	/*Clear OVR flag*/
	temp = SPI1->DR;
	temp = SPI1->SR;
}

void spi1_receive(uint8_t *data, uint32_t size)
{
	while(size)
	{
		/*Send dummy data*/
		SPI1->DR = 0;

		/*Wait for RXNE flag to be set*/
		while(!(SPI1->SR * (SR_RXNE))) {}

		/*Read data from data register*/
		*data++ = (SPI1->DR);
		size--;
	}
}

void cs_enable(void)
{
	GPIOA->ODR &=~ (1U<<9);
}

void cs_disable(void)
{
	GPIOA->ODR |= (1U<<9);
}

