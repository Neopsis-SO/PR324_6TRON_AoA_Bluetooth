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

void exit_if(int condition, const char *prefix)
{
    if (condition) {
        perror(prefix);
    }
}

int verif_trame(char * trame)
{
    char verif_t[5];
    strncpy(verif_t,trame,5);
    if( strcmp(verif_t,"+UUDF") == 0)
        return 0;        
    else
        return -1;
}

static char special_char = ',';


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
                    if(verif_trame(bufferReceived) != 0)
                    {
                        printf("Trame recue non conforme\n");
                        strncpy(bufferReceived,"\0",strlen(bufferReceived));
                    }
                    else
                    {
                        char rssi_pol1[NB_CHAR_SECT] = "\0";
                        char angle_azimuth[NB_CHAR_SECT] = "\0";
                        char angle_elevation[NB_CHAR_SECT] = "\0";
                        char rssi_pol2[NB_CHAR_SECT] = "\0";  
                        int j   = 0;
                        int k_1 = 0;
                        int k_2 = 0;
                        int k_3 = 0;
                        int k_4 = 0;
                        char p = bufferReceived[0];

                        for (int i = 0;  p != '\0' ; i++)
                        { 
                            p = bufferReceived[i];
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
                                        rssi_pol1[k_1] = bufferReceived[i];
                                        k_1++;
                                        break;
                                    case 2:
                                        angle_azimuth[k_2] = bufferReceived[i];
                                        k_2++;
                                        break;
                                    case 3:
                                        angle_elevation[k_3] = bufferReceived[i];
                                        k_3++;
                                        break;
                                    case 4:
                                        rssi_pol2[k_4] = bufferReceived[i];
                                        k_4++;
                                        break;
                                    default:
                                        break;
                                }
                            }
                        }
                        // Conversion and value assignment at the struct
                        if (j >= 4)
                        {
                            receivedUBLOXdata.rssi_pol1 = atoi(rssi_pol1);
                            receivedUBLOXdata.angle_azimuth = atoi(angle_azimuth);
                            receivedUBLOXdata.angle_elevation = atoi(angle_elevation);
                            receivedUBLOXdata.rssi_pol2 = atoi(rssi_pol2);

                            printf("%d, %d, %d, %d\n", receivedUBLOXdata.rssi_pol1, receivedUBLOXdata.angle_azimuth, receivedUBLOXdata.angle_elevation, receivedUBLOXdata.rssi_pol2);
                        }
                    }
                    bufferReceived[0] = '\0';
                    break;
                }
            }
        } else {
            ThisThread::sleep_for(10ms);
        }
    }
}