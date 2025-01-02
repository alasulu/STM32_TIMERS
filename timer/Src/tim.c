#include "stm32f107xx.h"

#define TIM2EN 		(0x1 << 0)
#define CR1_CEN		(0x1 << 0)
#define UIE			(0x1 << 0)

void tim2_1hz_init(void)
{
	/* Enable Clock Access to Timer 2 */
	RCC->APB1ENR |= TIM2EN;	// TIM2 is connected to APB1 BUS
	/* Set Prescaler Value */
	TIM2->PSC = (72000); // 36 000 000 (APB1 BUS Clock) / 36 000 = 1 000
	// We count from the bit zero, considering that "-1" is written.
	/* Set Auto-reload Value */
	TIM2->ARR = (2000-1); // 1 000 / 1 000 = 1 (Update Event)
	/* Clear Counter */
	TIM2->CNT = 0;
	/* Enable Timer */
	TIM2->CR1 = CR1_CEN;
	}