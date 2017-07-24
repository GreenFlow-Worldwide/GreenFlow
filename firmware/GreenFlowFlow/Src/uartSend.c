/*

In here will be the code to talk to the hub
will grab data from check errors and calclate volume 
only hit this c file when flag timer told main to go

all functions and file_wide variables will have prefix us
*/



#include "batteryCheck.h"
#include "chargerState.h"
#include "uartSend.h"
#include "uartIO.h"
#include "calcVolume.h"

uint8_t us_sendDataToFlow()
{
  //initalize variables
  uint8_t errorCode = 0;
  uint16_t updatedVolumeInTicks = 0;
  uint8_t updatedFlowCharger = 0xFF;
  uint8_t updatedFlowBattery = 0xFF;
  uint8_t updatedErrorCode = 0xCC;
  
  //grab flow information from increment and battery + charger
  errorCode = cs_getUpdatedHubCharger(&updatedFlowCharger);
  errorCode = bc_getUpdatedHubBattery(&updatedFlowBattery);
  errorCode = cv_getUpdatedFlowVolume(&updatedVolumeInTicks);
  
  //init struct that will be sent
  dataHandler dataToSend;
  
  dataToSend.volumeInTicks = updatedVolumeInTicks;
  dataToSend.flowChargerFlags = updatedFlowCharger;
  dataToSend.flowBatteryFlags = updatedFlowBattery;
  dataToSend.errorCode = updatedErrorCode;
  
  
  errorCode = uio_sentPacket(dataToSend);
  
  return errorCode;

}