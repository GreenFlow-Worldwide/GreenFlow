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

char lcd_write(SPI_HandleTypeDef * spiHandler, uint8_t data, uint8_t regSelect){
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

char lcd_clear(SPI_HandleTypeDef * spiHandler){
  char errorCode = 0;
  lcd_write(spiHandler, 0x01, 0);
  return errorCode;
}

char lcd_goto(SPI_HandleTypeDef * spiHandler, uint8_t pos, uint8_t line){
  char errorCode = 0;
  if (line == 1) {
    lcd_write(spiHandler, 0x80+pos, 0);	// 0x80 is the goto command
  }
  if (line == 2) {
    lcd_write(spiHandler, 0x80+pos+0x40, 0); // The second line starts at 0x40
  }
  if (line == 3) {
    lcd_write(spiHandler, 0x80+pos+0x14, 0); // The third line starts at 0x14
  }
  if (line == 4) {
    lcd_write(spiHandler, 0x80+pos+0x54, 0); // The fourth line starts at 0x54
  }
  return errorCode;
}

char lcd_putString(SPI_HandleTypeDef * spiHandler, uint8_t * s){
  char errorCode = 0;
  while(*s){
    lcd_write(spiHandler, *s++, 1);
  }
  return errorCode;
}

char lcd_staticText(SPI_HandleTypeDef * spiHandler){
  char errorCode = 0;
  lcd_clear(spiHandler);
  lcd_goto(spiHandler, 5, 1);
  lcd_putString(spiHandler, "GreenFlow");
  lcd_goto(spiHandler, 0, 3);
  lcd_putString(spiHandler, "Current Use:");
  lcd_goto(spiHandler, 15, 3);
  lcd_write(spiHandler, 0xA5, 1);
  lcd_goto(spiHandler, 19, 3);
  lcd_putString(spiHandler, "L");
  lcd_goto(spiHandler, 0, 4);
  lcd_putString(spiHandler, "Total Use:");
  lcd_goto(spiHandler, 15, 4);
  lcd_write(spiHandler, 0xA5, 1);
  lcd_goto(spiHandler, 19, 4);
  lcd_putString(spiHandler, "L");
  return errorCode;
}

char lcd_statusMessage(SPI_HandleTypeDef * spiHandler, gd_lcdData displayData){
  char errorCode = 0;
  static uint8_t lcd_messageCount = 0;
  if(lcd_messageCount < 8){
    if(displayData.flowChargerFlags){
      lcd_goto(spiHandler, 0, 2);
      lcd_putString(spiHandler, "Flow Charging");
    }
    else{
      lcd_messageCount = 8;
    }
  }
  else if(lcd_messageCount < 16){
    if(displayData.flowBatteryFlags){
      lcd_goto(spiHandler, 0, 2);
      lcd_putString(spiHandler, "FLOW BATT LOW");
    }
    else{
      lcd_messageCount = 16;
    }
  }
  else if(lcd_messageCount < 24){
    if(displayData.hubCharger){
      lcd_goto(spiHandler, 0, 2);
      lcd_putString(spiHandler, "Hub Charging");
      lcd_write(spiHandler, 0x20, 1);
    }
    else{
      lcd_messageCount = 24;
    }
  }
  else if(lcd_messageCount < 32){
    if(displayData.hubBattery){
      lcd_goto(spiHandler, 0, 2);
      lcd_putString(spiHandler, "HUB BATT LOW");
      lcd_write(spiHandler, 0x20, 1);
    }
    else{
      lcd_messageCount = 0;
    }
  }
  lcd_messageCount = lcd_messageCount + 1;
  if (lcd_messageCount > 32){
    lcd_messageCount = 0;
  }
  
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
  
  lcd_write(spiHandler, 0x28, 0);// 4 bit, 2-line, 5x8 dots
  lcd_write(spiHandler, 0x0C, 0);// display on, cursor off, no blink
  //lcd_write(spiHandler, 0x10, 0);      //set curser
  //lcd_write(spiHandler, 0x0F, 0);      //set Display ON, Blinking
  lcd_write(spiHandler, 0x06, 0);// increment cursor, no shift/Entry Mode Set
  
  lcd_clear(spiHandler);
  lcd_staticText(spiHandler);
  return errorCode;
}


char lcd_updateScreen(SPI_HandleTypeDef * spiHandler, gd_lcdData displayData)
{
  char errorCode = 0;
  char buttonInput = 0;
  //test LCD Code for debugging
  
  //look in buttonStates.h on this function
  errorCode = bs_getInputButtons(&buttonInput);
  //TODO for JP: update lcd in here with values from displayData and 
  //interupt flags from the push buttons
  lcd_statusMessage(spiHandler, displayData);
/*
  displayData.currentVolumeInLiters=0;
  displayData.totalVolumeInLiters=0;
  
  displayData.flowChargerFlags = 0;
  displayData.flowBatteryFlags = 0;
  displayData.hubCharger = 0;
  displayData.hubBattery = 0;
  */
  
  return errorCode;
}