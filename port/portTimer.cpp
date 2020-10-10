#include "mbed.h"
#include "port.h"
#include "mbport.h"

static Timeout timeout;
static void timeoutHandle(void);
static std::chrono::microseconds interval;

BOOL    xMBPortTimersInit( USHORT usTimeOut50us )
{
    interval = std::chrono::microseconds(usTimeOut50us * 50);
    return TRUE;
}

void    xMBPortTimersClose( void )
{
    timeout.detach();
}

void    vMBPortTimersEnable( void )
{
    timeout.detach();
    timeout.attach(&timeoutHandle, interval);
}

void    vMBPortTimersDisable( void )
{
    timeout.detach();
}

void    vMBPortTimersDelay( USHORT usTimeOutMS )
{
    ThisThread::sleep_for(std::chrono::milliseconds(usTimeOutMS));
}

void timeoutHandle(void)
{
    (void) pxMBPortCBTimerExpired();
    timeout.detach();
}