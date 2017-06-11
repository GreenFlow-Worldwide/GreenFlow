/*
we will have a the shared uart io library. this file will be present on both
hub and flow systems

all functions and file_wide variables will have prefix uio
*/

#include "stm32l0xx_hal.h"
#include "stdint.h"
#include "uartIO.h"
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
  uio_sentPacket();
  return errorCode;
}

char uio_sentPacket()
{
  uint8_t outputChar[3] = {1,2,3};
  uint8_t inputChar[3] = {0,0,0};
  // HAL_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)
  char errorCode = HAL_UART_Transmit(uio_uartHandler, outputChar, 3, 1000);
  HAL_Delay(500);
  //HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);
  //errorCode = HAL_UART_Receive(uio_uartHandler, inputChar, 3, 1000);
  return 0;
}