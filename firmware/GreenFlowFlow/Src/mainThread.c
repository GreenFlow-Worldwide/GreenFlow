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
  errorCode = bc_initBatteryCheck(batteryAdcHandler);
  return errorCode;
}

uint8_t mainThread()
{
  uint8_t errorCode = 0;
  uint16_t updatedVolumeInTicks = 0;
  uint8_t updatedFlowCharger = 0;
  uint8_t updatedFlowBattery = 0;
  uint8_t updatedErrorCode = 0;
  //grab flow information from increment and battery + charger
  errorCode = cs_getUpdatedHubCharger(&updatedFlowCharger);
  errorCode = bc_getUpdatedHubBattery(&updatedFlowBattery);
  errorCode = cv_getUpdatedFlowVolume(&updatedVolumeInTicks);
  
  dataHandler dataToSend;
  dataToSend.volumeInTicks = updatedVolumeInTicks;
  dataToSend.flowChargerFlags = updatedFlowCharger;
  dataToSend.flowBatteryFlags = updatedFlowBattery;
  dataToSend.errorCode = updatedErrorCode;
  
  
  uio_sentPacket(dataToSend);

  return errorCode;
}