/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

#include "UART/UART.h"

// Blinking rate in milliseconds
#define BLINKING_RATE     500ms

char buffer[256] = "First send with UART\n";
int bufferSize = 0;
int returnedValue = 0;

int main()
{
    // Initialise the digital pin LED1 as an output
#ifdef LED1
    DigitalOut led(LED1);
#else
    bool led;
#endif

    returnedValue = UARTInitialization();
    if(!returnedValue) {
        printf("UART lauched !\n");
    } else {
        printf("UART not lauched !\n");
    }
    serial_port.write(buffer, sizeof(buffer));

    while (true) {
        if (uint32_t bufferSize = serial_port.read(buffer, sizeof(buffer))) {
            // Toggle the LED.
            led.write(!led);

            // Echo the input back to the terminal.
            serial_port.write(buffer, bufferSize);
        }
        ThisThread::sleep_for(UART_SLEEP);
    }
}
