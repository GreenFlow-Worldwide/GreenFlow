/*
we will have a the shared uart io library. this file will be present on both
hub and flow systems

all functions and file_wide variables will have prefix uio
*/

#include "stm32l0xx_hal.h"

static UART_HandleTypeDef * uio_uartHandler;

char uio_initUartIO(UART_HandleTypeDef * uartHandler)
{
  char errorCode = 0;
  
  uio_uartHandler = uartHandler;
  
  return errorCode;
}

char uio_getUartRawData(double *volume, char *flowChargerFlags, char *flowBatteryFlags)
{
  char errorCode = 0;
  
  *volume = 5;
  *flowChargerFlags = 0;
  *flowBatteryFlags = 1;
  
  return errorCode;
}