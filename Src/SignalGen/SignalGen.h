/*
 * SignalGen.h
 *
 *  Created on: 7 May 2020
 *      Author: Bodnár Benjamin
 */

#ifndef SIGNALGEN_SIGNALGEN_H_
#define SIGNALGEN_SIGNALGEN_H_

#include "types.h"

typedef enum
{
	Sine,
	Pattern,
} dtSignalGenMode;

extern void SignalGen_Init(void);
extern void SignalGen_Apply(uint32 Freq);
extern void SignalGen_Stop(void);

#endif /* SIGNALGEN_SIGNALGEN_H_ */
