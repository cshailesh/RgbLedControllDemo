/*
 * CLedPatterns.h
 *
 *  Created on: 25 Dec 2018
 *      Author: Shailesh
 */

#ifndef CPATM_H_
#define CPATM_H_

#include "CWsLed.h"
#include "CPatternCommon.h"
#include "CAdc.h"

//----------------------------------------------------------------------

uint8_t BeatSense()
{
	if (HAL_GPIO_ReadPin(MIC_IN_GPIO_Port, MIC_IN_Pin) == GPIO_PIN_RESET)
	{
		KEY_DEDBOUCE_DELAY();
		return 1;
	}

	return 0;
}

uint8_t PlayBeatRed(uint8_t pIsRed, uint8_t pIsGreen, uint8_t pIsBlue)
{
	uint32_t val;
	uint8_t key;

	BeatSenseStop();
	BeatSenseStart();

	FillAllOff();
	SendLedData();

	while (1)
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

//		val = AdcGet();
//		if (val > 1000)
//		{
//			BlinkBeat(pIsRed, pIsGreen, pIsBlue);
//		}
		val = BeatSense();
		if (val > 0)
		{
			BlinkBeat(pIsRed, pIsGreen, pIsBlue);
		}

	}
}

//----------------------------------------------------------------------
#endif /* CPATM */
