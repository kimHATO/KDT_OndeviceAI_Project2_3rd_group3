/*
 * arrLED.h
 *
 *  Created on: 2026. 5. 27.
 *      Author: rlaeh
 */

#ifndef APPLICATION_USER_ARRLED_H_
#define APPLICATION_USER_ARRLED_H_

#ifndef INC_ARR_LED_H_
#define INC_ARR_LED_H_

#include "main.h"
#include "elevator_ctrl.h"

// 이동 방향 정의 (elevator_ctrl.h의 DirectionStatus와 매칭되도록 설계)
typedef enum {
    ARR_DIR_STOP = 0,
    ARR_DIR_UP,
    ARR_DIR_DOWN
} ArrLedDirection;

// 배열 LED 초기화
void ArrLed_Init(void);

// 메인 루프에서 지속적으로 호출되어 애니메이션을 처리하는 함수 (Non-blocking)
void ArrLed_Update(ArrLedDirection dir);

#endif /* INC_ARR_LED_H_ */


#endif /* APPLICATION_USER_ARRLED_H_ */
