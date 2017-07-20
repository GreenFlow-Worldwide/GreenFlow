/*
we will have be dealing with changes in the LCD
all functions and file_wide variables will have prefix lcd
*/
#include "grabData.h"
#include "lcdControl.h"
#include "buttonStates.h"
#include "stm32l0xx_hal.h"
#include "stdint.h"

static SPI_HandleTypeDef * spiHandler;

/*
this function takes the spi handler and a byte of data and sends it out of the 
spi port. It sends the byte 3 times while toggling the Enable bit for the LCD
*/
char lcd_sendData(uint8_t data){
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

/*
This function takes the spi handler, a byte of data, and the register select
bit and breaks the data into upper and lower nibble, appending the register
select bit onto each new byte, and sends each byte to lcd_sendData
*/
char lcd_write(uint8_t data, uint8_t regSelect){
  char errorCode = 0; 
  //data needs to be flipped due to hardware configurations
  data = (data & 0xF0) >> 4 | (data & 0x0F) << 4;
  data = (data & 0xCC) >> 2 | (data & 0x33) << 2;
  data = (data & 0xAA) >> 1 | (data & 0x55) << 1;
  
  uint8_t upper_nibble = (data << 4)| (regSelect);
  uint8_t lower_nibble = (data & 0xF0)| (regSelect);

  lcd_sendData(upper_nibble);
  lcd_sendData(lower_nibble);
  return errorCode;
}

/*
This function takes the spi handler, and clears the LCD of all data
*/
char lcd_clear(){
  char errorCode = 0;
  lcd_write(0x01, 0);
  return errorCode;
}

/*
This function takes the spi handler, the selected position and line, and sets
the cursor to that position
*/
char lcd_goto(uint8_t pos, uint8_t line){
  char errorCode = 0;
  if (line == 1) {
    lcd_write(0x80+pos, 0);	// 0x80 is the goto command
  }
  if (line == 2) {
    lcd_write(0x80+pos+0x40, 0); // The second line starts at 0x40
  }
  if (line == 3) {
    lcd_write(0x80+pos+0x14, 0); // The third line starts at 0x14
  }
  if (line == 4) {
    lcd_write(0x80+pos+0x54, 0); // The fourth line starts at 0x54
  }
  return errorCode;
}

/*
This function takes the spi handler, and a string, and writes that string to 
the current position
*/
char lcd_putString(uint8_t * s){
  char errorCode = 0;
  while(*s){
    lcd_write(*s++, 1);
  }
  return errorCode;
}

/*
This function takes the spi handler, and displays the static text on the LCD
*/
char lcd_staticText(){
  char errorCode = 0;
  lcd_clear();
  lcd_goto(5, 1);
  lcd_putString("GreenFlow");
  lcd_goto(0, 3);
  lcd_putString("Current Use:");
  lcd_goto(19, 3);
  lcd_putString("L");
  lcd_goto(0, 4);
  lcd_putString("Total Use:");
  lcd_goto(19, 4);
  lcd_putString("L");
  return errorCode;
}

/*
This function takes the spi handler, and the displayData class, and displays
the the relevant battery flags on the second line of the LCD
*/
char lcd_statusMessage(gd_lcdData displayData){
  char errorCode = 0;
  static uint8_t lcd_messageCount = 0;
  if(lcd_messageCount < 3){
    if(displayData.flowChargerFlags){
      lcd_goto(0, 2);
      lcd_putString("Flow Charging");
    }
    else{
      lcd_messageCount = 8;
    }
  }
  else if(lcd_messageCount < 16){
    if(displayData.flowBatteryFlags){
      lcd_goto(0, 2);
      lcd_putString("FLOW BATT LOW");
    }
    else{
      lcd_messageCount = 16;
    }
  }
  else if(lcd_messageCount < 24){
    if(displayData.hubCharger){
      lcd_goto(0, 2);
      lcd_putString("Hub Charging");
      lcd_write(0x20, 1);
    }
    else{
      lcd_messageCount = 24;
    }
  }
  else if(lcd_messageCount < 32){
    if(displayData.hubBattery){
      lcd_goto(0, 2);
      lcd_putString("HUB BATT LOW");
      lcd_write(0x20, 1);
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

/*
This function takes the spi handler, and the displayData class, and displays
the current volume on the third line of the LCD
*/
char lcd_displayCurrent(gd_lcdData displayData){
  char errorCode = 0;
  char currentLiters[10];
  lcd_goto(13, 3);
  
  sprintf(currentLiters, "%.1f", displayData.currentVolumeInLiters);
  if(displayData.currentVolumeInLiters >= 10000){
    lcd_goto(12, 3); //go back a space
    sprintf(currentLiters, "%.0f", displayData.currentVolumeInLiters);
    lcd_putString(currentLiters);   
  }
  else if(displayData.currentVolumeInLiters >= 1000){
    sprintf(currentLiters, "%.0f", displayData.currentVolumeInLiters);
    lcd_write(0x20, 1);
    lcd_putString(currentLiters);   
  }
  else if(displayData.currentVolumeInLiters >= 100){
    lcd_putString(currentLiters);
  }
  else if(displayData.currentVolumeInLiters >= 10){
    lcd_putString(" ");
    lcd_putString(currentLiters);  
  }
  else{
    lcd_putString("  ");
    lcd_putString(currentLiters);  
  }
  return errorCode;
}

/*
This function takes the spi handler, and the displayData class, and displays
the total volume on the fourth line of the LCD
*/
char lcd_displayTotal(gd_lcdData displayData){
  char errorCode = 0;
  char totalLiters[10];
  sprintf(totalLiters, "%.1f", displayData.totalVolumeInLiters);
  if(displayData.totalVolumeInLiters >= 100000){
    sprintf(totalLiters, "%.0f", displayData.totalVolumeInLiters);
    lcd_goto(12, 4);
    lcd_putString(totalLiters);   
  }
  else if(displayData.totalVolumeInLiters >= 10000){
    sprintf(totalLiters, "%.0f", displayData.totalVolumeInLiters);
    lcd_goto(12, 4);
    lcd_write(0x20, 1);
    lcd_putString(totalLiters);   
  }
  else if(displayData.totalVolumeInLiters >= 1000){
    sprintf(totalLiters, "%.0f", displayData.totalVolumeInLiters);
    lcd_goto(12, 4);
    lcd_write(0x20, 1);
    lcd_write(0x20, 1);
    lcd_putString(totalLiters);   
  }
  else if(displayData.totalVolumeInLiters >= 100){
    lcd_goto(12, 4);
    lcd_write(0x20, 1);
    lcd_putString(totalLiters);
  }
  else if(displayData.totalVolumeInLiters >= 10){
    lcd_goto(12, 4);
    lcd_write(0x20, 1);
    lcd_write(0x20, 1);
    lcd_putString(totalLiters);  
  }
  else{
    lcd_goto(12, 4);
    lcd_write(0x20, 1);
    lcd_write(0x20, 1);
    lcd_write(0x20, 1);
    lcd_putString(totalLiters);  
  }
  return errorCode;
}

/*
This function takes the spi handler, initializes the LCD
*/
char lcd_initLcdData(SPI_HandleTypeDef * spiHandlerTemp)
{
  //save SPI handler here so it doesn't need to be passed in later 
  spiHandler = spiHandlerTemp;
  uint8_t data;
// INIT LCD HERE
  char errorCode = 0;
  char bs_initButtonStates();
  //Pull LCD_LED high turns backlight on.
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);

  //set the !EO pin low for the shift register output enable
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
  //set latch low to turn off 
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);

  HAL_Delay(150); //delay after power is applied
  data = 0xC0; //data should be 0x30  but has been flipped and shifted
  lcd_sendData(data);
  HAL_Delay(5);
  lcd_sendData(data);
  HAL_Delay(1);
  lcd_sendData(data);
  HAL_Delay(1);
  
  data= 0x40; //data should be 0x20  but has been flipped and shifted
  lcd_sendData(data);
  HAL_Delay(1);
  
  lcd_write(0x28, 0);// 4 bit, 2-line, 5x8 dots
  lcd_write(0x0C, 0);// display on, cursor off, no blink
  //lcd_write(0x10, 0);      //set curser
  //lcd_write(0x0F, 0);      //set Display ON, Blinking
  lcd_write(0x06, 0);// increment cursor, no shift/Entry Mode Set
  
  lcd_clear();
  lcd_staticText();
  return errorCode;
}

/*
This function takes the spi handler, and the displayData class, calls the 
appropriate functions to display status messages, as well as current and 
total volumes
*/
char lcd_updateScreen(gd_lcdData displayData)
{
  char errorCode = 0;
  char buttonInput = 0;
  //look in buttonStates.h on this function
  errorCode = bs_getInputButtons(&buttonInput);
  //TODO for JP: update lcd in here with values from displayData
  lcd_statusMessage(displayData);
  lcd_displayCurrent(displayData);
  lcd_displayTotal(displayData);

  return errorCode;
}