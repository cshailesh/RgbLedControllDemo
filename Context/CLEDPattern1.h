/*
 * CLedPatterns.h
 *
 *  Created on: 25 Dec 2018
 *      Author: Shailesh
 */

#ifndef CLEDPATTERN1_H_
#define CLEDPATTERN1_H_

#include "CWsLed.h"
#include "CPatternCommon.h"
#include "CAdc.h"

#define Play2Delay 			1000
#define MaxLoop				255
#define MaxLoopPercentage	100
//#define DEFAULT_TONE_LEVEL 200

#define DEFAULT_TONE_LEVEL_RED 40

uint8_t PlayColorToneRed()
{

	BeatSenseStop();

	uint8_t tmpR = 0;

	uint32_t patternDelay = 0;

	gPatternSpeed[gCurMenu] = DEFAULT_TONE_LEVEL_RED;
	LCD_Update_Speed();
	tmpR = gPatternSpeed[gCurMenu];

	FillAllOff();
	SendLedData();

	while (1)
	{
		FillColor(Set_Val(tmpR), Set_Val(0), Set_Val(0));
		SendLedData();
		tmpR = gPatternSpeed[gCurMenu];
		patternDelay = gPatternSpeed[gCurMenu];
		if (PatternDelay(patternDelay))
		{
			return 0;
		}
	}
}

#define DEFAULT_TONE_LEVEL_BLUE 200

uint8_t PlayColorToneBlue()
{
	BeatSenseStop();

	uint8_t tmpB = 0;

	uint32_t patternDelay = 0;

	gPatternSpeed[gCurMenu] = DEFAULT_TONE_LEVEL_BLUE;
	LCD_Update_Speed();
	tmpB = gPatternSpeed[gCurMenu];

	FillAllOff();
	SendLedData();

	while (1)
	{
		//FillColor(255, 255, 255 - tmpB);
		FillColor(Set_Val(0), Set_Val(0), Set_Val(tmpB));

//		FillColor(0, 0, tmpB);
		SendLedData();
		tmpB = gPatternSpeed[gCurMenu];
		patternDelay = gPatternSpeed[gCurMenu];
		if (PatternDelay(patternDelay))
		{
			return 0;
		}
	}
}

#define DEFAULT_TONE_LEVEL_GREEN 200

uint8_t PlayColorToneGreen()
{
	BeatSenseStop();

	uint8_t tmpG = 0;
//	uint8_t tmpR = 0;
//	uint8_t tmpB = 0;

	uint32_t patternDelay = 0;

	gPatternSpeed[gCurMenu] = DEFAULT_TONE_LEVEL_GREEN;
	LCD_Update_Speed();
	tmpG = gPatternSpeed[gCurMenu];

	FillAllOff();
	SendLedData();

	while (1)
	{
		//FillColor(0, tmpG, 0);
		FillColor(Set_Val(0), Set_Val(tmpG), Set_Val(0));
		SendLedData();
		tmpG = gPatternSpeed[gCurMenu];
		patternDelay = gPatternSpeed[gCurMenu];
		if (PatternDelay(patternDelay))
		{
			return 0;
		}

	}
}

#define DEFAULT_TONE_LEVEL_PINK	30

uint8_t PlayColorTonePink()
{
	BeatSenseStop();

	uint8_t tmpR = 255;
	uint8_t tmpB = DEFAULT_TONE_LEVEL_PINK;

	uint32_t patternDelay = 0;

	gPatternSpeed[gCurMenu] = DEFAULT_TONE_LEVEL_PINK;
	LCD_Update_Speed();
	tmpB = gPatternSpeed[gCurMenu];
	//tmpR = tmpB;

	FillAllOff();
	SendLedData();

	while (1)
	{
		//FillColor(255 - tmpR, 255, 255 - tmpB);
		FillColor(Set_Val(tmpR), Set_Val(0),
//				Set_Val(255 -  tmpB));
				Set_Val(tmpB));
		SendLedData();
		tmpB = gPatternSpeed[gCurMenu];
		//tmpR = tmpB;

		patternDelay = gPatternSpeed[gCurMenu];
		if (PatternDelay(patternDelay))
		{
			return 0;
		}
	}
}

#define DEFAULT_TONE_LEVEL_SKYBLUE	130

uint8_t PlayColorToneSkyBlue()
{
	BeatSenseStop();

	uint8_t tmpG = DEFAULT_TONE_LEVEL_SKYBLUE;
	uint8_t tmpB = 255;

	uint32_t patternDelay = 0;

	gPatternSpeed[gCurMenu] = DEFAULT_TONE_LEVEL_SKYBLUE;
	LCD_Update_Speed();
	tmpG = gPatternSpeed[gCurMenu];

	FillAllOff();
	SendLedData();

	while (1)
	{
		FillColor(Set_Val(0), Set_Val(tmpG), Set_Val(tmpB));
		//FillColor(0, tmpG, tmpB);
		SendLedData();
		tmpG = gPatternSpeed[gCurMenu];

		patternDelay = gPatternSpeed[gCurMenu];
		if (PatternDelay(patternDelay))
		{
			return 0;
		}

	}
}

#define DEFAULT_TONE_LEVEL_YELLOW	30
uint8_t PlayColorToneYellow()
{
	BeatSenseStop();

//	uint8_t tmpR = 0;
	uint8_t tmpG = 0;

	uint32_t patternDelay = 0;

	gPatternSpeed[gCurMenu] = DEFAULT_TONE_LEVEL_YELLOW;
	LCD_Update_Speed();
//	tmpR = gPatternSpeed[gCurMenu];
	tmpG = gPatternSpeed[gCurMenu];

	FillAllOff();
	SendLedData();

	FillColor(0, 190, 255);
	SendLedData();

	while (1)
	{
		//	255  200  0
		FillColor(0, 240 - tmpG, 255);
//		FillColor(0, 190, 255);

		SendLedData();
//		tmpR = gPatternSpeed[gCurMenu];
		tmpG = gPatternSpeed[gCurMenu];

		patternDelay = gPatternSpeed[gCurMenu];
		if (PatternDelay(patternDelay))
		{
			return 0;
		}
	}
}

#define Beat_Bink_Delay() 	//HAL_Delay(1)

uint8_t BlinkBeat(uint8_t pRed, uint8_t pGreen, uint8_t pBlue)
{
	uint16_t percent = 0;
	uint8_t tmpR = gPatternSpeed[gCurMenu];
	uint8_t tmpG = gPatternSpeed[gCurMenu];
	uint8_t tmpB = gPatternSpeed[gCurMenu];

	uint32_t inc = 40;

	while (percent < 200)
	{
		tmpR = ((pRed > 0) ? percent : 0);
		tmpG = ((pGreen > 0) ? percent : 0);
		tmpB = ((pBlue > 0) ? percent : 0);

//		FillColor(tmpR, tmpG, tmpB);
		FillColor(Set_Val(tmpR), Set_Val(tmpG), Set_Val(tmpB));
		SendLedData();
		Beat_Bink_Delay();
		percent += inc;
	}

	while (percent > 0)
	{
		tmpR = ((pRed > 0) ? percent : 0);
		tmpG = ((pGreen > 0) ? percent : 0);
		tmpB = ((pBlue > 0) ? percent : 0);

		//FillColor(tmpR, tmpG, tmpB);
		FillColor(Set_Val(tmpR), Set_Val(tmpG), Set_Val(tmpB));
		SendLedData();
		Beat_Bink_Delay();
		percent -= inc;
	}

	FillAllOff();
	SendLedData();
	return 0;
}

//uint8_t PlayBeatRed(uint8_t pIsRed, uint8_t pIsGreen, uint8_t pIsBlue)
//{
//	uint32_t val;
//	uint8_t key;
//
//	BeatSenseStop();
//	BeatSenseStart();
//
//	FillAllOff();
//	SendLedData();
//
//	while (1)
//	{
//		ReadKeyBoard();
//		key = GetKeyPressed();
//		if ((key == KEY_LEFT) || (key == KEY_RIGHT))
//		{
//			ProcessSpeed();
//		}
//		if ((key == KEY_UP) || (key == KEY_DOWN))
//		{
//			return 1;
//		}
//		val = AdcGet();
//		if (val > 1000)
//		{
//			BlinkBeat(pIsRed, pIsGreen, pIsBlue);
//		}
//	}
//}

#define BEAM_MULTI_MAX	7
//#define BEAM_MULTI_MAX	7

#define BEAM_MULTI_MAX_BASE	5
uint8_t gBeatMultiData[BEAM_MULTI_MAX][3];
uint8_t gBeatMultiCnt;
uint8_t gBeatMultiCntBase;
uint16_t gAdcRefVal;

uint8_t PlayBeatMulti()
{
	__NOP();
	gPatternSpeed[gCurMenu] = 30;
	CalculateSenseRef();

	uint32_t val;
	uint8_t key;

	gBeatMultiCntBase = 0;
	gBeatMultiCnt = 0;

	gBeatMultiData[0][0] = 1;
	gBeatMultiData[0][1] = 0;
	gBeatMultiData[0][2] = 0;

	gBeatMultiData[1][0] = 1;
	gBeatMultiData[1][1] = 1;
	gBeatMultiData[1][2] = 0;

	gBeatMultiData[2][0] = 1;
	gBeatMultiData[2][1] = 0;
	gBeatMultiData[2][2] = 1;

	gBeatMultiData[3][0] = 0;
	gBeatMultiData[3][1] = 1;
	gBeatMultiData[3][2] = 0;

	gBeatMultiData[4][0] = 0;
	gBeatMultiData[4][1] = 1;
	gBeatMultiData[4][2] = 1;

	gBeatMultiData[5][0] = 1;
	gBeatMultiData[5][1] = 0;
	gBeatMultiData[5][2] = 1;

	gBeatMultiData[6][0] = 0;
	gBeatMultiData[6][1] = 0;
	gBeatMultiData[6][2] = 1;

	uint8_t isRed = 0;
	uint8_t isGreen = 0;
	uint8_t isBlue = 0;
//
//	BeatSenseStop();
//	BeatSenseStart();
//
//	LCD_Update_Sense();
//
//	FillAllOff();
//	SendLedData();
//
//	while (1)
//	{
//		ReadKeyBoard();
//		key = GetKeyPressed();
//		if ((key == KEY_LEFT) || (key == KEY_RIGHT))
//		{
//			ProcessSense();
//		}
//		if ((key == KEY_UP) || (key == KEY_DOWN))
//		{
//			return 1;
//		}
//		val = AdcGet();
//		if (val > gAdcRefVal)
//		{
//			isRed = gBeatMultiData[gBeatMultiCnt][0];
//			isBlue = gBeatMultiData[gBeatMultiCnt][1];
//			isGreen = gBeatMultiData[gBeatMultiCnt][2];
//
//			BlinkBeat(isRed, isGreen, isBlue);
//
//			gBeatMultiCntBase+=3;
//			if (gBeatMultiCntBase > BEAM_MULTI_MAX_BASE)
//			{
//				gBeatMultiCntBase = 0;
//				gBeatMultiCnt++;
//				if (gBeatMultiCnt > BEAM_MULTI_MAX)
//				{
//					gBeatMultiCnt = 0;
//				}
//			}
//		}
//	}
}

uint8_t PlayBeatMulti2()
{
	__NOP();

	gPatternSpeed[gCurMenu] = 30;
	CalculateSenseRef();

	uint32_t val;
	uint8_t key;

	gBeatMultiCntBase = 0;
	gBeatMultiCnt = 0;

	gBeatMultiData[0][0] = 1;
	gBeatMultiData[0][1] = 0;
	gBeatMultiData[0][2] = 0;

	gBeatMultiData[1][0] = 1;
	gBeatMultiData[1][1] = 1;
	gBeatMultiData[1][2] = 0;

	gBeatMultiData[2][0] = 1;
	gBeatMultiData[2][1] = 0;
	gBeatMultiData[2][2] = 1;

	gBeatMultiData[3][0] = 0;
	gBeatMultiData[3][1] = 1;
	gBeatMultiData[3][2] = 0;

	gBeatMultiData[4][0] = 0;
	gBeatMultiData[4][1] = 1;
	gBeatMultiData[4][2] = 1;

	gBeatMultiData[5][0] = 1;
	gBeatMultiData[5][1] = 0;
	gBeatMultiData[5][2] = 1;

	gBeatMultiData[6][0] = 0;
	gBeatMultiData[6][1] = 0;
	gBeatMultiData[6][2] = 1;

	uint8_t isRed = 0;
	uint8_t isGreen = 0;
	uint8_t isBlue = 0;

	BeatSenseStop();
	BeatSenseStart();

	//LCD_Update_Sense();

	FillAllOff();
	SendLedData();

	while (1)
	{
		ReadKeyBoard();
		key = GetKeyPressed();
		if ((key == KEY_LEFT) || (key == KEY_RIGHT))
		{
			ProcessSense();
		}
		if ((key == KEY_UP) || (key == KEY_DOWN))
		{
			return 1;
		}
		val = AdcGet();
		if (val > gAdcRefVal)
		{
			isRed = gBeatMultiData[gBeatMultiCnt][0];
			isBlue = gBeatMultiData[gBeatMultiCnt][1];
			isGreen = gBeatMultiData[gBeatMultiCnt][2];

			BlinkBeat(isRed, isGreen, isBlue);

			gBeatMultiCntBase+=3;
			if (gBeatMultiCntBase > BEAM_MULTI_MAX_BASE)
			{
				gBeatMultiCntBase = 0;
				gBeatMultiCnt++;
				if (gBeatMultiCnt > BEAM_MULTI_MAX)
				{
					gBeatMultiCnt = 0;
				}
			}
		}
	}
}


//----------------------------------------------------------------------
#endif /* CLEDPATTERN1_H_ */
