#include "led.h"

typedef struct
{
    GPIO_TypeDef    *port;
    uint16_t        pinNumber;
    GPIO_PinState   onState;
    GPIO_PinState   offState;
} LED_CONTROL;

// main.c의 Enum 정의 순서와 완벽히 일치하도록 배열 재구성
LED_CONTROL led[LED_MAX] =
{
    {GPIOA, GPIO_PIN_12, GPIO_PIN_SET, GPIO_PIN_RESET}, // 0: LED_EXT_1F (PA12)
    {GPIOC, GPIO_PIN_10, GPIO_PIN_SET, GPIO_PIN_RESET}, // 1: LED_EXT_2F (PC10)
    {GPIOC, GPIO_PIN_11, GPIO_PIN_SET, GPIO_PIN_RESET}, // 2: LED_EXT_3F (PC11)
    {GPIOC, GPIO_PIN_12, GPIO_PIN_SET, GPIO_PIN_RESET}, // 3: LED_EXT_4F (PC12)
    {GPIOA, GPIO_PIN_11, GPIO_PIN_SET, GPIO_PIN_RESET}  // 4: LED_INT    (PA11)
};

void ledOn(uint8_t num)
{
    if (num < LED_MAX) {
        HAL_GPIO_WritePin(led[num].port, led[num].pinNumber, led[num].onState);
    }
}

void ledOff(uint8_t num)
{
    if (num < LED_MAX) {
        HAL_GPIO_WritePin(led[num].port, led[num].pinNumber, led[num].offState);
    }
}

void ledToggle(uint8_t num)
{
    if (num < LED_MAX) {
        HAL_GPIO_TogglePin(led[num].port, led[num].pinNumber);
    }
}
