#ifndef __nrf905_H
#define __nrf905_H
 
#define  data_size 0x0A;

#define Bit(bit)  (1<<(bit))
#define ClearBit(reg, bit)       reg &= (~(1<<(bit)))
#define SetBit(reg, bit)          reg |= (1<<(bit))
#define BitIsClear(reg, bit)    ((reg & (1<<(bit))) == 0)
#define BitIsSet(reg, bit)       ((reg & (1<<(bit))) != 0)
#define InvBit(reg, bit)          reg ^= (1<<(bit))
//------------------------------------------------------------------------------------


#define NRF905_CS_HI	HAL_GPIO_WritePin(CS_NRF_GPIO_Port, CS_NRF_Pin, GPIO_PIN_SET)
#define NRF905_CS_LO	HAL_GPIO_WritePin(CS_NRF_GPIO_Port, CS_NRF_Pin, GPIO_PIN_RESET)
#define NRF905_CE_HI	HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_SET)
#define NRF905_CE_LO	HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_RESET)

#define W_CONFIG     0x00
#define R_CONFIG     0x10
#define W_TX_PAYLOAD 0x20
#define R_TX_PAYLOAD 0x21
#define W_TX_ADDRESS 0x22
#define R_TX_ADDRESS 0x23 
#define R_RX_PAYLOAD 0x24
//#define CHANNEL_CONFIG
//#define R_STATUS_REGISTER
#define NOP          0xFF


#define FREQ_433MHz                0
#define FREQ_868MHz                1
#define PWR_10mdBm                 0
#define PWR_2mdBm                  1
#define PWR_6dBm                   2
#define PWR_10dBm                  3
#define RED_PWR_ENABLE             1
#define RED_PWR_DISABLE            0
#define AUTO_RET_ENABLE            1
#define AUTO_RET_DISABLE           0
#define RX_ADDR_WIDTH_1Byte        1
#define RX_ADDR_WIDTH_2Byte        2
#define RX_ADDR_WIDTH_3Byte        3
#define RX_ADDR_WIDTH_4Byte        4
#define TX_ADDR_WIDTH_1Byte        1
#define TX_ADDR_WIDTH_2Byte        2
#define TX_ADDR_WIDTH_3Byte        3
#define TX_ADDR_WIDTH_4Byte        4
#define OUT_CLOCK_FREQ_4MHz        0
#define OUT_CLOCK_FREQ_2MHz        1
#define OUT_CLOCK_FREQ_1MHz        2
#define OUT_CLOCK_FREQ_500kHz      3
#define OUT_CLOCK_ENABLE           1
#define OUT_CLOCK_DISABLE          1
#define CRYSTAL_OSC_FREQ_4MHz      0
#define CRYSTAL_OSC_FREQ_8MHz      1
#define CRYSTAL_OSC_FREQ_12MHz     2
#define CRYSTAL_OSC_FREQ_16MHz     3
#define CRYSTAL_OSC_FREQ_20MHz     4
#define CRC_CHECK_ENABLE           1
#define CRC_CHECK_DISABLE          0
#define CRC_MODE_8bit              0
#define CRC_MODE_16bit             1

 #pragma pack(push, 1)
struct NRF905_Conf
 {
    unsigned int   CH_NO_1:8; // 0-511 byte 0
    unsigned char  CH_NO_2:1; // byte 1 bit 0
    unsigned char  HFREQ_PLL:1; // byte 1 bit 1
    unsigned char  PA_PWR:2; // byte 1 bit 2-3
    unsigned char  RX_RED_PWR:1; // byte 1 bit 4
    unsigned char  AUTO_RETRAN:1; // byte 1 bit 5
    unsigned char  NC_1:2; // byte 1 bit 6-7
    unsigned char  RX_AFW:3;// byte 2 bit 0-2
    unsigned char  NC_2:1; // byte 2 bit 3
    unsigned char  TX_AFW:3; // byte 2 bit 4-6
    unsigned char  NC_3:1; // byte 2 bit 7
    unsigned char  RX_PW:6;  // byte 3 bit 0-5  RX-payload width 1-32 byte
    unsigned char  NC_4:2; // byte 3 bit 6-7
    unsigned char  TX_PW:6; // byte 4 bit 0-5  TX-payload width 1-32 byte
    unsigned char  NC_5:2; // byte 4 bit 6-7
    unsigned long  RX_ADDRESS:32; // byte 5-8 RX address identity
    unsigned char  UP_CLK_FREQ:2; // byte 9 bit 0-1
    unsigned char  UP_CLK_EN:1; // byte 9 bit 2
    unsigned char  XOF:3; // byte 9 bit 3-5
    unsigned char  CRC_EN:1; // byte 9 bit 6 
    unsigned char  CRC_MODE :1; // byte 9 bit 7
 } ;

#pragma pack(pop) 
 
uint8_t NRF905_ReadReg(uint8_t reg);
uint8_t NRF905_WriteReg(uint8_t reg, uint8_t data );
void NRF905_ReadBuf(uint8_t reg,uint8_t *pBuf,uint8_t bytes); 
void NRF905_WriteBuf(uint8_t reg,uint8_t *pBuf,uint8_t bytes);
uint8_t NRF905_INIT(struct NRF905_Conf *Conf);
void NRF905_POWER_ON (void);
void NRF905_POWER_OFF (void);
void WriteDataToSend(uint32_t addr, uint8_t *pBuf, uint8_t size);
void ReadReciveData(uint8_t *pBuf, uint8_t size);
void StartSend( void );
void TransmitMode ( void );
void ReciveMode ( void );
#endif 