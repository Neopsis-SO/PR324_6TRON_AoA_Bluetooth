/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "6TRON_AoA_Bluetooth.h"
#include "UART/UART.h"
#include "Asserv/AsservTask.h"

rtos::MemoryPool<UBLOX_Data, 32> xUARTsharedMemory;
rtos::Queue<UBLOX_Data, 32> xUARTreceiveQueue;
rtos::Semaphore xSemaphoreAsserv(1);

int main()
{
    // System initialization
    if (init_main() != osOK) {
        printf("Initialization FAILED\n");
    } else {
        printf("Initialization SUCCESS\n");
    }

    // UART Thread lauch
    rtos::Thread UART_TaskOS(UART_TASK_PRIORITY, UART_TASK_STACK_SIZE, NULL, NULL);
    rtos::Thread ASSERV_TaskOS(ASSERV_TASK_PRIORITY, ASSERV_TASK_STACK_SIZE, NULL, NULL);

    if (UART_TaskOS.start(UART_Task) != osOK) {
        printf("UART Task starting FAILED\n");
    } else {
        printf("UART Task starting SUCCESS\n");
    }

    if (ASSERV_TaskOS.start(ASSERV_Task) != osOK) {
        printf("ASSERV Task starting FAILED\n");
    } else {
        printf("ASSERV Task starting SUCCESS\n");
    }

    while (true)
    {
        // printf("I'm alive\n");
        ThisThread::sleep_for(5s);
    }
}
