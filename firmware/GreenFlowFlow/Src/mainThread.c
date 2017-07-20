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
  
  //TODO: remove test code
  HAL_GPIO_WritePin(GPIOB, LED_Red_Pin|LED_Orange_Pin|LED_Green_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, LED_Red_Pin|LED_Orange_Pin|LED_Green_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOB, LED_Green_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, LED_Green_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOB, LED_Orange_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, LED_Orange_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOB, LED_Red_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, LED_Red_Pin, GPIO_PIN_RESET);
  
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11 , GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12 , GPIO_PIN_SET);
  errorCode = bc_initBatteryCheck(batteryAdcHandler);
  errorCode = ft_initFlag();
  return errorCode;
}

uint8_t mainThread()
{
  uint8_t errorCode = 0;
  //TODO check flag timer
  bool flagTimer = false;
  
  //TODO: remove test code
  bool flowpulse = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1);
  bool adpp = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12);
  bool stat = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13);
  bool flt = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14);
  bool bluetoothPair = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
  
  
  errorCode = ft_checkTimerFlag(&flagTimer);
  //if it is time, send data
  if(flagTimer){
    us_sendDataToFlow();
  }
  
  return errorCode;
}