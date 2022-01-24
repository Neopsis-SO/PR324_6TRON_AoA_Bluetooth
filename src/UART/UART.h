#include "6TRON_AoA_Bluetooth.h"

#ifndef __UART_H__
#define __UART_H__

#define UART_TASK_PRIORITY      osPriorityNormal
#define UART_TASK_STACK_SIZE    OS_STACK_SIZE

#define UART_SLEEP  1000ms
#define BAUD_RATE   115200

extern BufferedSerial serial_port;

void UART_Task();
int UARTInitialization (void);

#endif