/*
 * CWsLed.h
 *
 *  Created on: 25 Dec 2018
 *      Author: Shailesh
 */

#ifndef CWSLED_H_
#define CWSLED_H_

extern TIM_HandleTypeDef htim1;
extern DMA_HandleTypeDef hdma_tim1_ch1;

#define WS_PERIOD	89  //90-1
#define WS_0		18
#define WS_1		71
//#define WS_1		60

//#define WS_LED_COUNT			125
#define WS_LED_COUNT			125

//#define WS_BYTES_PER_LED		24
//#define WS_RESET_BYTES			24
//#define WS_LED_BYTES			(WS_LED_COUNT*WS_BYTES_PER_LED)
//#define WS_TOTAL_LED_DATA_SIZE	WS_RESET_BYTES+WS_LED_BYTES+WS_RESET_BYTES

#define LED_RED_PWM_MIN			0
#define LED_GREEN_PWM_MIN		0
#define LED_BLUE_PWM_MIN		0

#define LED_RED_PWM_MAX			150
//#define LED_RED_PWM_MAX		255
#define LED_GREEN_PWM_MAX		255
#define LED_BLUE_PWM_MAX		255

//#define MAX_WS_TOTAL_BUFFER		1024*4

#define CONFIG_IS_DRIVER_INVERTED	1

#define SET_LED_VALUE(x) (CONFIG_IS_DRIVER_INVERTED ? 255-x : x)

uint8_t Set_Val(uint8_t pX)
{
	if (CONFIG_IS_DRIVER_INVERTED)
	{
		return 255 - pX;
	}
	else
	{
		return pX;
	}
}

uint8_t gCurrentLedCount;
uint16_t gCurrentLedBytesCount;

#define MAX_WS_TOTAL_BUFFER		(24 + (24 * WS_LED_COUNT) + 24)

uint8_t gLedBuff[MAX_WS_TOTAL_BUFFER];
uint8_t gLEDBuffShadow[MAX_WS_TOTAL_BUFFER];

uint32_t gWS_LED_COUNT; 			//		3000ul
uint32_t gWS_BYTES_PER_LED; 		//		24
uint32_t gWS_RESET_BYTES;			//		24
uint32_t gWS_LED_BYTES;				//		(WS_LED_COUNT*WS_BYTES_PER_LED)
uint32_t gWS_TOTAL_LED_DATA_SIZE;//		WS_RESET_BYTES+WS_LED_BYTES+WS_RESET_BYTES
uint32_t gMAX_WS_TOTAL_BUFFER;		//		1024*5

void WsWait()
{
	for (int var = 0; var < 100; ++var)
	{
		__NOP();
	}
}

void WS_Init_Data()
{

	gWS_LED_COUNT = WS_LED_COUNT;
	gWS_BYTES_PER_LED = 24;
	gWS_RESET_BYTES = 24;
	gWS_LED_BYTES = gWS_BYTES_PER_LED * gWS_LED_COUNT;
	gWS_TOTAL_LED_DATA_SIZE = gWS_RESET_BYTES + gWS_LED_BYTES + gWS_RESET_BYTES;

	for (int ii = 0; ii < gWS_TOTAL_LED_DATA_SIZE; ++ii)
	{
		gLedBuff[ii] = 0;
		gLEDBuffShadow[ii] = 0;
	}
	gCurrentLedCount = gWS_LED_COUNT;
	gCurrentLedBytesCount = gWS_RESET_BYTES
			+ (gCurrentLedCount * gWS_BYTES_PER_LED) + gWS_RESET_BYTES;
}

void SetLedColor(uint16_t pIndex, uint8_t pR, uint8_t pG, uint8_t pB)
{

	//decrease to increase watts
	//----------------------------------------------

	if (pR < 220)
	{
		pR = 220;
	}

	//--------------------------------------------------

//	if (pG < 20)
//	{
//		pG = 20;
//	}

	if (pIndex > gWS_LED_COUNT - 1)
	{
		return;
	}

	if (pIndex < 0)
	{
		return;
	}
	uint16_t baseAddr = (24 * pIndex) + gWS_RESET_BYTES;
	if (baseAddr > gCurrentLedBytesCount)
	{
		return;
	}

	for (int j = 0; j < 8; ++j)
	{
		gLEDBuffShadow[baseAddr + j] = ((pR << j) & 0x80) ? WS_1 : WS_0;
		gLEDBuffShadow[8 + baseAddr + j] = ((pG << j) & 0x80) ? WS_1 : WS_0;
		gLEDBuffShadow[16 + baseAddr + j] = ((pB << j) & 0x80) ? WS_1 : WS_0;
	}
}

void SetLedColor32(uint16_t pIndex, uint32_t pColorU32)
{
	uint8_t r = (uint8_t) (pColorU32 >> 16);
	uint8_t g = (uint8_t) (pColorU32 >> 8);
	uint8_t b = (uint8_t) pColorU32;
	SetLedColor(pIndex, r, g, b);
}

//void SetLedColorPercent(uint16_t pIndex, uint8_t pRedPer, uint8_t pGreenPer,
//		uint8_t pBluePer)
//{
//
//	uint8_t resRed = LED_RED_PWM_MAX * pRedPer / 100;
//	uint8_t resGreen = LED_GREEN_PWM_MAX * pGreenPer / 100;
//	uint8_t resBlue = LED_BLUE_PWM_MAX * pBluePer / 100;
//
//	resRed = LED_RED_PWM_MAX - resRed;
//	resGreen = LED_GREEN_PWM_MAX - resGreen;
//	resBlue = LED_BLUE_PWM_MAX - resBlue;
//
//	SetLedColor(pIndex, resRed, resGreen, resBlue);
//}

void CopyShadow()
{
	for (uint16_t i = 0; i < gCurrentLedBytesCount; ++i)
	{
		gLedBuff[i] = gLEDBuffShadow[i];
	}
}

void FillColor(uint8_t pRed, uint8_t pGreen, uint8_t pBlue)
{

	for (int i = 0; i < gCurrentLedCount; ++i)
	{
		SetLedColor(i, pRed, pGreen, pBlue);
	}
}

//void FillColorPercent(uint8_t pRedPer, uint8_t pGreenPer, uint8_t pBluePer)
//{
//	for (int i = 0; i < gCurrentLedCount; ++i)
//	{
//		SetLedColorPercent(i, pRedPer, pGreenPer, pBluePer);
//	}
//}

void FillAllOff()
{
	for (int i = 0; i < gCurrentLedCount; ++i)
	{
		SetLedColor(i, 255, 255, 255);
	}
}

//void FillColorFromToPercent(int pStart, int pEnd, uint8_t pRedPer,
//		uint8_t pGreenPer, uint8_t pBluePer)
//{
//	uint8_t current = pStart;
//	while (current <= pEnd)
//	{
//		SetLedColorPercent(current, pRedPer, pGreenPer, pBluePer);
//		current++;
//	}
//}

void SendLedData()
{
	CopyShadow();
	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t*) gLedBuff,
			gWS_TOTAL_LED_DATA_SIZE);
	WsWait();
	//HAL_Delay(1);
	//HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_1);
}

void WSHardwareInit()
{
	HAL_TIM_Base_Start(&htim1);
	//__HAL_TIM_ENABLE_IT(&htim1, TIM_IT_UPDATE);
	WS_Init_Data();
}

#endif /* CWSLED_H_ */
