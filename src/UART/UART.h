#include "mbed.h"

#ifndef __UART_H__
#define __UART_H__

#define UART_SLEEP  1000ms
#define BAUD_RATE   115200

extern BufferedSerial serial_port;

int UARTInitialization (void);

#endif