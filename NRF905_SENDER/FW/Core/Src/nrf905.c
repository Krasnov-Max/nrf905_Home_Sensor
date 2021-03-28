
#include "main.h"
#include "nrf905.h"
#include "spi.h"
//extern SPI_HandleTypeDef hspi1;

uint8_t NRF905_ReadReg(uint8_t reg)
{
 uint8_t dt=0, cmd=0;
 reg |= R_CONFIG;
 NRF905_CS_LO;
 LL_SPI_TransmitData8(SPI1, reg);
 dt = LL_SPI_ReceiveData8(SPI1);
 dt = LL_SPI_ReceiveData8(SPI1);
 NRF905_CS_HI;	
 return dt;
}

uint8_t NRF905_WriteReg(uint8_t reg, uint8_t data )
{
 reg |= W_CONFIG;
 NRF905_CS_LO;
 LL_SPI_TransmitData8(SPI1, reg);
 LL_SPI_TransmitData8(SPI1, data);
 NRF905_CS_HI;
 return 0;
}
void NRF905_ReadBuf(uint8_t reg,uint8_t *pBuf,uint8_t bytes)
{
  uint8_t i=0, tmp;
 reg |= R_CONFIG;
 
 NRF905_CS_LO;
 LL_SPI_TransmitData8(SPI1, reg);
 tmp = NOP;
for (i=0; i<bytes; i++)
  {
    LL_SPI_TransmitData8(SPI1, tmp);
    pBuf = LL_SPI_ReceiveData8(SPI1);
    pBuf++;
  }
 NRF905_CS_HI;
}


void NRF905_WriteBuf(uint8_t reg,uint8_t *pBuf,uint8_t bytes)
{
 uint8_t i,y; 
 reg |=W_CONFIG;
 NRF905_CS_LO;
 LL_SPI_TransmitData8(SPI1, reg);
 for (i=0;i<bytes;i++) 
   {
     LL_SPI_TransmitData8(SPI1, pBuf);
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
  LL_SPI_TransmitData8(SPI1, tmp);
  tmp = addr;
  LL_SPI_TransmitData8(SPI1, tmp);
  NRF905_CS_HI;
  NRF905_CS_LO;
  tmp = W_TX_PAYLOAD;
  LL_SPI_TransmitData8(SPI1, tmp);
  for (i=0; i<size; i++) 
    {
      LL_SPI_TransmitData8(SPI1, pBuf);
      pBuf++;    
    }
  NRF905_CS_HI;
}
void ReadReciveData(uint8_t *pBuf, uint8_t size)
{
   uint8_t i=0, tmp, tmp1;
   tmp1 = R_RX_PAYLOAD;
  
 NRF905_CS_LO;
 LL_SPI_TransmitData8(SPI1, tmp);
 tmp = NOP;
for (i=0; i<size; i++)
  {
   LL_SPI_TransmitData8(SPI1, tmp);
   pBuf = LL_SPI_ReceiveData8(SPI1);
   pBuf++;
  }
 NRF905_CS_HI;
}

void NRF905_PowerOff (void)
{
  LL_GPIO_ResetOutputPin(NRF_POWER_GPIO_Port, NRF_POWER_Pin);
}
void NRF905_ILDE_Mode(void)
{
  LL_GPIO_SetOutputPin(NRF_POWER_GPIO_Port, NRF_POWER_Pin);
  HAL_Delay(1);
  LL_GPIO_ResetOutputPin(TRX_CE_GPIO_Port, TRX_CE_Pin);
  LL_GPIO_ResetOutputPin(TX_EN_GPIO_Port, TX_EN_Pin);
}
void NRF905_StartSend(void)
{
  LL_GPIO_SetOutputPin(TRX_CE_GPIO_Port, TRX_CE_Pin);
  while (LL_GPIO_IsInputPinSet(DR_GPIO_Port, DR_Pin) !=1) {}
  LL_GPIO_ResetOutputPin(TRX_CE_GPIO_Port, TRX_CE_Pin);
}
void NRF905_Reciver_Mode (void)
{
  LL_GPIO_SetOutputPin(NRF_POWER_GPIO_Port, NRF_POWER_Pin);
  LL_GPIO_ResetOutputPin(TX_EN_GPIO_Port, TX_EN_Pin);
  LL_GPIO_SetOutputPin(TRX_CE_GPIO_Port, TRX_CE_Pin);
}

void NRF905_Transmitter_Mode(void)
{
  LL_GPIO_SetOutputPin(NRF_POWER_GPIO_Port, NRF_POWER_Pin);
  LL_GPIO_SetOutputPin(TX_EN_GPIO_Port, TX_EN_Pin);
}


