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
#include "stm32f0xx_hal.h"

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
#define LCD_LED_Pin GPIO_PIN_3
#define LCD_LED_GPIO_Port GPIOA
#define LCD_DC_Pin GPIO_PIN_4
#define LCD_DC_GPIO_Port GPIOF
#define LCD_RES_Pin GPIO_PIN_5
#define LCD_RES_GPIO_Port GPIOF
#define LCD_CS_Pin GPIO_PIN_4
#define LCD_CS_GPIO_Port GPIOA
#define LCD_CLK_Pin GPIO_PIN_5
#define LCD_CLK_GPIO_Port GPIOA
#define LCD_MISO_Pin GPIO_PIN_6
#define LCD_MISO_GPIO_Port GPIOA
#define LCD_MOSI_Pin GPIO_PIN_7
#define LCD_MOSI_GPIO_Port GPIOA
#define NRF_CS_Pin GPIO_PIN_12
#define NRF_CS_GPIO_Port GPIOB
#define NRF_CLK_Pin GPIO_PIN_13
#define NRF_CLK_GPIO_Port GPIOB
#define NRF_MISO_Pin GPIO_PIN_14
#define NRF_MISO_GPIO_Port GPIOB
#define NRF_MOSI_Pin GPIO_PIN_15
#define NRF_MOSI_GPIO_Port GPIOB
#define NRF_PWR_Pin GPIO_PIN_6
#define NRF_PWR_GPIO_Port GPIOC
#define NRF_CE_Pin GPIO_PIN_7
#define NRF_CE_GPIO_Port GPIOC
#define NRF_TXEN_Pin GPIO_PIN_8
#define NRF_TXEN_GPIO_Port GPIOC
#define NRF_DR_Pin GPIO_PIN_9
#define NRF_DR_GPIO_Port GPIOC
#define NRF_AM_Pin GPIO_PIN_8
#define NRF_AM_GPIO_Port GPIOA
#define NRF_CD_Pin GPIO_PIN_9
#define NRF_CD_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */
typedef struct {
uint8_t id[4];
long humm;
long temp;
long press;
long count;
uint16_t vbat;
}Packet_send;

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
