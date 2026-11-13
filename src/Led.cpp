#include "stm32f0xx.h"
#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_gpio.h"
#include "SysTickHandler.hpp"
#include "Timer.hpp"
#include "Led.hpp"
#include <string.h>
#include <stdio.h>

Led::Led() {

}

void Led::Callback(void* context) {
    Led* led = static_cast<Led3*>(context);
    led->Toggle();
}

Led3::Led3() {
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

Led4::Led4() {
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
