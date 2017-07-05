#ifndef _BATTERY_CHECK_H_ 
#define _BATTERY_CHECK_H_
#include "stm32l0xx_hal.h"
uint8_t bc_getUpdatedHubBattery(uint8_t * batteryFlag);
uint8_t bc_initBatteryCheck(ADC_HandleTypeDef* batteryAdcHandler);

#endif