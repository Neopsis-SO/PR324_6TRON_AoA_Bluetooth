#include "mbed.h"
#include "UART.h"

BufferedSerial serial_port (UART1_TX, UART1_RX);
ATCmdParser at_cmd_parser(&serial_port, "\r\n");

// Initialise the serial communication
osStatus UART_TaskInit (void)
{
    serial_port.set_baud(UART_BAUD_RATE);
    serial_port.set_format(
        /* bits */ 8,
        /* parity */ BufferedSerial::None,
        /* stop bit */ 1
    );
    at_cmd_parser.debug_on(false);
    return osOK;
}


void UART_Task()
{
    // Initialise the digital pin LED1 as an output
    DigitalOut led(LED1);

    while(true)
    {
        UBLOX_Data *message = xUARTsharedMemory.try_alloc();
        if(message != NULL)
        {
            if(at_cmd_parser.recv("+UUDF:6C1DEBA42203,%d,%d,%d,%d", &message->rssi_pol1, &message->angle_azimuth, &message->angle_elevation, &message->rssi_pol2))
            {
                led = !led;
                // printf("RSSI:%d, AZIMUTH:%d, ELEVATION:%d, RSSI2:%d\n", message->rssi_pol1, message->angle_azimuth, message->angle_elevation, message->rssi_pol2);
                if(xUARTreceiveQueue.try_put(message) != true)
                {
                    printf("Error put xUARTreceiveQueue\n");
                }
            }
            else
            {
                printf("Timeout UBLOX received\n");
            }
        }
        else
        {
            printf("Error memory allocation\n");
        }
    }
}