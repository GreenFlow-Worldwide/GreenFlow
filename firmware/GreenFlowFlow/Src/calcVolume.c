/*

In here will be the code to calculate the total water output
should be one function call from UART to calcVolume

all functions and file_wide variables will have prefix cv
*/

#include "stdint.h"
#include "calcVolume.h"
#include "flagTimer.h"


int32_t flowCount;
int32_t flowCountOld;

void cv_initFlowCount()
{
    flowCount = 0;
    flowCountOld = 0;
}

void cv_incrementFlowCount()
{
    ++flowCount;

}

uint8_t cv_getUpdatedFlowVolume(uint16_t * volumeInTicks)
{
    uint8_t errorCode = 0;
    bool newVolumeRecorded = false;
    bool resetVolume = false;
    //have a very low threshold to reset values 
    if((flowCount - flowCountOld) < 5)
    {
      newVolumeRecorded = false;
    }else
    {
      newVolumeRecorded = true;
    }
    //update old flow count to compare to next time around
    flowCountOld = flowCount;
  
    //if no new data has been sent out in a while, reset the value.
    errorCode = ft_checkResetVolumeFlag(newVolumeRecorded, &resetVolume);
    if(resetVolume)
    {
      flowCount = 0;
    }
  
    *volumeInTicks = flowCount;
    
    return errorCode;
}