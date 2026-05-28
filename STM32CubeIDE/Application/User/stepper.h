#ifndef INC_STEPPER_H_
#define INC_STEPPER_H_

#include "main.h"
#include "elevator_ctrl.h"

/* 방향 (상위 제어기와 이름 충돌 방지를 위해 STEPPER_ 접두사 추가) */
#define STEPPER_DIR_UP    0
#define STEPPER_DIR_DOWN  1

/* 엘리베이터 설정 */
#define ELEVATOR_MAX_FLOOR 4
#define STEPS_PER_FLOOR 3500 // 4cm 기준 (여유)

/* ULN2003 연결 핀 */
#define IN1_PORT GPIOB
#define IN1_PIN  GPIO_PIN_13

#define IN2_PORT GPIOB
#define IN2_PIN  GPIO_PIN_14

#define IN3_PORT GPIOB
#define IN3_PIN  GPIO_PIN_15

#define IN4_PORT GPIOB
#define IN4_PIN  GPIO_PIN_1

#define PhotoIt_PORT	GPIOB
#define PhotoIt_PIN		GPIO_PIN_7

void Stepper_Init(TIM_HandleTypeDef *htim);
void Stepper_MoveToFloor(uint8_t floor);
void Stepper_MoveSteps(uint32_t steps, uint8_t direction);
void Stepper_Stop(void);

uint8_t Stepper_IsBusy(void);
uint8_t Stepper_GetCurrentFloor(void);
uint8_t Stepper_GetTargetFloor(void);

#endif
