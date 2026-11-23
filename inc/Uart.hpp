#ifndef UART_HPP_INCLUDED
#define UART_HPP_INCLUDED
#include "stm32f0xx.h"

class Uart {
public:
    Uart() {};
    virtual void WriteLine(const char* text) = 0;
    virtual void WriteChar(char c) = 0;
    virtual void Write(const char* text) = 0;
};

class UART_1 : public Uart {
public:
    UART_1(uint32_t baudrate);
    void WriteLine(const char* text) override;
    void WriteChar(char c) override;
    void Write(const char* text) override;
};

#endif // UART_HPP_INCLUDED
