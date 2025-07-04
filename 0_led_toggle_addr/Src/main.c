 //Where is the led connected?
//Port:	A
//Pin:	5

#define PERIPH_BASE			(0x40000000UL)
#define AHB1PERIPH_OFFSET	(0x00020000UL)
#define AHB1PERIPH_BASE		(PERIPH_BASE + AHB1PERIPH_OFFSET)
#define GPIOA_OFFSET		(0x0000U)	// 0x 0000 0000

#define GPIOA_BASE			(AHB1PERIPH_BASE + GPIOA_OFFSET)

#define RCC_OFFSET			(0x3800UL)
#define RCC_BASE			(AHB1PERIPH_BASE + RCC_OFFSET)

#define AHB1EN_R_OFFSET		(0x30UL)
#define RCC_AHB1EN_R		(*(volatile unsigned int *)(RCC_BASE + AHB1EN_R_OFFSET))

#define MODE_R_OFFSET		(0x00UL)
#define GPIOA_MODE_R		(*(volatile unsigned int *)(GPIOA_BASE + MODE_R_OFFSET))

#define OD_R_OFFSET			(0x14UL)
#define GPIOA_OD_R			(*(volatile unsigned int *)(GPIOA_BASE + OD_R_OFFSET))

#define GPIOAEN				(1U<<0)

#define PIN5				(1U<<5)
#define LED_PIN				PIN5

/*
 * (1U<<10) // Set bit 10 to 1
 * &=~(1U<<11) Set bit 11 to 0*/

//0b 0000 0000 0000 0000 0000 0000 0001
//(1U <<1) == 0b 0000 0000 0000 0000 0000 0000 0010

//0x4000 0000 + 0x0002 0000 = 0x4002 0000


int main (void) {
	/*1. Enable clock access to GPIOA
	 * 2. Set PA5 as output pin */
	RCC_AHB1EN_R |= GPIOAEN;
	//Use or equals to avoid zeroing out bits
	GPIOA_MODE_R |= (1U<<10); //Set bit 10 to 1
	GPIOA_MODE_R &=~ (1U<<11); //Set bit 11 to 0

	 while(1) {
		 /* 3. Set PA5 high */
		 //GPIOA_OD_R |= LED_PIN;

		 /*4. Experiment 2: toggle PA5 */
		 GPIOA_OD_R ^= LED_PIN;
		 for(int i = 0; i<100000; i++){}
	 }
}
