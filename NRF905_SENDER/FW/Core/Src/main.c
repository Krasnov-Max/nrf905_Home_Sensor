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
#include "rtc.h"
#include "adc.h"
#include "dma.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "bme280.h"
#include "nrf905.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

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
  volatile long j=0;
  volatile uint16_t k, adc[2]={0};
  volatile uint16_t flg_adc_end=0;
  volatile float t = 0;
  volatile uint16_t vref_cal = 0;
  volatile uint8_t PwerFlag = 0;
  extern RTC_HandleTypeDef hrtc;
  extern ADC_HandleTypeDef hadc;
  extern DMA_HandleTypeDef hdma_adc;

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  SystemClock_Config();
  __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
  GPIO_Init();
  MX_SPI1_Init();
  MX_DMA_Init();
  MX_ADC_Init();
  MX_RTC_Init();
  vref_cal = flash_read (0x1FF80078);
  HAL_GPIO_WritePin(CS_BME_Port, CS_BME_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(CS_NRF_Port, CS_NRF_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(StepUP_EN_Port, StepUP_EN_Pin, GPIO_PIN_SET);
  HAL_ADCEx_Calibration_Start(&hadc, 0);
  HAL_ADC_Start_DMA(&hadc, (uint32_t*)&adc, 2);
  while (flg_adc_end == 1) {}
  flg_adc_end = 0;
  HAL_ADC_Stop_DMA(&hadc);
  HAL_GPIO_WritePin(SlaveDevice_Port, SlaveDevice_Pin, GPIO_PIN_RESET);
  HAL_Delay(1);
  NRF905_ILDE_Mode();
  HAL_Delay(1);
  NRF905_Config_t.AUTO_RETRAN = 0 ;
  NRF905_Config_t.CH_NO_1 = 0;
  NRF905_Config_t.CH_NO_2 = 0;
  NRF905_Config_t.CRC_EN = 0;
  NRF905_Config_t.CRC_MODE = 0;
  NRF905_Config_t.HFREQ_PLL = 0;
  NRF905_Config_t.PA_PWR = 0;
  NRF905_Config_t.RX_ADDRESS = 0;
  NRF905_Config_t.RX_AFW = 0;
  NRF905_Config_t.RX_PW =  0;
  NRF905_Config_t.XOF = 0;

  NRF905_Config_t.AUTO_RETRAN = AUTO_RET_DISABLE ;
  NRF905_Config_t.CH_NO_1 = 50;
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
  NRF905_Config_t.UP_CLK_EN = OUT_CLOCK_DISABLE;
  NRF905_Config_t.UP_CLK_FREQ =  OUT_CLOCK_FREQ_4MHz;
  NRF905_Config_t.XOF = CRYSTAL_OSC_FREQ_8MHz;
  if (NRF905_Init(&NRF905_Config_t ) == 0)
    {
      while (1) {}
    }
  HAL_RTCEx_DeactivateWakeUpTimer(&hrtc);
  HAL_ADCEx_Calibration_Start(&hadc, 0);
  HAL_ADC_Start(&hadc);
  HAL_ADC_Start_DMA(&hadc, (uint32_t*)&adc, 2);
  while (flg_adc_end == 1) {}
  flg_adc_end = 0;
  HAL_ADC_Stop_DMA(&hadc);
  if (initBME280(&dev_bme) == 1)
    { 
      GetCalibData_BME280(&dev_bme);
	    GetData_BME280(&dev_bme); 
    }
  P.humm = dev_bme.data.humidity;
  P.press = dev_bme.data.pressure;
  P.temp = dev_bme.data.temperature;
  P.count = j;
  t = (vref_cal * 3000) / adc[0];
  P.vbat = (adc[1] * t )/4096;
  j++;
  HAL_Delay(1);
  k = sizeof(P);
  WriteDataToSend(0xE7E7E7E6, &P, k);
  NRF905_StartSend();
  NRF905_ILDE_Mode();
  if (P.vbat <2000) {HAL_GPIO_WritePin(StepUP_EN_Port, StepUP_EN_Pin, GPIO_PIN_SET);} else {HAL_GPIO_WritePin(StepUP_EN_Port, StepUP_EN_Pin, GPIO_PIN_RESET);}
  GPIO_Stop();
  HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, 300, RTC_WAKEUPCLOCK_CK_SPRE_16BITS);
  HAL_PWR_EnterSTANDBYMode();
  }

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_5;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void SPI_GET_DAT( uint8_t *ADDR, uint8_t *data)
{
	HAL_GPIO_WritePin(CS_BME_Port, CS_BME_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, ADDR, 1, 10);
	HAL_SPI_Receive(&hspi1, data, 1, 10);
	HAL_GPIO_WritePin(CS_BME_Port, CS_BME_Pin, GPIO_PIN_SET);
}

void SPI_SET_DAT( uint8_t *ADDR, uint8_t *data)
{
	uint8_t addr;
	addr = *(uint8_t *)ADDR;
	addr = addr & 0x7f;

	HAL_GPIO_WritePin(CS_BME_Port, CS_BME_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, &addr, 1, 10);
	HAL_SPI_Transmit(&hspi1, data, 1, 10);
	HAL_GPIO_WritePin(CS_BME_Port, CS_BME_Pin, GPIO_PIN_SET);
}

uint16_t flash_read(uint32_t address)
{
    return (*(__IO uint16_t*) address);
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
