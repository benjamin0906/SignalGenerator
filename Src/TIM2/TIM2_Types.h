/*
 * TIM2_Types.h
 *
 *  Created on: May 6, 2020
 *      Author: Bodnár Benjamin
 */

#ifndef TIM2_TIM2_TYPES_H_
#define TIM2_TIM2_TYPES_H_

#include "types.h"

typedef union
{
	struct
	{
		uint32 CEN		:1;
		uint32 UDIS		:1;
		uint32 URS		:1;
		uint32 OPM		:1;
		uint32 DIR		:1;
		uint32 CMS		:2;
		uint32 ARPE		:1;
		uint32 CKD		:2;
		uint32 			:1;
		uint32 UIFREMAP	:1;
		uint32 			:4;
		uint32 			:16;
	} Field;
	uint32 Word;
} dtCR1;

typedef union
{
	struct
	{
		uint32 			:3;
		uint32 CCDS		:1;
		uint32 MMS		:3;
		uint32 TI1S		:1;
		uint32			:8;
		uint32 			:16;
	} Field;
	uint32 Word;
} dtCR2;

typedef union
{
	struct
	{
		uint32 SMS_1	:3;
		uint32 OCCS		:1;
		uint32 TS		:3;
		uint32 MSM		:1;
		uint32 ETF		:4;
		uint32 ETPS		:2;
		uint32 ECE		:1;
		uint32 ETP		:1;
		uint32 SMS_2	:1;
		uint32 			:15;
	} Field;
	uint32 Word;
} dtSMCR;

typedef union
{
	struct
	{
		uint32 UIE		:1;
		uint32 CC1IE	:1;
		uint32 CC2IE	:1;
		uint32 CC3IE	:1;
		uint32 CC4IE	:1;
		uint32 			:1;
		uint32 TIE		:1;
		uint32 			:1;
		uint32 UDE		:1;
		uint32 CC1DE	:1;
		uint32 CC2DE	:1;
		uint32 CC3DE	:1;
		uint32 CC4DE	:1;
		uint32 			:1;
		uint32 TDE		:1;
		uint32 			:17;
	} Field;
	uint32 Word;
} dtDIER;

typedef union
{
	struct
	{
		uint32 UIF		:1;
		uint32 CC1IF	:1;
		uint32 CC2IF	:1;
		uint32 CC3IF	:1;
		uint32 CC4IF	:1;
		uint32 			:1;
		uint32 TIF		:1;
		uint32 			:2;
		uint32 CC1OF	:1;
		uint32 CC2OF	:1;
		uint32 CC3OF	:1;
		uint32 CC4OF	:1;
		uint32 			:19;
	} Field;
	uint32 Word;
} dtSR;

typedef union
{
	struct
	{
		uint32 UG		:1;
		uint32 CC1G		:1;
		uint32 CC2G		:1;
		uint32 CC3G		:1;
		uint32 CC4G		:1;
		uint32			:1;
		uint32 TG		:1;
		uint32			:9;
		uint32 			:16;
	} Field;
	uint32 Word;
} dtEGR;

typedef union
{
	struct
	{
		uint32 CC1S		:2;
		uint32 OC1FE	:1;
		uint32 OC1PE	:1;
		uint32 OC1M_1	:3;
		uint32 OC1CE	:1;
		uint32 CC2S		:2;
		uint32 OC2FE	:1;
		uint32 OC2PE	:1;
		uint32 OC2M_1	:3;
		uint32 OC2CE	:1;
		uint32 OC1M_2	:1;
		uint32 			:7;
		uint32 OC2M_2	:1;
		uint32 			:7;
	} OC_mode_Field;
	struct
	{
		uint32 CC1S		:2;
		uint32 IC1PSC	:2;
		uint32 IC1F		:4;
		uint32 CC2S		:2;
		uint32 IC2PSC	:2;
		uint32 IC2F		:4;
		uint32 			:16;
	}IC_mode_Field;
	uint32 Word;
} dtCCMR1;

typedef union
{
	struct
	{
		uint32 CC3S		:2;
		uint32 OC3FE	:1;
		uint32 OC3PE	:1;
		uint32 OC3M_1	:3;
		uint32 OC3CE	:1;
		uint32 CC4S		:2;
		uint32 OC4FE	:1;
		uint32 OC4PE	:1;
		uint32 OC4M_1	:3;
		uint32 OC4CE	:1;
		uint32 OC3M_2	:1;
		uint32 			:7;
		uint32 OC4M_2	:1;
		uint32 			:7;
	} OC_mode_Field;
	struct
	{
		uint32 CC3S		:2;
		uint32 IC3PSC	:2;
		uint32 IC3F		:4;
		uint32 CC4S		:2;
		uint32 IC4PSC	:2;
		uint32 IC4F		:4;
		uint32 			:16;
	}IC_mode_Field;
	uint32 Word;
} dtCCMR2;

typedef union
{
	struct
	{
		uint32 CC1E		:1;
		uint32 CC1P		:1;
		uint32 			:1;
		uint32 CC1NP	:1;
		uint32 CC2E		:1;
		uint32 CC2P		:1;
		uint32 			:1;
		uint32 CC2NP	:1;
		uint32 CC3E		:1;
		uint32 CC3P		:1;
		uint32 			:1;
		uint32 CC3NP	:1;
		uint32 CC4E		:1;
		uint32 CC4P		:1;
		uint32 			:1;
		uint32 CC4NP	:1;
		uint32 			:16;
	} Field;
	uint32 Word;
} dtCCER;

typedef union
{
	struct
	{
		uint32 CNT		:31;
		uint32 UIFCPY	:1;
	} Field_UIFREMAP;
	struct
	{
		uint32 CNT		:32;
	} Field;
	uint32 Word;
} dtCNT;

typedef union
{
	struct
	{
		uint32 PSC		:16;
		uint32			:16;
	} Field;
	uint32 Word;
} dtPSC;

typedef union
{
	struct
	{
		uint32 ARR		:32;
	} Field;
	uint32 Word;
} dtARR;

typedef union
{
	struct
	{
		uint32 CCRx		:32;
	} Field;
	uint32 Word;
} dtCCRx;

typedef union
{
	struct
	{
		uint32 DBA		:5;
		uint32 			:3;
		uint32 DBL		:5;
		uint32 			:19;
	} Field;
	uint32 Word;
} dtDCR;

typedef union
{
	struct
	{
		uint32 DMAB		:16;
		uint32 			:16;
	} Field;
	uint32 Word;
} dtDMAR;

typedef union
{
	struct
	{
		uint32 ITR1_RMP		:1;
		uint32 ETR_RMP		:1;
		uint32 TI4_RMP		:2;
		uint32 				:12;
		uint32 				:16;
	} Field;
	uint32 Word;
} dtOR1;

typedef union
{
	struct
	{
		uint32				:14;
		uint32 ETRSEL		:2;
		uint32 ETRSEL2		:1;
		uint32 				:15;
	} Field;
	uint32 Word;
} dtOR2;

typedef struct
{
	dtCR1 CR1;		//0x00
	dtCR2 CR2;		//0x04
	dtSMCR SMCR;	//0x08
	dtDIER DIER;	//0x0C
	dtSR SR;		//0x10
	dtEGR EGR;		//0x14
	dtCCMR1 CCMR1;	//0x18
	dtCCMR2 CCMR2;	//0x1C
	dtCCER CCER;	//0x20
	dtCNT CNT;		//0x24
	dtPSC PSC;		//0x28
	dtARR ARR;		//0x2C
	uint32	:32;	//0x30
	dtCCRx CCR1;	//0x34
	dtCCRx CCR2;	//0x38
	dtCCRx CCR3;	//0x3C
	dtCCRx CCR4;	//0x40
	uint32	:32;	//0x44
	dtDCR DCR;		//0x48
	dtDMAR DMAR;	//0x4C
	dtOR1 OR1;		//0x50
	uint32	:32;	//0x54
	uint32	:32;	//0x58
	uint32	:32;	//0x5C
	dtOR2 OR2;		//0x60
} dtTIM2;

#endif /* TIM2_TIM2_TYPES_H_ */
