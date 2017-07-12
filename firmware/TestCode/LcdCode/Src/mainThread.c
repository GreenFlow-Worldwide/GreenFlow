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
char initMainThread(ADC_HandleTypeDef * batteryAdcHandler, UART_HandleTypeDef * uartHandler)
{
  char errorCode = 0;
  //zero all file wide variables flowing downward.
  //errorCode = gd_initGrabData(batteryAdcHandler, uartHandler);
  errorCode = lcd_initLcdData();
  displayData.volumeInLiters = 0;
  displayData.flowChargerFlags = 0;
  displayData.flowBatteryFlags = 0;
  displayData.hubCharger = 0;
  displayData.hubBattery = 0;
  
  return errorCode;
}

char mainThread()
{
  char errorCode = 0;
  //Check For New Data with this function
  //errorCode = gd_getDisplayData(&displayData);
  
  //every loop volume will go up.
  displayData.volumeInLiters += 1.23;
  HAL_Delay(250);
  //give updated data to lcd to update screen
  errorCode = lcd_updateScreen(displayData);
  return errorCode;
}