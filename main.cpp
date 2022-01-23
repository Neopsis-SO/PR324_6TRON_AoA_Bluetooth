/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"


// Blinking rate in milliseconds
#define BLINKING_RATE     500ms
#define UART_SLEEP  1000ms
#define BAUD_RATE   9600

BufferedSerial serial_port (UART1_TX, UART1_RX);
char buffer[256] = "First send with UART\n";
int bufferSize = 0;

int main()
{
    // Initialise the digital pin LED1 as an output
#ifdef LED1
    DigitalOut led(LED1);
#else
    bool led;
#endif

    // Initialise the serial communication
    serial_port.set_baud(BAUD_RATE);
    serial_port.set_format(
        /* bits */ 8,
        /* parity */ BufferedSerial::None,
        /* stop bit */ 1
    );

    printf("Lauched !\n");
    serial_port.write(buffer, sizeof(buffer));

    while (true) {
        
        serial_port.write(buffer, sizeof(buffer));
        if (uint32_t bufferSize = serial_port.read(buffer, sizeof(buffer))) {
            // Toggle the LED.
            led.write(!led);

            // Echo the input back to the terminal.
            serial_port.write(buffer, bufferSize);
        }
        ThisThread::sleep_for(UART_SLEEP);
    }
}
