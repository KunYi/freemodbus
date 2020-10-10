
#include "mbed.h"
#include "port.h"
#include "mbport.h"

static Queue<eMBEventType, 8> queue;

BOOL    xMBPortEventInit( void )
{
    return TRUE;
}

BOOL    xMBPortEventPost( eMBEventType eEvent )
{
    return queue.try_put(&eEvent) ? TRUE : FALSE;
}

BOOL    xMBPortEventGet(  /*@out@ */ eMBEventType * eEvent )
{
    return queue.try_get(&eEvent) ? TRUE : FALSE;
}