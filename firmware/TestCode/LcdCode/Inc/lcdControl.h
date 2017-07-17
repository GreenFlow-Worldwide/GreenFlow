#ifndef _LCD_CONTROL_H_ 
#define _LCD_CONTROL_H_
#include "stm32l0xx_hal.h"
#include "grabData.h"

char lcd_sendData(SPI_HandleTypeDef * spiHandler, uint8_t data);
char lcd_initLcdData(SPI_HandleTypeDef * spiHandler);
char lcd_updateScreen(SPI_HandleTypeDef * spiHandler, gd_lcdData displayData);
char lcd_Write(SPI_HandleTypeDef * spiHandler, uint8_t data, uint8_t regSelect);

#endif