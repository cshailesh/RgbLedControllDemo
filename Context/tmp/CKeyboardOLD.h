/*
 * CKeyboard.h
 *
 *  Created on: 20 Dec 2018
 *      Author: Shailesh
 */

#ifndef CKEYBOARDOLD_H_
#define CKEYBOARDOLD_H_

#include <main.h>
#include "tm_stm32_hd44780.h"

//#define KEY_NONE		5
//#define KEY_UP		10
//#define KEY_DOWN		11
//#define KEY_LEFT		12
//#define KEY_RIGHT		13
//#define KEY_OK		14

uint8_t ReadKeyboard()
{
	if (HAL_GPIO_ReadPin(SW_UP_GPIO_Port, SW_UP_Pin) == GPIO_PIN_RESET)
	{
		HAL_Delay(5);
		return KEY_UP;
	}

	if (HAL_GPIO_ReadPin(SW_DOWN_GPIO_Port, SW_DOWN_Pin) == GPIO_PIN_RESET)
	{
		HAL_Delay(5);
		return KEY_DOWN;
	}

	if (HAL_GPIO_ReadPin(SW_LEFT_GPIO_Port, SW_LEFT_Pin) == GPIO_PIN_RESET)
	{
		HAL_Delay(5);
		return KEY_LEFT;
	}

	if (HAL_GPIO_ReadPin(SW_RIGHT_GPIO_Port, SW_RIGHT_Pin) == GPIO_PIN_RESET)
	{
		HAL_Delay(5);
		return KEY_RIGHT;
	}

	if (HAL_GPIO_ReadPin(SW_OK_GPIO_Port, SW_OK_Pin) == GPIO_PIN_RESET)
	{
		HAL_Delay(5);
		return KEY_OK;
	}

	return KEY_NONE;

}

#define PATTERN_MIN	1
#define PATTERN_MAX	8

#define SPEED_MIN	1
#define SPEED_MAX	100

uint8_t gKeyPressed;

void KeyboardInit()
{
	gCurMenu = PATTERN_MIN;
	gKeyPressed = KEY_NONE;
	gSpeed=20;

	LCD_Update_Pattern();
	LCD_Update_Speed();

}


void Processkeys()
{
	uint8_t keyPressed = ReadKeyboard();

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

#endif /* CKEYBOARDOLD_H_ */
