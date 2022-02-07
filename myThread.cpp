#include "main.h"

#define   ESP8266_DEFAULT_BAUD_RATE   115200

/* Send Thread */
void send_thread(void)
{
    uint32_t i = 0;
    while (true) {
        // i++; // fake data update
        // message_t *message = mpool.try_alloc();
        // message->rssi = i + 1;
        // message->current = i + 2;
        // message->counter = i;
        // if(queue.try_put(message) == true)
        //     printf("Message OK\n");
        osEvent evt = queue.get();
        if (evt.status == osEventMessage) {
            message_t *message = (message_t *)evt.value.p;
            // printf("\nRSSI:%d, AZIMUT:%d, ELEVATION:%d, RSSI2:%d\n", message->rssi, message->azimut, message->elevation, message->rssi2);
            mpool.free(message);
        }
        // ThisThread::sleep_for(1s);
    }
}