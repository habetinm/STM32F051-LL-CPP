#ifndef DELAY_HPP_INCLUDED
#define DELAY_HPP_INCLUDED

#include "stm32f0xx.h"


class Delay {
    friend class DelayPool;

public:
    Delay();
    uint8_t Delay_ms(uint32_t interval_ms);
    void Loop();

private:
    uint32_t last_ms;
    uint32_t delay_ms;
    uint32_t curr_ms;
    uint8_t done;
    uint8_t used;
};

class DelayPool {
private:
    static constexpr uint8_t MAX_DELAYS = 10;

public:
    static DelayPool& GetInstance();
    Delay* Get();
    void Loop();

private:
    DelayPool();
    DelayPool(const DelayPool&) = delete;
    DelayPool& operator=(const DelayPool&) = delete;

private:
    static DelayPool* instance;
    Delay delays[MAX_DELAYS];
};



#endif // DELAY_HPP_INCLUDED