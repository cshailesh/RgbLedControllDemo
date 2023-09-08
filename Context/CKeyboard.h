/*
 * CKeyboard.h
 *
 *  Created on: 20 Dec 2018
 *      Author: Shailesh
 */

#ifndef CKEYBOARD_H_
#define CKEYBOARD_H_

#include <main.h>

#define KEY_NONE		5
#define KEY_UP			10
#define KEY_DOWN		11
#define KEY_LEFT		12
#define KEY_RIGHT		13
#define KEY_OK			14

//#define SW_UP_Pin GPIO_PIN_9
//#define SW_UP_GPIO_Port GPIOA
//#define SW_DOWN_Pin GPIO_PIN_10
//#define SW_DOWN_GPIO_Port GPIOA
//#define SW_LEFT_Pin GPIO_PIN_11
//#define SW_LEFT_GPIO_Port GPIOA
//#define SW_RIGHT_Pin GPIO_PIN_12
//#define SW_RIGHT_GPIO_Port GPIOA
//#define SW_OK_Pin GPIO_PIN_3
//#define SW_OK_GPIO_Port GPIOB

#define KEY_DEDBOUCE_DELAY() HAL_Delay(1);

uint8_t gKeyPressed;
uint8_t gKeyLastPressed;

uint8_t ReadKeyPin()
{
	if (HAL_GPIO_ReadPin(SW_UP_GPIO_Port, SW_UP_Pin) == GPIO_PIN_RESET)
	{
		KEY_DEDBOUCE_DELAY();
		return KEY_UP;
	}

	if (HAL_GPIO_ReadPin(SW_DOWN_GPIO_Port, SW_DOWN_Pin) == GPIO_PIN_RESET)
	{
		KEY_DEDBOUCE_DELAY();
		return KEY_DOWN;
	}

	if (HAL_GPIO_ReadPin(SW_LEFT_GPIO_Port, SW_LEFT_Pin) == GPIO_PIN_RESET)
	{
		KEY_DEDBOUCE_DELAY();
		return KEY_LEFT;
	}

	if (HAL_GPIO_ReadPin(SW_RIGHT_GPIO_Port, SW_RIGHT_Pin) == GPIO_PIN_RESET)
	{
		KEY_DEDBOUCE_DELAY();
		return KEY_RIGHT;
	}

	if (HAL_GPIO_ReadPin(SW_OK_GPIO_Port, SW_OK_Pin) == GPIO_PIN_RESET)
	{
		KEY_DEDBOUCE_DELAY();
		return KEY_OK;
	}

	return KEY_NONE;

}

uint8_t ReadKeyBoard()
{
	gKeyPressed = ReadKeyPin();
	if (gKeyPressed != KEY_NONE)
	{
		gKeyLastPressed = gKeyPressed;
	}

	return gKeyPressed;
}

uint8_t GetKeyPressed()
{
	return gKeyPressed;
}

void ResetKeyPresed()
{
	gKeyPressed = KEY_NONE;
}

void KeyboardInit()
{
	gKeyPressed = KEY_NONE;
}




#endif /* CKEYBOARD_H_ */
