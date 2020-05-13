/*
 * SignalGen_Types.h
 *
 *  Created on: 7 May 2020
 *      Author: Bodnár Benjamin
 */

#ifndef SIGNALGEN_SIGNALGEN_TYPES_H_
#define SIGNALGEN_SIGNALGEN_TYPES_H_

#include "types.h"

typedef enum
{
	Ch_1 = 0,
	Ch_2,
} dtChs;

typedef struct
{
	uint32	Duty:31;
	dtChs	Ch	:1;
} dtChDuty;

#endif /* SIGNALGEN_SIGNALGEN_TYPES_H_ */
