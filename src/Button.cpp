#include "stm32f0xx.h"
#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_gpio.h"
#include "Button.hpp"


Button::Button() :
    context(0),
    callback(0),
    pressed(0) {
}

void Button::SetCB(void* obj, button_cb cb) {
    context = obj;
    callback = cb;
}

uint8_t Button::IsPressed() {
    return pressed;
}

UserButton::UserButton() :
    Button(),
    last_state(0),
    button_state(0),
    state(0),
    last_change_time(0),
    milliseconds(0) {

    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_0, LL_GPIO_MODE_INPUT);
}

void UserButton::Loop() {
    milliseconds = SysTickHandler::GetInstance().GetMilliseconds();
    current_state = LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_0);

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

            if (context != 0) {
                if (callback != 0) {
                    callback(context, state);
                }
            }
        }
    }
}

