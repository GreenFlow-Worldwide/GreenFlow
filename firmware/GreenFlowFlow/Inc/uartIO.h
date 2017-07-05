#ifndef _UART_IO_H_ 
#define _UART_IO_H_

#include "stm32l0xx_hal.h"

typedef struct
{
	uint16_t volumeInTicks;
	uint8_t flowChargerFlags;
	uint8_t flowBatteryFlags;
	uint8_t errorCode;
}__attribute__((__packed__)) dataHandler;

char uio_getUartRawData(double *volume, char *flowChargerFlags, char *flowBatteryFlags);
char uio_sentPacket();
char uio_initUartIO(UART_HandleTypeDef * uartHandler);



#endif