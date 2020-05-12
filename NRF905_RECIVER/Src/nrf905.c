
#include "main.h"
#include "nrf905.h"
#include "spi.h"
//extern SPI_HandleTypeDef hspi1;

uint8_t NRF905_ReadReg(uint8_t reg)
{
 uint8_t dt=0, cmd=0;
 reg |= R_CONFIG;
 NRF905_CS_LO;
 HAL_SPI_TransmitReceive(&hspi3,&reg,&dt,1,1000);
 HAL_SPI_Receive(&hspi3,&dt,1,1000);
  NRF905_CS_HI;	
 return dt;
}

uint8_t NRF905_WriteReg(uint8_t reg, uint8_t data )
{
 reg |= W_CONFIG;
 NRF905_CS_LO;
 HAL_SPI_Transmit(&hspi3,&reg,1,1000);
 HAL_SPI_Transmit(&hspi3,&data,1,1000);
 NRF905_CS_HI;
 return 0;
}
void NRF905_ReadBuf(uint8_t reg,uint8_t *pBuf,uint8_t bytes)
{
  uint8_t i=0, tmp;
 reg |= R_CONFIG;
 
 NRF905_CS_LO;
 HAL_SPI_TransmitReceive(&hspi3,&reg,&tmp,1,1000);
 tmp = NOP;
for (i=0; i<bytes; i++)
  {
   HAL_SPI_TransmitReceive(&hspi3,&tmp,pBuf,1,1000);
    pBuf++;
  }
 NRF905_CS_HI;
}


void NRF905_WriteBuf(uint8_t reg,uint8_t *pBuf,uint8_t bytes)
{
 uint8_t i,y; 
 reg |=W_CONFIG;
 NRF905_CS_LO;
 HAL_SPI_TransmitReceive(&hspi3,&reg, &y,1,1000);
 for (i=0;i<bytes;i++) 
   {
     HAL_SPI_TransmitReceive(&hspi3,pBuf,&y,1,1000);
     pBuf++;
   }
 NRF905_CS_HI;
}
void NRF905_POWER_ON (void)
{
 HAL_GPIO_WritePin(PWR_GPIO_Port, PWR_Pin, GPIO_PIN_SET);
 HAL_GPIO_WritePin(TXE_GPIO_Port, TXE_Pin, GPIO_PIN_RESET);
 HAL_Delay(1);
}
void NRF905_POWER_OFF (void)
{
 HAL_GPIO_WritePin(PWR_GPIO_Port, PWR_Pin, GPIO_PIN_RESET);
}
uint8_t NRF905_INIT(struct NRF905_Conf *Conf)
{
 struct NRF905_Conf tmp;   

 NRF905_ReadBuf(0,&tmp,sizeof(tmp));
 HAL_Delay(5000);
 tmp.RX_ADDRESS=0xE7E7E7E7;
 NRF905_WriteBuf(0,&tmp,sizeof(tmp));
 HAL_Delay(5000);
 tmp.RX_ADDRESS = 0;
 NRF905_ReadBuf(0,&tmp,sizeof(tmp));
 if ((tmp.RX_ADDRESS != 0xE7E7E7E7)) 
   {
     return 0;
   } else
      {
     /* code */
       HAL_Delay(5000);
       NRF905_WriteBuf(0,Conf,10);
       return 1;
      }
  
}
void WriteDataToSend(uint32_t addr, uint8_t *pBuf, uint8_t size)
{
  uint8_t i,y, tmp;
  tmp = W_TX_ADDRESS; 
  NRF905_CS_LO;
  HAL_SPI_TransmitReceive(&hspi3,&tmp, &y, 1, 1000);
  tmp = addr;
  HAL_SPI_TransmitReceive(&hspi3,&tmp, &y, 1, 1000); 
  NRF905_CS_HI;
  NRF905_CS_LO;
  tmp = W_TX_PAYLOAD;
  HAL_SPI_TransmitReceive(&hspi3,&tmp, &y, 1, 1000);
  for (i=0;i<size;i++) 
   {
     HAL_SPI_TransmitReceive(&hspi3,pBuf,&y,1,1000);
     pBuf++;
   }
 NRF905_CS_HI;
}
void ReadReciveData(uint8_t *pBuf, uint8_t size)
{
   uint8_t i=0, tmp;
  
 NRF905_CS_LO;
 i = R_RX_PAYLOAD;
 HAL_SPI_TransmitReceive(&hspi3,&i,&tmp,1,1000);
 tmp = NOP;
for (i=0; i<size; i++)
  {
   HAL_SPI_TransmitReceive(&hspi3,&tmp,pBuf,1,1000);
    pBuf++;
  }
 NRF905_CS_HI;
}
void StartSend( void )
{
   TransmitMode();
   HAL_Delay(1);
   HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_SET);
   while (HAL_GPIO_ReadPin(DR_GPIO_Port, DR_Pin) != 1)
   {}
   HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_RESET);
}
void TransmitMode ( void )
{
  HAL_GPIO_WritePin(TXE_GPIO_Port, TXE_Pin, GPIO_PIN_SET);
}
void ReciveMode ( void )
{
  HAL_GPIO_WritePin(TXE_GPIO_Port, TXE_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_SET);
}