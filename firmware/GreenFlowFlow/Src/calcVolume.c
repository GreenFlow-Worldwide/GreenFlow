/*

In here will be the code to calculate the total water output
should be one function call from UART to calcVolume

all functions and file_wide variables will have prefix cv
*/

#include "stdint.h"
#include "calcVolume.h"

int valueTest = 1000; //TODO: REMOVE TEST LINE
uint8_t cv_getUpdatedFlowVolume(uint16_t * volumeInTicks)
{
  uint8_t errorCode = 0;
  valueTest += 100;
  //REMOVE TEST MATH
  *volumeInTicks = valueTest;
  
  return errorCode;
}