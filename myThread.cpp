#include "main.h"

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
            printf("Message OK\n");
        ThisThread::sleep_for(1s);
    }
}