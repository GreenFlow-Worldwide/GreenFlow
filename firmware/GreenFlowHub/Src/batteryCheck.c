/*
we will have be taking adc reading of the battery as well as 
dealing with battery reading from flow

all functions and file_wide variables will have prefix bc
*/
static char bc_batteryFlag;

//TODO: grab battery states and put them here to be decoded later.
char bc_checkBatteryStatus()
{
  char errorCode = 0;
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
