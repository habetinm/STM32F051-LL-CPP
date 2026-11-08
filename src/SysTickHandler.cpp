#include <cstdint>
#include "stm32f0xx.h"
#include "system_stm32f0xx.h"
#include "SysTickHandler.hpp"

SysTickHandler* SysTickHandler::instance = nullptr;

SysTickHandler::SysTickHandler() : milliseconds(0) {
    instance = this;
    SysTick_Config(SystemCoreClock / 1000);
}

void SysTickHandler::Handler() {
    milliseconds++;
}

uint32_t SysTickHandler::GetMilliseconds() const {
    return milliseconds;
}

void SysTickHandler::InterruptHandler() {
    if (instance != nullptr) {
        instance->Handler();
    }
}

extern "C" void SysTick_Handler() {
    SysTickHandler::InterruptHandler();
}
