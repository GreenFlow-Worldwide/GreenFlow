#ifndef _DECODED_DATA_H_ 
#define _DECODED_DATA_H_

char dd_getUpdatedFlowData(double * flowVolume, char * flowBatteryFlags, char * flowChargerFlags);
char dd_initDecodedData(UART_HandleTypeDef * uartHandler);

#endif