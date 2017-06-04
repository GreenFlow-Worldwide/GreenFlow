#ifndef _UART_IO_H_ 
#define _UART_IO_H_

char uio_initUartIO(UART_HandleTypeDef * uartHandler);
char uio_getUartRawData(double *volume, char *flowChargerFlags, char *flowBatteryFlags);

#endif