#include "stm32f0xx.h"
#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_gpio.h"
#include "SysTickHandler.hpp"
#include "Timer.hpp"
#include "Led.hpp"
#include <string.h>
#include <stdio.h>


int main(void) {
    int x = 0;
    Timers timers;
    Timer* timer;
    //Class obj;
    Led3 led3(timer);


    //SysTick_Config(SystemCoreClock / 1000);




    timer = timers.Get();
    timer->Init();
    timer->Set(400, &led3, Led3::Callback); // timer is for now just a fake context !!!
    timer->Start();

    while (1) {
        timers.Loop();
    }
}
