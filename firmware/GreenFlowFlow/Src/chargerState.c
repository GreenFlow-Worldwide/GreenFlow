/*
we will have be checking the charger state

all functions and file_wide variables will have prefix cs
*/
#include "chargerState.h"
#include "stdint.h"

static uint8_t cs_chargerFlag;

uint8_t cs_initChargerState()
{
  char errorCode = 0;
  cs_chargerFlag = 0;
  return errorCode;
}

//TODO: grab charger states and put them here to be decoded later.
uint8_t cs_checkChargerStatus()
{
  char errorCode = 0;
  cs_chargerFlag = 5;
  return errorCode;
}

uint8_t cs_getUpdatedHubCharger(uint8_t * chargerFlag)
{
  char errorCode = 0;
  //deal with error code now if possible
  errorCode = cs_checkChargerStatus();
  
  //return chargerFlag
  *chargerFlag = cs_chargerFlag;
  return errorCode;
}

