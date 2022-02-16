/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "6TRON_AoA_Bluetooth.h"
#include "UART/UART.h"
#include "Asserv.h"
#include "AsservTask.h"

rtos::MemoryPool<UBLOX_Data, 32> xUARTsharedMemory;
rtos::Queue<UBLOX_Data, 32> xUARTreceiveQueue;
rtos::Semaphore xSemaphoreAsserv(1);

UBLOX_Data globalMessageUBLOX;

int main()
{   
    float distance_lisse_tab[15];
    float distance_lisse;
    float distance_lisse_tab2[15];
    float distance_lisse2;
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
        osEvent evt = xUARTreceiveQueue.get();
        if (evt.status == osEventMessage) {
            UBLOX_Data* messageUBLOX = (UBLOX_Data*)evt.value.p;
            // printf("Received message -> RSSI:%d, AZIMUTH:%d, ELEVATION:%d, RSSI2:%d\n", messageUBLOX->rssi_pol1, messageUBLOX->angle_azimuth, messageUBLOX->angle_elevation, messageUBLOX->rssi_pol2);
            xSemaphoreAsserv.acquire();
            messageUBLOX->rssi_pol1 ;//=lissage(messageUBLOX->rssi_pol1,distance_lisse_tab,15);
            messageUBLOX->rssi_pol2 ;//=lissage(messageUBLOX->rssi_pol2,distance_lisse_tab2,15);

            globalMessageUBLOX = *messageUBLOX;
            xSemaphoreAsserv.release();
            // printf("Copied message -> RSSI:%d, AZIMUTH:%d, ELEVATION:%d, RSSI2:%d\n", globalMessageUBLOX.rssi_pol1, globalMessageUBLOX.angle_azimuth, globalMessageUBLOX.angle_elevation, globalMessageUBLOX.rssi_pol2);
            xUARTsharedMemory.free(messageUBLOX);
        }
        // ThisThread::sleep_for(5s);
    }
}
