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
    Timer* timer4 = 0;
    Timer* timer5 = 0;
    Timer* timer6 = 0;
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

    timer3 = timers->Get();
    timer3->Init();
    timer3->Set(2100, &led3, Led3::Callback);
    timer3->Start();

    timer4 = timers->Get();
    timer4->Init();
    timer4->Set(2200, &led3, Led3::Callback);
    timer4->Start();

    timer5 = timers->Get();
    timer5->Init();
    timer5->Set(2300, &led3, Led3::Callback);
    timer5->Start();

    timer6 = timers->Get();
    timer6->Init();
    timer6->Set(2400, &led3, Led3::Callback);
    timer6->Start();

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
