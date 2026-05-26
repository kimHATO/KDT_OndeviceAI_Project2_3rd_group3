#ifndef INC_LED_H_
#define INC_LED_H_

#include "stm32f4xx_hal.h"

typedef enum {
    LED_EXT_1F = 0, // LED1 (PA12)  : 외부 1층 버튼 표시용
    LED_EXT_2F,     // LED1 (PC10) : 외부 2층 버튼 표시용 (안전핀)
    LED_EXT_3F,     // LED1 (PC11) : 외부 3층 버튼 표시용 (안전핀)
    LED_EXT_4F,     // LED1 (PC12) : 외부 4층 버튼 표시용 (안전핀)
    LED_INT,        // LED2 (PA11)  : 내부 층 버튼 표시용
    LED_MAX
} LedNumber;

void ledOn(uint8_t num);
void ledOff(uint8_t num);
void ledToggle(uint8_t num);

#endif /* INC_LED_H_ */
