/*
  where our main loop will live
  will have 2 functions

  int initMainThread() which will return an error code
  int mainThread() which returns an error code
  


*/

#include "flagTimer.h"
#include "batteryCheck.h"
#include "chargerState.h"
#include "uartSend.h"
#include "uartIO.h"
#include "calcVolume.h"



char initMainThread(ADC_HandleTypeDef * batteryAdcHandler, UART_HandleTypeDef * uartHandler)
{
  uint8_t errorCode = 0;
  //set green LED on as indicator of board turning on
  HAL_GPIO_WritePin(GPIOB, LED_Green_Pin, GPIO_PIN_SET);
  uio_initUartIO(uartHandler);
 
  errorCode = bc_initBatteryCheck(batteryAdcHandler);
  errorCode = ft_initFlag();
  return errorCode;
}

uint8_t mainThread()
{
  uint8_t errorCode = 0;
  //TODO check flag timer
  bool flagTimer = false;
  bool resetVolume = false;
  //check if it is time to reset volume and reset 
  errorCode = ft_checkTimerFlag(&flagTimer);
  //if it is time, send data
  if(flagTimer){
    us_sendDataToFlow();
  }
  
  return errorCode;
}