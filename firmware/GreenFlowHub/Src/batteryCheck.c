/*
we will have be taking adc reading of the battery as well as 
dealing with battery reading from flow

all functions and file_wide variables will have prefix bc
*/
#include "stm32l0xx_hal.h"

//adc handler needed for HAL function calls
static ADC_HandleTypeDef * bc_batteryAdcHandle;

//battery flag storage variable
//TODO: design what the variable returns
static char bc_batteryFlag;



char bc_initBatteryCheck(ADC_HandleTypeDef * batteryAdcHandle)
{
  char errorCode = 0;
  bc_batteryFlag = 0;
  
  //copy Adc handler to be used in this c file
  bc_batteryAdcHandle = batteryAdcHandle;
  
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);
  
  //TODO: if HAL library returns any error, escape and restart hardware
  if(HAL_ADC_Start(bc_batteryAdcHandle))
  {
    errorCode = 1; //fatal error
    return errorCode;
  }
  return errorCode;
}


//TODO: grab battery states and put them here to be decoded later.
char bc_checkBatteryStatus()
{
  char errorCode = 0;
  
  uint32_t currentBatteryValue = HAL_ADC_GetValue(bc_batteryAdcHandle);
  
  bc_batteryFlag = 10;
  return errorCode;
}

char bc_getUpdatedHubBattery(char * batteryFlag)
{
  char errorCode = 0;
  //TODO: deal with error code now if possible
  errorCode =  bc_checkBatteryStatus();
  
  //return values for battery flag
  *batteryFlag = bc_batteryFlag;
  return errorCode;
}
