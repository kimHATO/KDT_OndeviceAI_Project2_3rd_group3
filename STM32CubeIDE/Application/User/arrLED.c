/*
 * arrLED.c
 *
 *  Created on: 2026. 5. 27.
 *      Author: rlaeh
 */


#include "arrLED.h"
#include "arrLED.h"

#define ARR_LED_COUNT 8
#define ANIMATION_SPEED_MS 100 // LED 이동 속도 (100ms 간격)

typedef struct {
    GPIO_TypeDef *port;
    uint16_t pin;
} ArrLedPin_t;

// 사용자 지정 핀 배열 (아래에서 위로 올라가는 순서라고 가정)
// 순서: [0]PC15 -> [1]PC14 -> [2]PC13 -> [3]PD2 -> [4]PA15 -> [5]PB10 -> [6]PC4
static const ArrLedPin_t arrLeds[ARR_LED_COUNT] = {
    {GPIOA, GPIO_PIN_8}, 		// 가장 아래 LED
    {GPIOA, GPIO_PIN_9},
    {GPIOC, GPIO_PIN_13},
    {GPIOD, GPIO_PIN_2},
    {GPIOA, GPIO_PIN_15},
    {GPIOB, GPIO_PIN_10},
    {GPIOC, GPIO_PIN_4},
	{GPIOB, GPIO_PIN_12}		// 가장 위 LED
};

static uint32_t lastUpdateTick = 0;
static int8_t currentLedIndex = -1;

// 모든 배열 LED 소등
static void ArrLed_AllOff(void) {
    for (int i = 0; i < ARR_LED_COUNT; i++) {
        HAL_GPIO_WritePin(arrLeds[i].port, arrLeds[i].pin, GPIO_PIN_RESET);
    }
}

void ArrLed_Init(void) {
    ArrLed_AllOff();
    currentLedIndex = -1;
}

void ArrLed_Update(ArrLedDirection dir) {
    uint32_t currentTick = HAL_GetTick();

    // 정지 상태일 경우 모든 LED 소등
    if (dir == ARR_DIR_STOP) {
        if (currentLedIndex != -1) {
            ArrLed_AllOff();
            currentLedIndex = -1;
        }
        return;
    }

    // 설정된 애니메이션 속도마다 LED 갱신
    if (currentTick - lastUpdateTick >= ANIMATION_SPEED_MS) {
        lastUpdateTick = currentTick;

        // 이전 LED 끄기
        if (currentLedIndex >= 0 && currentLedIndex < ARR_LED_COUNT) {
            HAL_GPIO_WritePin(arrLeds[currentLedIndex].port, arrLeds[currentLedIndex].pin, GPIO_PIN_RESET);
        }

        // 인덱스 이동
        if (dir == ARR_DIR_UP) {
            currentLedIndex++;
            if (currentLedIndex >= ARR_LED_COUNT) {
                currentLedIndex = 0; // 끝에 도달하면 처음부터 다시 시작
            }
        }
        else if (dir == ARR_DIR_DOWN) {
            if (currentLedIndex <= 0) {
                currentLedIndex = ARR_LED_COUNT - 1; // 처음이면 끝에서 다시 시작
            } else {
                currentLedIndex--;
            }
        }

        // 현재 인덱스의 LED 켜기
        if (currentLedIndex >= 0 && currentLedIndex < ARR_LED_COUNT) {
            HAL_GPIO_WritePin(arrLeds[currentLedIndex].port, arrLeds[currentLedIndex].pin, GPIO_PIN_SET);
        }
    }
}
