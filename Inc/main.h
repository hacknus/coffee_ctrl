/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#define ENC_SW_Pin GPIO_PIN_13
#define ENC_SW_GPIO_Port GPIOC
#define PUMP_Pin GPIO_PIN_14
#define PUMP_GPIO_Port GPIOC
#define HEATER_Pin GPIO_PIN_15
#define HEATER_GPIO_Port GPIOC
#define P_Pin GPIO_PIN_0
#define P_GPIO_Port GPIOA
#define I_Pin GPIO_PIN_1
#define I_GPIO_Port GPIOA
#define LVL_Pin GPIO_PIN_2
#define LVL_GPIO_Port GPIOA
#define STEAM_Pin GPIO_PIN_3
#define STEAM_GPIO_Port GPIOA
#define SPI1_CS_Pin GPIO_PIN_4
#define SPI1_CS_GPIO_Port GPIOA
#define SW3_Pin GPIO_PIN_0
#define SW3_GPIO_Port GPIOB
#define SW2_Pin GPIO_PIN_1
#define SW2_GPIO_Port GPIOB
#define LED_SW2_Pin GPIO_PIN_10
#define LED_SW2_GPIO_Port GPIOB
#define LED_SW1_Pin GPIO_PIN_11
#define LED_SW1_GPIO_Port GPIOB
#define SPI2_CS_Pin GPIO_PIN_12
#define SPI2_CS_GPIO_Port GPIOB
#define LED2_Pin GPIO_PIN_4
#define LED2_GPIO_Port GPIOB
#define LED1_Pin GPIO_PIN_5
#define LED1_GPIO_Port GPIOB
#define BUZZ_Pin GPIO_PIN_8
#define BUZZ_GPIO_Port GPIOB
#define SERVO_Pin GPIO_PIN_9
#define SERVO_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
