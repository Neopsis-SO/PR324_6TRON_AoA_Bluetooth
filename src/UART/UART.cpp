#include "UART.h"

BufferedSerial serial_port (UART1_TX, UART1_RX);

// Initialise the serial communication
osStatus UART_TaskInit (void)
{
    serial_port.set_baud(UART_BAUD_RATE);
    serial_port.set_format(
        /* bits */ 8,
        /* parity */ BufferedSerial::None,
        /* stop bit */ 1
    );
    return osOK;
}

// static UART_print()
// {
//     char buffer[64];
//     xUARTreceiveQueue.try_get(buffer);
//     printf("%s\n", buffer);
// }


void UART_Task()
{
    char buffer[128] = "AT";
    char buffer2[128];

    // Initialise the digital pin LED1 as an output
    #ifdef LED1
        DigitalOut led(LED1);
    #else
        bool led;
    #endif
    ThisThread::sleep_for(2000ms);
    serial_port.write(buffer, sizeof(buffer));
    printf("%s\n",buffer);
    // ThisThread::sleep_for(1000ms);
    // serial_port.read(buffer, sizeof(buffer));
    // printf("%s", buffer);


    while(true)
    {
        int i = 0;
        if(serial_port.readable())
        {
            while(serial_port.read(&buffer2[i++], 1))
            {
                led.write(!led);
                printf("%c", buffer2[i-1]); //With this line, the software is ok for slow and medium speed UBLOX communication
            }
            printf("i=%d\n", i);  // #warning : never go to this line because serial_port.read() never return 0, find why and a solution to find when all data has been received !
        } else {
            ThisThread::sleep_for(10ms);
        }
    }
}