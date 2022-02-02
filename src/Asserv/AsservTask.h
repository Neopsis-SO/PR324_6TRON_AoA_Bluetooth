#ifndef __ASSERV_TASK_H__
#define __ASSERV_TASK_H__

#include "6TRON_AoA_Bluetooth.h"

#define ASSERV_TASK_PRIORITY      osPriorityNormal
#define ASSERV_TASK_STACK_SIZE    OS_STACK_SIZE

#define ASSERV_SLEEP_TASK  1000ms

void ASSERV_Task();
osStatus ASSERV_TaskInit (void);

#endif