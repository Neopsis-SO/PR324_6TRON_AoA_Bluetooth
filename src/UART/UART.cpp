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
//     char bufferSend[64];
//     xUARTreceiveQueue.try_get(bufferSend);
//     printf("%s\n", bufferSend);
// }


static char special_char = ',';

// Extract data from a frame
void extract_data(char *trame, UBLOX_Data *Data)
{
    static char rssi_pol1[NB_CHAR_SECT] = "0\0";
    static char angle_azimuth[NB_CHAR_SECT] = "0\n";
    static char angle_elevation[NB_CHAR_SECT] = "0\n";
    static char rssi_pol2[NB_CHAR_SECT] = "0\n";  
    int j = 0;
    // int k_0 = 0;
    int k_1 = 0;
    int k_2 = 0;
    int k_3 = 0;
    int k_4 = 0;
    char p = trame[0];

    // Loop to sweep a frame 
    for (int i = 0;  p != '\0' ; i++)
    { 
        p = trame[i];
        if(j == 4)
        {
            break;
        }
        // Comparaison to find delimiter character
        if (p == special_char)
        {
            j++;                           
        } 
        else 
        {
            // Separation of usefull informations
            switch(j)
            {
                case 1:
                    rssi_pol1[k_1] = trame[i];
                    k_1++;
                    break;
                case 2:
                    angle_azimuth[k_2] = trame[i];
                    k_2++;
                    break;
                case 3:
                    angle_elevation[k_3] = trame[i];
                    k_3++;
                    break;
                case 4:
                    rssi_pol2[k_4] = trame[i];
                    k_4++;
                    break;
                default :
                    break;
            }
        }
    }
    // Conversion and value assignment at the struct
    if(j >= 4)
    {
        // Data->rssi_pol1 = atoi(rssi_pol1);
        // Data->angle_azimuth = atoi(angle_azimuth);
        // Data->angle_elevation = atoi(angle_elevation);
        // Data->rssi_pol2 = atoi(rssi_pol2);
    }
}

void UART_Task()
{
    char bufferSend[UART_BUFFER_SIZE] = "\0";
    char bufferReceived[UART_BUFFER_SIZE] = "\0";
    UBLOX_Data receivedUBLOXdata;

    // Initialise the digital pin LED1 as an output
    #ifdef LED1
        DigitalOut led(LED1);
    #else
        bool led;
    #endif
    ThisThread::sleep_for(2000ms);
    serial_port.write(bufferSend, sizeof(bufferSend));
    printf("%s\n",bufferSend);
    // ThisThread::sleep_for(1000ms);
    // serial_port.read(bufferSend, sizeof(bufferSend));
    // printf("%s", bufferSend);


    while(true)
    {
        char c;
        int i = 0;
        if(serial_port.readable())
        {
            while(serial_port.read(&c, 1))
            {
                strcat(bufferReceived, &c);
                i++;
                if(!strcmp(&c, "\n"))
                {
                    led.write(!led);
                    bufferReceived[i-1] = '\0';
                    printf("%s\n", bufferReceived);
                    extract_data(bufferReceived, &receivedUBLOXdata);
                    // sscanf(bufferReceived, "%*:%s,%d,%d,%d,%d,%*", id, &rssi, &azimut, &elevation, &rssi2);
                    // printf("%d, %d, %d, %d\n", rssi, azimut, elevation, rssi2);
                    // printf("%d, %d, %d, %d\n", receivedUBLOXdata.rssi_pol1, receivedUBLOXdata.angle_azimuth, receivedUBLOXdata.angle_elevation, receivedUBLOXdata.rssi_pol2);
                    bufferReceived[0] = '\0';
                    break;
                }
                // printf("%c", bufferReceived[i-1]); //With this line, the software is ok for slow and medium speed UBLOX communication
            }
            // printf("i=%d\n", i);  // #warning : never go to this line because serial_port.read() never return 0, find why and a solution to find when all data has been received !
        } else {
            ThisThread::sleep_for(10ms);
        }
    }
}