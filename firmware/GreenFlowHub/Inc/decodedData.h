#ifndef _DECODED_DATA_H_ 
#define _DECODED_DATA_H_
#include <stdbool.h>

char dd_getUpdatedFlowData(double * flowVolume, char * flowBatteryFlags, char * flowChargerFlags, bool * newData);
char dd_initDecodedData(UART_HandleTypeDef * uartHandler);

#endif