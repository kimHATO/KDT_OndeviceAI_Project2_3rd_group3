
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
    {GPIOC, GPIO_PIN_7,  GPIO_PIN_RESET}, // BTN_INT_4F
//    {GPIOB, GPIO_PIN_12, GPIO_PIN_RESET}, // BTN_INT_OPEN
//    {GPIOB, GPIO_PIN_6,  GPIO_PIN_RESET}  // BTN_INT_CLOSE (DONT USE : RESET)
};

static GPIO_PinState prevDebouncedState[BTN_MAX];

static bool toggleState[BTN_MAX] = {false, };     // 토글 상태 저장 배열
static bool isEdgeDetected[BTN_MAX] = {false, };  // 에지(눌림) 1회 감지 플래그

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
            if (currentState != button[i].debouncedState)
            {
                button[i].debouncedState = currentState;

                // 에지 및 토글 처리 로직 복구
                if (button[i].debouncedState == button[i].onState)
                {
                    isEdgeDetected[i] = true;

                    if (i != BTN_INT_OPEN && i != BTN_INT_CLOSE)
                    {
                        toggleState[i] = !toggleState[i];
                    }
                }
            }
        }
        button[i].lastState = currentState;
    }
}

/* * [푸쉬(Push) 버튼용]
 * BTN_INT_OPEN, BTN_INT_CLOSE 버튼 확인용 함수입니다.
 * 호출 시 버튼이 눌렸다면 한 번만 true를 반환하고 플래그를 지웁니다.
 */
bool buttonWasPressed(uint8_t num)
{
    if (num >= BTN_MAX) return false;

    if (isEdgeDetected[num])
    {
        isEdgeDetected[num] = false; // 플래그를 지워 1회성 동작 보장
        return true;
    }
    return false;
}

/* * [토글(Toggle) 버튼용]
 * 층수 호출 버튼 확인용 함수입니다.
 * 현재 버튼의 토글 상태(ON/OFF)를 지속적으로 반환합니다.
 */
bool buttonGetToggleState(uint8_t num)
{
    if (num >= BTN_MAX) return false;
    return toggleState[num];
}

/* * [토글 상태 초기화]
 * 엘리베이터가 호출된 층에 도착하여 동작을 완료했을 때,
 * 외부에서 명시적으로 해당 층의 토글 상태를 꺼주기 위해 사용합니다.
 */
void buttonSetToggleState(uint8_t num, bool state)
{
    if (num >= BTN_MAX) return;
    toggleState[num] = state;
}
