
#include "main.h"
#include "nrf905.h"
#include "spi.h"
//extern SPI_HandleTypeDef hspi1;

uint8_t NRF905_ReadReg(uint8_t reg)
{
 uint8_t dt=0, cmd=0;
 reg |= R_CONFIG;
 NRF905_CS_LO;
 HAL_SPI_TransmitReceive(&hspi1,&reg,&dt,1,1000);
 HAL_SPI_Receive(&hspi1,&dt,1,1000);
  NRF905_CS_HI;	
 return dt;
}

uint8_t NRF905_WriteReg(uint8_t reg, uint8_t data )
{
 reg |= W_CONFIG;
 NRF905_CS_LO;
 HAL_SPI_Transmit(&hspi1,&reg,1,1000);
 HAL_SPI_Transmit(&hspi1,&data,1,1000);
 NRF905_CS_HI;
 return 0;
}
void NRF905_ReadBuf(uint8_t reg,uint8_t *pBuf,uint8_t bytes)
{
  uint8_t i=0, tmp;
 reg |= R_CONFIG;
 
 NRF905_CS_LO;
 HAL_SPI_TransmitReceive(&hspi1,&reg,&tmp,1,1000);
 tmp = NOP;
for (i=0; i<bytes; i++)
  {
   HAL_SPI_TransmitReceive(&hspi1,&tmp,pBuf,1,1000);
    pBuf++;
  }
 NRF905_CS_HI;
}


void NRF905_WriteBuf(uint8_t reg,uint8_t *pBuf,uint8_t bytes)
{
 uint8_t i,y; 
 reg |=W_CONFIG;
 NRF905_CS_LO;
 HAL_SPI_TransmitReceive(&hspi1,&reg, &y,1,1000);
 for (i=0;i<bytes;i++) 
   {
     HAL_SPI_TransmitReceive(&hspi1,pBuf,&y,1,1000);
     pBuf++;
   }
 NRF905_CS_HI;
}

uint8_t NRF905_Init(struct NRF905_Conf *Conf)
{
 struct NRF905_Conf tmp;   

 NRF905_ReadBuf(0,&tmp,sizeof(tmp));
 tmp.RX_ADDRESS=0xE4E5E6E7;
 NRF905_WriteBuf(0,&tmp,sizeof(tmp));
 tmp.RX_ADDRESS = 0;
 NRF905_ReadBuf(0,&tmp,sizeof(tmp));
 if ((tmp.RX_ADDRESS != 0xE4E5E6E7)) 
   {
     return 0;
   } else
      {
     /* code */
       NRF905_WriteBuf(0,Conf,10);
       return 1;
      }
  
}
void WriteDataToSend(uint32_t addr, uint8_t *pBuf, uint8_t size)
{
  uint8_t i,y, tmp;
  tmp = W_TX_ADDRESS; 
  NRF905_CS_LO;
  HAL_SPI_Transmit(&hspi1,&tmp, 1, 1000);
  tmp = addr;
  HAL_SPI_Transmit(&hspi1,&tmp, 1, 1000); 
  NRF905_CS_HI;
  NRF905_CS_LO;
  tmp = W_TX_PAYLOAD;
  HAL_SPI_Transmit(&hspi1,&tmp, 1, 1000);
  //for (i=0;i<size;i++) 
  // {
  //   HAL_SPI_TransmitReceive(&hspi1,pBuf,&y,1,1000);
  //   pBuf++;
  // }
  HAL_SPI_Transmit(&hspi1,pBuf,size,1000);
 NRF905_CS_HI;
}
void ReadReciveData(uint8_t *pBuf, uint8_t size)
{
   uint8_t i=0, tmp, tmp1;
   tmp1 = R_RX_PAYLOAD;
  
 NRF905_CS_LO;
 HAL_SPI_TransmitReceive(&hspi1,&tmp1,&tmp,1,1000);
 tmp = NOP;
for (i=0; i<size; i++)
  {
   HAL_SPI_TransmitReceive(&hspi1,&tmp,pBuf,1,1000);
    pBuf++;
  }
 NRF905_CS_HI;
}

void NRF905_PowerOff (void)
{
  HAL_GPIO_WritePin(PWR_Port, PWR_Pin, GPIO_PIN_RESET);
}
void NRF905_ILDE_Mode(void)
{
  HAL_GPIO_WritePin(PWR_Port, PWR_Pin, GPIO_PIN_SET);
  HAL_Delay(1);
  HAL_GPIO_WritePin(TRX_CE_Port, TRX_CE_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(TX_EN_Port, TX_EN_Pin, GPIO_PIN_RESET);
  
}
void NRF905_StartSend(void)
{
  HAL_GPIO_WritePin(TRX_CE_Port, TRX_CE_Pin, GPIO_PIN_SET);
  while (HAL_GPIO_ReadPin(DR_Port, DR_Pin) != 1)   {}
  HAL_GPIO_WritePin(TRX_CE_Port, TRX_CE_Pin, GPIO_PIN_RESET);
}
void NRF905_Reciver_Mode (void)
{
  HAL_GPIO_WritePin(PWR_Port, PWR_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(TX_EN_Port, TX_EN_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(TRX_CE_Port, TRX_CE_Pin, GPIO_PIN_SET);
}

void NRF905_Transmitter_Mode(void)
{
  HAL_GPIO_WritePin(PWR_Port, PWR_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(TX_EN_Port, TX_EN_Pin, GPIO_PIN_SET);
}


