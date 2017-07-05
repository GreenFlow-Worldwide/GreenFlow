/*
  where our main loop will live
  will have 2 functions

  int initMainThread() which will return an error code
  int mainThread() which returns an error code
  


*/


#include "stdint.h"
#include "stm32l0xx_hal.h"
//#include "wifi.h"    //TODO future work

static UART_HandleTypeDef * staticUartHandler;


//init all variables and send adc, uart handlers down to respective files
//ADC handler goes to battery check
//huart handler goes to uartIO
char initMainThread(UART_HandleTypeDef * uartHandler)
{
  char errorCode = 0;
  staticUartHandler = uartHandler;
  
  return errorCode;
}

char mainThread()
{
  char errorCode = 0;
  //Check For New Data with this function


  return errorCode;
}