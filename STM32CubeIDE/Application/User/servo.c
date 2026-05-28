/*
 * servo.c
 *
 * Created on: 2026. 5. 26.
 * Author: user10
 */

#include "servo.h"

#define PWM_DOOR_CLOSED       100
#define PWM_DOOR_OPENED       200
#define SERVO_MOVE_TIME_MS    1000 // 문이 열리거나 닫히는 총 소요 시간 (1초)
#define SERVO_UPDATE_INTERVAL 10   // 서보모터 위치 업데이트 주기 (10ms)
#define DOOR_HOLD_TIME_MS     3000 // 문이 완전히 열린 후 유지되는 시간 (3초)

extern TIM_HandleTypeDef htim3;
#define SERVO_TIM           &htim3
#define SERVO_CHANNEL       TIM_CHANNEL_2

// 상태 및 제어 변수
static uint8_t ServoState = DOOR_CLOSED;
static uint32_t lastUpdateTime = 0;
static float currentPwm = PWM_DOOR_CLOSED;
static uint32_t doorOpenStartTime = 0;
static float pwmStep = 0;

/* 서보모터 및 PWM 초기화 */
void Init_Servo(void) {
    HAL_TIM_PWM_Start_IT(SERVO_TIM, SERVO_CHANNEL);

    // 초기 위치를 '문 닫힘' 상태로 설정
    currentPwm = PWM_DOOR_CLOSED;
    __HAL_TIM_SET_COMPARE(SERVO_TIM, SERVO_CHANNEL, (uint32_t)currentPwm);
    ServoState = DOOR_CLOSED;

    // 10ms마다 업데이트할 PWM 변화량(Step) 계산
    // (1500 - 1000) / (1000ms / 10ms) = 500 / 100 = 5.0
    pwmStep = (float)(PWM_DOOR_OPENED - PWM_DOOR_CLOSED) / (SERVO_MOVE_TIME_MS / SERVO_UPDATE_INTERVAL);
}

/* 문 열기 동작 명령 */
void OpenDoor(void) {
    // 조건: 닫혀있거나(DOOR_CLOSED), 닫히는 도중(DOOR_CLOSING)일 때 열기 허용
    if (ServoState == DOOR_CLOSED || ServoState == DOOR_CLOSING) {
        ServoState = DOOR_OPENING;
    }
}

/* 문 닫기 동작 명령 */
void CloseDoor(void) {
    // 조건: 완전히 열려있을 때(DOOR_OPENED)만 닫기 허용
    // 열리는 도중(DOOR_OPENING)에는 닫기 명령 무시
    if (ServoState == DOOR_OPENED) {
        ServoState = DOOR_CLOSING;
    }
}

/* 서보모터 상태 갱신 및 구동 상태 반환 (메인 루프에서 지속적 호출 필요) */
void ServoStateUpdate(void) {
    uint32_t currentTick = HAL_GetTick();

    // 설정된 주기(10ms)마다 모터 위치 및 상태 갱신
    if (currentTick - lastUpdateTime >= SERVO_UPDATE_INTERVAL) {
        lastUpdateTime = currentTick;

        if (ServoState == DOOR_OPENING) {
            currentPwm += pwmStep; // 틱마다 점진적 증가

            if (currentPwm >= PWM_DOOR_OPENED) {
                currentPwm = PWM_DOOR_OPENED;
                ServoState = DOOR_OPENED;
                doorOpenStartTime = currentTick; // 완전히 열린 시점의 틱 기록
            }
            __HAL_TIM_SET_COMPARE(SERVO_TIM, SERVO_CHANNEL, (uint32_t)currentPwm);
        }
        else if (ServoState == DOOR_OPENED) {
            // 문이 완전히 열린 상태에서 대기 시간이 경과했는지 확인
            if (currentTick - doorOpenStartTime >= DOOR_HOLD_TIME_MS) {
                ServoState = DOOR_CLOSING; // 대기 시간이 지나면 자동으로 닫힘 상태로 전환
            }
        }
        else if (ServoState == DOOR_CLOSING) {
            currentPwm -= pwmStep; // 틱마다 점진적 감소

            if (currentPwm <= PWM_DOOR_CLOSED) {
                currentPwm = PWM_DOOR_CLOSED;
                ServoState = DOOR_CLOSED;
            }
            __HAL_TIM_SET_COMPARE(SERVO_TIM, SERVO_CHANNEL, (uint32_t)currentPwm);
        }
    }

    return;
}

bool IsServoBusy()
{
	if (ServoState != DOOR_CLOSED) {return true;}
	return false;
}

