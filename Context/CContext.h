/*
 * CContext.h
 *
 *  Created on: 28 Dec 2018
 *      Author: Shailesh
 */

#ifndef CCONTEXT_H_
#define CCONTEXT_H_

#include <CKeyboard.h>
#include <main.h>
#include "tm_stm32_hd44780.h"
#include "CWsLed.h"
#include "CPatternCommon.h"
#include "CLEDPattern1.h"
#include "CPatternPar.h"
#include "CAdc.h"
#include "CSecurity.h"

void ProcesskeysUpDown()
{
	//uint8_t keyPressed = ReadKeyboard();

	uint8_t keyPressed = ReadKeyBoard();

	if (keyPressed == KEY_DOWN)
	{
		gCurMenu++;
		if (gCurMenu > PATTERN_MAX)
		{
			gCurMenu = PATTERN_MIN;
		}

		LCD_Update_Pattern();
	}

	if (keyPressed == KEY_UP)
	{
		gCurMenu--;
		if (gCurMenu < PATTERN_MIN)
		{
			gCurMenu = PATTERN_MAX;
		}
		LCD_Update_Pattern();
	}

	ResetKeyPresed();
}

uint32_t adcLCdCnt;
void LCD_Update_Adc()
{
//	adcLCdCnt++;
//	if(adcLCdCnt>1)
//	{
//		adcLCdCnt=0;
//	}

//	uint32_t val = AdcGet();

	/*
	 //TM_HD44780_Puts(0, 1, "                ");
	 snprintf(gLCDStrSpeedbuffer, 16, "SPEED - %.3d +\0",
	 val);
	 TM_HD44780_Puts(0, 1, gLCDStrSpeedbuffer);
	 */
	//TM_HD44780_Puts(0, 1, "                ");
//	HAL_Delay(10);
//	snprintf(gLCDStrSpeedbuffer, 16, "%.3d\n", val);
//	TM_HD44780_Puts(0, adcLCdCnt, "    ");
//	TM_HD44780_Puts(0, adcLCdCnt, gLCDStrSpeedbuffer);
}

void LCD_Update_Pattern()
{
	TM_HD44780_Puts(0, 0, "                ");
	TM_HD44780_Puts(0, 0, MenuListMain[gCurMenu - 1]);
}

void LCD_Update_Speed()
{
	TM_HD44780_Puts(0, 1, "                ");
	snprintf(gLCDStrSpeedbuffer, 16, "TONE  - %.3d +\0",
			gPatternSpeed[gCurMenu]);
	TM_HD44780_Puts(0, 1, gLCDStrSpeedbuffer);
}

void LCD_Update_Sense()
{
	TM_HD44780_Puts(0, 1, "                ");
	snprintf(gLCDStrSpeedbuffer, 16, "MIC SENSE-%.3d+\0",
			gPatternSpeed[gCurMenu]);
	TM_HD44780_Puts(0, 1, gLCDStrSpeedbuffer);
}

void LcdLoad()
{
	HAL_Delay(200);
	TM_HD44780_Puts(0, 0, "    REDGLOW     ");
	TM_HD44780_Puts(0, 1, "                ");

	HAL_Delay(1000);

	TM_HD44780_Puts(0, 0, "   LOADING..    ");
	TM_HD44780_Puts(0, 1, "                ");

	HAL_Delay(1000);

//	TM_HD44780_Puts(0, 0, "    WELCOME  ");
//	TM_HD44780_Puts(0, 1, "REDSUN PVT. LTD.");

	HAL_Delay(500);
}

void ContextInit()
{

	if (!ContextPin())
	{
		return;
	}

	gCurMenu = PATTERN_MIN;
	//gSpeed = 20;

	gPatternSpeed[0] = 1;
	gPatternSpeed[1] = 1;
	gPatternSpeed[2] = 1;
	gPatternSpeed[3] = 1;
	gPatternSpeed[4] = 1;
	gPatternSpeed[5] = 1;
	gPatternSpeed[6] = 1;

	KeyboardInit();
	LcdInit();

	LcdLoad();

	LCD_Update_Pattern();
	LCD_Update_Speed();
}

void TestProcesskeys()
{
	uint8_t keyPressed = ReadKeyPin();

	if (keyPressed == KEY_DOWN)
	{
		gCurMenu++;
		if (gCurMenu > PATTERN_MAX)
		{
			gCurMenu = PATTERN_MIN;
		}

		LCD_Update_Pattern();
	}

	if (keyPressed == KEY_UP)
	{
		gCurMenu--;
		if (gCurMenu < PATTERN_MIN)
		{
			gCurMenu = PATTERN_MAX;
		}
		LCD_Update_Pattern();
	}

	if (keyPressed == KEY_RIGHT)
	{
		gSpeed++;
		if (gSpeed > SPEED_MAX)
		{
			gSpeed = SPEED_MIN;
		}

		LCD_Update_Speed();
	}

	if (keyPressed == KEY_LEFT)
	{
		gSpeed--;
		if (gSpeed < SPEED_MIN)
		{
			gSpeed = SPEED_MAX;
		}

		LCD_Update_Speed();
	}

}

void Pattern4(uint32_t pTimes)
{
	uint8_t red = 0;
	uint8_t green = 50;
	uint8_t blue = 100;

	gPatternSpeed[1] = 500;
	uint32_t speed = gPatternSpeed[1];

	int flag = 0;

	uint8_t isForever;
	if (pTimes == 0)
	{
		isForever = 1;
	}
	else
	{

		isForever = 0;
	}

	uint32_t cnt = pTimes;
	while (1)
	{
		if (!isForever)
		{
			cnt--;
			if (cnt == 0)
			{
				return;
			}
		}

		FillAllOff();
		SendLedData();
		HAL_Delay(speed);

		for (int i = 0; i < gCurrentLedCount; ++i)
		{

			flag++;
			if (flag > 3)
			{
				flag = 1;
			}

			if (flag == 1)
			{
				red = 100;
				green = 0;
				blue = 0;
			}
			else if (flag == 2)
			{
				red = 0;
				green = 100;
				blue = 0;
			}
			else if (flag == 3)
			{
				red = 0;
				green = 0;
				blue = 100;
			}

			SetLedColorPercent(i, red, green, blue);
		}

		SendLedData();
		HAL_Delay(speed);

		FillAllOff();
		SendLedData();
		HAL_Delay(speed);

		flag = 0;
		for (int i = 0; i < gCurrentLedCount; ++i)
		{

			flag++;
			if (flag > 3)
			{
				flag = 1;
			}

			if (flag == 1)
			{
				red = 0;
				green = 0;
				blue = 100;
			}
			else if (flag == 2)
			{
				red = 100;
				green = 100;
				blue = 0;
			}
			else if (flag == 3)
			{
				red = 0;
				green = 0;
				blue = 100;
			}

			SetLedColorPercent(i, red, green, blue);
		}
		SendLedData();
		HAL_Delay(speed);

	}
}

#endif /* CCONTEXT_H_ */
