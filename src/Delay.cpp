#include <cstdint>
#include <string.h>
#include "Delay.hpp"
#include "SysTickHandler.hpp"


DelayPool* DelayPool::instance = nullptr;

DelayPool::DelayPool() {
    memset((void*)&delays[0], 0, sizeof(delays));
}

Delay* DelayPool::Get() {
    Delay* delay = 0;
    for (int i = 0; i < MAX_DELAYS; i++) {
        if (!delays[i].used) {
            delays[i].used = 1;
            delay = &delays[i];
            break;
        }
    }
    return delay;
}

void DelayPool::Loop() {
    for (int i = 0; i < MAX_DELAYS; i++) {
        delays[i].Loop();
    }
}

Delay::Delay() :
    last_ms(0),
    delay_ms(0),
    curr_ms(0),
    done(0),
    used(0) {
}

uint8_t Delay::Delay_ms(uint32_t interval_ms) {
    uint8_t ret = 0;
    delay_ms = interval_ms;
    if (done) {
        ret = 1;
        done = 0;
    } else {
        ret = 0;
    }

    return ret;
}

void Delay::Loop() {
    curr_ms = SysTickHandler::GetInstance().GetMilliseconds();
    if (curr_ms - last_ms > delay_ms) {
        last_ms = curr_ms;
        done = 1;
    }
}

DelayPool& DelayPool::GetInstance()
{
    static DelayPool instance;
    return instance;
}