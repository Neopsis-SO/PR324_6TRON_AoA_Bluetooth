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