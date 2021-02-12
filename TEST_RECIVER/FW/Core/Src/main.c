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
#include "rtc.h"
#include "spi.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "nrf905.h"
#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
Packet_send P;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint16_t i =0 ;
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
  uint8_t buf[15];
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
  MX_RTC_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  HAL_GPIO_WritePin(LCD_LED_GPIO_Port, LCD_LED_Pin, GPIO_PIN_SET);
  ILI9341_Init();
  ILI9341_Fill_Screen(BLACK);
  ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
  //ILI9341_Draw_Text("Start",0,0,BLACK,4,WHITE);
  //HAL_Delay(10000);
  
  NRF905_POWER_ON();
HAL_Delay(2);
NRF905_Config_t.AUTO_RETRAN = AUTO_RET_DISABLE ;
NRF905_Config_t.CH_NO_1 = 50;
NRF905_Config_t.CH_NO_2 = 0;
NRF905_Config_t.CRC_EN = CRC_CHECK_ENABLE;
NRF905_Config_t.CRC_MODE = CRC_MODE_16bit;
NRF905_Config_t.HFREQ_PLL = FREQ_433MHz ;
NRF905_Config_t.PA_PWR = PWR_10dBm;
NRF905_Config_t.RX_ADDRESS = 0xE7E7E7E6;
NRF905_Config_t.RX_AFW = TX_ADDR_WIDTH_4Byte ;
NRF905_Config_t.RX_PW =  sizeof(P);
NRF905_Config_t.RX_RED_PWR = RED_PWR_DISABLE;
NRF905_Config_t.TX_AFW = TX_ADDR_WIDTH_4Byte;
NRF905_Config_t.TX_PW = sizeof(P);
NRF905_Config_t.UP_CLK_EN = OUT_CLOCK_DISABLE;
NRF905_Config_t.UP_CLK_FREQ =  OUT_CLOCK_FREQ_500kHz;
NRF905_Config_t.XOF = CRYSTAL_OSC_FREQ_16MHz;

if (NRF905_INIT(&NRF905_Config_t ))
  {
    HAL_GPIO_WritePin(NRF905_PWR_GPIO_Port, NRF905_PWR_Pin, GPIO_PIN_SET);
    HAL_Delay(2);
    HAL_GPIO_WritePin(NRF905_TXEN_GPIO_Port, NRF905_TXEN_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(NRF905_CE_GPIO_Port, NRF905_CE_Pin, GPIO_PIN_SET);
  } else {
          ILI9341_Draw_Text("Module NRF905 not found!!!! ",0,0,BLACK,29,WHITE);
          HAL_Delay(5000);
          while (1)
          {
           HAL_Delay(500);
           ILI9341_Fill_Screen(RED);
           HAL_Delay(500);
           ILI9341_Fill_Screen(WHITE); 
          }
         }

  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  
  while (1)
    {
      if (HAL_GPIO_ReadPin(NRF_DR_GPIO_Port, NRF_DR_Pin) == 1) 
        {
          ReadReciveData(&P, sizeof(P));
          sprintf(buf, "Temoerature = %3d.%2d C",P.temp/100, ((P.temp%100)*-1)  );
          ILI9341_Draw_Text(buf,0,20,WHITE,2,BLACK);
          sprintf(buf, "Pressue = %4d hPa ",P.press/100);
          ILI9341_Draw_Text(buf,0,40,WHITE,2,BLACK);
          sprintf(buf, "humidity = %3d %%RH ",P.humm/1024);
          ILI9341_Draw_Text(buf,0,60,WHITE,2,BLACK);
          sprintf(buf, "Vbat = %1d.%3d",P.vbat/1000,P.vbat%1000  );
          ILI9341_Draw_Text(buf,0,220,WHITE,2,BLACK);

        }
     

    /* USER CODE END WHILE */
    }    
    /* USER CODE BEGIN 3 */
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_HSE_DIV32;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
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
