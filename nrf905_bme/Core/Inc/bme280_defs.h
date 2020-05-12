#ifndef BME280_DEFS_H_
#define BME280_DEFS_H_
#include "main.h"

#define BME280_CHIP_ID_ADDR               UINT8_C(0xD0)
#define BME280_RESET_ADDR                 UINT8_C(0xE0)
#define BME280_TEMP_PRESS_CALIB_DATA_ADDR UINT8_C(0x88)
#define BME280_HUMIDITY_CALIB_DATA_ADDR   UINT8_C(0xE1)
#define BME280_PWR_CTRL_ADDR              UINT8_C(0xF4)
#define BME280_CTRL_HUM_ADDR              UINT8_C(0xF2)
#define BME280_CTRL_MEAS_ADDR             UINT8_C(0xF4)
#define BME280_CONFIG_ADDR                UINT8_C(0xF5)
#define BME280_DATA_ADDR                  UINT8_C(0xF7)

#define RESET_CMD						  UINT8_C(0xB6)

#define BME280_TEMP_PRESS_CALIB_DATA_LEN  UINT8_C(26)
#define BME280_HUMIDITY_CALIB_DATA_LEN    UINT8_C(7)
#define BME280_P_T_H_DATA_LEN             UINT8_C(8)
#define BME280_CONCAT_BYTES(msb, lsb)     (((uint16_t)msb << 8) | (uint16_t)lsb)


/**\name Oversampling macros */
#define BME280_OSRS_H_NO_OVERSAMPLING      UINT8_C(0x00) // 00000000
#define BME280_OSRS_H_OVERSAMPLING_1X      UINT8_C(0x01) // 00000001
#define BME280_OSRS_H_OVERSAMPLING_2X      UINT8_C(0x02) // 00000010
#define BME280_OSRS_H_OVERSAMPLING_4X      UINT8_C(0x03) // 00000011
#define BME280_OSRS_H_OVERSAMPLING_8X      UINT8_C(0x04) // 00000100
#define BME280_OSRS_H_OVERSAMPLING_16X     UINT8_C(0x05) // 00000101

#define BME280_OSRS_T_NO_OVERSAMPLING      UINT8_C(0x00) // 00000000
#define BME280_OSRS_T_OVERSAMPLING_1X      UINT8_C(0x20) // 00100000
#define BME280_OSRS_T_OVERSAMPLING_2X      UINT8_C(0x40) // 01000000
#define BME280_OSRS_T_OVERSAMPLING_4X      UINT8_C(0x60) // 01100000
#define BME280_OSRS_T_OVERSAMPLING_8X      UINT8_C(0x80) // 10000000
#define BME280_OSRS_T_OVERSAMPLING_16X     UINT8_C(0xA0) // 10100000

#define BME280_OSRS_P_NO_OVERSAMPLING      UINT8_C(0x00) // 00000000
#define BME280_OSRS_P_OVERSAMPLING_1X      UINT8_C(0x04) // 00000100
#define BME280_OSRS_P_OVERSAMPLING_2X      UINT8_C(0x08) // 00001000
#define BME280_OSRS_P_OVERSAMPLING_4X      UINT8_C(0x0C) // 00001100
#define BME280_OSRS_P_OVERSAMPLING_8X      UINT8_C(0x10) // 00010000
#define BME280_OSRS_P_OVERSAMPLING_16X     UINT8_C(0x14) // 00010100

#define BME280_SLEEP_MODE                  UINT8_C(0x00) // 00000000
#define BME280_FORCE_MODE      			   UINT8_C(0x01) // 00000001
#define BME280_NORMAL_MODE     			   UINT8_C(0x03) // 00000011

/**\name Standby duration selection macros */
#define BME280_STANDBY_TIME_0_5_MS    		 UINT8_C(0x00) // 00000000
#define BME280_STANDBY_TIME_62_5_MS   		 UINT8_C(0x20) // 00100000
#define BME280_STANDBY_TIME_125_MS    		 UINT8_C(0x40) // 01000000
#define BME280_STANDBY_TIME_250_MS    		 UINT8_C(0x60) // 01100000
#define BME280_STANDBY_TIME_500_MS    		 UINT8_C(0x80) // 10000000
#define BME280_STANDBY_TIME_1000_MS   		 UINT8_C(0xA0) // 10100000
#define BME280_STANDBY_TIME_10_MS     		 UINT8_C(0xC0) // 11000000
#define BME280_STANDBY_TIME_20_MS     		 UINT8_C(0xE0) // 11100000

/**\name Filter coefficient selection macros */
#define BME280_FILTER_COEFF_OFF       		 UINT8_C(0x00) // 00000000
#define BME280_FILTER_COEFF_2         		 UINT8_C(0x04) // 00000100
#define BME280_FILTER_COEFF_4         		 UINT8_C(0x08) // 00001000
#define BME280_FILTER_COEFF_8         		 UINT8_C(0x0C) // 00001100
#define BME280_FILTER_COEFF_16        		 UINT8_C(0x10) // 00010000

struct bme280_calib_data
{
    uint16_t dig_T1;
    int16_t dig_T2;
    int16_t dig_T3;
    uint16_t dig_P1;
    int16_t dig_P2;
    int16_t dig_P3;
    int16_t dig_P4;
    int16_t dig_P5;
    int16_t dig_P6;
    int16_t dig_P7;
    int16_t dig_P8;
    int16_t dig_P9;
    uint8_t dig_H1;
    int16_t dig_H2;
    uint8_t dig_H3;
    int16_t dig_H4;
    int16_t dig_H5;
    int8_t dig_H6;
    int32_t t_fine;
};


struct bme280_data
{
    uint32_t pressure;
    int32_t temperature;
    uint32_t humidity;
};

struct bme280_uncomp_data
{
    uint32_t pressure;
    uint32_t temperature;
    uint32_t humidity;
};

struct bme280_settings
{
    uint8_t config; 
		uint8_t ctrl_meas;
		uint8_t ctrl_hum; 
};

struct bme280_dev
{
    uint8_t calib_0_25[BME280_TEMP_PRESS_CALIB_DATA_LEN];
	uint8_t calib_26_41[BME280_HUMIDITY_CALIB_DATA_LEN];
	uint8_t raw_data[BME280_P_T_H_DATA_LEN];
    struct bme280_calib_data calib_data;
    struct bme280_settings settings;
	struct bme280_uncomp_data uncomp_dat;
	struct bme280_data data;
};

#endif /* BME280_DEFS_H_ */
