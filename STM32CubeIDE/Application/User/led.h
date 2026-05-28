#ifndef INC_LED_H_
#define INC_LED_H_

#include "stm32f4xx_hal.h"

typedef enum {
    LED_EXT_1F_UP = 0, 	// LED0 (PA12)  : 외부 1층 UP 버튼 표시용
    LED_EXT_2F_UP,     	// LED1 (PC10) : 외부 2층 UP 버튼 표시용 (안전핀)
    LED_EXT_2F_DOWN,	// LED2 (PC11) : 외부 2층 DOWN 버튼 표시용 (안전핀)
	LED_EXT_3F_UP,  	// LED3 (PC12) : 외부 3층 UP 버튼 표시용 (안전핀)
    LED_EXT_3F_DOWN,	// LED4 (PA11) : 외부 3층 DOWN 버튼 표시용 (안전핀)
	LED_EXT_4F_UP,  	// LED5 (PA10) : 외부 4층 DOWN 버튼 표시용 (안전핀)
    LED_INT_1F,			// LED6 (PC0) : 내부 1층 버튼 표시용
	LED_INT_2F,			// LED7 (PC1) : 내부 2층 버튼 표시용
	LED_INT_3F,			// LED8 (PC2) : 내부 3층 버튼 표시용
	LED_INT_4F,			// LED9 (PC3) : 내부 4층 버튼 표시용
	LED_INT_OPEN_BUTTON,// LED10 (PA8)  : 내부 OPEN 표시용
	LED_INT_CLOSE_BUTTON,// LED11 (PA9)  : 내부 CLOSE 표시용
	LED_MAX
} LedNumber;

void ledOn(uint8_t num);
void ledOff(uint8_t num);
void ledToggle(uint8_t num);

#endif /* INC_LED_H_ */
