/*
we will have be grabbing the decoded data, charger state data
battery check data and putting it all into a single struct to return to main.
this data can be easily used by LCD control to find information and print 
it to the screen

all functions and file_wide variables will have prefix gd
*/
//TODO: add section in struct for total water usage

#include "stm32l0xx_hal.h"
#include "batteryCheck.h"
#include "chargerState.h"
#include "decodedData.h"
#include "grabData.h"

double totalWaterUse;
//initalize all data and function call decoded data, charger state
// and battery check to initalize as well.
char gd_initGrabData(ADC_HandleTypeDef * batteryAdcHandler, UART_HandleTypeDef * uartHandler)
{
  char errorCode = 0;
  //pass uart handler to decodedData -> UartIO
  errorCode = dd_initDecodedData(uartHandler);

  errorCode = cs_initChargerState();
  
  //pass adcHandler to the battery 
  errorCode = bc_initBatteryCheck(batteryAdcHandler);
  totalWaterUse = 0.0;
  return errorCode;
}

char gd_getDisplayData(gd_lcdData * displayData, bool * newData)
{
  //have error code here display something different for each function call
  char errorCode = 0;
  
  double updatedCurrentVolume = 0;
  double updatedTotalVolume = 0;
  char updatedFlowBatteryFlags = 0;
  char updatedFlowChargerFlags = 0;
  char updatedHubCharger = 0;
  char updatedHubBattery = 0;
  
  //TODO: error check after each function, deal with each error code seperately
  errorCode = dd_getUpdatedFlowData(&updatedCurrentVolume, &updatedFlowBatteryFlags, &updatedFlowChargerFlags, newData);
  errorCode = cs_getUpdatedHubCharger(&updatedHubCharger);
  errorCode = bc_getUpdatedHubBattery(&updatedHubBattery);
  
  //copy values to struct to pass back
  displayData->currentVolumeInLiters = updatedCurrentVolume;
  displayData->totalVolumeInLiters = 500 + updatedCurrentVolume;
  displayData->flowChargerFlags = updatedFlowChargerFlags;
  displayData->flowBatteryFlags = updatedFlowBatteryFlags;
  displayData->hubCharger = updatedHubCharger;
  displayData->hubBattery = updatedHubBattery;
  
  //return any error code that needs to be sent up. 
  //SOME ERROR CODES CAN BE DEALT WITH IN THIS FUNCTION AND DO NOT NEED TO BE PASSED UP
  return errorCode;
}