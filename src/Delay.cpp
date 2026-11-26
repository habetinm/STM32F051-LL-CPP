#include "Delay.hpp"
#include "SysTickHandler.hpp"


Delay::Delay() :
    milliseconds(0),
    last_ms(0),
    delay_ms(0),
    done(0) {
}

uint8_t Delay::Interval(uint32_t interval_ms) {
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
    uint32_t curr_ms = SysTickHandler::GetInstance().GetMilliseconds();
    if (curr_ms - last_ms > delay_ms) {
        last_ms = curr_ms;
        done = 1;
    }
}
