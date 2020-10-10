#include "mbed.h"
#include "port.h"
#include "mbport.h"

static UnbufferedSerial modbus_uart(
    MBED_CONF_FREEMODBUS_MODBUS_TX, 
    MBED_CONF_FREEMODBUS_MODBUS_RX,
    MBED_CONF_FREEMODBUS_MODBUS_BAUDRATE);

static void on_rx(void);
static void on_tx_empty(void);

BOOL    xMBPortSerialInit( UCHAR ucPort, ULONG ulBaudRate,
                            UCHAR ucDataBits, eMBParity eParity )
{
    (void)ucPort;
    mbed::SerialBase::Parity  parity;
    int stopbit = 1;

    switch (eParity) {
    case MB_PAR_ODD:
        parity = mbed::SerialBase::Odd;
        break;
    case MB_PAR_EVEN:
        parity = mbed::SerialBase::Even;
        break;
    case MB_PAR_NONE:
    default:
        parity = mbed::SerialBase::None;
        stopbit = 2;
    }

    modbus_uart.baud(ulBaudRate);
    modbus_uart.format(
        /* bits */      ucDataBits,
        /* parity */    parity,
        /* stop bit */  stopbit);

    modbus_uart.attach(on_rx, mbed::SerialBase::RxIrq);
    modbus_uart.attach(on_tx_empty, mbed::SerialBase::TxIrq);
    return TRUE;
}

void   vMBPortClose( void )
{
    modbus_uart.attach(NULL, mbed::SerialBase::RxIrq);
    modbus_uart.attach(NULL, mbed::SerialBase::TxIrq);
}

#if 0 
/* defininition in mbport.h, but always call vMBPortClose */
void    xMBPortSerialClose( void ) 
{
    modbus_uart.attach(NULL, mbed::SerialBase::RxIrq);
    modbus_uart.attach(NULL, mbed::SerialBase::TxIrq);
}
#endif

void    vMBPortSerialEnable( BOOL xRxEnable, BOOL xTxEnable )
{
    bool bRx = (xRxEnable == TRUE);
    bool bTx = (xTxEnable == TRUE);

    if (bRx)
        modbus_uart.attach(on_rx, mbed::SerialBase::RxIrq);
    else 
        modbus_uart.attach(NULL, mbed::SerialBase::RxIrq);

    if (bTx)
        modbus_uart.attach(on_tx_empty, mbed::SerialBase::TxIrq);
    else
        modbus_uart.attach(NULL, mbed::SerialBase::TxIrq);
}

BOOL    xMBPortSerialGetByte( CHAR * pucByte )
{
    CHAR t;
    modbus_uart.read(&t, sizeof(CHAR));
    *pucByte = t;
    return TRUE;
}

BOOL    xMBPortSerialPutByte( CHAR ucByte )
{
    modbus_uart.write(&ucByte, sizeof(UCHAR));
    return TRUE;
}

static void on_rx(void)
{
    vMBPortTimersDisable ();
    pxMBFrameCBByteReceived ();
}

static void on_tx_empty(void)
{
    (void) pxMBFrameCBTransmitterEmpty ();
}