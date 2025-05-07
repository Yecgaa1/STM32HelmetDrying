/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "stm32g4xx_hal.h"

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
#define hot0_Pin GPIO_PIN_10
#define hot0_GPIO_Port GPIOG
#define Light1_Pin GPIO_PIN_0
#define Light1_GPIO_Port GPIOC
#define Light2_Pin GPIO_PIN_1
#define Light2_GPIO_Port GPIOC
#define Light3_Pin GPIO_PIN_2
#define Light3_GPIO_Port GPIOC
#define Light4_Pin GPIO_PIN_3
#define Light4_GPIO_Port GPIOC
#define Hot1_Pin GPIO_PIN_10
#define Hot1_GPIO_Port GPIOB
#define Hot2_Pin GPIO_PIN_11
#define Hot2_GPIO_Port GPIOB
#define Hot3_Pin GPIO_PIN_12
#define Hot3_GPIO_Port GPIOB
#define Hot4_Pin GPIO_PIN_13
#define Hot4_GPIO_Port GPIOB
#define Hot5_Pin GPIO_PIN_14
#define Hot5_GPIO_Port GPIOB
#define Hot6_Pin GPIO_PIN_15
#define Hot6_GPIO_Port GPIOB
#define Light5_Pin GPIO_PIN_6
#define Light5_GPIO_Port GPIOC
#define Light6_Pin GPIO_PIN_7
#define Light6_GPIO_Port GPIOC
#define DoorInput_Pin GPIO_PIN_8
#define DoorInput_GPIO_Port GPIOC
#define Beep_Pin GPIO_PIN_9
#define Beep_GPIO_Port GPIOC
#define DoorLight_Pin GPIO_PIN_8
#define DoorLight_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
