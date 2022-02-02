#ifndef __6TRON_AOA_BLUETOOTH_H__
#define __6TRON_AOA_BLUETOOTH_H__

#include "mbed.h"
#include "rtos.h"

int init_main(void);

// rtos::Queue<char[64], 8> xUARTreceiveQueue();

// Store data collect from UBLOX-C211
typedef struct {
    int rssi_pol1;
    int angle_azimuth;
    int angle_elevation;
    int rssi_pol2;
} UBLOX_Data;

#endif