#ifndef _BATTERY_CHECK_H_ 
#define _BATTERY_CHECK_H_
//init function
void bs_initButtonStates();

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
*/
char bs_getInputButtons(char * buttonInput);

//interupt function flags
void bs_setNextButtonState();
void bs_setBackButtonState();
void bs_setDownButtonState();
void bs_setUpButtonState();

#endif