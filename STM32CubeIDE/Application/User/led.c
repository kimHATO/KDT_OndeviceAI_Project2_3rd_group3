#include "led.h"

typedef struct
{
    GPIO_TypeDef    *port;
    uint16_t        pinNumber;
    GPIO_PinState   onState;
    GPIO_PinState   offState;
} LED_CONTROL;

// main.c의 Enum 정의 순서와 완벽히 일치하도록 배열 재구성
static LED_CONTROL led[LED_MAX] =
{
    {GPIOA, GPIO_PIN_12, GPIO_PIN_SET, GPIO_PIN_RESET}, // 0: LED_EXT_1F_UP (PA12)
    {GPIOC, GPIO_PIN_10, GPIO_PIN_SET, GPIO_PIN_RESET}, // 1: LED_EXT_2F_UP (PC10)
    {GPIOC, GPIO_PIN_11, GPIO_PIN_SET, GPIO_PIN_RESET}, // 2: LED_EXT_2F_DOWN (PC11)
    {GPIOC, GPIO_PIN_12, GPIO_PIN_SET, GPIO_PIN_RESET}, // 3: LED_EXT_3F_UP (PC12)
    {GPIOA, GPIO_PIN_11, GPIO_PIN_SET, GPIO_PIN_RESET},  // 4: LED_EXT_3F_DOWN (PA11)
	{GPIOA, GPIO_PIN_10, GPIO_PIN_SET, GPIO_PIN_RESET},	// 5: LED_EXT_4F_DOWN (PA10)
    {GPIOC, GPIO_PIN_0, GPIO_PIN_SET, GPIO_PIN_RESET},	// 6: LED_INT_1F_BUTTON (PC0)
    {GPIOC, GPIO_PIN_1, GPIO_PIN_SET, GPIO_PIN_RESET},	// 7: LED_INT_2F_BUTTON (PC1)
    {GPIOC, GPIO_PIN_2, GPIO_PIN_SET, GPIO_PIN_RESET},	// 8: LED_INT_3F_BUTTON (PC2)
    {GPIOC, GPIO_PIN_3, GPIO_PIN_SET, GPIO_PIN_RESET},	// 9: LED_INT_4F_BUTTON (PC3)
//    {GPIOA, GPIO_PIN_8, GPIO_PIN_SET, GPIO_PIN_RESET},	// 10: LED_INT_OPEN_BUTTON (PA8)
//    {GPIOA, GPIO_PIN_9, GPIO_PIN_SET, GPIO_PIN_RESET}	// 11: LED_INT_CLOSE_BUTTON (PA9)

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
