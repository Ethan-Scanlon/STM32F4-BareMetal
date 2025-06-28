#include "stm32f4xx.h"
#include <stdint.h>

#define GPIOAEN			(1U<<0)
#define UART2EN			(1U<<17)

#define CR1_TE			(1U<<3)
#define CR1_UE			(1U<<13)
#define SR_TXE			(1U<<7)

#define SYS_FREQ		16000000
#define APB1_CLK		(SYS_FREQ/2U)

#define UART_BAUDRATE	115200



static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);

void uart2_tx_init(void);
void uart2_write(int ch);

int main(void) {

	uart2_tx_init();

	while(1) {
		uart2_write('Y');
		for (volatile int i=0; i<100000; i++);
	}
}

void uart2_tx_init(void) {
	/*Configure uart gpio pin (PA2, ALT FUNC 7)*/
	/*Enable clock access for gpioA, set PA2 mode to
	 * alt function mode, set pa2 alternate function type
	 * to UART_TX (AF07)
	 */
	/*Configure USART Module*
	 * Enable clock access to uart2
	 * Configure uart baud rate
	 * Configure the transfer direction
	 * Enable Uart module when we are done
	 */

	RCC->AHB1ENR |= GPIOAEN;
	GPIOA->MODER &=~ (1U<<4);
	GPIOA->MODER |= (1U<<5);
	GPIOA->AFR[0] &=~ (1U<<11);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<8);

	RCC->APB1ENR |= UART2EN;
	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

	USART2->CR1 = CR1_TE;
	USART2->CR1 |= CR1_UE;

}

void uart2_write(int ch) {

	/*Make sure the transmit data register is empty before we put somehting into it*/
	while(!(USART2->SR & SR_TXE)) {}
	/*Write to transmit data register*/
	USART2->DR = (ch & 0xFF);
	//Turn into 8 bit?

}
static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate) {
	USARTx->BRR = compute_uart_bd(PeriphClk, BaudRate);
}

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate) {

	return (uint16_t)((PeriphClk + (BaudRate/2U))/BaudRate);

}
