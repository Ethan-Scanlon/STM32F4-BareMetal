/*
 * tim.h
 *
 *  Created on: Jul 7, 2025
 *      Author: scanny
 */

#ifndef TIM_H_
#define TIM_H_

void tim2_1hz_init(void);
void tim2_pa5_output_compare(void);
void tim3_pa6_input_compare(void);

#define SR_UIF				(1U<<0)
#define SR_CC1IF			(1U<<1)

#endif /* TIM_H_ */
