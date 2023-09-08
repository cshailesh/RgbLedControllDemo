/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MIC_IN_Pin GPIO_PIN_0
#define MIC_IN_GPIO_Port GPIOA
#define USER_GPIO1_Pin GPIO_PIN_3
#define USER_GPIO1_GPIO_Port GPIOA
#define USER_GPIO2_Pin GPIO_PIN_4
#define USER_GPIO2_GPIO_Port GPIOA
#define USER_GPIO3_Pin GPIO_PIN_5
#define USER_GPIO3_GPIO_Port GPIOA
#define SW_OK_Pin GPIO_PIN_6
#define SW_OK_GPIO_Port GPIOA
#define SW_LEFT_Pin GPIO_PIN_7
#define SW_LEFT_GPIO_Port GPIOA
#define SW_RIGHT_Pin GPIO_PIN_0
#define SW_RIGHT_GPIO_Port GPIOB
#define SW_DOWN_Pin GPIO_PIN_1
#define SW_DOWN_GPIO_Port GPIOB
#define SW_UP_Pin GPIO_PIN_2
#define SW_UP_GPIO_Port GPIOB
#define HD44780_RS_Pin GPIO_PIN_10
#define HD44780_RS_GPIO_Port GPIOB
#define HD44780_E_Pin GPIO_PIN_11
#define HD44780_E_GPIO_Port GPIOB
#define HD44780_D4_Pin GPIO_PIN_12
#define HD44780_D4_GPIO_Port GPIOB
#define HD44780_D5_Pin GPIO_PIN_13
#define HD44780_D5_GPIO_Port GPIOB
#define HD44780_D6_Pin GPIO_PIN_14
#define HD44780_D6_GPIO_Port GPIOB
#define HD44780_D7_Pin GPIO_PIN_15
#define HD44780_D7_GPIO_Port GPIOB
#define DATA_OUT_Pin GPIO_PIN_8
#define DATA_OUT_GPIO_Port GPIOA
#define BEEP_Pin GPIO_PIN_15
#define BEEP_GPIO_Port GPIOA
#define MIC_SENS_Pin GPIO_PIN_4
#define MIC_SENS_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
