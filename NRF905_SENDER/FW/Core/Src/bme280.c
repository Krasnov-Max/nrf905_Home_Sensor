#include "main.h"
#include "bme280_defs.h"
#include "bme280.h"

static int32_t compensate_temperature(struct bme280_dev *dev);

static uint32_t compensate_pressure(struct bme280_dev *dev);

static uint32_t compensate_humidity(struct bme280_dev *dev);
static void bme280_parse_sensor_data(const uint8_t *reg_data, struct bme280_dev *dev);

static void parse_temp_press_calib_data(const uint8_t *reg_data, struct bme280_dev *dev);

static void parse_humidity_calib_data(const uint8_t *reg_data, struct bme280_dev *dev);

static int8_t bme280_compensate_data(struct bme280_dev *dev);


void bme280_parse_sensor_data(const uint8_t *reg_data, struct bme280_dev *dev)
{
    /* Variables to store the sensor data */
    uint32_t data_xlsb;
    uint32_t data_lsb;
    uint32_t data_msb;

    /* Store the parsed register values for pressure data */
    data_msb = (uint32_t)reg_data[0] << 12;
    data_lsb = (uint32_t)reg_data[1] << 4;
    data_xlsb = (uint32_t)reg_data[2] >> 4;
    dev->uncomp_dat.pressure = data_msb | data_lsb | data_xlsb;
		data_msb = data_lsb = data_xlsb =0;
    /* Store the parsed register values for temperature data */
    data_msb = (uint32_t)reg_data[3] << 12;
    data_lsb = (uint32_t)reg_data[4] << 4;
    data_xlsb = (uint32_t)reg_data[5] >> 4;
    dev->uncomp_dat.temperature = data_msb | data_lsb | data_xlsb;
		data_msb = data_lsb = data_xlsb =0;
    /* Store the parsed register values for temperature data */
    data_lsb = (uint32_t)reg_data[6] << 8;
    data_msb = (uint32_t)reg_data[7];
    dev->uncomp_dat.humidity = data_msb | data_lsb;
}

int8_t bme280_compensate_data(struct bme280_dev *dev)
{
    int8_t rslt = 1;

        /* Initialize to zero */
	      dev->data.temperature = 0;
        dev->data.pressure = 0;
        dev->data.humidity = 0;
        dev->data.temperature = compensate_temperature(dev);
        dev->data.pressure = compensate_pressure(dev);
        dev->data.humidity = compensate_humidity(dev);

    return rslt;
}

static int32_t compensate_temperature(struct bme280_dev *dev)
{
    int32_t var1;
    int32_t var2;
    int32_t temperature;
    int32_t temperature_min = -4000;
    int32_t temperature_max = 8500;

    var1 = (int32_t)((dev->uncomp_dat.temperature / 8) - ((int32_t) dev->calib_data.dig_T1 * 2));
    var1 = (var1 * ((int32_t)dev->calib_data.dig_T2)) / 2048;
    var2 = (int32_t)((dev->uncomp_dat.temperature / 16) - ((int32_t)dev->calib_data.dig_T1));
    var2 = (((var2 * var2) / 4096) * ((int32_t)dev->calib_data.dig_T3)) / 16384;
    dev->calib_data.t_fine = var1 + var2;
    temperature = (dev->calib_data.t_fine * 5 + 128) / 256;
    if (temperature < temperature_min)
    {
        temperature = temperature_min;
    }
    else if (temperature > temperature_max)
    {
        temperature = temperature_max;
    }

    return temperature;
}
static uint32_t compensate_pressure(struct bme280_dev *dev)
{
    int32_t var1;
    int32_t var2;
    int32_t var3;
    int32_t var4;
    uint32_t var5;
    uint32_t pressure;
    uint32_t pressure_min = 30000;
    uint32_t pressure_max = 110000;

    var1 = (((int32_t)dev->calib_data.t_fine) / 2) - (int32_t)64000;
    var2 = (((var1 / 4) * (var1 / 4)) / 2048) * ((int32_t)dev->calib_data.dig_P6);
    var2 = var2 + ((var1 * ((int32_t)dev->calib_data.dig_P5)) * 2);
    var2 = (var2 / 4) + (((int32_t)dev->calib_data.dig_P4) * 65536);
    var3 = (dev->calib_data.dig_P3 * (((var1 / 4) * (var1 / 4)) / 8192)) / 8;
    var4 = (((int32_t)dev->calib_data.dig_P2) * var1) / 2;
    var1 = (var3 + var4) / 262144;
    var1 = (((32768 + var1)) * ((int32_t)dev->calib_data.dig_P1)) / 32768;

    /* avoid exception caused by division by zero */
    if (var1)
    {
        var5 = (uint32_t)((uint32_t)1048576) - dev->uncomp_dat.pressure;
        pressure = ((uint32_t)(var5 - (uint32_t)(var2 / 4096))) * 3125;
        if (pressure < 0x80000000)
        {
            pressure = (pressure << 1) / ((uint32_t)var1);
        }
        else
        {
            pressure = (pressure / (uint32_t)var1) * 2;
        }
        var1 = (((int32_t)dev->calib_data.dig_P9) * ((int32_t)(((pressure / 8) * (pressure / 8)) / 8192))) / 4096;
        var2 = (((int32_t)(pressure / 4)) * ((int32_t)dev->calib_data.dig_P8)) / 8192;
        pressure = (uint32_t)((int32_t)pressure + ((var1 + var2 + dev->calib_data.dig_P7) / 16));
        if (pressure < pressure_min)
        {
            pressure = pressure_min;
        }
        else if (pressure > pressure_max)
        {
            pressure = pressure_max;
        }
    }
    else
    {
        pressure = pressure_min;
    }

    return pressure;
}
static uint32_t compensate_humidity(struct bme280_dev *dev)
{
    int32_t var1;
    int32_t var2;
    int32_t var3;
    int32_t var4;
    int32_t var5;
    uint32_t humidity;
    uint32_t humidity_max = 102400;

    var1 = dev->calib_data.t_fine - ((int32_t)76800);
    var2 = (int32_t)(dev->uncomp_dat.humidity * 16384);
    var3 = (int32_t)(((int32_t)dev->calib_data.dig_H4) * 1048576);
    var4 = ((int32_t)dev->calib_data.dig_H5) * var1;
    var5 = (((var2 - var3) - var4) + (int32_t)16384) / 32768;
    var2 = (var1 * ((int32_t)dev->calib_data.dig_H6)) / 1024;
    var3 = (var1 * ((int32_t)dev->calib_data.dig_H3)) / 2048;
    var4 = ((var2 * (var3 + (int32_t)32768)) / 1024) + (int32_t)2097152;
    var2 = ((var4 * ((int32_t)dev->calib_data.dig_H2)) + 8192) / 16384;
    var3 = var5 * var2;
    var4 = ((var3 / 32768) * (var3 / 32768)) / 128;
    var5 = var3 - ((var4 * ((int32_t)dev->calib_data.dig_H1)) / 16);
    var5 = (var5 < 0 ? 0 : var5);
    var5 = (var5 > 419430400 ? 419430400 : var5);
    humidity = (uint32_t)(var5 / 4096);
    if (humidity > humidity_max)
    {
        humidity = humidity_max;
    }

    return humidity;
}
void parse_temp_press_calib_data(const uint8_t *reg_data, struct bme280_dev *dev)
{
    struct bme280_calib_data *calib_data = &dev->calib_data;

    calib_data->dig_T1 = BME280_CONCAT_BYTES(reg_data[1], reg_data[0]);
    calib_data->dig_T2 = (int16_t)BME280_CONCAT_BYTES(reg_data[3], reg_data[2]);
    calib_data->dig_T3 = (int16_t)BME280_CONCAT_BYTES(reg_data[5], reg_data[4]);
    calib_data->dig_P1 = BME280_CONCAT_BYTES(reg_data[7], reg_data[6]);
    calib_data->dig_P2 = (int16_t)BME280_CONCAT_BYTES(reg_data[9], reg_data[8]);
    calib_data->dig_P3 = (int16_t)BME280_CONCAT_BYTES(reg_data[11], reg_data[10]);
    calib_data->dig_P4 = (int16_t)BME280_CONCAT_BYTES(reg_data[13], reg_data[12]);
    calib_data->dig_P5 = (int16_t)BME280_CONCAT_BYTES(reg_data[15], reg_data[14]);
    calib_data->dig_P6 = (int16_t)BME280_CONCAT_BYTES(reg_data[17], reg_data[16]);
    calib_data->dig_P7 = (int16_t)BME280_CONCAT_BYTES(reg_data[19], reg_data[18]);
    calib_data->dig_P8 = (int16_t)BME280_CONCAT_BYTES(reg_data[21], reg_data[20]);
    calib_data->dig_P9 = (int16_t)BME280_CONCAT_BYTES(reg_data[23], reg_data[22]);
    calib_data->dig_H1 = reg_data[25];
}
 void parse_humidity_calib_data(const uint8_t *reg_data, struct bme280_dev *dev)
{
    struct bme280_calib_data *calib_data = &dev->calib_data;
    int16_t dig_H4_lsb;
    int16_t dig_H4_msb;
    int16_t dig_H5_lsb;
    int16_t dig_H5_msb;

    calib_data->dig_H2 = (int16_t)BME280_CONCAT_BYTES(reg_data[1], reg_data[0]);
    calib_data->dig_H3 = reg_data[2];
    dig_H4_msb = (int16_t)(int8_t)reg_data[3] * 16;
    dig_H4_lsb = (int16_t)(reg_data[4] & 0x0F);
    calib_data->dig_H4 = dig_H4_msb | dig_H4_lsb;
    dig_H5_msb = (int16_t)(int8_t)reg_data[5] * 16;
    dig_H5_lsb = (int16_t)(reg_data[4] >> 4);
    calib_data->dig_H5 = dig_H5_msb | dig_H5_lsb;
    calib_data->dig_H6 = (int8_t)reg_data[6];
}
void GetCalibData_BME280(struct bme280_dev *dev)
{	
		uint8_t index_i,index_j;
	
		index_i = 0;
		index_j = 0;
		
		for (index_i=BME280_TEMP_PRESS_CALIB_DATA_ADDR; index_i<BME280_TEMP_PRESS_CALIB_DATA_ADDR+BME280_TEMP_PRESS_CALIB_DATA_LEN; index_i++)
			{
				SPI_GET_DAT(&index_i, &dev->calib_0_25[index_j]);
				index_j++;
			}
		
		
		index_j=0;
		for (index_i=BME280_HUMIDITY_CALIB_DATA_ADDR; index_i<BME280_HUMIDITY_CALIB_DATA_ADDR+BME280_HUMIDITY_CALIB_DATA_LEN; index_i++)
			{
				SPI_GET_DAT(&index_i, &dev->calib_26_41[index_j]);
				index_j++;
			}
}
void GetData_BME280(struct bme280_dev *dev)
{
	uint8_t index_i,index_j;
	
	index_i = 0;
	index_j = 0;
	
		for (index_i=BME280_DATA_ADDR; index_i<BME280_DATA_ADDR+BME280_P_T_H_DATA_LEN; index_i++)
			{
				SPI_GET_DAT(&index_i, &dev->raw_data[index_j]);
				index_j++;
			}	
		bme280_parse_sensor_data(dev->raw_data, dev);
		parse_temp_press_calib_data(dev->calib_0_25, dev);
		parse_humidity_calib_data(dev->calib_26_41, dev);
		bme280_compensate_data(dev);
}
uint8_t initBME280(struct bme280_dev *dev)
{
	uint8_t result, addr;
	
	result = 0;
	addr = BME280_RESET_ADDR;
	result = RESET_CMD;
	SPI_SET_DAT(&addr, &result);
	result = 0;
	addr = BME280_CHIP_ID_ADDR;
	SPI_GET_DAT(&addr, &result);
	if (result != 0x060) { return 0;}
	
	dev->settings.config = 0;
	dev->settings.config |= BME280_STANDBY_TIME_1000_MS | BME280_FILTER_COEFF_OFF;
	dev->settings.ctrl_hum = 0;
	dev->settings.ctrl_hum |= BME280_OSRS_H_OVERSAMPLING_1X;
	dev->settings.ctrl_meas = 0;
	dev->settings.ctrl_meas |= BME280_OSRS_T_OVERSAMPLING_1X | BME280_OSRS_P_OVERSAMPLING_1X | BME280_FORCE_MODE;
	addr = BME280_CONFIG_ADDR; 
	SPI_SET_DAT(&addr, &dev->settings.config);
	addr = BME280_CTRL_HUM_ADDR; 
	SPI_SET_DAT(&addr, &dev->settings.ctrl_hum);
	addr = BME280_CTRL_MEAS_ADDR; 
	SPI_SET_DAT(&addr, &dev->settings.ctrl_meas);
	

	
	return 1;
}
void FORCEMode (struct bme280_dev *dev)
{
	uint8_t addr;
	addr = BME280_CTRL_MEAS_ADDR; 
	SPI_SET_DAT(&addr, &dev->settings.ctrl_meas);
}

