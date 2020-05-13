/*
 * SignalGen.c
 *
 *  Created on: 7 May 2020
 *      Author: Bodnár Benjamin
 */

#include "SignalGen_Types.h"
#include "SignalGen.h"
#include "TIM2.h"
#include "RCC.h"
#include "Utilities.h"
#include "DMA.h"

static dtSignalGenMode Mode;
static const float32 SineLookupTable[50] = {
0.000000000,0.062790520,0.125333234,0.187381315,0.248689887,
0.309016994,0.368124553,0.425779292,0.481753674,0.535826795,
0.587785252,0.637423990,0.684547106,0.728968627,0.770513243,
0.809016994,0.844327926,0.876306680,0.904827052,0.929776486,
0.951056516,0.968583161,0.982287251,0.992114701,0.998026728,
1.000000000,0.998026728,0.992114701,0.982287251,0.968583161,
0.951056516,0.929776486,0.904827052,0.876306680,0.844327926,
0.809016994,0.770513243,0.728968627,0.684547106,0.637423990,
0.587785252,0.535826795,0.481753674,0.425779292,0.368124553,
0.309016994,0.248689887,0.187381315,0.125333234,0.062790520,
};

static uint32 Ch1Pattern[2000];
static uint32 Ch2Pattern[2000];

void SignalGen_Init(void);
void SignalGen_Trigger(void);
void SetModulatorFreq(uint32 Freq);
void SineGen(uint32 Sample);
void SignalGen_Apply(uint32 Freq);
void SignalGen_Stop(void);

extern void Blink(void);

void SignalGen_Init(void)
{
	TIM2_Init(&Blink);

	DMA_Set(DMA_1,Ch5,Ch1Pattern, TIM2_GetCompAddr(1), DMA_CS4|DMA_MEMREAD|DMA_CIRC|DMA_PER_32|DMA_MEM_INC|DMA_MEM_32|DMA_PRIO_VH,0);
	DMA_Set(DMA_1,Ch7,Ch2Pattern, TIM2_GetCompAddr(2), DMA_CS4|DMA_MEMREAD|DMA_CIRC|DMA_PER_32|DMA_MEM_INC|DMA_MEM_32|DMA_PRIO_VH,0);
}

void SignalGen_Apply(uint32 Freq)
{
	float32 fperiod = sqrt(ClockFreq/Freq);
	uint32 period = fperiod;
	if((fperiod - (float32)period) >= 0.5) period++;
	TIM2_SetPeriod(period);

	SineGen(period);

	DMA_Start(DMA_1,Ch5, period);
	DMA_Start(DMA_1,Ch7, period);
}

void SignalGen_ApplyPattern(uint32 freq, float32 *Pattern, uint32 PatternLenght)
{

}

void SignalGen_Stop(void)
{
	DMA_Stop(DMA_1,Ch5);
	DMA_Stop(DMA_1,Ch7);
}

void SineGen(uint32 Sample)
{
	uint32 Result;
	float32 Value1;
	float32 Value2;
	float32 LookupRes = (float32)Sample/(sizeof(SineLookupTable)>>1);
	float32 EndValue;
	uint32 looper;

	for(looper = 0; looper<Sample; looper++)
	{
		uint32 index = looper/LookupRes;

		/* In case of too high index the index shall be decreased by the max index value. This is due to the fact that
		 * the sine wave is periodical */
		{
			uint32 LookupIndex = index;
			if(LookupIndex >= (sizeof(SineLookupTable)>>2)) LookupIndex -= sizeof(SineLookupTable)>>2;
			Value1 = SineLookupTable[LookupIndex++];
			if(LookupIndex >= (sizeof(SineLookupTable)>>2)) LookupIndex -= sizeof(SineLookupTable)>>2;
			Value2 = SineLookupTable[LookupIndex];
		}
		/* Linear interpolation of the sine wave */
		EndValue = Value1 + (Value2-Value1)*((float32)looper/LookupRes-index);

		/* Calculation of the required duty cycle */
		EndValue *= ((float32)Sample);

		/* Rounding of the duty cycle */
		Result = (uint32)EndValue;
		EndValue -= (float32)Result;
		if(EndValue >= 0.5) Result++;

		Ch1Pattern[looper] = 0;
		Ch2Pattern[looper] = 0;
		if((float32)looper >= ((float32) Sample/2))
		{
			Ch2Pattern[looper] = Result;
		}
		else Ch1Pattern[looper] = Result;
	}
}
