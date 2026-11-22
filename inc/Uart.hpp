#ifndef UART_HPP_INCLUDED
#define UART_HPP_INCLUDED
#include "stm32f0xx.h"

class Uart {
public:
    Uart(uint32_t baudrate) {};
    void Init(uint32_t baudrate) {};
    void WriteLine(const char* text) {};
    void WriteChar(char c) {};
    void Write(const char* text) {};
};

class UART_1 : public Uart {
public:
    UART_1(uint32_t baudrate);
    void Init(uint32_t baudrate);
    void WriteLine(const char* text);
    void WriteChar(char c);
    void Write(const char* text);
};

#endif // UART_HPP_INCLUDED
