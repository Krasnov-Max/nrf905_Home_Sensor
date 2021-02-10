
#include "main.h"
#include "nrf905.h"
#include "spi.h"
//extern SPI_HandleTypeDef hspi1;

uint8_t NRF905_ReadReg(uint8_t reg)
{
 uint8_t dt=0, cmd=0;
 reg |= R_CONFIG;
 NRF905_CS_LO;
 HAL_SPI_TransmitReceive(SPI_INSTANCE_NRF,&reg,&dt,1,1000);
 HAL_SPI_Receive(SPI_INSTANCE_NRF,&dt,1,1000);
  NRF905_CS_HI;	
 return dt;
}

uint8_t NRF905_WriteReg(uint8_t reg, uint8_t data )
{
 reg |= W_CONFIG;
 NRF905_CS_LO;
 HAL_SPI_Transmit(SPI_INSTANCE_NRF,&reg,1,1000);
 HAL_SPI_Transmit(SPI_INSTANCE_NRF,&data,1,1000);
 NRF905_CS_HI;
 return 0;
}
void NRF905_ReadBuf(uint8_t reg,uint8_t *pBuf,uint8_t bytes)
{
  uint8_t i=0, tmp;
 reg |= R_CONFIG;
 
 NRF905_CS_LO;
 HAL_SPI_TransmitReceive(SPI_INSTANCE_NRF,&reg,&tmp,1,1000);
 tmp = NOP;
for (i=0; i<bytes; i++)
  {
   HAL_SPI_TransmitReceive(SPI_INSTANCE_NRF,&tmp,pBuf,1,1000);
    pBuf++;
  }
 NRF905_CS_HI;
}


void NRF905_WriteBuf(uint8_t reg,uint8_t *pBuf,uint8_t bytes)
{
 uint8_t i,y; 
 reg |=W_CONFIG;
 NRF905_CS_LO;
 HAL_SPI_TransmitReceive(SPI_INSTANCE_NRF,&reg, &y,1,1000);
 for (i=0;i<bytes;i++) 
   {
     HAL_SPI_TransmitReceive(SPI_INSTANCE_NRF,pBuf,&y,1,1000);
     pBuf++;
   }
 NRF905_CS_HI;
}
void NRF905_POWER_ON (void)
{
 HAL_GPIO_WritePin(NRF905_PWR_GPIO_Port, NRF905_PWR_Pin, GPIO_PIN_SET);
 HAL_Delay(1);
 ReciveOn ();
 HAL_Delay(2);
}
void NRF905_POWER_OFF (void)
{
 HAL_GPIO_WritePin(NRF905_PWR_GPIO_Port, NRF905_PWR_Pin, GPIO_PIN_RESET);
}
uint8_t NRF905_INIT(struct NRF905_Conf *Conf)
{
 struct NRF905_Conf tmp;   

 NRF905_ReadBuf(0,&tmp,sizeof(tmp));
 tmp.RX_ADDRESS=0xE7E7E7E7;
 NRF905_WriteBuf(0,&tmp,sizeof(tmp));
 tmp.RX_ADDRESS = 0;
 NRF905_ReadBuf(0,&tmp,sizeof(tmp));
 if ((tmp.RX_ADDRESS != 0xE7E7E7E7)) 
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
  HAL_SPI_TransmitReceive(SPI_INSTANCE_NRF,&tmp, &y, 1, 1000);
  tmp = addr;
  HAL_SPI_TransmitReceive(SPI_INSTANCE_NRF,&tmp, &y, 1, 1000); 
  NRF905_CS_HI;
  NRF905_CS_LO;
  tmp = W_TX_PAYLOAD;
  HAL_SPI_TransmitReceive(SPI_INSTANCE_NRF,&tmp, &y, 1, 1000);
  for (i=0;i<size;i++) 
   {
     HAL_SPI_TransmitReceive(SPI_INSTANCE_NRF,pBuf,&y,1,1000);
     pBuf++;
   }
 NRF905_CS_HI;
}
void ReadReciveData(uint8_t *pBuf, uint8_t size)
{
   uint8_t i=0, tmp, tmp1;
   tmp1 = R_RX_PAYLOAD;
  
 NRF905_CS_LO;
 HAL_SPI_TransmitReceive(SPI_INSTANCE_NRF,&tmp1,&tmp,1,1000);
 tmp = NOP;
for (i=0; i<size; i++)
  {
   HAL_SPI_TransmitReceive(SPI_INSTANCE_NRF,&tmp,pBuf,1,1000);
    pBuf++;
  }
 NRF905_CS_HI;
}
void StartSend( void )
{
   HAL_GPIO_WritePin(NRF905_CE_GPIO_Port, NRF905_CE_Pin, GPIO_PIN_SET);
   while (HAL_GPIO_ReadPin(NRF905_DR_GPIO_Port, NRF905_DR_Pin) != 1)
   {}
   HAL_GPIO_WritePin(NRF905_CE_GPIO_Port, NRF905_CE_Pin, GPIO_PIN_RESET);
}
void ReciveOn ( void )
{
  HAL_GPIO_WritePin(NRF905_TXEN_GPIO_Port, NRF905_TXEN_Pin, GPIO_PIN_SET);
}
void ReciveOff ( void )
{
  HAL_GPIO_WritePin(NRF905_TXEN_GPIO_Port, NRF905_TXEN_Pin, GPIO_PIN_RESET);
}