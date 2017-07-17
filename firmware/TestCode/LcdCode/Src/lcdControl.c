/*
we will have be dealing with changes in the LCD
all functions and file_wide variables will have prefix lcd
*/
#include "grabData.h"
#include "lcdControl.h"
#include "buttonStates.h"
#include "stm32l0xx_hal.h"
#include "stdint.h"

char lcd_sendData(SPI_HandleTypeDef * spiHandler, uint8_t data){
  char errorCode = 0;
  char sendData= 0xFF;
  for(uint8_t i=0; i<3; i++){
    sendData = data | ((i & 0x01) << 2); //toggle enable bit 0-1-0
    //set latch 
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
    //wait till SPI transmit is done
    //while(__HAL_SPI_GET_FLAG(spiHandler, SPI_FLAG_BSY) != RESET);
    //send SPI
    HAL_SPI_Transmit(spiHandler, &sendData, 1, 1);
    //wait till SPI transmit is done
    while(__HAL_SPI_GET_FLAG(spiHandler, SPI_FLAG_BSY) != RESET);
    //set latch
    HAL_Delay(1);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
    HAL_Delay(1);
  }
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
  return errorCode;
}

char lcd_Write(SPI_HandleTypeDef * spiHandler, uint8_t data, uint8_t regSelect){
  char errorCode = 0; 
  //data needs to be flipped due to hardware configurations
  data = (data & 0xF0) >> 4 | (data & 0x0F) << 4;
  data = (data & 0xCC) >> 2 | (data & 0x33) << 2;
  data = (data & 0xAA) >> 1 | (data & 0x55) << 1;
  
  uint8_t upper_nibble = (data << 4)| (regSelect);
  uint8_t lower_nibble = (data & 0xF0)| (regSelect);

  lcd_sendData(spiHandler, upper_nibble);
  lcd_sendData(spiHandler, lower_nibble);
  return errorCode;
}

//zero or initalize any variables here
char lcd_initLcdData(SPI_HandleTypeDef * spiHandler)
{
   uint8_t data;
// INIT LCD HERE
  char errorCode = 0;
  char bs_initButtonStates();
  //set the !EO pin low for the shift register output enable
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
  //set latch low to turn off 
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
  HAL_Delay(150); //delay after power is applied
  data = 0xC0; //data should be 0x30  but has been flipped and shifted
  lcd_sendData(spiHandler, data);
  HAL_Delay(5);
  lcd_sendData(spiHandler, data);
  HAL_Delay(1);
  lcd_sendData(spiHandler, data);
  HAL_Delay(1);
  
  data= 0x40; //data should be 0x20  but has been flipped and shifted
  lcd_sendData(spiHandler, data);
  HAL_Delay(1);
  
  lcd_Write(spiHandler, 0x28, 0);// 4 bit, 2-line, 5x8 dots
  //lcd_Write(spiHandler, 0x0C, 0);// display on, cursor off, no blink
  lcd_Write(spiHandler, 0x10, 0);      //set curser
  lcd_Write(spiHandler, 0x0F, 0);      //set Display ON, Blinking
  lcd_Write(spiHandler, 0x06, 0);// increment cursor, no shift/Entry Mode Set
  
  return errorCode;
}


char lcd_updateScreen(SPI_HandleTypeDef * spiHandler, gd_lcdData displayData)
{
  char errorCode = 0;
  char buttonInput = 0;
  
  //test LCD Code for debugging
  //lcd_Write(spiHandler, 0x10, 0); 
  //lcd_Write(spiHandler, 0x7C, 1);
  //uint8_t data = 0xC0; //data should be 0x30  but has been flipped and shifted
  //lcd_sendData(spiHandler, data);
  lcd_Write(spiHandler, 0x61, 1);
  //look in buttonStates.h on this function
  errorCode = bs_getInputButtons(&buttonInput);
  //TODO for JP: update lcd in here with values from displayData and 
  //interupt flags from the push buttons
  
/*
  displayData.currentVolumeInLiters=0;
  displayData.totalVolumeInLiters=0;
  displayData.volumeInLiters = 0;
  
  displayData.flowChargerFlags = 0;
  displayData.flowBatteryFlags = 0;
  displayData.hubCharger = 0;
  displayData.hubBattery = 0;
  */
  
  return errorCode;
}