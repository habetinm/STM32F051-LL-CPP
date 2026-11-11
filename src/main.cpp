#include "stm32f0xx.h"
#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_gpio.h"
#include "SysTickHandler.hpp"
#include "Timer.hpp"
#include <string.h>
#include <stdio.h>

typedef void (*TimerCb)(void);

int main(void) {
    Timers timers;
    Timer* timer;

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
    timer->Set(100, timer, TimerCb()); // timer is for now just a fake context !!!

    while (1) {
        timers.Loop();

    }
}
