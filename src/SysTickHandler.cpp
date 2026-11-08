#include "SysTyckHandler.hpp"

SysTick* SysTick::Instance = 0;

SysTick::SysTick() : milliseconds(0) {
    instance = this;
    SysTick_Config(SystemCoreClock / 1000);
}

void SysTick::Handler() {
    milliseconds++;
}

uint32_t SysTick::GetMilliseconds() const {
    return milliseconds;
}

void SysTick::InterruptHandler() {
    if (instance != nullptr) {
        instance->Handler();
    }
}

extern "C" void SysTick_Handler() {
    SysTick::InterruptHandler();
}
