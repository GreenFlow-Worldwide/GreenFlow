#include "incrementFlow.h"

int flowCount;

void initFlowCount()
{
  flowCount = 0;
}

void incrementFlowCount()
{
  ++flowCount;
  if(flowCount == 20){
    flowCount = 0;
  }
}