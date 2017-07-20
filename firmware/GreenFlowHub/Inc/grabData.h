#ifndef _GRAB_DATA_H_
#define _GRAB_DATA_H_

//include to remove error of ADC_HandelTypeDef in this file
#include "stm32l0xx_hal.h"
#include <stdbool.h>


typedef struct
{
	double currentVolumeInLiters;
	double totalVolumeInLiters;
	char flowChargerFlags;
	char flowBatteryFlags;
	char hubCharger;
	char hubBattery;
}gd_lcdData;

char gd_getDisplayData(gd_lcdData * displayData, bool * newPacket);
char gd_initGrabData(ADC_HandleTypeDef * batteryAdcHandler, UART_HandleTypeDef * uartHandler);

#endif