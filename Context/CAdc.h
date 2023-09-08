/*
 * CAdc.h
 *
 *  Created on: 20 Jan 2019
 *      Author: Shailesh
 */

#ifndef CADC_H_
#define CADC_H_
#include "main.h"
#include "stm32f1xx_hal.h"

uint16_t gAdcValueRaw;
uint16_t gADCArrayValue[10];
uint16_t gAdcSampleCnt;
uint16_t gAdcAvgValue;

#define ADC_MAX_SAMPLE	6

uint16_t GetAdcSampleCnt()
{
	gAdcSampleCnt++;
	if (gAdcSampleCnt > ADC_MAX_SAMPLE - 1)
	{
		gAdcSampleCnt = 0;
	}
	return gAdcSampleCnt;
}

void AdcResetValue()
{
	for (int i = 0; i < ADC_MAX_SAMPLE; ++i)
	{
		gADCArrayValue[i] = 0;
	}
}

uint16_t AdcGet()
{
	uint16_t sum = 0;
	uint16_t res = 0;
	for (int var = 0; var < ADC_MAX_SAMPLE; ++var)
	{
		sum += gADCArrayValue[var];
	}

	res = sum / ADC_MAX_SAMPLE;
	return res;
}

void AdcSetValue(uint16_t pVal)
{
	uint16_t cnt = GetAdcSampleCnt();
	gADCArrayValue[cnt] = pVal;
	gAdcAvgValue = AdcGet();
}

void AdcInit()
{
	AdcResetValue();
}

void BeatSenseStart()
{
	//gBeatRefVal=0;
	HAL_ADC_Start_IT(&hadc1);
}

void BeatSenseStop()
{
	//gBeatRefVal=0;
	HAL_ADC_Stop_IT(&hadc1);
}

#endif /* CADC_H_ */
