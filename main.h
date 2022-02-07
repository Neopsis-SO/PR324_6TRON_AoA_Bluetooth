#ifndef __MAIN_H__
#define __MAIN_H__

#include "mbed.h"

void send_thread(void);

typedef struct {
    int    rssi;   /* AD result of measured voltage */
    int    azimut;   /* AD result of measured current */
    int    elevation;   /* A counter value               */
    int    rssi2;
} message_t;

extern rtos::MemoryPool<message_t, 16> mpool;
extern rtos::Queue<message_t, 16> queue;

#endif