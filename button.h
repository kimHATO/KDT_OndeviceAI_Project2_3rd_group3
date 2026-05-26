
#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"
#include <stdbool.h>

typedef enum {
    BTN_EXT_1F_UP = 0,
    BTN_EXT_2F_UP,
    BTN_EXT_2F_DOWN,
    BTN_EXT_3F_UP,
    BTN_EXT_3F_DOWN,
    BTN_EXT_4F_DOWN,
    BTN_INT_1F,
    BTN_INT_2F,
    BTN_INT_3F,
    BTN_INT_4F,
    BTN_INT_OPEN,
    BTN_INT_CLOSE,
    BTN_MAX
} ButtonNumber;

typedef struct
{
    GPIO_TypeDef    *port;
    uint16_t        pinNumber;
    GPIO_PinState   onState;

    GPIO_PinState   lastState;
    GPIO_PinState   debouncedState;
    uint32_t        lastDebounceTime;
} BUTTON_CONTROL;

void buttonInit(void);
void buttonScan(void);
bool buttonWasPressed(uint8_t num);

#endif /* INC_BUTTON_H_ */
