#include "stm32f0xx.h"
#include "Timer.hpp"
#include "Led.hpp"
#include "Button.hpp"
#include "Uart.hpp"
#include "Delay.hpp"


int main(void) {
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
    Delay* delay = DelayPool::GetInstance().Get();
    Delay* delay2 = DelayPool::GetInstance().Get();

    timer = Timers::GetInstance().Get();
    timer->Init();
    timer->Set(1000, &led3, Led3::Callback);
    timer->Start();

    timer2 = Timers::GetInstance().Get();
    timer2->Init();
    timer2->Set(50, &led4, Led4::Callback);
    timer2->Start();

    timer3 = Timers::GetInstance().Get();
    timer3->Init();
    timer3->Set(2100, &led3, Led3::Callback);
    timer3->Start();

    timer4 = Timers::GetInstance().Get();
    timer4->Init();
    timer4->Set(2200, &led3, Led3::Callback);
    timer4->Start();

    timer5 = Timers::GetInstance().Get();
    timer5->Init();
    timer5->Set(2300, &led3, Led3::Callback);
    timer5->Start();

    timer6 = Timers::GetInstance().Get();
    timer6->Init();
    timer6->Set(2400, &led3, Led3::Callback);
    timer6->Start();

    uart.WriteLine("Start");

    while (1) {
        Timers::GetInstance().Loop();
        button.Loop();
        DelayPool::GetInstance().Loop();

        //if (delay->Delay_ms(500)) {
        //    led4.Toggle();
          
            if (!button.IsPressed()) {
                 timer2->Pause();
            } else {
                timer2->Resume();
            }
        //}

        //if (delay2->Delay_ms(200)) {
        //    led3.Toggle();
        //}
    }
}
// 321730792/0300
