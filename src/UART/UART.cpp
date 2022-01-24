#include "UART.h"

BufferedSerial serial_port (UART1_TX, UART1_RX);

// Initialise the serial communication
int UARTInitialization (void)
{
    serial_port.set_baud(BAUD_RATE);
    serial_port.set_format(
        /* bits */ 8,
        /* parity */ BufferedSerial::None,
        /* stop bit */ 1
    );
    return 0;
}

void UART_Task()
{
    char buffer[256] = "First send with UART\n";
    int bufferSize = 0;
    int returnedValue = 0;

    // Initialise the digital pin LED1 as an output
    #ifdef LED1
        DigitalOut led(LED1);
    #else
        bool led;
    #endif

    returnedValue = UARTInitialization();
    if(!returnedValue) {
        printf("UART lauched !\n\r");
    } else {
        printf("UART not lauched !\n\r");
    }
    serial_port.write(buffer, sizeof(buffer));

    while(true)
    {
        if (uint32_t bufferSize = serial_port.read(buffer, sizeof(buffer))) {
            // Toggle the LED.
            led.write(!led);

            // Echo the input back to the terminal.
            serial_port.write(buffer, bufferSize);
        }
        ThisThread::sleep_for(UART_SLEEP);
    }
}