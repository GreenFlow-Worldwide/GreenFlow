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
  errorCode = ft_checkTimerFlag(&flagTimer);
  //if it is time, send data
  if(flagTimer){
    us_sendDataToFlow();
  }
  
  return errorCode;
}