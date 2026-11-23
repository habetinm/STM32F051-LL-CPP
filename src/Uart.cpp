#include <stdint.h>
#include "Uart.hpp"
#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_gpio.h"
#include "stm32f0xx_ll_usart.h"
#include "system_stm32f0xx.h"


UART_1::UART_1(uint32_t baudrate) {
    // Clock GPIOA
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);

    // Clock USART1
    LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_USART1);

    // PA9 - USART1_TX
    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_9, LL_GPIO_MODE_ALTERNATE);
    //LL_GPIO_SetPinAlternateFunction(GPIOA, LL_GPIO_PIN_9, LL_GPIO_AF_1);
    LL_GPIO_SetAFPin_8_15(GPIOA, LL_GPIO_PIN_9, LL_GPIO_AF_1);

    // USART1 configuration
    LL_USART_SetBaudRate(
        USART1,
        SystemCoreClock,
        LL_USART_OVERSAMPLING_16,
        baudrate
    );

    LL_USART_SetDataWidth(USART1, LL_USART_DATAWIDTH_8B);
    LL_USART_SetStopBitsLength(USART1, LL_USART_STOPBITS_1);
    LL_USART_SetParity(USART1, LL_USART_PARITY_NONE);
    LL_USART_SetTransferDirection(USART1, LL_USART_DIRECTION_TX);
    LL_USART_SetHWFlowCtrl(USART1, LL_USART_HWCONTROL_NONE);

    LL_USART_Enable(USART1);
}

void UART_1::WriteLine(const char* text) {
    Write(text);
    Write("\r\n");
}

void UART_1::WriteChar(char c) {
    while (!LL_USART_IsActiveFlag_TXE(USART1))
    {
    }

    LL_USART_TransmitData8(USART1, (uint8_t)c);
}

void UART_1::Write(const char* text) {
    while (*text)
    {
        WriteChar(*text++);
    }
}
