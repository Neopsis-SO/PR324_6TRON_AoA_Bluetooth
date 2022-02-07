/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "main.h"

#define   ESP8266_DEFAULT_BAUD_RATE   115200

rtos::MemoryPool<message_t, 16> mpool;
rtos::Queue<message_t, 16> queue;
Thread thread;

int main()
{
    BufferedSerial *_serial;
    ATCmdParser *_parser;

    printf("\nATCmdParser with ESP8266 example");

    thread.start(callback(send_thread));

    _serial = new BufferedSerial(UART1_TX, UART1_RX, ESP8266_DEFAULT_BAUD_RATE);
    _parser = new ATCmdParser(_serial, "\r\n");
    // _parser->set_delimiter(",");
    _parser->debug_on(false);
    // char cmdType[32];
    // char tmpChar[32];
    // char tmpChar2[32];
    // int rssi, azimut, elevation, rssi2 = 0;
    //Now get the FW version number of ESP8266 by sending an AT command
    printf("\nATCmdParser: Retrieving FW version");
    _parser->send("AT");
    // int version = 1;
    while(true)
    {
        message_t *message = mpool.try_alloc();
        if(_parser->recv("+UUDF:6C1DEBA42203,%d,%d,%d,%d", &message->rssi, &message->azimut, &message->elevation, &message->rssi2)) {
        // if (_parser->recv("AT")) {
            // printf("RSSI:%d, AZIMUT:%d, ELEVATION:%d, RSSI2:%d\n", message->rssi, message->azimut, message->elevation, message->rssi2);
            if(queue.try_put(message) == true) {}
                // printf("Message OK\n");
            // printf("\nATCmdParser: FW version: %d", version);
            // printf("\nATCmdParser: Retrieving FW version successful");
        } else {
            printf("\nATCmdParser: Retrieving FW version failed");
            // return -1;
        }
        // mpool.free(message);
    }
}

/*
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
*/