/*
we will have be taking input from push buttons.

all functions and file_wide variables will have prefix bs
*/

#include "buttonStates.h"
#include "stdbool.h"


//initalize buttons to be used in this program
static bool bs_backState;
static bool bs_upState;
static bool bs_downState;
static bool bs_nextState;


//set all button states to low
void bs_setButtonStatesLow()
{
  bs_backState = false;
  bs_upState = false;
  bs_downState = false;
  bs_nextState = false;
}

/*returns button input
 * 0x01 is back
 * 0x02 is down
 * 0x04 is up
 * 0x08 is next
 * This function checks for multiple button presses 
 * - if next and back are both pressed, everything is discarded
 * - if either next or back are pressed and any directions are pressed
 *   no directions will be used, only back or next is returned
 * - if back or next has not been pressed and both up and down
 *   has been pressed, ignore input
 * - will go up or down if one of them has been pressed
 * ------Not a pretty function, but is robust--------
 */
char bs_getInputButtons(char * buttonInput)
{
  char errorCode = 0;
  //if no button states are high, return right away
  if(!(bs_backState || bs_upState || bs_downState || bs_nextState))
  {
    return errorCode;
  }
  
  //if both next and back are high, set everything to zero, return and do nothing
  if(bs_backState & bs_nextState)
  {
    bs_setButtonStatesLow();
    return errorCode;
  }
  
  //take in back state and return value 0x01
  if(bs_backState)
  {
    bs_setButtonStatesLow();
    *buttonInput = 0x01;
    return errorCode;
  }
  //take in next state and return value of 0x08
  if(bs_nextState)
  {
    bs_setButtonStatesLow();
    *buttonInput = 0x08;
    return errorCode;
  }
  
  //both up and down pressed at the same time, return and do nothing
  if(bs_upState & bs_downState)
  {
    bs_setButtonStatesLow();
    return errorCode;
  }
  
  //take in up state and return value of 0x04
  if(bs_upState)
  {
    bs_setButtonStatesLow();
    *buttonInput = 0x04;
    return errorCode;
  }
  
    //take in down state and return value of 0x02
  if(bs_downState)
  {
    bs_setButtonStatesLow();
    *buttonInput = 0x02;
    return errorCode;
  }
  
  //TODO: something unexpected happened, return an error, probably need reset
  errorCode = 1;
  return errorCode;
}



//set all states to false and init any other firmware
void bs_initButtonStates()
{
  bs_setButtonStatesLow();
}

/* NEXT 4 FUNCTIONS ONLY CALLED BY INTERUPTS*/
//set up button to high
void bs_setUpButtonState()
{
  bs_upState = true;
}

//set down button to high
void bs_setDownButtonState()
{
  bs_downState = true;
}

//set back button to high
void bs_setBackButtonState()
{
  bs_backState = true;
}

//set Next Button to high
void bs_setNextButtonState()
{
  bs_nextState = true;
}