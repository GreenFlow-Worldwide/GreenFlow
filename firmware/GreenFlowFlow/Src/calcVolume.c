/*

In here will be the code to calculate the total water output
should be one function call from UART to calcVolume

all functions and file_wide variables will have prefix cv
*/

#include "stdint.h"
#include "calcVolume.h"

uint8_t cv_getUpdatedFlowVolume(uint16_t * volumeInTicks)
{
  uint8_t errorCode = 0;
  
  * volumeInTicks = 5;
  
  return errorCode;
}