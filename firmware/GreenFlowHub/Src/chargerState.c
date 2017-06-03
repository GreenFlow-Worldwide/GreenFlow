/*
we will have be checking the charger state

all functions and file_wide variables will have prefix cs
*/

static char cs_chargerFlag;

//TODO: grab charger states and put them here to be decoded later.
char cs_checkChargerStatus()
{
  char errorCode = 0;
  cs_chargerFlag = 5;
  return errorCode;
}

char cs_getUpdatedHubCharger(char * chargerFlag)
{
  char errorCode = 0;
  //deal with error code now if possible
  errorCode = cs_checkChargerStatus();
  
  //return chargerFlag
  *chargerFlag = cs_chargerFlag;
  return errorCode;
}

