/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "bme280.h"
#include "nrf905.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define Day 25
#define Mes 04
#define year 2020
#define hour 21
#define min 01
#define sec 13
Packet_send P;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
struct bme280_dev dev_bme = {0};


/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN */
  long j=0;

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
HAL_GPIO_WritePin(CS_BME_GPIO_Port, CS_BME_Pin, GPIO_PIN_SET);
HAL_GPIO_WritePin(CS_NRF_GPIO_Port, CS_NRF_Pin, GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOA, SP_EN_Pin, GPIO_PIN_SET);
NRF905_POWER_ON();
HAL_Delay(2);
NRF905_Config_t.AUTO_RETRAN = AUTO_RET_DISABLE ;
NRF905_Config_t.CH_NO_1 = 138;
NRF905_Config_t.CH_NO_2 = 0;
NRF905_Config_t.CRC_EN = CRC_CHECK_ENABLE;
NRF905_Config_t.CRC_MODE = CRC_MODE_16bit;
NRF905_Config_t.HFREQ_PLL = FREQ_433MHz ;
NRF905_Config_t.PA_PWR = PWR_10dBm;
NRF905_Config_t.RX_ADDRESS = 0xE7E7E7E7;
NRF905_Config_t.RX_AFW = TX_ADDR_WIDTH_4Byte ;
NRF905_Config_t.RX_PW =  sizeof(P);
NRF905_Config_t.RX_RED_PWR = RED_PWR_DISABLE;
NRF905_Config_t.TX_AFW = TX_ADDR_WIDTH_4Byte;
NRF905_Config_t.TX_PW = sizeof(P);
NRF905_Config_t.UP_CLK_EN = OUT_CLOCK_ENABLE;
NRF905_Config_t.UP_CLK_FREQ =  OUT_CLOCK_FREQ_500kHz;
NRF905_Config_t.XOF = CRYSTAL_OSC_FREQ_16MHz;

if (NRF905_INIT(&NRF905_Config_t ))
  {

  }
  /* USER CODE END 2 */
 
 

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    
   // HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
    if (initBME280(&dev_bme) == 1)
	   { 
		  GetCalibData_BME280(&dev_bme);
		  GetData_BME280(&dev_bme); 
  	 }
     P.descr[0]='B';
	   P.descr[1]='M';
	   P.descr[2]='E';
	   P.descr[3]='0';
	   P.descr[4]='1';
	   P.humm = dev_bme.data.humidity;
	   P.press = dev_bme.data.pressure;
	   P.temp = dev_bme.data.temperature;
	   P.count = j;
     //HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
     WriteDataToSend(0xE7E7E7E7, &P, sizeof(P));
     StartSend();
     j++;
     HAL_Delay(10000);
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_5;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void SPI_GET_DAT( uint8_t *ADDR, uint8_t *data)
{
	HAL_GPIO_WritePin(CS_BME_GPIO_Port, CS_BME_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, ADDR, 1, 10);
	HAL_SPI_Receive(&hspi1, data, 1, 10);
	HAL_GPIO_WritePin(CS_BME_GPIO_Port, CS_BME_Pin, GPIO_PIN_SET);
}

void SPI_SET_DAT( uint8_t *ADDR, uint8_t *data)
{
	uint8_t addr;
	addr = *(uint8_t *)ADDR;
	addr = addr & 0x7f;

	HAL_GPIO_WritePin(CS_BME_GPIO_Port, CS_BME_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, &addr, 1, 10);
	HAL_SPI_Transmit(&hspi1, data, 1, 10);
	HAL_GPIO_WritePin(CS_BME_GPIO_Port, CS_BME_Pin, GPIO_PIN_SET);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
