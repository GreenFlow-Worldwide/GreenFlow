/*
  where our main loop will live
  will have 2 functions

  int initMainThread() which will return an error code
  int mainThread() which returns an error code
  


*/

#include "lcdControl.h"
#include "grabData.h"
#include "stdint.h"
//#include "wifi.h"    //TODO future work

static gd_lcdData displayData;

char initMainThread()
{
  char errorCode = 0;
  
  displayData.volume = 0;
  displayData.flowFlags = 0;
  displayData.hubCharger = 0;
  displayData.hubBattery = 0;
  
  return errorCode;
}

char mainThread()
{
  char errorCode = 0;
  //Check For New Data with this function
  errorCode = gd_getDisplayData(&displayData);
  
  //give updated data to lcd to update screen
  errorCode = lcd_updateScreen(displayData);
  return errorCode;
}