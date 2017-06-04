/*
we will have be taking input from UART I/O and decoding it here

all functions and file_wide variables will have prefix dd
*/

#include "stm32l0xx_hal.h"
#include "uartIO.h"
#include "decodedData.h"

static double dd_currentVolume;
static char dd_flowBatteryFlags;
static char dd_flowChargerFlags;


char dd_initDecodedData(UART_HandleTypeDef * uartHandler)
{
  char errorCode = 0;
  //TODO: uart zero
  dd_currentVolume = 0;
  dd_flowChargerFlags = 0;
  dd_flowBatteryFlags = 0;
  errorCode = uio_initUartIO(uartHandler);
  
  return errorCode;
}

char dd_decodeData()
{
  char errorCode = 0;
  
  //grab the applicableDatafrom below
  double volume = 0;
  char flowChargerFlags = 0;
  char flowBatteryFlags = 0;
  
  //get the data from UartIO
  errorCode = uio_getUartRawData(&volume, &flowChargerFlags, &flowBatteryFlags);
  
  //If error code received that needs to be sent up, do it now.
  if(errorCode)
  {
    return errorCode;
  }
  
  //everything is good, save values and return
  dd_currentVolume = volume;
  dd_flowChargerFlags = flowChargerFlags;
  dd_flowBatteryFlags = flowBatteryFlags;
  
  return errorCode;
}

//grab volume and applicable flags to display on LCD
char dd_getUpdatedFlowData(double * flowVolume, char * flowBatteryFlags, char * flowChargerFlags)
{
  char errorCode = 0;
  errorCode = dd_decodeData();
  
  //return values passed in by reference with current values
  *flowVolume = dd_currentVolume;
  *flowBatteryFlags = dd_flowBatteryFlags;
  *flowChargerFlags = dd_flowChargerFlags;
  return errorCode;
}

