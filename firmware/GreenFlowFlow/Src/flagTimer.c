/*
we will have a timer flag in here to grab data. Flag will be set at 10 Hz.

may have flag in here to turn on ADC to read battery voltage

all functions and file_wide variables will have prefix ft
*/

#include "stm32l0xx_hal.h"
#include "stdbool.h"
#include <stdint.h>

bool timerFlag;
bool resetVolumeFlag;
uint8_t resetVolumeCounter;


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  timerFlag = true;
  
  if(resetVolumeCounter > 15)
  {
    resetVolumeCounter = 0;
    resetVolumeFlag = true;
  }
  resetVolumeCounter++;
}

uint8_t ft_initFlag()
{
  uint8_t errorCode = 0;
  resetVolumeCounter = 0;
  resetVolumeFlag= false;
  timerFlag = false;
  return errorCode;
}

uint8_t ft_checkTimerFlag(bool * isTimerFlag)
{
  uint8_t errorCode = 0;
  *isTimerFlag = timerFlag;
  timerFlag = false;
  
  
  return errorCode;
}

uint8_t ft_checkResetVolumeFlag(const bool newVolume, bool * isResetVolumeFlag)
{
  int newPacket = 1;
  if(newVolume)
  {
    *isResetVolumeFlag = false;
    resetVolumeCounter = 0;
  }else{
    *isResetVolumeFlag = resetVolumeFlag;
  }
  resetVolumeFlag = false;
}