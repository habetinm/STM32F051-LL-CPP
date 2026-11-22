#include "stm32f0xx.h"
#include "Timer.hpp"
#include "Led.hpp"
#include "Button.hpp"


int main(void) {
    int x = 0;
    Timers timers(&SysTickHandler::GetInstance());
    Timer* timer;
    Timer* timer2;
    Led3 led3(timer);
    Led4 led4(timer2);
    UserButton button(&SysTickHandler::GetInstance());

    timer = timers.Get();
    timer->Init();
    timer->Set(1000, &led3, Led3::Callback);
    timer->Start();

    timer2 = timers.Get();
    timer2->Init();
    timer2->Set(100, &led4, Led4::Callback);
    timer2->Start();

    while (1) {
        timers.Loop();
        button.Loop();

        if (!button.IsPressed()) {
            timer2->Pause();
        } else {
            timer2->Resume();
        }

    }
}
// 321730792/0300
