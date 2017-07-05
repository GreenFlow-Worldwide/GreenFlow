#ifndef _MAIN_THREAD_H_ 
#define _MAIN_THREAD_H_

char initMainThread(ADC_HandleTypeDef * batteryAdcHandler, UART_HandleTypeDef * uartHandler);

int mainThread();



#endif