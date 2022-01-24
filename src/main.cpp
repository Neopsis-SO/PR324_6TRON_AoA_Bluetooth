/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "6TRON_AoA_Bluetooth.h"

#include "UART/UART.h"


int main()
{
    rtos::Thread UART_TaskOS(UART_TASK_PRIORITY, UART_TASK_STACK_SIZE, NULL, NULL);
    if (UART_TaskOS.start(UART_Task) != osOK)
    {
        printf("UART OS start failed\n\r");
    } else {
        printf("UART OS start success\n\r");
    }


    while (true)
    {
        
        ThisThread::sleep_for(UART_SLEEP);
    }
}
