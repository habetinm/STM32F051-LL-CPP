#include "stm32f0xx.h"
#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_gpio.h"
#include "SysTickHandler.hpp"
#include "Timer.hpp"
#include "Led.hpp"
#include <string.h>
#include <stdio.h>

Led::Led(Timer* timer) : timer(timer) {

}

void Led::Callback(void* context) {
    Led* led = static_cast<Led*>(context);
    led->Toggle();
}

Led3::Led3(Timer* timer) : Led(timer) {
    /* Enable clock for GPIOC */
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);

    /* Configure PC9 as output */
    LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_9, LL_GPIO_MODE_OUTPUT);

    /* Push-pull output */
    LL_GPIO_SetPinOutputType(GPIOC, LL_GPIO_PIN_9, LL_GPIO_OUTPUT_PUSHPULL);

    /* No pull-up or pull-down */
    LL_GPIO_SetPinPull(GPIOC, LL_GPIO_PIN_9, LL_GPIO_PULL_NO);

    LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_9);
}

void Led3::Toggle() {
    LL_GPIO_TogglePin(GPIOC, LL_GPIO_PIN_9);
}

void Led3::ChangePeriod() {
    uint32_t new_period = 0;
    static uint8_t period_mul = 0;
    period_mul += 1;
    period_mul %= 2;
    new_period = 100 + period_mul * 100;
    //Timer_Set(TIMER_0, new_period, Led3_Toggle);
}

Led4::Led4(Timer* timer) : Led(timer) {
    /* Enable clock for GPIOC */
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);

    /* Configure PC9 as output */
    LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_8, LL_GPIO_MODE_OUTPUT);

    /* Push-pull output */
    LL_GPIO_SetPinOutputType(GPIOC, LL_GPIO_PIN_8, LL_GPIO_OUTPUT_PUSHPULL);

    /* No pull-up or pull-down */
    LL_GPIO_SetPinPull(GPIOC, LL_GPIO_PIN_8, LL_GPIO_PULL_NO);

    LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_8);
}

void Led4::Toggle() {
    LL_GPIO_TogglePin(GPIOC, LL_GPIO_PIN_8);
}

void Led4::ChangePeriod() {
}
