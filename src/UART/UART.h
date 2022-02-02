#ifndef __UART_H__
#define __UART_H__

#include "6TRON_AoA_Bluetooth.h"

#define UART_TASK_PRIORITY      osPriorityNormal
#define UART_TASK_STACK_SIZE    OS_STACK_SIZE

#define UART_SLEEP_TASK  10ms
#define UART_BAUD_RATE   115200

#define UART_BUFFER_SIZE    256

#define NB_CHAR_SECT 32
#define NB_CHAR_TRAME 256

void UART_Task();
osStatus UART_TaskInit (void);

#endif