#include "stm32f107xx.h"
#include "tim.h"

#define GPIOAEN 	(0x1 << 2)
#define UIF_EN		(0x1 << 0)
#define LED5		(0x1 << 5)

int main(void)
{
	// Enable Clock Access to GPIOA
	RCC->APB2ENR |= GPIOAEN;

	// Set PA5 as output pin
	GPIOA->CRL &= ~(0xF<<20);
	GPIOA->CRL |= (0x1<<20); /* 01: Output mode, max speed 10 MHz with 00:
	General purpose output push-pull */

	tim2_1hz_init();

	while(1)
		{
		/* Wait for UIF */
		while(!(TIM2->SR & UIF_EN)) {} // We want to wait for the UIF flag is to be set
		/* So, just like in the SysTick, that we waited for SysTick flag to be set in
		order for us to know the time as occured. In the timer 2, we wait for a particular
		flag to be set to indicate the time out has occured. This is known as UIF or Update
		Interrupt Flag, this is located in Timer Status Register. */

		/* Clear UIF */
		TIM2->SR &= ~(UIF_EN);

		/* Toggle the LED */
		GPIOA->ODR ^= LED5;
		}
}
