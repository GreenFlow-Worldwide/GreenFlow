/*
we will have a timer flag in here to grab data. Flag will be set at 10 Hz.

may have flag in here to turn on ADC to read battery voltage

all functions and file_wide variables will have prefix ft
*/

#include "stm32l0xx_hal.h"
#include "stdbool.h"
#include <stdint.h>

bool updateScreenFlag;
bool resetVolumeFlag;
static TIM_HandleTypeDef * timerHandler; //not using at the moment. Save for future work.
int resetVolumeCounter;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * TimerHandler)
{
  updateScreenFlag = true;
  if(resetVolumeCounter > 5)
  {
    resetVolumeCounter = 0;
    resetVolumeFlag = true;
  }
  resetVolumeCounter++;
  
}

//init timer 2 and timer 21 for interrupt flags
uint8_t ft_initFlag(TIM_HandleTypeDef * timerHandlerTemp)
{
  uint8_t errorCode = 0;
  resetVolumeCounter = 0;
  resetVolumeFlag = false;
  updateScreenFlag = false;
  //save timer handlers to compare to later.
  timerHandler = timerHandlerTemp;
  HAL_TIM_Base_Start_IT(timerHandler);
  return errorCode;
}

uint8_t ft_checkTimerFlag(bool * isUpdateScreenFlag, bool * isResetVolumeFlag)
{
  uint8_t errorCode = 0;
  *isUpdateScreenFlag = updateScreenFlag;
  updateScreenFlag = false;
  
  //TODO: DEAL WITH REFESH VOLUME COUNTER (set to 0 when reset until new data)
  *isResetVolumeFlag = resetVolumeFlag;
  resetVolumeFlag = false;
  
  return errorCode;
}