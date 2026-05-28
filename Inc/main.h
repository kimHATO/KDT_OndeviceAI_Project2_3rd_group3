/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32f4xx_hal.h"

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
#define arrLED3_Pin GPIO_PIN_13
#define arrLED3_GPIO_Port GPIOC
#define dontuse_Pin GPIO_PIN_14
#define dontuse_GPIO_Port GPIOC
#define dontuseC15_Pin GPIO_PIN_15
#define dontuseC15_GPIO_Port GPIOC
#define GPIO_Output_Pin GPIO_PIN_0
#define GPIO_Output_GPIO_Port GPIOA
#define arrLED7_Pin GPIO_PIN_4
#define arrLED7_GPIO_Port GPIOC
#define arrLED6_Pin GPIO_PIN_10
#define arrLED6_GPIO_Port GPIOB
#define arrLED8_Pin GPIO_PIN_12
#define arrLED8_GPIO_Port GPIOB
#define arrLED1_Pin GPIO_PIN_8
#define arrLED1_GPIO_Port GPIOA
#define arrLED2_Pin GPIO_PIN_9
#define arrLED2_GPIO_Port GPIOA
#define arrLED5_Pin GPIO_PIN_15
#define arrLED5_GPIO_Port GPIOA
#define arrLED4_Pin GPIO_PIN_2
#define arrLED4_GPIO_Port GPIOD
#define photoInterrupter_Pin GPIO_PIN_7
#define photoInterrupter_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
