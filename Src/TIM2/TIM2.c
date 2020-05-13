/*
 * TIM2.c
 *
 *  Created on: May 6, 2020
 *      Author: Bodnár Benjamin
 */

#include "TIM2_Types.h"
#include "NVIC.h"
#include "RCC.h"

static dtTIM2 *const TIM2 = (dtTIM2*)(0x40000000);
static void (*InterruptFunction)(void);

void TIM2_Init(void (*PeriodFunction)(void));
void TIM2_SetPeriod(uint32 period);
uint32* TIM2_GetCompAddr(uint8 Ch);

void TIM2_Init(void (*PeriodFunction)(void))
{
	TIM2->CR1.Field.UIFREMAP = 0;
	TIM2->CR1.Field.CMS = 0;
	TIM2->CR1.Field.ARPE = 1;
	TIM2->CR1.Field.DIR = 0;
	TIM2->CR1.Field.OPM = 0;
	TIM2->CR1.Field.URS = 1;
	TIM2->CR1.Field.UDIS = 0;

	TIM2->CR2.Field.CCDS = 1;

	dtDIER Tdier = {.Word = 0};
	Tdier.Field.UDE = 1;
	Tdier.Field.UIE = 1;
	Tdier.Field.CC1DE = 1;
	Tdier.Field.CC2DE = 1;
	TIM2->DIER = Tdier;
	NVIC_SetPriority(TIM2_IRQn,2);
	NVIC_EnableIRQ(TIM2_IRQn);

	TIM2->PSC.Field.PSC = 0;

	TIM2->ARR.Field.ARR = 100000;

	TIM2->CNT.Field.CNT = 0;

	dtCCMR1 temp = {.Word = 0};

	temp.OC_mode_Field.CC2S = 0;
	temp.OC_mode_Field.CC1S = 0;

	temp.OC_mode_Field.OC1M_1 = 6;
	temp.OC_mode_Field.OC1M_2 = 0;

	temp.OC_mode_Field.OC2M_1 = 6;
	temp.OC_mode_Field.OC2M_2 = 0;

	temp.OC_mode_Field.OC1PE = 1;
	temp.OC_mode_Field.OC2PE = 1;

	TIM2->CCMR1 = temp;

	TIM2->CCER.Field.CC1E = 1;
	TIM2->CCER.Field.CC2E = 1;

	TIM2->CCR1.Field.CCRx = 0;
	TIM2->CCR2.Field.CCRx = 0;

	if(PeriodFunction != 0) InterruptFunction = PeriodFunction;
}

void TIM2_SetPeriod(uint32 period)
{
	TIM2->ARR.Field.ARR = period;
	TIM2->CR1.Field.CEN = 1;
	TIM2->EGR.Field.UG = 1;
}

uint32* TIM2_GetCompAddr(uint8 Ch)
{
	uint32 *ret = 0;
	if(Ch == 1) ret = &TIM2->CCR1.Word;
	else if(Ch == 2) ret = &TIM2->CCR2.Word;
	return ret;
}

void TIM2_IRQHandler(void)
{
	TIM2->SR.Field.UIF = 0;
	if(InterruptFunction != 0) InterruptFunction();
}
