#ifndef HW_LCD_DEF_H
#define HW_LCD_DEF_H

#include "main.h"
#define ILI9341_SCREEN_HEIGHT 240 
#define ILI9341_SCREEN_WIDTH  320

//SPI INSTANCE
#define HSPI_INSTANCE_LCD						&hspi1

//CHIP SELECT PIN AND PORT, STANDARD GPIO
#define LCD_CS_PORT								GPIOA
#define LCD_CS_PIN								GPIO_PIN_4

//DATA COMMAND PIN AND PORT, STANDARD GPIO
#define LCD_DC_PORT								GPIOF
#define LCD_DC_PIN								GPIO_PIN_4

//RESET PIN AND PORT, STANDARD GPIO
#define	LCD_RST_PORT							GPIOF
#define	LCD_RST_PIN								GPIO_PIN_5
/*
#define HSPI_INSTANCE_TOUCH						&hspi2
#define TP_CLK_PORT								GPIOB
#define TP_CLK_PIN								GPIO_PIN_13

#define TP_CS_PORT								GPIOB
#define TP_CS_PIN								GPIO_PIN_12

#define TP_MISO_PORT							GPIOB
#define TP_MISO_PIN								GPIO_PIN_14

#define TP_MOSI_PORT							GPIOB
#define TP_MOSI_PIN								GPIO_PIN_15

#define TP_IRQ_PORT								GPIOB
#define TP_IRQ_PIN								GPIO_PIN_11
*/
#endif