/*
we will have be dealing with changes in the LCD

all functions and file_wide variables will have prefix lcd
*/
#include "grabData.h"
#include "lcdControl.h"
#include "buttonStates.h"



//zero or initalize any variables here
char lcd_initLcdData()
{
  char errorCode = 0;
  char bs_initButtonStates();
  return errorCode;
}

char lcd_updateScreen(gd_lcdData displayData)
{
  char errorCode = 0;
  char buttonInput = 0;
  
  //look in buttonStates.h on this function
  errorCode = bs_getInputButtons(&buttonInput);
  //TODO for JP: update lcd in here with values from displayData and 
  //interupt flags from the push buttons
  return errorCode;
}