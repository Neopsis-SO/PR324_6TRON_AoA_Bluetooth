/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

typedef struct {
    int    voltage;   /* AD result of measured voltage */
    int    current;   /* AD result of measured current */
    uint32_t counter;   /* A counter value               */
} message_t;

MemoryPool<message_t, 16> mpool;
rtos::Queue<message_t, 16> queue;
Thread thread;

/* Send Thread */
void send_thread(void)
{
    uint32_t i = 0;
    while (true) {
        i++; // fake data update
        message_t *message = mpool.try_alloc();
        message->voltage = i + 1;
        message->current = i + 2;
        message->counter = i;
        if(queue.try_put(message) == true)
        //     printf("Message OK\n");
        ThisThread::sleep_for(1s);
    }
}

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