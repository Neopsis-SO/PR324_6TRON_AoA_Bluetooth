#include "6TRON_AoA_Bluetooth.h"
#include "UART/UART.h"

int init_main(void)
{
    osStatus returnedValue = osOK;  // Init status (osOK if all good or osError if one error)

    //UART Initialization
    if(UART_TaskInit() != osOK) {
        printf("UART initialization FAILED !\n");
        returnedValue = osError;
    } else {
        printf("UART initialization SUCCESS !\n");
    }

    //Return the global initialization status
    return returnedValue;
}