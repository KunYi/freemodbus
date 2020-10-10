#include "mbed.h"
#include "port.h"

static Mutex mb_mutex;

void vMBPortEnterCritical(void)
{
    mb_mutex.lock();
}

void vMBPortExitCritical(void)
{
    mb_mutex.unlock();
}
