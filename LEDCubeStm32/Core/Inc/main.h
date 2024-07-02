/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define PIN11_Pin GPIO_PIN_0
#define PIN11_GPIO_Port GPIOC
#define PIN12_Pin GPIO_PIN_1
#define PIN12_GPIO_Port GPIOC
#define LAYER1_Pin GPIO_PIN_0
#define LAYER1_GPIO_Port GPIOA
#define LAYER2_Pin GPIO_PIN_1
#define LAYER2_GPIO_Port GPIOA
#define LAYER3_Pin GPIO_PIN_4
#define LAYER3_GPIO_Port GPIOA
#define PIN42_Pin GPIO_PIN_5
#define PIN42_GPIO_Port GPIOA
#define PIN41_Pin GPIO_PIN_6
#define PIN41_GPIO_Port GPIOA
#define PIN34_Pin GPIO_PIN_7
#define PIN34_GPIO_Port GPIOA
#define PIN31_Pin GPIO_PIN_5
#define PIN31_GPIO_Port GPIOC
#define LAYER4_Pin GPIO_PIN_0
#define LAYER4_GPIO_Port GPIOB
#define PIN23_Pin GPIO_PIN_10
#define PIN23_GPIO_Port GPIOB
#define PIN13_Pin GPIO_PIN_6
#define PIN13_GPIO_Port GPIOC
#define PIN32_Pin GPIO_PIN_7
#define PIN32_GPIO_Port GPIOC
#define LED_Pin GPIO_PIN_8
#define LED_GPIO_Port GPIOC
#define PIN24_Pin GPIO_PIN_8
#define PIN24_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define PIN14_Pin GPIO_PIN_3
#define PIN14_GPIO_Port GPIOB
#define PIN22_Pin GPIO_PIN_4
#define PIN22_GPIO_Port GPIOB
#define PIN21_Pin GPIO_PIN_5
#define PIN21_GPIO_Port GPIOB
#define PIN33_Pin GPIO_PIN_6
#define PIN33_GPIO_Port GPIOB
#define PIN44_Pin GPIO_PIN_8
#define PIN44_GPIO_Port GPIOB
#define PIN43_Pin GPIO_PIN_9
#define PIN43_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
