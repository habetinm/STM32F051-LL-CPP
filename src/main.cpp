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
    int x = 0;
    Timers timers;
    Timer* timer;
    //Class obj;
    Led3 led3(timer);


    SysTick_Config(SystemCoreClock / 1000);

    /* Enable clock for GPIOC */
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);

    /* Configure PC9 as output */
    LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_8, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_9, LL_GPIO_MODE_OUTPUT);

    /* Push-pull output */
    LL_GPIO_SetPinOutputType(GPIOC, LL_GPIO_PIN_9, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinOutputType(GPIOC, LL_GPIO_PIN_8, LL_GPIO_OUTPUT_PUSHPULL);

    /* No pull-up or pull-down */
    LL_GPIO_SetPinPull(GPIOC, LL_GPIO_PIN_9, LL_GPIO_PULL_NO);
    LL_GPIO_SetPinPull(GPIOC, LL_GPIO_PIN_8, LL_GPIO_PULL_NO);

    LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_9);
    LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_8);

    /* Enable clock for GPIOA */
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);

    /* Configure PA0 as input */
    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_0, LL_GPIO_MODE_INPUT);


    timer = timers.Get();
    timer->Init();
    timer->Set(100, &led3, Led3::Callback); // timer is for now just a fake context !!!
    timer->Start();

    while (1) {
        timers.Loop();

        //if (x++ >= 10000) {
        //    LL_GPIO_TogglePin(GPIOC, LL_GPIO_PIN_9);
        //    x = 0;
        //}

    }
}
