/*
 * CLedPatterns.h
 *
 *  Created on: 25 Dec 2018
 *      Author: Shailesh
 */

#ifndef CLEDLTH_H_
#define CLEDLTH_H_

#include "CWsLed.h"
#include "CPatternCommon.h"
#include "CAdc.h"

uint8_t PlayLTH2By2()
{
	BeatSenseStop();

	uint8_t tmpRunnerR = 100;
	uint8_t tmpRunnerG = 100;
	uint8_t tmpRunnerB = 100;

	gPatternSpeed[gCurMenu] = DEFAULT_TONE_LEVEL;
	LCD_Update_Speed();

	FillAllOff();
	SendLedData();

	while (1)
	{
		uint maxCount = 3;
		for (int Counter = 0; Counter < maxCount; ++Counter)
		{

			for (int jj = 0; jj < gWS_LED_COUNT; jj += 2)
			{
				FillAllOff();

				SetLedColorPercent(jj, tmpRunnerR, tmpRunnerG, tmpRunnerB);
				SetLedColorPercent(jj + 1, tmpRunnerR, tmpRunnerG, tmpRunnerB);
				asm("NOP");
				SendLedData();
				if (PatternDelay(100))
				{
					return 0;
				}
			}

			for (int jj = gWS_LED_COUNT - 1; jj > 0; jj -= 2)
			{
				FillAllOff();
				SetLedColorPercent(jj, tmpRunnerR, tmpRunnerG, tmpRunnerB);
				SetLedColorPercent(jj + 1, tmpRunnerR, tmpRunnerG, tmpRunnerB);
				SendLedData();
				if (PatternDelay(100))
				{
					return 0;
				}
			}
		}

		for (int Counter = 0; Counter < maxCount; ++Counter)
		{
			int start = 0;
			for (int jj = 0; jj < gWS_LED_COUNT; jj += 1)
			{
				FillAllOff();
				FillColorFromToPercent(start, jj, 100, 100, 100);
				asm("NOP");
				SendLedData();
				if (PatternDelay(100))
				{
					return 0;
				}
			}

			for (int jj = 0; jj < gWS_LED_COUNT; jj++)
			{
				FillAllOff();
				FillColorFromToPercent(jj, gWS_LED_COUNT - 1, 100, 100, 100);
				SendLedData();
				if (PatternDelay(100))
				{
					return 0;
				}
			}
		}
	}
}

uint8_t PlayDimFull2(uint8_t pRed, uint8_t pGreen, uint8_t pBlue)
{
	uint8_t tmpR = 0;
	uint8_t tmpG = 0;
	uint8_t tmpB = 0;

	tmpB = 0;

	while (1)
	{
//	for (int fwd = 150; fwd < 99; ++fwd)
//	{
//		FillColorPercent(tmpR, tmpG, tmpB);
//		SendLedData();
//
//		if (pRed > 0)
//		{
//			tmpR++;
//		}
//
//		if (pGreen > 0)
//		{
//			tmpG++;
//		}
//
//		if (pBlue > 0)
//		{
//			tmpB++;
//		}
//
//		//patternDelay = gPatternSpeed[gCurMenu];
//		if (PatternDelay(50))
//		{
//			return 0;
//		}
//	}
//
//	if (PatternDelay(50))
//	{
//		return 0;
//	}
//

		tmpR = 255;
		tmpG = 255;
		tmpB = 255;

		for (int fwd = 0; fwd < 149; ++fwd)
		{
			FillColor(tmpR, tmpG, tmpB);
			SendLedData();
			if (pRed > 0)
			{
				tmpR--;
			}

			if (pGreen > 0)
			{
				tmpG--;
			}

			if (pBlue > 0)
			{
				tmpB--;
			}

			//patternDelay = gPatternSpeed[gCurMenu];
			if (PatternDelay(500))
			{
				return 0;
			}
		}

		for (int fwd = 0; fwd < 149; ++fwd)
		{
			FillColor(tmpR, tmpG, tmpB);
			SendLedData();
			if (pRed > 0)
			{
				tmpR++;
			}

			if (pGreen > 0)
			{
				tmpG++;
			}

			if (pBlue > 0)
			{
				tmpB++;
			}

			//patternDelay = gPatternSpeed[gCurMenu];
			if (PatternDelay(500))
			{
				return 0;
			}
		}
	}

	//FillAllOff();
	//SendLedData();
}

uint8_t PlayLTHDimFull()
{
	BeatSenseStop();

	gPatternSpeed[gCurMenu] = 80;

	while (1)
	{
		PlayDimFull2(1, 1, 1);
		if (PatternDelay(200))
		{
			return 0;
		}
	}
}

uint8_t PlayLTHUpDown()
{
	BeatSenseStop();

	gPatternSpeed[gCurMenu] = DEFAULT_TONE_LEVEL;
	LCD_Update_Speed();

	FillAllOff();
	SendLedData();

	while (1)
	{
		int start = 0;
		for (int jj = 0; jj < gWS_LED_COUNT; jj += 1)
		{
			FillAllOff();
			FillColorFromToPercent(start, jj, 100, 100, 100);
			asm("NOP");
			SendLedData();
			if (PatternDelay(100))
			{
				return 0;
			}
		}

		for (int jj = 0; jj < gWS_LED_COUNT; jj++)
		{
			FillAllOff();
			FillColorFromToPercent(jj, gWS_LED_COUNT - 1, 100, 100, 100);
			SendLedData();
			if (PatternDelay(100))
			{
				return 0;
			}
		}
	}
}

uint8_t Play2by2()
{
	for (int jj = 0; jj < gWS_LED_COUNT; jj += 2)
	{
		FillAllOff();

		SetLedColorPercent(jj, 100, 100, 100);
		SetLedColorPercent(jj + 1, 100, 100, 100);
		asm("NOP");
		SendLedData();
		if (PatternDelay(50))
		{
			return 0;
		}
	}

	for (int jj = gWS_LED_COUNT - 1; jj > 0; jj -= 2)
	{
		FillAllOff();
		SetLedColorPercent(jj, 100, 100, 100);
		SetLedColorPercent(jj + 1, 100, 100, 100);
		SendLedData();
		if (PatternDelay(50))
		{
			return 0;
		}
	}

}

uint8_t PlayUPDown1()
{
	int start = 0;
	for (int jj = 0; jj < gWS_LED_COUNT; jj += 1)
	{
		FillAllOff();
		FillColorFromToPercent(start, jj, 100, 100, 100);
		asm("NOP");
		SendLedData();
		if (PatternDelay(50))
		{
			return 0;
		}
	}

	for (int jj = 0; jj < gWS_LED_COUNT; jj++)
	{
		FillAllOff();
		FillColorFromToPercent(jj, gWS_LED_COUNT - 1, 100, 100, 100);
		SendLedData();
		if (PatternDelay(50))
		{
			return 0;
		}
		return 0;
	}
}

void PlayCombined()
{
	while (1)
	{
		for (uint8_t i = 0; i < 5; i++)
		{
			if (Play2by2())
			{
				return 0;
			}
		}

		for (uint8_t i = 0; i < 5; i++)
		{
			if (PlayUPDown1())
			{
				return 0;
			}
		}
	}
}

//----------------------------------------------------------------------
#endif /* CLEDPATTERN1_H_ */
