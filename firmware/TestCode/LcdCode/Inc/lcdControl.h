#ifndef _LCD_CONTROL_H_ 
#define _LCD_CONTROL_H_
#include "stm32l0xx_hal.h"
#include "grabData.h"

char lcd_sendData(SPI_HandleTypeDef * spiHandler, uint8_t data);
char lcd_initLcdData(SPI_HandleTypeDef * spiHandler);
char lcd_updateScreen(SPI_HandleTypeDef * spiHandler, gd_lcdData displayData);
char lcd_write(SPI_HandleTypeDef * spiHandler, uint8_t data, uint8_t regSelect);
char lcd_clear(SPI_HandleTypeDef * spiHandler);
char lcd_goto(SPI_HandleTypeDef * spiHandler, uint8_t pos, uint8_t line);
char lcd_puts(SPI_HandleTypeDef * spiHandler, uint8_t * s);
char lcd_staticText(SPI_HandleTypeDef * spiHandler);
char lcd_statusMessage(SPI_HandleTypeDef * spiHandler, gd_lcdData displayData);
char lcd_displaCurrent(SPI_HandleTypeDef * spiHandler, gd_lcdData displayData);
char lcd_displayTotal(SPI_HandleTypeDef * spiHandler, gd_lcdData displayData);

#endif