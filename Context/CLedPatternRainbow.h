/*
 * CLedPatternRainbow.h
 *
 *  Created on: 13 Mar 2020
 *      Author: JANVI
 */

#ifndef CLEDPATTERNRAINBOW_H_
#define CLEDPATTERNRAINBOW_H_

#include "CWsLed.h"
#include "CPatternCommon.h"
#include "CAdc.h"

//
//uint32_t ColorU32(uint8_t r, uint8_t g, uint8_t b)
//{
//	return ((uint32_t) r << 16) | ((uint32_t) g << 8) | b;
//}
//
//uint32_t Wheel(int8_t WheelPos)
//{
//	if (WheelPos < 85)
//	{
//		return ColorU32(WheelPos * 3, 255 - WheelPos * 3, 0);
//	}
//	else if (WheelPos < 170)
//	{
//		WheelPos -= 85;
//		return ColorU32(255 - WheelPos * 3, 0, WheelPos * 3);
//	}
//	else
//	{
//		WheelPos -= 170;
//		return ColorU32(0, WheelPos * 3, 255 - WheelPos * 3);
//	}
//}
//
//uint32_t Wheel32(int8_t WheelPos)
//{
//	if (WheelPos < 85)
//	{
//		return ColorU32(WheelPos * 3, 255 - WheelPos * 3, 255);
//	}
//	else if (WheelPos < 170)
//	{
//		WheelPos -= 85;
//		return ColorU32(WheelPos * 3, 255, 255 - WheelPos * 3);
//	}
//	else
//	{
//		WheelPos -= 170;
//		return ColorU32(255, 255 - WheelPos * 3, WheelPos * 3);
//	}
//}
//
////uint8_t PlayRainbow()
////{
////	uint16_t i, j;
////	uint8_t speed = 0;
////
////	uint32_t patternDelay = 50;
////
////	while (1)
////	{
////		for (j = 0; j < 255; j++)
////		{
////			for (i = 0; i < WS_LED_COUNT; i++)
////			{
////				uint32_t col = Wheel32((i * 1 + j) & 255);
////				SetLedColor32(i, col);
////			}
////
////			SendLedData();
////			speed = gPatternSpeed[gCurMenu];
////			patternDelay = gPatternSpeed[gCurMenu];
////			patternDelay = patternDelay * 10;
////			if (PatternDelay(patternDelay))
////			{
////				return 0;
////			}
////		}
////	}
////}

#define PATIDX_MAX		6
#define PLAY_RAINBOW_DELAY	1

uint8_t PlayRainbow2()
{
	uint16_t i;
	uint32_t patIdx = 1;

	uint8_t r;
	uint8_t g;
	uint8_t b;

	uint32_t patternDelay = PLAY_RAINBOW_DELAY;
	gPatternSpeed[gCurMenu] = PLAY_RAINBOW_DELAY;
	LCD_Update_Speed();

	uint8_t patColors[6][3];

	patColors[0][0] = 200;
	patColors[0][1] = 0;
	patColors[0][2] = 0;

	patColors[1][0] = 0;
	patColors[1][1] = 200;
	patColors[1][2] = 0;

	patColors[2][0] = 0;
	patColors[2][1] = 0;
	patColors[2][2] = 200;

	patColors[3][0] = 150;
	patColors[3][1] = 200;
	patColors[3][2] = 0;

	patColors[4][0] = 0;
	patColors[4][1] = 190;
	patColors[4][2] = 200;

	patColors[5][0] = 150;
	patColors[5][1] = 0;
	patColors[5][2] = 200;

	r = Set_Val(patColors[0][0]);
	g = Set_Val(patColors[0][1]);
	b = Set_Val(patColors[0][2]);

	FillColor(r, g, b);
	SendLedData();

	while (1)
	{
		for (i = 0; i < WS_LED_COUNT; i++)
		{
			r = Set_Val(patColors[patIdx][0]);
			g = Set_Val(patColors[patIdx][1]);
			b = Set_Val(patColors[patIdx][2]);

			SetLedColor(i, r, g, b);
			SendLedData();
			HAL_Delay(1);
			SetLedColor(i, r, g, b);
			SendLedData();

			patternDelay = gPatternSpeed[gCurMenu];
			patternDelay = patternDelay * 50;
			if (PatternDelay(patternDelay))
			{
				return 0;
			}
		}

		patIdx++;
		if (patIdx > PATIDX_MAX - 1)
		{
			patIdx = 0;
		}
	}
}

#endif /* CLEDPATTERNRAINBOW_H_ */
