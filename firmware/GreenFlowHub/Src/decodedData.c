/*
we will have be taking input from UART I/O and decoding it here

all functions and file_wide variables will have prefix dd
*/

#include "uartIO.h"
#include "decodedData.h"

static double dd_currentVolume;
static char dd_currentFlags;

void dd_zeroDecodedData()
{
  //TODO: uart zero
  dd_currentVolume = 0;
  dd_currentFlags = 0;
}

char dd_decodeData()
{
  char errorCode = 0;
  dd_currentVolume = 3; 
  dd_currentFlags = 1;
  return errorCode;
}

//grab volume and applicable flags to display on LCD
char dd_getUpdatedFlowData(double * flowVolume, char * flowFlags)
{
  char errorCode = 0;
  errorCode = dd_decodeData();
  
  //return values passed in by reference with current values
  *flowVolume = dd_currentVolume;
  *flowFlags = dd_currentFlags;
  return errorCode;
}

