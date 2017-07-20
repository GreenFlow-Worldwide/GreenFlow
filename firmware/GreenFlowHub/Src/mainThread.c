/*
  where our main loop will live
  will have 2 functions

  int initMainThread() which will return an error code
  int mainThread() which returns an error code
  


*/

#include "lcdControl.h"
#include "grabData.h"
#include "stdint.h"
#include "stm32l0xx_hal.h"
//#include "wifi.h"    //TODO future work

static gd_lcdData displayData;

//init all variables and send adc, uart handlers down to respective files
//ADC handler goes to battery check
//huart handler goes to uartIO
char initMainThread(ADC_HandleTypeDef * batteryAdcHandler, UART_HandleTypeDef * uartHandler, SPI_HandleTypeDef * spiHandler)
{
  char errorCode = 0;
  //zero all file wide variables flowing downward.
  errorCode = gd_initGrabData(batteryAdcHandler, uartHandler);
  errorCode = lcd_initLcdData(spiHandler);
  displayData.currentVolumeInLiters=0;
  displayData.totalVolumeInLiters=0;
  displayData.flowChargerFlags = 0;
  displayData.flowBatteryFlags = 0;
  displayData.hubCharger = 0;
  displayData.hubBattery = 0;

  
  //test LED lights
  HAL_GPIO_WritePin(GPIOB, LED_Red_Pin|LED_Blue_Pin|LED_Green_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, LED_Red_Pin|LED_Blue_Pin|LED_Green_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOB, LED_Green_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, LED_Green_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOB, LED_Blue_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, LED_Blue_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOB, LED_Red_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, LED_Red_Pin, GPIO_PIN_RESET);

  
  return errorCode;
}

char mainThread()
{
  char errorCode = 0;
  //Check For New Data with this function
  bool newPacket = false;
  errorCode = gd_getDisplayData(&displayData, &newPacket);

//only update the screen whenever a new packet is recieved
  //or tick timer is hit.
  if(newPacket){
    //give updated data to lcd to update screen
    errorCode = lcd_updateScreen(displayData);
  }
  return errorCode;
}