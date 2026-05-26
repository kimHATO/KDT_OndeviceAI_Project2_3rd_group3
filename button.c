
#include "button.h"

#define DEBOUNCE_DELAY  10

// 풀업 사양이므로 평상시 HIGH(SET), 눌렀을 때 LOW(RESET)가 됩니다.
// 구조체 초기화 시 발생할 수 있는 핀 상태 왜곡을 방지하기 위해 핀 주소만 매핑합니다.
BUTTON_CONTROL button[BTN_MAX] =
{
    // 외부 버튼
    {GPIOC, GPIO_PIN_8,  GPIO_PIN_RESET}, // BTN_EXT_1F_UP
    {GPIOC, GPIO_PIN_6,  GPIO_PIN_RESET}, // BTN_EXT_2F_UP
    {GPIOC, GPIO_PIN_5,  GPIO_PIN_RESET}, // BTN_EXT_2F_DOWN
    {GPIOC, GPIO_PIN_9,  GPIO_PIN_RESET}, // BTN_EXT_3F_UP
    {GPIOB, GPIO_PIN_8,  GPIO_PIN_RESET}, // BTN_EXT_3F_DOWN
    {GPIOB, GPIO_PIN_9,  GPIO_PIN_RESET}, // BTN_EXT_4F_DOWN

    // 내부 버튼
    {GPIOA, GPIO_PIN_5,  GPIO_PIN_RESET}, // BTN_INT_1F
    {GPIOA, GPIO_PIN_6,  GPIO_PIN_RESET}, // BTN_INT_2F
    {GPIOA, GPIO_PIN_7,  GPIO_PIN_RESET}, // BTN_INT_3F
    {GPIOB, GPIO_PIN_6,  GPIO_PIN_RESET}, // BTN_INT_4F
    {GPIOB, GPIO_PIN_12, GPIO_PIN_RESET}, // BTN_INT_OPEN
    {GPIOC, GPIO_PIN_7,  GPIO_PIN_RESET}  // BTN_INT_CLOSE
};

static GPIO_PinState prevDebouncedState[BTN_MAX];

void buttonInit(void)
{
    for(int i = 0; i < BTN_MAX; i++)
    {
        // 보드가 켜진 직후의 실제 핀 상태(풀업 저항에 의해 HIGH인 상태)를 정확히 읽어옵니다.
        GPIO_PinState currentState = HAL_GPIO_ReadPin(button[i].port, button[i].pinNumber);

        button[i].lastState = currentState;
        button[i].debouncedState = currentState;
        button[i].lastDebounceTime = HAL_GetTick();

        prevDebouncedState[i] = currentState;
    }
}

void buttonScan(void)
{
    uint32_t currentTime = HAL_GetTick();

    for (int i = 0; i < BTN_MAX; i++)
    {
        GPIO_PinState currentState = HAL_GPIO_ReadPin(button[i].port, button[i].pinNumber);

        if (currentState != button[i].lastState)
        {
            button[i].lastDebounceTime = currentTime;
        }

        if ((currentTime - button[i].lastDebounceTime) > DEBOUNCE_DELAY)
        {
            button[i].debouncedState = currentState;
        }

        button[i].lastState = currentState;
    }
}

bool buttonWasPressed(uint8_t num)
{
    if (num >= BTN_MAX) return false;

    bool ret = false;
    // 이전에 안 눌려있다가 (풀업이므로 button[num].onState인 RESET이 아닐 때)
    // 지금 안정적으로 눌림 (RESET 상태)이 되었을 때 딱 한 번 에지 감지
    if (prevDebouncedState[num] != button[num].onState && button[num].debouncedState == button[num].onState)
    {
        ret = true;
    }
    prevDebouncedState[num] = button[num].debouncedState;
    return ret;
}
