/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "main.h"

rtos::MemoryPool<message_t, 16> mpool;
rtos::Queue<message_t, 16> queue;
Thread thread;


int main(void)
{
    thread.start(callback(send_thread));

    while (true) {
        osEvent evt = queue.get();
        if (evt.status == osEventMessage) {
            message_t *message = (message_t *)evt.value.p;
            // message_t ** message;
            // if(queue.try_get(&message) == true) {
                printf("\nVoltage: %d V\n\r", message->voltage);
                printf("Current: %d A\n\r", message->current);
                printf("Number of cycles: %lu\n\r", message->counter);

                mpool.free(message);
            }
        // }
    }
}