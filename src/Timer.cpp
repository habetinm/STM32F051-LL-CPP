#include <cstdint>
#include "Timer.hpp"

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

void Timer::Set(uint32_t interval_ms, void* context, timer_cb cb) {
    interval = interval_ms;
    time = timers->systick.GetMilliseconds();
    interval = interval_ms; 
    context = context;
    callback = cb;
    used = 1;
}

void Timer::Loop() {
    if (used) {
        if (running) {
            if ((timers->systick.GetMilliseconds() - time) >= interval) {
                time = timers->systick.GetMilliseconds();
                if (callback != 0) {
                    callback(context);
                }
            }
        }
    }
}

//void Timer::SetCallback(void (*func)()) {
//    callback = func;
//}

uint8_t Timer::Paused() {
    return ~running;
}

Timers::Timers() {
    for (int i = 0; i < MAX_TIMERS; i++) {
        timer_array[i].timers = this;
    }
}

Timers::~Timers() {
}

Timer* Timers::Get() {
    for (int i = 0; i < MAX_TIMERS; i++) {
        if (!timer_array[i].used) {
            timer_array[i].used = 1;
            return &timer_array[i];
        }
    }
}

void Timers::Loop() {
    for (int i = 0; i < MAX_TIMERS; i++) {
        timer_array[i].Loop();
    }
}
