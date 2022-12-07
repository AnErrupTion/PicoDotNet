#pragma once
#include <Lib/Types.h>
#include <HAL/Driver.h>

/// @brief Serial port identifier
typedef enum
{
    SERIAL_DISABLED = 0x000,
    SERIAL_COM1     = 0x3F8,
    SERIAL_COM2     = 0x2F8,
    SERIAL_COM3     = 0x3E8,
    SERIAL_COM4     = 0x2E8,
} SERIAL_PORT;

typedef struct
{
    PICO_Driver   driver;
    SERIAL_PORT port;
} PICO_SerialController;

/// @brief Start serial controller @param port Serial port identifier
bool PICO_StartSerial(PICO_SerialController* serial, SERIAL_PORT port);

/// @brief Stop serial controller
void PICO_StopSerial(PICO_SerialController* serial);

/// @brief Read character from active serial port
char PICO_SerialRead(PICO_SerialController* serial);

/// @brief Write character to active serial port @param c Character to write
void PICO_SerialWrite(PICO_SerialController* serial, char c);

/// @brief Write string to active serial port @param str Pointer of string to write
void PICO_SerialPrint(PICO_SerialController* serial, const char* str);

/// @brief Determine if serial port is available for reading @return Reading is allowed
bool PICO_SerialCanRead(PICO_SerialController* serial);

/// @brief Determine if serial port is available for writing @return Writing is allowed
bool PICO_SerialCanWrite(PICO_SerialController* serial);

/// @brief Check if serial identifier is valid @param port Serial port identifier @param allow_disabled Consider SERIAL_DISABLED to be a valid port @return Serial port identifier is valid
bool PICO_SerialValidatePort(SERIAL_PORT port, bool allow_disabled);

/// @brief Get active serial port @return Active serial port identifier
SERIAL_PORT PICO_GetSerialPort(PICO_SerialController* serial);

/// @brief Convert serial port identifier to its string representation @param port Serial port identifier @return Pointer to serial port name string
const char* PICO_SerialPortName(SERIAL_PORT port);