#include "stepper.h"

/* 28BYJ-48 Half-step sequence */
static const uint8_t HALF_STEP_SEQ[8][4] = {
    {1, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 1},
    {0, 0, 0, 1},
    {1, 0, 0, 1}
};

/* 속도 설정 */
#define STEPPER_TIMER_HZ 1000000UL
#define STEPPER_SPEED_HZ 550

static TIM_HandleTypeDef *stepper_htim = NULL;

static volatile uint8_t currentStep = 0;
static volatile uint32_t remainingSteps = 0;
static volatile uint8_t motorDirection = DIR_UP;
static volatile uint8_t motorBusy = 0;

static volatile uint8_t currentFloor = 1;
static volatile uint8_t targetFloor = 1;

static void Stepper_Write(uint8_t step)
{
    HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, HALF_STEP_SEQ[step][0]);
    HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, HALF_STEP_SEQ[step][1]);
    HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, HALF_STEP_SEQ[step][2]);
    HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, HALF_STEP_SEQ[step][3]);
}

static void Stepper_AllOff(void)
{
    HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, GPIO_PIN_RESET);
}

static void Stepper_TimerConfig(TIM_HandleTypeDef *htim)
{
    uint32_t arr = (STEPPER_TIMER_HZ / STEPPER_SPEED_HZ) - 1;

    __HAL_TIM_SET_PRESCALER(htim, 100 - 1);
    __HAL_TIM_SET_AUTORELOAD(htim, arr);
    __HAL_TIM_SET_COUNTER(htim, 0);

    HAL_TIM_GenerateEvent(htim, TIM_EVENTSOURCE_UPDATE);
}

void Stepper_Init(TIM_HandleTypeDef *htim)
{
    stepper_htim = htim;

    currentStep = 0;
    motorBusy = 1; // 초기화 중 다른 명령 무시

//    uint32_t timeoutTick = HAL_GetTick();

        // 포토 인터럽트가 감지될 때까지(RESET이 될 때까지) 모터를 하강시킴
        while (HAL_GPIO_ReadPin(PhotoIt_PORT, PhotoIt_PIN) == GPIO_PIN_RESET)
        {
            currentStep = (currentStep == 0) ? 7 : currentStep - 1;
            Stepper_Write(currentStep);
            HAL_Delay(1);

//            // 5초(5000ms) 타임아웃 발생 시 무한 루프 강제 탈출
//            if (HAL_GetTick() - timeoutTick > 5000) {
//                break;
//            }
        }
    // 초기화 위치 도달 완료
    Stepper_AllOff();

    remainingSteps = 0;
    motorBusy = 0;

    // 현재 층을 1층으로 세팅
    currentFloor = 1;
    targetFloor = 1;

    Stepper_TimerConfig(stepper_htim);
}

void Stepper_MoveSteps(uint32_t steps, uint8_t direction)
{
    if (stepper_htim == NULL) return;
    if (steps == 0) return;
    if (motorBusy) return;

    remainingSteps = steps;
    motorDirection = direction;
    motorBusy = 1;

    HAL_TIM_Base_Start_IT(stepper_htim);
}

void Stepper_MoveToFloor(uint8_t floor)
{
    if (floor < 1 || floor > ELEVATOR_MAX_FLOOR) return;
    if (motorBusy) return;
    if (floor == currentFloor) return;

    targetFloor = floor;

    uint32_t stepsToMove;
    uint8_t direction;

    if (targetFloor > currentFloor)
    {
        stepsToMove = (targetFloor - currentFloor) * STEPS_PER_FLOOR;
        direction = STEPPER_DIR_UP;
    }
    else
    {
        stepsToMove = (currentFloor - targetFloor) * STEPS_PER_FLOOR;
        direction = STEPPER_DIR_DOWN;
    }

    Stepper_MoveSteps(stepsToMove, direction);
}

void Stepper_Stop(void)
{
    if (stepper_htim != NULL)
    {
        HAL_TIM_Base_Stop_IT(stepper_htim);
    }

    remainingSteps = 0;
    motorBusy = 0;

    Stepper_AllOff();
}

uint8_t Stepper_IsBusy(void)
{
    return motorBusy;
}

uint8_t Stepper_GetCurrentFloor(void)
{
    return currentFloor;
}

uint8_t Stepper_GetTargetFloor(void)
{
    return targetFloor;
}

/*
 * TIM11 인터럽트 콜백
 * 프로젝트 전체에서 HAL_TIM_PeriodElapsedCallback은 한 곳에만 있어야 함
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (stepper_htim == NULL) return;

    if (htim->Instance == stepper_htim->Instance)
    {
        if (remainingSteps > 0)
        {
            if (motorDirection == STEPPER_DIR_UP)
            {
                currentStep = (currentStep + 1) % 8;
            }
            else
            {
                currentStep = (currentStep == 0) ? 7 : currentStep - 1;
            }

            Stepper_Write(currentStep);
            remainingSteps--;
        }
        else
        {
            HAL_TIM_Base_Stop_IT(stepper_htim);
            Stepper_AllOff();

            currentFloor = targetFloor;
            motorBusy = 0;
        }
    }
}
