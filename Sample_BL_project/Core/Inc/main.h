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
#define STATUS_LED_Pin GPIO_PIN_13
#define STATUS_LED_GPIO_Port GPIOC
#define PWR_LED_Pin GPIO_PIN_14
#define PWR_LED_GPIO_Port GPIOC
#define DO5_Pin GPIO_PIN_15
#define DO5_GPIO_Port GPIOC
#define UDO2_Pin GPIO_PIN_1
#define UDO2_GPIO_Port GPIOA
#define DO1_Pin GPIO_PIN_2
#define DO1_GPIO_Port GPIOB
#define DO2_Pin GPIO_PIN_10
#define DO2_GPIO_Port GPIOB
#define DO3_Pin GPIO_PIN_12
#define DO3_GPIO_Port GPIOB
#define DO4_Pin GPIO_PIN_13
#define DO4_GPIO_Port GPIOB
#define GSM_PWR_Pin GPIO_PIN_14
#define GSM_PWR_GPIO_Port GPIOB
#define GSM_RST_Pin GPIO_PIN_15
#define GSM_RST_GPIO_Port GPIOB
#define TX_EN_Pin GPIO_PIN_8
#define TX_EN_GPIO_Port GPIOA
#define DI1_Pin GPIO_PIN_11
#define DI1_GPIO_Port GPIOA
#define DI2_Pin GPIO_PIN_12
#define DI2_GPIO_Port GPIOA
#define DI5_Pin GPIO_PIN_15
#define DI5_GPIO_Port GPIOA
#define DI5_EXTI_IRQn EXTI15_10_IRQn
#define DI3_Pin GPIO_PIN_3
#define DI3_GPIO_Port GPIOB
#define DI4_Pin GPIO_PIN_4
#define DI4_GPIO_Port GPIOB
#define EE_WP_Pin GPIO_PIN_5
#define EE_WP_GPIO_Port GPIOB
#define GSM_EN_Pin GPIO_PIN_8
#define GSM_EN_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
