/*
 * CLEDPatternFlipColor.h
 *
 *  Created on: 13 Mar 2020
 *      Author: JANVI
 */

#ifndef CLEDPATTERNFLIPCOLOR_H_
#define CLEDPATTERNFLIPCOLOR_H_

#include "CWsLed.h"
#include "CPatternCommon.h"
#include "CAdc.h"

#define FLIP_COLORS_MAX	8

uint8_t gFlipColorTable[FLIP_COLORS_MAX][3];

void FlipColorTableInit()
{
	gFlipColorTable[0][0] = 0;
	gFlipColorTable[0][1] = 255;
	gFlipColorTable[0][2] = 0;
//-----------------------------------
	gFlipColorTable[1][0] = 0;
	gFlipColorTable[1][1] = 0;
	gFlipColorTable[1][2] = 255;
//-----------------------------------
	gFlipColorTable[2][0] = 255;
	gFlipColorTable[2][1] = 0;
	gFlipColorTable[2][2] = 0;
//-----------------------------------
	gFlipColorTable[3][0] = 0;
	gFlipColorTable[3][1] = 255;
	gFlipColorTable[3][2] = 255;
//-----------------------------------
	gFlipColorTable[4][0] = 255;
	gFlipColorTable[4][1] = 255;
	gFlipColorTable[4][2] = 0;
//-----------------------------------
	gFlipColorTable[5][0] = 255;
	gFlipColorTable[5][1] = 0;
	gFlipColorTable[5][2] = 120;
//-----------------------------------
	gFlipColorTable[6][0] = 255;
	gFlipColorTable[6][1] = 255;
	gFlipColorTable[6][2] = 255;
//-----------------------------------
	gFlipColorTable[7][0] = 0;
	gFlipColorTable[7][1] = 0;
	gFlipColorTable[7][2] = 0;
//-----------------------------------
//	gFlipColorTable[8][0] = 255;
//	gFlipColorTable[8][1] = 0;
//	gFlipColorTable[8][2] = 0;
//-----------------------------------
	// 8. all color four times
	// min 25
}

#define DEFAULT_FLIP_COLOR_DELAY	15

uint8_t PlayFlipColor()
{

	BeatSenseStop();

	uint8_t tmpR = 0;
	uint8_t tmpG = 0;
	uint8_t tmpB = 0;

	uint32_t patternDelay = 0;

	gPatternSpeed[gCurMenu] = DEFAULT_FLIP_COLOR_DELAY;
	LCD_Update_Speed();

	FillAllOff();
	SendLedData();

	tmpR = gFlipColorTable[0][0];
	tmpG = gFlipColorTable[0][1];
	tmpB = gFlipColorTable[0][2];
	FillColor(Set_Val(tmpR),Set_Val(tmpG),Set_Val(tmpB));
	//FillColor(255 - tmpR, 255 - tmpG, 255 - tmpB);
	SendLedData();

	//HAL_Delay(1);

	uint8_t gColorIdx = 1;

	while (1)
	{

		if (gColorIdx >= FLIP_COLORS_MAX - 1)
		{
			gColorIdx = 0;
		}

		tmpR = gFlipColorTable[gColorIdx][0];
		tmpG = gFlipColorTable[gColorIdx][1];
		tmpB = gFlipColorTable[gColorIdx][2];

		//FillColor(255 - tmpR, 255 - tmpG, 255 - tmpB);
		FillColor(Set_Val(tmpR),Set_Val(tmpG),Set_Val(tmpB));
		SendLedData();
		patternDelay = gPatternSpeed[gCurMenu];
		patternDelay = patternDelay * 100;
		if (PatternDelay(patternDelay))
		{
			return 0;
		}

		gColorIdx++;

	}
}

#endif /* CLEDPATTERNFLIPCOLOR_H_ */
