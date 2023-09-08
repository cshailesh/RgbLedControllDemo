/*
 * CLedPatterns.h
 *
 *  Created on: 25 Dec 2018
 *      Author: Shailesh
 */

#ifndef CPATTERNPAR_H_
#define CPATTERNPAR_H_

#include "CWsLed.h"
#include "CPatternCommon.h"
#include "CAdc.h"

//----------------------------------------------------------------------

//uint8_t wheelMidLedNo;

#define DEFUALT_SLOW_MOTION_DELAY		5
#define DEFUALT_SLOW_MOTION_DELAY_INC	2

uint8_t PlaySlowMotion3()
{
	BeatSenseStop();

	volatile uint32_t fwd = 0;
	//wheelMidLedNo = gCurrentLedCount / 2;

	gPatternSpeed[gCurMenu] = DEFUALT_SLOW_MOTION_DELAY;
//	gPatternSpeed[gCurMenu] = 10;
	LCD_Update_Speed();

	uint8_t tmpR = 0;
	uint8_t tmpG = 0;
	uint8_t tmpB = 0;

	uint32_t patternDelay = 0;

	uint32_t isFirst = 1;

	while (1)
	{
		//red
		if (isFirst == 1)
		{
			for (fwd = 0; fwd < MaxLoop; ++fwd)
			{
				//FillColor(255 - tmpR, 255 - tmpG, 255 - tmpB);
				FillColor(Set_Val(tmpR), Set_Val(tmpG), Set_Val(tmpB));
				SendLedData();
				tmpR++;
				patternDelay = DEFUALT_SLOW_MOTION_DELAY_INC
						* gPatternSpeed[gCurMenu];
//				patternDelay = 100 - gPatternSpeed[gCurMenu];
				if (PatternDelay(patternDelay))
				{
					return 0;
				}
			}

			isFirst = 0;
		}

		//pink
		tmpR = 255;
		tmpG = 0;
		tmpB = 0;

		for (fwd = 0; fwd < MaxLoop; ++fwd)
		{
//			FillColor(tmpR, tmpG, tmpB);
			FillColor(Set_Val(tmpR), Set_Val(tmpG), Set_Val(tmpB));

			//			FillColor(255 - tmpR, 255 - tmpG, 255 - tmpB);
			SendLedData();
			tmpB++;
			patternDelay = DEFUALT_SLOW_MOTION_DELAY_INC
					* gPatternSpeed[gCurMenu];
//			patternDelay = 100 - gPatternSpeed[gCurMenu];
			if (PatternDelay(patternDelay))
			{
				return 0;
			}
		}

		/// pink stable
		for (fwd = 0; fwd < MaxLoop / 2; ++fwd)
		{
			if (PatternDelay(patternDelay))
			{
				return 0;
			}
		}

		// blue

		for (fwd = 0; fwd < MaxLoop; ++fwd)
		{
//			FillColor(tmpR, tmpG, tmpB);
//			FillColor(255 - tmpR, 255 - tmpG, 255 - tmpB);
			FillColor(Set_Val(tmpR), Set_Val(tmpG), Set_Val(tmpB));
			SendLedData();
			tmpR--;
			patternDelay = DEFUALT_SLOW_MOTION_DELAY_INC
					* gPatternSpeed[gCurMenu];
			if (PatternDelay(patternDelay))
			{
				return 0;
			}
		}

		//blue stable
		for (fwd = 0; fwd < MaxLoop / 2; ++fwd)
		{
			if (PatternDelay(patternDelay))
			{
				return 0;
			}
		}

		// skyblue

		for (fwd = 0; fwd < MaxLoop; ++fwd)
		{
//			FillColor(tmpR, tmpG, tmpB);
			FillColor(Set_Val(tmpR), Set_Val(tmpG), Set_Val(tmpB));
//			FillColor(255 - tmpR, 255 - tmpG, 255 - tmpB);
			SendLedData();
			tmpG++;
			patternDelay = DEFUALT_SLOW_MOTION_DELAY_INC
					* gPatternSpeed[gCurMenu];
			if (PatternDelay(patternDelay))
			{
				return 0;
			}
		}
		///  stable
		for (fwd = 0; fwd < MaxLoop / 2; ++fwd)
		{
			if (PatternDelay(patternDelay))
			{
				return 0;
			}
		}

		// green

		for (fwd = 0; fwd < MaxLoop; ++fwd)
		{
			FillColor(Set_Val(tmpR), Set_Val(tmpG), Set_Val(tmpB));
			//FillColor(255 - tmpR, 255 - tmpG, 255 - tmpB);
			//			FillColor(tmpR, tmpG, tmpB);
			SendLedData();
			tmpB--;
			patternDelay = DEFUALT_SLOW_MOTION_DELAY_INC
					* gPatternSpeed[gCurMenu];
			if (PatternDelay(patternDelay))
			{
				return 0;
			}
		}

		// GREEN stable
		for (fwd = 0; fwd < MaxLoop / 2; ++fwd)
		{
			if (PatternDelay(patternDelay))
			{
				return 0;
			}
		}

		//white
		for (fwd = 0; fwd < MaxLoop; ++fwd)
		{
			FillColor(Set_Val(tmpR), Set_Val(tmpG), Set_Val(tmpB));
			SendLedData();
			tmpB++;
			tmpR++;
			patternDelay = DEFUALT_SLOW_MOTION_DELAY_INC
					* gPatternSpeed[gCurMenu];
			if (PatternDelay(patternDelay))
			{
				return 0;
			}
		}

		// red

		for (fwd = 0; fwd < MaxLoop; ++fwd)
		{
			FillColor(Set_Val(tmpR), Set_Val(tmpG), Set_Val(tmpB));
//			FillColor(255 - tmpR, 255 - tmpG, 255 - tmpB);
//			FillColor(tmpR, tmpG, tmpB);
			SendLedData();
			tmpG--;
			tmpB--;

			patternDelay = DEFUALT_SLOW_MOTION_DELAY_INC
					* gPatternSpeed[gCurMenu];
			if (PatternDelay(patternDelay))
			{
				return 0;
			}
		}
		// red
		for (fwd = 0; fwd < MaxLoop / 2; ++fwd)
		{
			if (PatternDelay(patternDelay))
			{
				return 0;
			}
		}
	}
}

//----------------------------------------------------------------------
#endif /* CLEDPATTERN1_H_ */
