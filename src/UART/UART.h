#include "6TRON_AoA_Bluetooth.h"

#ifndef __UART_H__
#define __UART_H__

#define UART_TASK_PRIORITY      osPriorityNormal
#define UART_TASK_STACK_SIZE    OS_STACK_SIZE

#define UART_SLEEP_TASK  100ms
#define UART_BAUD_RATE   115200

void UART_Task();
osStatus UART_TaskInit (void);

#endif