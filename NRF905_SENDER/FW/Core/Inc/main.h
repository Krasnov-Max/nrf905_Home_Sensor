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
#include "stm32l0xx_hal.h"

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
#define PWR_Pin GPIO_PIN_14
#define PWR_Port GPIOC
#define TRX_CE_Pin GPIO_PIN_10
#define TRX_CE_Port GPIOA
#define TX_EN_Pin GPIO_PIN_15
#define TX_EN_Port GPIOC
#define CS_BME_Pin GPIO_PIN_9
#define CS_BME_Port GPIOA
#define CS_NRF_Pin GPIO_PIN_1
#define CS_NRF_Port GPIOB
#define DR_Pin GPIO_PIN_4
#define DR_Port GPIOA
#define StepUP_EN_Pin  GPIO_PIN_1
#define StepUP_EN_Port  GPIOA
#define SlaveDevice_Pin GPIO_PIN_3
#define SlaveDevice_Port GPIOA
/* USER CODE BEGIN Private defines */
typedef struct {
uint8_t id[4];
long humm;
long temp;
long press;
long count;
uint16_t vbat;
}Packet_send;

uint16_t flash_read(uint32_t address);
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
