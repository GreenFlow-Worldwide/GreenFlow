#ifndef _BATTERY_CHECK_H_ 
#define _BATTERY_CHECK_H_

char bc_getUpdatedHubBattery(char * batteryFlag);
char bc_initBatteryCheck(ADC_HandleTypeDef* batteryAdcHandler);

#endif