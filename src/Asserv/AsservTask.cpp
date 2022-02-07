#include "AsservTask.h"

UBLOX_Data localMessageUBLOX;

osStatus ASSERV_TaskInit (void)
{
    return osOK;
}

void ASSERV_Task()
{
    while(true)
    {
        // printf("AsservTask launched\n");
        osEvent evt = xUARTreceiveQueue.get();
        if (evt.status == osEventMessage) {
            UBLOX_Data* messageUBLOX = (UBLOX_Data*)evt.value.p;
            printf("Received message -> RSSI:%d, AZIMUTH:%d, ELEVATION:%d, RSSI2:%d\n", messageUBLOX->rssi_pol1, messageUBLOX->angle_azimuth, messageUBLOX->angle_elevation, messageUBLOX->rssi_pol2);
            xSemaphoreAsserv.acquire();
            localMessageUBLOX = *messageUBLOX;
            xSemaphoreAsserv.release();
            printf("Copied message -> RSSI:%d, AZIMUTH:%d, ELEVATION:%d, RSSI2:%d\n", localMessageUBLOX.rssi_pol1, localMessageUBLOX.angle_azimuth, localMessageUBLOX.angle_elevation, localMessageUBLOX.rssi_pol2);
            xUARTsharedMemory.free(messageUBLOX);
        }
        ThisThread::sleep_for(ASSERV_SLEEP_TASK);
    }

}