#include "Timer.hpp"

void Timer::Timer(Timers* timers) :
    timers(timers),
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

void Timer::Set(uint32_t interval_ms) {
    interval = interval_ms;
    time = timers->systick.GetMilliseconds();
    interval = interval_ms; 
    timer_cb = cb;
    used = 1;
}

void Timer::Loop() {
    if (used) {
        if (running) {
	    if ((timers->systick.getMilliseconds() - time) >= interval) {
	        time = timers->systick.GetMilliseconds();
		if (timer_cb != 0) {
		    timr_cb();
		}
	    }
	}
    }
}

uint8_t Timer::Paused() {
    return ~running;
}

Timers::Timers() {
    for (int i = 0; i < MAX_TIMERS; i++) {
        timer_array[i].timers = this;
    }
}

Timers::~Timers() {
    for (int i = 0; i < MAX_TIMERS; i++) {
        delete(timer_array[i]);
    }
}

Timer* Timers::Get() {
    for (int i = 0; i < MAX_TIMERS; i++) {
	if (!timer_array[i].used) {
	    timer_array[i].used = 1;
	    return timer_array[i];
	}
    }
}

void Timers::Loop() {
    for (int i = 0; i < MAX_TIMERS; i++) {
        timer_array[i].Loop();
/*
	if (timer_array[i].used) {
	    if (timer_array[i].running) {	
	        if ((systick.GetMiliseconds() - timer_array[i].time) >= timers_array[i].interval) {
	            timer_array[i].time = systick.GetMilliseconds();
	            if (timer_array[i].timer_cb != 0) {
	                timer_array[i].timer_cb();
	            }
	        }
	    }
	}
*/
    }
}
