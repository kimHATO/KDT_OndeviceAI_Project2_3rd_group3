#ifndef INC_ELEVATOR_CTRL_H_
#define INC_ELEVATOR_CTRL_H_

#include "main.h"
#include "servo.h"
#include "stepper.h"
#include "fnd.h"
#include "button.h"
#include "led.h"
#include "arrLED.h"

typedef enum {
    STATE_IDLE_CLOSED = 0, // 엘리베이터 정지 / 문 닫힘
    STATE_DOOR_OPENING,    // 문 열리는 중
    STATE_DOOR_OPEN,       // 문 열림 유지
    STATE_DOOR_CLOSING,    // 문 닫히는 중
    STATE_MOVING           // 엘리베이터 이동 중 (문 닫힘)
} ElevatorState;

typedef enum {
    DIR_STOP = 0,
    DIR_UP,
    DIR_DOWN
} DirectionStatus;

void ElevatorSystem_Init(TIM_HandleTypeDef *stepper_htim);
void ElevatorSystem_Run(void);
DirectionStatus ElevatorSystem_GetDirectionStatus(void);
void ElevatorSystem_PowerTest(void);

#endif /* INC_ELEVATOR_CTRL_H_ */
