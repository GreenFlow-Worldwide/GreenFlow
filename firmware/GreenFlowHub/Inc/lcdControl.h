#ifndef _LCD_CONTROL_H_ 
#define _LCD_CONTROL_H_
#include "stm32l0xx_hal.h"
#include "grabData.h"

char lcd_sendData(uint8_t data);
char lcd_initLcdData(SPI_HandleTypeDef * spiHandler);
char lcd_updateScreen(gd_lcdData displayData);
char lcd_write(uint8_t data, uint8_t regSelect);
char lcd_clear();
char lcd_goto(uint8_t pos, uint8_t line);
char lcd_puts(uint8_t * s);
char lcd_staticText();
char lcd_statusMessage(gd_lcdData displayData);
char lcd_displaCurrent(gd_lcdData displayData);
char lcd_displayTotal(gd_lcdData displayData);

#endif
