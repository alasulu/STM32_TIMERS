#include "stm32f107xx.h"
#include "tim.h"

int timestamp = 0;

/* Set up: Connect a jumper wire from PA0 (Output) to PA6 (Input) */
int main(void)
{

tim5_PA0_output_compare();
tim3_PA6_input_capture();
/* What are we going to do here is we would have to wait until the edge is captured.
We would have to check a bit in the timer status register bit number one. */

	while(1)
		{
		/* Wait until edge is capture */
		while(!(TIM3->SR & CC1G)){}

		/* Read Captured Value */
		timestamp = (TIM3->CCR1);
}
}
