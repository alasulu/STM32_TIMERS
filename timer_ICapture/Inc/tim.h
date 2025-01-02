/*
 * tim.h
 *
 *  Created on: Dec 9, 2024
 *      Author: rf_lab
 */

#ifndef TIM_H_
#define TIM_H_

void tim2_1hz_init(void);
void tim5_PA0_output_compare(void);
void tim3_PA6_input_capture(void);

#define UIF_EN		(0x1 << 0)
#define CC1G		(0x1 << 1)

#endif /* TIM_H_ */
