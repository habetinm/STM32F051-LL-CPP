#include "stm32f0xx.h"
#include "Timer.hpp"
#include "Led.hpp"
#include "Button.hpp"
#include "Uart.hpp"


int main(void) {
    Timers* timers = &Timers::GetInstance();
    Timer* timer = 0;
    Timer* timer2 = 0;
    Timer* timer3 = 0;
    Led3 led3;
    Led4 led4;
    UserButton button;
    UART_1 uart(115200);

    timer = timers->Get();
    timer->Init();
    timer->Set(1000, &led3, Led3::Callback);
    timer->Start();

    timer2 = timers->Get();
    timer2->Init();
    timer2->Set(100, &led4, Led4::Callback);
    timer2->Start();
/*
    timer3 = timers->Get();
    timer3->Init();
    led3.contextModif = 1;
    timer3->Set(2000, &led3, Led3::Callback);
    timer3->Start();
*/
    uart.WriteLine("Start");

    while (1) {
        timers->Loop();
        button.Loop();

        if (!button.IsPressed()) {
            timer2->Pause();
        } else {
            timer2->Resume();
        }

    }
}
// 321730792/0300
