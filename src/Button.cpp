#include "stm32f0xx.h"
#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_gpio.h"
#include "Button.hpp"


Button::Button() :
    pressed(0),
    context(0) {

}

void Button::SetCB(void* obj, button_cb cb) {
    context = obj;
    callback = cb;
}

void Button::Loop() {
    static uint8_t last_state = 1;
    static uint8_t button_state = 1;
    static uint32_t last_change_time = 0;
    static uint8_t state = 0;
    static uint32_t milliseconds = 0;

    uint8_t current_state = LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_0); //(GPIOA->IDR & GPIO_IDR_0) ? 1 : 0;

    milliseconds = systick.GetMilliseconds();

    // Zaznamenání změny vstupu
    if (current_state != last_state) {
        last_change_time = milliseconds;
        last_state = current_state;
    }

    // Ověření, zda je vstup stabilní alespoň 20 ms
    if ((current_state != button_state) && ((uint32_t)(milliseconds - last_change_time) >= 20)) {
        button_state = current_state;

        // Reakce na stisk tlačítka (aktivní v log. 0)
        if (button_state == 0) {
            state = !state;
            pressed = state;
            callback(context, state);
        }
    }
}

uint8_t Button::IsPressed() {
    return pressed;
}
