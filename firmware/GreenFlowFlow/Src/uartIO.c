/*
we will have a the shared uart io library. this file will be present on both
hub and flow systems

all functions and file_wide variables will have prefix uio
*/

#include "stm32l0xx_hal.h"
#include "stdint.h"
#include "uartIO.h"

#define SIZE_OF_STRUCT 5

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

char uio_sentPacket(dataHandler dataToSend)
{
    uint8_t outputData[SIZE_OF_STRUCT];
    memcpy(outputData, &dataToSend, SIZE_OF_STRUCT);

        //HAL_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);
    char errorCode = HAL_UART_Transmit(uio_uartHandler, outputData, SIZE_OF_STRUCT, 1000);
  return 0;
}