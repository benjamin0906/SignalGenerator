/*
 * SignalGen.c
 *
 *  Created on: 7 May 2020
 *      Author: Bodnár Benjamin
 */

#include "SignalGen_Types.h"
#include "SignalGen.h"
#include "TIM2.h"

static uint32 Frequency;
static uint32 SampleNumber;
static dtSignalGenMode Mode;
static const float32 SineLookupTable[50] = {
0.062790519529, 0.125333233564, 0.187381314586, 0.248689887165, 0.309016994375, 
0.368124552685, 0.425779291565, 0.481753674102, 0.535826794979, 0.587785252292, 
0.637423989749, 0.684547105929, 0.728968627421, 0.770513242776, 0.809016994375, 
0.844327925502, 0.876306680044, 0.904827052466, 0.929776485888, 0.951056516295, 
0.968583161129, 0.982287250729, 0.992114701314, 0.998026728428, 1.000000000000, 
0.998026728428, 0.992114701314, 0.982287250729, 0.968583161129, 0.951056516295, 
0.929776485888, 0.904827052466, 0.876306680044, 0.844327925502, 0.809016994375, 
0.770513242776, 0.728968627421, 0.684547105929, 0.637423989749, 0.587785252292, 
0.535826794979, 0.481753674102, 0.425779291565, 0.368124552685, 0.309016994375, 
0.248689887165, 0.187381314586, 0.125333233564, 0.062790519529, 0.000000000000,
};
static uint32 Iterator;

void SignalGen_Init(void);
void SignalGen_Trigger(void);

void SignalGen_Init(void)
{
	TIM2_Init(&SignalGen_Trigger);
	SampleNumber = TIM2_SetPeriod(10000);
}

dtChDuty SineGen(void)
{
	dtChDuty Ret = {0, Ch1};
	float32 Value1;
	float32 Value2;
	float32 LookupRes = (float32)SampleNumber/(sizeof(SineLookupTable)>>1);
	float32 EndValue;
	uint32 index = Iterator/LookupRes;

	/* In case of too high index the index shall be decreased by the max index value. This is due to the fact that
	 * the sine wave is periodical */
	if(index >= sizeof(SineLookupTable)) index -= sizeof(SineLookupTable);
	Value1 = SineLookupTable[index++];
	if(index >= sizeof(SineLookupTable)) index -= sizeof(SineLookupTable);
	Value2 = SineLookupTable[index];

	/* Linear interpolation of the sine wave */
	EndValue = Value1 + (Value2-Value1)*((float32)Iterator/LookupRes-index);

	/* Calculation of the required duty cycle */
	EndValue *= (float32)SampleNumber;

	/* Rounding of the duty cycle */
	Ret.Duty = (uint32)EndValue;
	EndValue -= (float32)Ret.Duty;
	if(EndValue >= 0.5) Ret.Duty++;

	if((float32)Iterator >= ((float32) SampleNumber/2)) Ret.Ch = Ch2;

	return Ret;
}

void SignalGen_Trigger(void)
{
	dtChDuty Duty;
	switch(Mode)
	{
	case Sine:
		Duty = SineGen();
		break;
	}
	Iterator++;
	Duty.Duty = 4000;
	TIM2_SetDuty(Duty.Duty,Duty.Ch);
}
