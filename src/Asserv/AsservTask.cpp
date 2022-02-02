#include "AsservTask.h"

osStatus ASSERV_TaskInit (void)
{
    return osOK;
}

void ASSERV_Task()
{
    while(true)
    {
        printf("AsservTask launched\n");
        ThisThread::sleep_for(ASSERV_SLEEP_TASK);
    }

}