#ifndef BME280_H_
#define BME280_H_

/*! CPP guard */
#ifdef __cplusplus
extern "C" {
#endif

/* Header includes */
#include <main.h>
#include "bme280_defs.h"

void SPI_GET_DAT( uint8_t *ADDR, uint8_t *data); // Release user look main.c
void SPI_SET_DAT( uint8_t *ADDR, uint8_t *data); // Release user look main.c
	
/*
// BEGIN	EXAMLE RELEASE
	
	void SPI_GET_DAT( uint8_t *ADDR, uint8_t *data)
{
	HAL_GPIO_WritePin(CS_BME_GPIO_Port, CS_BME_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, ADDR, 1, 10);
	HAL_SPI_Receive(&hspi2, data, 1, 10);
	HAL_GPIO_WritePin(CS_BME_GPIO_Port, CS_BME_Pin, GPIO_PIN_SET);
}

void SPI_SET_DAT( uint8_t *addr, uint8_t *data)
{
	HAL_GPIO_WritePin(CS_BME_GPIO_Port, CS_BME_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, ADDR, 1, 10);
	HAL_SPI_Transmit(&hspi2, data, 1, 10);
	HAL_GPIO_WritePin(CS_BME_GPIO_Port, CS_BME_Pin, GPIO_PIN_SET);
}
	
// END EXAMPLE RELEASE 
 */	
	
uint8_t initBME280(struct bme280_dev *dev);
void GetCalibData_BME280(struct bme280_dev *dev);
void GetData_BME280(struct bme280_dev *dev); 
void FORCEMode (struct bme280_dev *dev);	

                              


//int8_t bme280_get_sensor_data(struct bme280_dev *dev);
//static int8_t get_calib_data(struct bme280_dev *dev);


#ifdef __cplusplus
}
#endif /* End of CPP guard */
#endif /* BME280_H_ */

