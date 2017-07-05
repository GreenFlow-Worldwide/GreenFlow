/*
we will have a the shared uart io library. this file will be present on both
hub and flow systems

all functions and file_wide variables will have prefix uio
*/

#include "stm32l0xx_hal.h"
#include "stdint.h"
#include "stdbool.h"
#include "uartIO.h"

#define SIZE_OF_BUFFER 5

static UART_HandleTypeDef * uio_uartHandler;

char recieveBuffer[SIZE_OF_BUFFER];
char saveData[SIZE_OF_BUFFER];
bool newData;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huartInterruptHandler)
{
	if (huartInterruptHandler->Instance == USART1)	//current UART
		{
                  for(int i = 0; i < SIZE_OF_BUFFER; i++){ 
                    saveData[i] = recieveBuffer[i];
                    recieveBuffer[i] = 0; 
                  }
                newData = true;
		HAL_UART_Receive_IT(uio_uartHandler, (uint8_t *)recieveBuffer, SIZE_OF_BUFFER);	//activate UART receive interrupt every time
		}
 
}

//saves uart handler and inits values, start interrupt
char uio_initUartIO(UART_HandleTypeDef * uartHandler)
{
  char errorCode = 0;
  newData = false;
  uio_uartHandler = uartHandler;
  HAL_UART_Receive_IT(uio_uartHandler, (uint8_t *)recieveBuffer, SIZE_OF_BUFFER);
  return errorCode;
}

//get Uart values recieved from last uart interrupt
char uio_getUartRawData(double *volumeInLitres, char *flowChargerFlags, char *flowBatteryFlags)
{
  char errorCode = 0;
  dataHandler recievedData;
  if(newData){
    int value = sizeof(recievedData);
    memcpy(&recievedData, saveData, SIZE_OF_BUFFER);
    newData = false;
  }
  //convertTicks to volume 1850 ticks = 4 litres from tests
  //roughly every 463 is a litre 
  *volumeInLitres = (double)recievedData.volumeInTicks / 463.0;
  *flowChargerFlags = recievedData.flowChargerFlags;
  *flowBatteryFlags = recievedData.flowBatteryFlags;
  
  //TODO: deal with incomming errors
  
  return errorCode;
}

//TODO: Remove testCode,
//char uio_sentPacket()
//{
//  uint8_t outputChar[3] = {1,2,3};
//  uint8_t inputChar[3] = {0,0,0};
  // HAL_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)
//  char errorCode = HAL_UART_Transmit(uio_uartHandler, outputChar, 3, 1000);
//  HAL_Delay(500);
  //HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);
  //errorCode = HAL_UART_Receive(uio_uartHandler, inputChar, 3, 1000);
//  return 0;
//}