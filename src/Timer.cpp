#include <cstdint>
#include <string.h>
#include "Timer.hpp"
#include "stm32f0xx.h"
#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_gpio.h"

Timer::Timer() {
}

Timer::Timer(Timers* timers) :
    timers(timers),
    context(0),
    running(0),
    used(0),
    interval(0),
    time(0) {
}

void Timer::Init() {
}

void Timer::Start() {
    running = 1;
}

void Timer::Pause() {
    running = 0;
}

void Timer::Resume() {
    running = 1;
}

void Timer::Set(uint32_t interval_ms, void* obj, timer_cb cb) {
    interval = interval_ms;
    time = timers->systick->GetMilliseconds();
    interval = interval_ms; 
    context = obj;
    callback = cb;
    used = 1;
}

void Timer::Loop() {
    if (used) {
        if (running) {
            if ((timers->systick->GetMilliseconds() - time) >= interval) {
                time = timers->systick->GetMilliseconds();
                if (context != 0) {
                    if (callback != 0) {
                        callback(context);
                    }
                }
            }
        }
    }
}

uint8_t Timer::Paused() {
    return ~running;
}

Timers::Timers(SysTickHandler* systck) : systick(systck) {
    memset((void*)timer_array, 0, sizeof(timer_array));
    for (int i = 0; i < MAX_TIMERS; i++) {
        timer_array[i].timers = this;
    }
}

Timers::~Timers() {
}

Timer* Timers::Get() {
    Timer* timer = 0;
    for (int i = 0; i < MAX_TIMERS; i++) {
        if (!timer_array[i].used) {
            //timer_array[i].used = 1;
            timer = &timer_array[i];
            break;
        }
    }
    return timer;
}

void Timers::Loop() {
    for (int i = 0; i < MAX_TIMERS; i++) {
        timer_array[i].Loop();
    }
}
