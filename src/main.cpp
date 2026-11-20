#include "stm32f0xx.h"
#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_gpio.h"
#include "SysTickHandler.hpp"
#include "Timer.hpp"
#include "Led.hpp"
#include "Button.hpp"
#include <string.h>
#include <stdio.h>


int main(void) {
    int x = 0;
    SysTickHandler* systck = &SysTickHandler::GetInstance();
    Timers timers(systck);
    Timer* timer;
    Timer* timer2;
    //Class obj;
    Led3 led3(timer);
    Led4 led4(timer2);
    Button button(systck);

    timer = timers.Get();
    timer->Init();
    timer->Set(1000, &led3, Led3::Callback); // timer is for now just a fake context !!!
    timer->Start();

    timer2 = timers.Get();
    timer2->Init();
    timer2->Set(100, &led4, Led4::Callback); // timer is for now just a fake context !!!
    timer2->Start();

    while (1) {
        timers.Loop();
        button.Loop();
        //timer2->Resume();
/*
        if (!button.IsPressed()) {
            timer2->Pause();
        } else {
            timer2->Resume();
        }
*/
    }
}
// 321730792/0300
