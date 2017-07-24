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
  
  //SET adc read pin high.
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);
  
  //TODO: if HAL library returns any error, escape and restart hardware
  if(HAL_ADC_Start(bc_batteryAdcHandle))
  {
    errorCode = 1; //fatal error
    return errorCode;
  }
  return errorCode;
}


 uint8_t bc_checkBatteryStatus()
{
  uint8_t errorCode = 0;
  //set ADC read pin high here.
  uint32_t currentBatteryValue = HAL_ADC_GetValue(bc_batteryAdcHandle);
  
  //check below will raise a flag if the ADC check value is less than 3v3
  //value 3217/4095 is 3.3/4.2 volts
  if(currentBatteryValue  < 3217)
  {
    bc_batteryFlag = 1;
  }else{
    bc_batteryFlag = 0;
  }

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
