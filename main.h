#ifndef __MAIN_H__
#define __MAIN_H__

#include "mbed.h"

void send_thread(void);

typedef struct {
    int    voltage;   /* AD result of measured voltage */
    int    current;   /* AD result of measured current */
    uint32_t counter;   /* A counter value               */
} message_t;

extern rtos::MemoryPool<message_t, 16> mpool;
extern rtos::Queue<message_t, 16> queue;

#endif