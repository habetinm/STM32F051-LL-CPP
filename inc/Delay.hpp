#ifndef DELAY_HPP_INCLUDED
#define DELAY_HPP_INCLUDED

#include "stm32f0xx.h"

class Delay {
public:
    static Delay& GetInstance();
    uint8_t Delay_ms(uint32_t interval_ms);
    void Loop();

private:
    Delay();
    Delay(const Delay&) = delete;
    Delay& operator=(const Delay&) = delete;

private:
    static Delay* instance;
    uint32_t milliseconds;
    uint32_t last_ms;
    uint32_t delay_ms;
    uint8_t done;

};

#endif // DELAY_HPP_INCLUDED