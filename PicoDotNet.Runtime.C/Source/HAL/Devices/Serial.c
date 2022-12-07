#include <HAL/Devices/Serial.h>
#include <Core/Common.h>

static const char* _portnames[5] = { "disabled", "com1", "com2", "com3", "com4" };
static SERIAL_PORT _port         = SERIAL_DISABLED;

bool PICO_StartSerial(PICO_SerialController* serial, SERIAL_PORT port)
{
    // validate port
    if (!PICO_SerialValidatePort(port, true)) { return false; }
    if (port == SERIAL_DISABLED) { PICO_StopSerial(serial); return false; }

    // set serial port and send information to serial controller
    _port = port;
    PICO_PortOutb(_port + 1, 0x00);      // disable all interrupts
    PICO_PortOutb(_port + 3, 0x80);      // set baud rate divisor
    PICO_PortOutb(_port + 0, 0x03);      // set divisor to 3 (lo uint8_t) 38400 baud
    PICO_PortOutb(_port + 1, 0x00);      // hi uint8_t
    PICO_PortOutb(_port + 3, 0x03);      // 8 bits, no parity, one stop bit
    PICO_PortOutb(_port + 2, 0xC7);      // enable fifo, clear them, with 14-uint8_t threshold
    PICO_PortOutb(_port + 4, 0x0B);      // irqs enabled, rts/dsr set
    PICO_PortOutb(_port + 4, 0x1E);      // set in loopback mode, test the serial chip
    PICO_PortOutb(_port + 0, 0xAE);      // test serial chip (send uint8_t 0xAE and check if serial returns same uint8_t)

    // serial initialization failed - stop device
    if (PICO_PortInb(_port) != 0xAE) { PICO_StopSerial(serial); return false; }

    // stop testing chip
    PICO_PortOutb(_port + 4, 0x0F);
    return true;
}

void PICO_StopSerial(PICO_SerialController* serial)
{
    _port = SERIAL_DISABLED;
}

char PICO_SerialRead(PICO_SerialController* serial)
{
    if (!PICO_SerialValidatePort(_port, false)) { return 0; }
    while (!PICO_SerialCanRead(serial));
    return PICO_PortInb(_port);
}

void PICO_SerialWrite(PICO_SerialController* serial, char c)
{
    if (!PICO_SerialValidatePort(_port, false)) { return; }
    while (!PICO_SerialCanWrite(serial));
    PICO_PortOutb(_port, c);
}

void PICO_SerialPrint(PICO_SerialController* serial, const char* str)
{
    if (str == NULL || PICO_StrLen(str) == 0) { return; }

    register int i = 0;
    while (str[i] != 0) { PICO_SerialWrite(serial, str[i++]); }
}

bool PICO_SerialCanRead(PICO_SerialController* serial) { return PICO_PortInb(_port + 5) & 0x01; }

bool PICO_SerialCanWrite(PICO_SerialController* serial) { return PICO_PortInb(_port + 5) & 0x20; }

bool PICO_SerialValidatePort(SERIAL_PORT port, bool allow_disabled)
{
    switch (port)
    {
        case SERIAL_COM1: 
        case SERIAL_COM2: 
        case SERIAL_COM3: 
        case SERIAL_COM4:     { return true; }
        case SERIAL_DISABLED: { return allow_disabled; }
    }
    return false;
}

SERIAL_PORT PICO_GetSerialPort(PICO_SerialController* serial) { return _port; }

const char* PICO_SerialPortName(SERIAL_PORT port)
{
    switch (port)
    {
        default:          { return _portnames[0]; }
        case SERIAL_COM1: { return _portnames[1]; }
        case SERIAL_COM2: { return _portnames[2]; }
        case SERIAL_COM3: { return _portnames[3]; }
        case SERIAL_COM4: { return _portnames[4]; }
    }
}