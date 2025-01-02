#include "stm32f107xx.h"

#define TIM5EN 		(0x1 << 3)
#define TIM2EN		(0x1 << 0)
#define CR1_CEN		(0x1 << 0)
#define TOGGLE_OC	(0x3 << 4)
#define CC1E		(0x1 << 0)
#define GPIOAEN 	(0x1 << 2)
#define AFIOEN		(0x1 << 0)

void tim2_1hz_init(void)
{
	/* Enable Clock Access to Timer 2 */
	RCC->APB1ENR |= TIM2EN;	// TIM2 is connected to APB1 BUS
	/* Set Prescaler Value */
	TIM5->PSC = (36000-1); // 36 000 000 (APB1 BUS Clock) / 36 000 = 1 000
	// We count from the bit zero, considering that "-1" is written.
	/* Set Auto-reload Value */
	TIM2->ARR = (1000-1); // 1 000 / 1 000 = 1 (Update Event)
	/* Clear Counter */
	TIM2->CNT = 0;
	/* Enable Timer */
	TIM2->CR1 = CR1_CEN;
	}

void tim5_PA0_output_compare(void)
{
	/* Enable Clock Access to GPIOA */
	RCC->APB2ENR |= GPIOAEN;

	/* Set ALternate Function On for Board */
	RCC->APB2ENR |= AFIOEN;

	/* Configure PA0 to Output Alternate Function */
	GPIOA->CRL &= ~(0xF<<0);
	GPIOA->CRL |= (0x9<<0); /* 01: Output mode, max speed 10 MHz with
	10: Alternate function output Push-pull */

	/* Enable Clock Access to Timer 5 */
	RCC->APB1ENR |= TIM5EN;	// TIM5 is connected to APB1 BUS

	/* Set Prescaler Value */
	TIM5->PSC = (72000-1); // 36 000 000 (APB1 BUS Clock) / 36 000 = 1 000
	// We count from the bit zero, considering that "-1" is written.

	/* Set Auto-reload Value */
	TIM5->ARR = (2000-1); // 1 000 / 1 000 = 1 (Update Event)

	/* Set Output Compare Toggle Mode */
	TIM5->CCMR1 = TOGGLE_OC;
	// We will use the Channel 1 of TIMER 5, so we consider OC1M. If we use Channel 2,
	//OC2M will be considered.
	// 011: Toggle - OC1REF toggles when TIMx_CNT=TIMx_CCR1.

	/* Enable Timer 5 Channel 1 in Compare Mode */
	TIM5->CCER |= CC1E;

	/* Clear Counter */
	TIM5->CNT = 0;

	/* Enable Timer */
	TIM5->CR1 = CR1_CEN;
	}
