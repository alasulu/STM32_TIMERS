#include "stm32f107xx.h"
#include "tim.h"

#define GPIOAEN 	(0x1 << 2)
#define UIF_EN		(0x1 << 0)
#define LED5		(0x1 << 5)

static void tim2_callback(void);

int main(void)
{
	// Enable Clock Access to GPIOA
	RCC->APB2ENR |= GPIOAEN;

	// Set PA5 as output pin
	GPIOA->CRL &= ~(0xF<<20);
	GPIOA->CRL |= (0x1<<20); /* 01: Output mode, max speed 10 MHz with 00:
	General purpose output push-pull */

	tim2_1hz_interrupt_init();

	while(1)
		{

		}
}

static void tim2_callback(void)
{
	/* Toggle the LED */
	GPIOA->ODR ^= LED5;// We are dealing with interrupts, no need to wait for the flags
}

void TIM2_IRQHandler(void){

	/* Clear Update Interrupt Flag */
	TIM2->SR &= ~UIF_EN;  // We update in DMA/Interrupt Enable Register, but we
	//clear it in status register

	/* Do something */
	tim2_callback();

}
