#ifndef DELAY_HPP_INCLUDED
#define DELAY_HPP_INCLUDED

#include "stm32f0xx.h"

class Delay {
public:
    Delay();
    uint8_t Interval(uint32_t interval_ms);
    void Loop();


private:
    uint32_t milliseconds;
    uint32_t last_ms;
    uint32_t delay_ms;
    uint8_t done;
};

#endif // DELAY_HPP_INCLUDED