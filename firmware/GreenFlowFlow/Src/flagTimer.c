/*
we will have a timer flag in here to grab data. Flag will be set at 10 Hz.

may have flag in here to turn on ADC to read battery voltage

all functions and file_wide variables will have prefix ft
*/

#include "stm32l0xx_hal.h"
#include "stdbool.h"
#include <stdint.h>

bool timerFlag;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  timerFlag = true;
  
  if(resetVolumeCounter > 5)
  {
    resetVolumeCounter = 0;
    resetVolumeFlag = true;
  }
  resetVolumeCounter++;
}

uint8_t ft_initFlag()
{
  uint8_t errorCode = 0;
  timerFlag = false;
  return errorCode;
}

uint8_t ft_checkTimerFlag(bool * isTimerFlag)
{
  uint8_t errorCode = 0;
  *isTimerFlag = timerFlag;
  timerFlag = false;
  
  if(newPacket)
  {
    *isResetVolumeFlag = false;
    resetVolumeCounter = 0;
  }else{
    *isResetVolumeFlag = resetVolumeFlag;
  }
  resetVolumeFlag = false;
  
  
  return errorCode;
}