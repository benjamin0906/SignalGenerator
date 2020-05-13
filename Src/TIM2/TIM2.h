/*
 * TIM2.h
 *
 *  Created on: May 6, 2020
 *      Author: Bodnár Benjamin
 */

#ifndef TIM2_TIM2_H_
#define TIM2_TIM2_H_

extern void TIM2_Init(void (*PeriodFunction)(void));
extern void TIM2_SetPeriod(uint32 period);
extern uint32* TIM2_GetCompAddr(uint8 Ch);
extern uint32 TIM2_GetAdd(uint8 ch);

#endif /* TIM2_TIM2_H_ */
