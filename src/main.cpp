#include "stm32f0xx.h"
#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_gpio.h"
#include "SysTickHandler.hpp"
#include "Timer.hpp"
#include "Led.hpp"
#include <string.h>
#include <stdio.h>

//typedef void (*TimerCb)(void);
/*
class Class {
public:
    Class() {

    };

    static void Callback(void) {

    };
};
*/

int main(void) {
    Timers timers;
    Timer* timer;
    //Class obj;
    Led3 led3;

    timer = timers.Get();
    timer->Init();
    timer->Set(100, &led3, Led3::Callback); // timer is for now just a fake context !!!
    timer->Start();

    while (1) {
        timers.Loop();

    }
}
