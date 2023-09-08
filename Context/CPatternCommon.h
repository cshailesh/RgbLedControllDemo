/*
 * CPatternCommon.h
 *
 *  Created on: 28 Dec 2018
 *      Author: Shailesh
 */

#ifndef CPATTERNCOMMON_H_
#define CPATTERNCOMMON_H_

#include "tm_stm32_hd44780.h"

#define DEFAULT_TONE_LEVEL 75


#define PATTERN_MIN	1
#define PATTERN_MAX	10

#define SPEED_MIN	1
#define SPEED_MAX	255

#define SENSE_MIN	1
#define SENSE_MAX	255

void PlayBeep(uint32_t pTone)
{
	HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_SET);
	for (int i = 0; i < pTone; ++i)
	{
		HAL_GPIO_TogglePin(BEEP_GPIO_Port, BEEP_Pin);
		HAL_Delay(20);
	}
	HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_RESET);
}

static const unsigned char MenuListMain[PATTERN_MAX][16] =
{ "RIDER       -01\0"
, "SLOW MOTION -02\0"
, "FLIP COLOR  -03\0"
, "BEAT        -04\0"
, "GOLDEN      -05\0"
, "PINK        -06\0"
, "SKYBLUE     -07\0"
, "RED         -08\0"
, "GREEN       -09\0"
, "BLUE        -10\0"
};


#define PATTERN_OPT_MIN_1	1
#define PATTERN_OPT_MAX_1	255

#define PATTERN_OPT_MIN_2	1
#define PATTERN_OPT_MAX_2	255

#define PATTERN_OPT_MIN_3	1
#define PATTERN_OPT_MAX_3	255

#define PATTERN_OPT_MIN_4	1
#define PATTERN_OPT_MAX_4	255

#define PATTERN_OPT_MIN_5	1
#define PATTERN_OPT_MAX_5	255

#define PATTERN_OPT_MIN_6	1
#define PATTERN_OPT_MAX_6	255

#define PATTERN_OPT_MIN_7	1
#define PATTERN_OPT_MAX_7	255

#define PATTERN_OPT_MIN_8	1
#define PATTERN_OPT_MAX_8	255

#define PATTERN_OPT_MIN_9	1
#define PATTERN_OPT_MAX_9	255

#define PATTERN_OPT_MIN_10	1
#define PATTERN_OPT_MAX_10	255

uint32_t gPatternSpeed[PATTERN_MAX];

void ProcessSpeed()
{
	uint8_t keyPressed = GetKeyPressed();

	if (keyPressed == KEY_RIGHT)
	{
		gPatternSpeed[gCurMenu]++;
		if (gPatternSpeed[gCurMenu] > SPEED_MAX)
		{
			gPatternSpeed[gCurMenu] = SPEED_MIN;
		}

		LCD_Update_Speed();
		PlayBeep(5);
	}

	if (keyPressed == KEY_LEFT)
	{
		gPatternSpeed[gCurMenu]--;
		if (gPatternSpeed[gCurMenu] < SPEED_MIN)
		{
			gPatternSpeed[gCurMenu] = SPEED_MAX;
		}

		LCD_Update_Speed();
		PlayBeep(5);
	}
}

uint16_t gAdcRefVal;
#define MAX_SENSE_VALUE  2500

void CalculateSenseRef()
{
	gAdcRefVal = MAX_SENSE_VALUE
			- (gPatternSpeed[gCurMenu] * MAX_SENSE_VALUE / 100);
}

void ProcessSense()
{
	uint8_t keyPressed = GetKeyPressed();

	if (keyPressed == KEY_RIGHT)
	{
		gPatternSpeed[gCurMenu]++;
		if (gPatternSpeed[gCurMenu] > SENSE_MAX)
		{
			gPatternSpeed[gCurMenu] = SENSE_MIN;
		}

		LCD_Update_Sense();
		//gAdcRefVal=	gPatternSpeed[gCurMenu]*30;
		CalculateSenseRef();
	}

	if (keyPressed == KEY_LEFT)
	{
		gPatternSpeed[gCurMenu]--;
		if (gPatternSpeed[gCurMenu] < SENSE_MIN)
		{
			gPatternSpeed[gCurMenu] = SENSE_MAX;
		}

		LCD_Update_Sense();
	}
}

uint8_t PatternDelay(uint32_t pDelay)
{
	uint32_t tickstart = HAL_GetTick();
	uint32_t wait = pDelay;
	uint8_t key;

	/* Add a freq to guarantee minimum wait */
	if (wait < HAL_MAX_DELAY)
	{
//		wait += (uint32_t) (1);
		wait += (uint32_t) (1);
	}

	while ((HAL_GetTick() - tickstart) < wait)
	{

		ReadKeyBoard();
		key = GetKeyPressed();
		if ((key == KEY_LEFT) || (key == KEY_RIGHT))
		{
			ProcessSpeed();
		}
		if ((key == KEY_UP) || (key == KEY_DOWN))
		{
			return 1;
		}
	}

	return 0;
}

#endif /* CPATTERNCOMMON_H_ */
