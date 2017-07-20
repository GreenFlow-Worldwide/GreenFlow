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
  
  //TODO: SET LEDS LOW BY DEFAULT
  //HAL_GPIO_WritePin(GPIOB, LED_Red_Pin|LED_Blue_Pin|LED_Green_Pin, GPIO_PIN_RESET);
  //test LED lights
  //HAL_GPIO_WritePin(GPIOB, LED_Red_Pin|LED_Blue_Pin|LED_Green_Pin, GPIO_PIN_SET);
  //HAL_GPIO_WritePin(GPIOB, LED_Red_Pin|LED_Blue_Pin|LED_Green_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOB, LED_Green_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, LED_Green_Pin, GPIO_PIN_RESET);
  //HAL_GPIO_WritePin(GPIOB, LED_Blue_Pin, GPIO_PIN_SET);
  //HAL_GPIO_WritePin(GPIOB, LED_Blue_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11 , GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12 , GPIO_PIN_SET);
  
  errorCode = lcd_initLcdData(spiHandler);
  displayData.currentVolumeInLiters=0;
  displayData.totalVolumeInLiters=0;
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
  bool newPacket = false;
  errorCode = gd_getDisplayData(&displayData, &newPacket);

  
  bool backbtn = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
  bool downbtn = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1);
   bool upbtn = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4);
   bool nextbtn = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5);
   bool adpp = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12);
   bool stat = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13);
    bool flt = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14);
    bool bluetoothPair = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
  
  
  
//only update the screen whenever a new packet is recieved
  //or tick timer is hit.
  if(newPacket){
    //give updated data to lcd to update screen
    errorCode = lcd_updateScreen(displayData);
  }
  return errorCode;
}