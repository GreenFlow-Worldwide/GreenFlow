#ifndef _UART_IO_H_ 
#define _UART_IO_H_
#include <stdbool.h>

#include <stdbool.h>

typedef struct
{
	uint32_t volumeInTicks;
	uint8_t flowChargerFlags;
	uint8_t flowBatteryFlags;
	uint8_t errorCode;
}__attribute__((__packed__)) dataHandler;

char uio_initUartIO(UART_HandleTypeDef * uartHandler);
char uio_getUartRawData(double *volume, char *flowChargerFlags, char *flowBatteryFlags, bool * newData);
char uio_sentPacket(dataHandler dataToSend);



#endif