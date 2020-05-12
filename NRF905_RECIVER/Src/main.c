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
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "nrf905.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/*volatile const struct NRF905_Conf __attribute__((section (".myBufSection"))) NRF905_Config = {
        AUTO_RET_DISABLE,138,0,CRC_CHECK_ENABLE,CRC_MODE_16bit,FREQ_433MHz, PWR_10mdBm, 
        0xE7E7E7E7, RX_ADDR_WIDTH_4Byte,28,RED_PWR_DISABLE, TX_ADDR_WIDTH_4Byte, 28,
        OUT_CLOCK_ENABLE, OUT_CLOCK_FREQ_500kHz, CRYSTAL_OSC_FREQ_16MHz};
*/
volatile const uint8_t __attribute__((section (".myBufSection"))) Conf[10] = {0};       
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
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
  /* USER CODE BEGIN 1 */
uint8_t tmp;
uint8_t buff[255] = {0};
Packet_send P;
struct NRF905_Conf  NRF905_Config_t;
volatile uint8_t y;
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
  MX_SPI3_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
HAL_GPIO_WritePin(CS_NRF_GPIO_Port, CS_NRF_Pin, GPIO_PIN_SET);
NRF905_POWER_ON();
HAL_Delay(500);
y = sizeof(P);
/*HAL_FLASH_Unlock();
NRF905_Config_t.AUTO_RETRAN = AUTO_RET_DISABLE ;
NRF905_Config_t.CH_NO_1 = 138;
NRF905_Config_t.CH_NO_2 = 0;
NRF905_Config_t.CRC_EN = CRC_CHECK_ENABLE;
NRF905_Config_t.CRC_MODE = CRC_MODE_16bit;
NRF905_Config_t.HFREQ_PLL = FREQ_433MHz ;
NRF905_Config_t.PA_PWR = PWR_10mdBm;
NRF905_Config_t.RX_ADDRESS = 0xE7E7E7E7 ; 
NRF905_Config_t.RX_AFW = RX_ADDR_WIDTH_4Byte ;
NRF905_Config_t.RX_PW =  sizeof(P);
NRF905_Config_t.RX_RED_PWR = RED_PWR_DISABLE;
NRF905_Config_t.TX_AFW = TX_ADDR_WIDTH_4Byte;
NRF905_Config_t.TX_PW = sizeof(P);
NRF905_Config_t.UP_CLK_EN = OUT_CLOCK_ENABLE;
NRF905_Config_t.UP_CLK_FREQ =  OUT_CLOCK_FREQ_500kHz;
NRF905_Config_t.XOF = CRYSTAL_OSC_FREQ_16MHz;
HAL_FLASH_Lock(); 
NRF905_Config_t.AUTO_RETRAN = NRF905_Config.AUTO_RETRAN;
NRF905_Config_t.CH_NO_1 = NRF905_Config.CH_NO_1;
NRF905_Config_t.CH_NO_2 = NRF905_Config.CH_NO_2;
NRF905_Config_t.CRC_EN = NRF905_Config.CRC_EN ;
NRF905_Config_t.CRC_MODE = NRF905_Config.CRC_MODE;
NRF905_Config_t.HFREQ_PLL = NRF905_Config.HFREQ_PLL ;
NRF905_Config_t.PA_PWR = NRF905_Config.PA_PWR;
NRF905_Config_t.RX_ADDRESS = NRF905_Config.RX_ADDRESS ; 
NRF905_Config_t.RX_AFW = NRF905_Config.RX_AFW ;
NRF905_Config_t.RX_PW =  NRF905_Config.RX_PW;
NRF905_Config_t.RX_RED_PWR = NRF905_Config.RX_RED_PWR;
NRF905_Config_t.TX_AFW = NRF905_Config.TX_AFW;
NRF905_Config_t.TX_PW = NRF905_Config.TX_PW;
NRF905_Config_t.UP_CLK_EN = NRF905_Config.UP_CLK_EN;
NRF905_Config_t.UP_CLK_FREQ =  NRF905_Config.UP_CLK_FREQ;
NRF905_Config_t.XOF = NRF905_Config.XOF;
*/
memcpy(&NRF905_Config_t, 0x08060000, 10);
if (NRF905_INIT(&NRF905_Config_t ))
{
 // ReciveMode();
 HAL_GPIO_WritePin(TXE_GPIO_Port, TXE_Pin, GPIO_PIN_RESET);
 HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_SET);
 HAL_Delay(5);
}
  /* USER CODE END 2 */
 
 

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    y = HAL_GPIO_ReadPin(CD_GPIO_Port, CD_Pin);
    y = HAL_GPIO_ReadPin(AM_GPIO_Port, AM_Pin);
    y = HAL_GPIO_ReadPin(DR_GPIO_Port, DR_Pin);
    if (HAL_GPIO_ReadPin(DR_GPIO_Port, DR_Pin) == 1)
     {
      ReadReciveData(&P, sizeof(P));
      tmp = sprintf(buff, "HUMM - %d %%RH\n\rPRESS - %d hPa\n\rTEMP - %d C\n\rCOUNT - %d \n\n\r", P.humm/1024, P.press/100, P.temp/100, P.count );
		  HAL_UART_Transmit(&huart2, &buff, tmp+1, 10);
     }
    /* USER CODE END WHILE */

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
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

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
