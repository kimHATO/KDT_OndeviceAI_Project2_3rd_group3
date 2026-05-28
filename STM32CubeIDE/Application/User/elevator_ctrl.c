#include "elevator_ctrl.h"

static ElevatorState currentState = STATE_IDLE_CLOSED;
static DirectionStatus currentDirStatus = DIR_STOP;

static uint32_t doorOpenTick = 0;
static const uint32_t DOOR_OPEN_DURATION = 3000;

static bool callUp[5] = {false, };
static bool callDown[5] = {false, };
static bool callInternal[5] = {false, };

static uint8_t GetFloorFromButton(uint8_t btnNum) {
    if (btnNum == BTN_EXT_1F_UP || btnNum == BTN_INT_1F) return 1;
    if (btnNum == BTN_EXT_2F_UP || btnNum == BTN_EXT_2F_DOWN || btnNum == BTN_INT_2F) return 2;
    if (btnNum == BTN_EXT_3F_UP || btnNum == BTN_EXT_3F_DOWN || btnNum == BTN_INT_3F) return 3;
    if (btnNum == BTN_EXT_4F_DOWN || btnNum == BTN_INT_4F) return 4;
    return 0;
}

// 진행 방향에 대기 중인 호출이 있는지 확인 (스캔 로직)
static bool CheckCallsAhead(uint8_t floor, DirectionStatus dir) {
    if (dir == DIR_UP) {
        for (int i = floor + 1; i <= 4; i++) {
            if (callUp[i] || callDown[i] || callInternal[i]) return true;
        }
    } else if (dir == DIR_DOWN) {
        for (int i = floor - 1; i >= 1; i--) {
            if (callUp[i] || callDown[i] || callInternal[i]) return true;
        }
    }
    return false;
}

// 방향에 맞는 호출과 LED 해제
static void ClearFloorCallByDirection(uint8_t floor, DirectionStatus dir) {
    // 내부 층수 버튼은 방향 무관하게 도착 시 해제
    callInternal[floor] = false;
    for (int i = BTN_INT_1F; i <= BTN_INT_4F; i++) {
        if (GetFloorFromButton(i) == floor) {
            buttonSetToggleState(i, false);
            ledOff(i);
        }
    }

    if (dir == DIR_UP || floor == 1) {
        callUp[floor] = false;
        for (int i = 0; i < BTN_INT_1F; i++) {
            if (GetFloorFromButton(i) == floor && (i == BTN_EXT_1F_UP || i == BTN_EXT_2F_UP || i == BTN_EXT_3F_UP)) {
                buttonSetToggleState(i, false);
                ledOff(i);
            }
        }
    }

    if (dir == DIR_DOWN || floor == 4) {
        callDown[floor] = false;
        for (int i = 0; i < BTN_INT_1F; i++) {
            if (GetFloorFromButton(i) == floor && (i == BTN_EXT_2F_DOWN || i == BTN_EXT_3F_DOWN || i == BTN_EXT_4F_DOWN)) {
                buttonSetToggleState(i, false);
                ledOff(i);
            }
        }
    }
}

void ElevatorSystem_Init(TIM_HandleTypeDef *stepper_htim) {
    Init_Servo();
    FND_Init();
    FND_DisplayNumber(8);
    Stepper_Init(stepper_htim);
    FND_DisplayNumber(1);
    buttonInit();
    ArrLed_Init();

    currentState = STATE_IDLE_CLOSED;
    currentDirStatus = DIR_STOP;
}

DirectionStatus ElevatorSystem_GetDirectionStatus(void) {
    return currentDirStatus;
}

void ElevatorSystem_Run(void) {
    uint32_t currentTick = HAL_GetTick();

    buttonScan();
    ServoStateUpdate();

    uint8_t currentFloor = Stepper_GetCurrentFloor();

    // 입력 스캔 및 등록 (버튼 조작은 항상 분석)
    if (buttonGetToggleState(BTN_EXT_1F_UP))   { callUp[1] = true; ledOn(BTN_EXT_1F_UP); }
    if (buttonGetToggleState(BTN_INT_1F))      { callInternal[1] = true; ledOn(BTN_INT_1F); }
    if (buttonGetToggleState(BTN_EXT_2F_UP))   { callUp[2] = true; ledOn(BTN_EXT_2F_UP); }
    if (buttonGetToggleState(BTN_EXT_2F_DOWN)) { callDown[2] = true; ledOn(BTN_EXT_2F_DOWN); }
    if (buttonGetToggleState(BTN_INT_2F))      { callInternal[2] = true; ledOn(BTN_INT_2F); }
    if (buttonGetToggleState(BTN_EXT_3F_UP))   { callUp[3] = true; ledOn(BTN_EXT_3F_UP); }
    if (buttonGetToggleState(BTN_EXT_3F_DOWN)) { callDown[3] = true; ledOn(BTN_EXT_3F_DOWN); }
    if (buttonGetToggleState(BTN_INT_3F))      { callInternal[3] = true; ledOn(BTN_INT_3F); }
    if (buttonGetToggleState(BTN_EXT_4F_DOWN)) { callDown[4] = true; ledOn(BTN_EXT_4F_DOWN); }
    if (buttonGetToggleState(BTN_INT_4F))      { callInternal[4] = true; ledOn(BTN_INT_4F); }

    switch (currentState) {
        // [1] 엘리베이터 정지 / 문 닫힘 상태
        case STATE_IDLE_CLOSED:
            ArrLed_Update(ARR_DIR_STOP);

            // 우선순위 1: 가던 방향 계속 진행 분석
            if (currentDirStatus != DIR_STOP && CheckCallsAhead(currentFloor, currentDirStatus)) {
                uint8_t target = (currentDirStatus == DIR_UP) ? currentFloor + 1 : currentFloor - 1;
                Stepper_MoveToFloor(target);
                currentState = STATE_MOVING;
            }
            // 우선순위 2: 현재 층 버튼 눌림 분석
            else if (callInternal[currentFloor] || callUp[currentFloor] || callDown[currentFloor]) {
                if (callUp[currentFloor]) currentDirStatus = DIR_UP;
                else if (callDown[currentFloor]) currentDirStatus = DIR_DOWN;
                else if (currentDirStatus == DIR_STOP) currentDirStatus = DIR_UP; // 기본값

                ClearFloorCallByDirection(currentFloor, currentDirStatus);
                OpenDoor();
                currentState = STATE_DOOR_OPENING;
            }
            // 우선순위 3: 반대 방향 분석
            else if (currentDirStatus != DIR_STOP && CheckCallsAhead(currentFloor, (currentDirStatus == DIR_UP) ? DIR_DOWN : DIR_UP)) {
                currentDirStatus = (currentDirStatus == DIR_UP) ? DIR_DOWN : DIR_UP;
                uint8_t target = (currentDirStatus == DIR_UP) ? currentFloor + 1 : currentFloor - 1;
                Stepper_MoveToFloor(target);
                currentState = STATE_MOVING;
            }
            // 우선순위 4: 완전 대기 상태에서 새로운 호출 발생 시 방향 판단
            else if (currentDirStatus == DIR_STOP) {
                if (CheckCallsAhead(currentFloor, DIR_UP)) {
                    currentDirStatus = DIR_UP;
                    Stepper_MoveToFloor(currentFloor + 1);
                    currentState = STATE_MOVING;
                } else if (CheckCallsAhead(currentFloor, DIR_DOWN)) {
                    currentDirStatus = DIR_DOWN;
                    Stepper_MoveToFloor(currentFloor - 1);
                    currentState = STATE_MOVING;
                }
            }
            break;

        // [2] 문 로직 (엘리베이터 정지)
        case STATE_DOOR_OPENING:
            ArrLed_Update(ARR_DIR_STOP); // arrLED Off
            if (!IsServoBusy()) {
                doorOpenTick = currentTick;
                currentState = STATE_DOOR_OPEN;
            }
            break;

        case STATE_DOOR_OPEN:
            ArrLed_Update(ARR_DIR_STOP);
            if (buttonWasPressed(BTN_INT_OPEN)) {
                doorOpenTick = currentTick;
            }
            if (buttonWasPressed(BTN_INT_CLOSE) || (currentTick - doorOpenTick >= DOOR_OPEN_DURATION)) {
                CloseDoor();
                currentState = STATE_DOOR_CLOSING;
            }
            break;

        case STATE_DOOR_CLOSING:
            ArrLed_Update(ARR_DIR_STOP);
            if (buttonWasPressed(BTN_INT_OPEN)) {
                OpenDoor();
                currentState = STATE_DOOR_OPENING;
            } else if (!IsServoBusy()) {
                currentState = STATE_IDLE_CLOSED; // 문 닫힘 완료 시 우선순위 재평가를 위해 IDLE로 전환
            }
            break;

        // [3] 이동 중 (문 닫힘 완료)
        case STATE_MOVING:
                    ArrLed_Update((ArrLedDirection)currentDirStatus); // 이동 중에만 arrLED 작동

                    // 스텝 모터가 목표 층(1개 층 이동)에 도달하여 구동을 멈추었을 때
                    if (!Stepper_IsBusy()) {
                        currentFloor = Stepper_GetCurrentFloor();
                        FND_DisplayNumber(currentFloor); // 층 도달 시 FND 변경

                        bool stopCondition = false;

                        // 정지 조건 1. 해당 층 내부 버튼이 눌렸는가?
                        if (callInternal[currentFloor]) {
                            stopCondition = true;
                        }

                        // 정지 조건 2. 같은 방향의 외부 버튼이 눌렸는가?
                        if (currentDirStatus == DIR_UP && callUp[currentFloor]) {
                            stopCondition = true;
                        }
                        if (currentDirStatus == DIR_DOWN && callDown[currentFloor]) {
                            stopCondition = true;
                        }

                        // 정지 조건 3. 더 이상 진행할 방향에 호출이 없는 상황(종점) 처리
                        if (!CheckCallsAhead(currentFloor, currentDirStatus)) {
                            if (currentDirStatus == DIR_UP && callDown[currentFloor]) {
                                currentDirStatus = DIR_DOWN; // 방향 전환 후 정지
                                stopCondition = true;
                            }
                            else if (currentDirStatus == DIR_DOWN && callUp[currentFloor]) {
                                currentDirStatus = DIR_UP;
                                stopCondition = true;
                            }
                            else if (callUp[currentFloor] || callDown[currentFloor]) {
                                // 잔여 예외 처리: 진행 방향 호출이 없으나 현재 층에 호출이 남아있을 경우 무조건 정지
                                stopCondition = true;
                            }
                        }

                        // 정지 조건을 만족했을 때 문 열기 수행
                        if (stopCondition) {
                            ClearFloorCallByDirection(currentFloor, currentDirStatus);
                            OpenDoor(); // 층 도달 시 문을 여는 함수 호출
                            currentState = STATE_DOOR_OPENING;
                        }
                        // 조건에 해당하지 않으면 멈추지 않고 다음 층으로 스텝 모터 재명령
                        else {
                            uint8_t nextTarget = (currentDirStatus == DIR_UP) ? currentFloor + 1 : currentFloor - 1;
                            Stepper_MoveToFloor(nextTarget);
                        }
                    }
                    break;
    }
}




// Elevator System Power Test Code

static uint32_t doorTestTick = 0;
static uint8_t doorTestState = 0;
static uint32_t ledTestTick = 0;
static bool ledToggleState = false;

void ElevatorSystem_PowerTest(void)
{
    uint32_t currentTick = HAL_GetTick();
    uint8_t str[16];

    /* 1. 최우선 처리: 서보모터 상태 갱신 및 버튼 스캔 */
    // 이 두 함수가 루프마다 지연 없이 실행되어야 서보모터가 정상적으로 회전합니다.
    ServoStateUpdate();
    buttonScan();

    /* 2. 스텝모터 왕복 테스트 (1층 <-> 4층) */
    if (!Stepper_IsBusy())
    {
        if (Stepper_GetCurrentFloor() == 1)
        {
            Stepper_MoveToFloor(4);
        }
        else
        {
            Stepper_MoveToFloor(1);
        }
    }

    /* 3. FND 상태 출력 */
    // 현재 스텝모터가 위치한 층수를 실시간으로 표출합니다.
    FND_DisplayNumber(Stepper_GetCurrentFloor());

    /* 4. 서보모터 개폐 테스트 (3초 간격) */
    if (currentTick - doorTestTick >= 3000)
    {
        doorTestTick = currentTick;
        if (doorTestState == 0)
        {
            OpenDoor();
            doorTestState = 1;
        }
        else
        {
            CloseDoor();
            doorTestState = 0;
        }
    }

    /* 5. LED 점멸 테스트 (1초 간격) */
    if (currentTick - ledTestTick >= 1000)
    {
        ledTestTick = currentTick;
        ledToggleState = !ledToggleState;

        for(int i = 0; i < LED_MAX; i++)
        {
            if (ledToggleState) {
                ledOn(i);
            } else {
                ledOff(i);
            }
        }
    }

    /* 6. 배열 LED (arrLED) 동작 테스트 */
    // 스텝모터의 현재 방향 상태를 가져와 배열 LED 애니메이션을 업데이트합니다.
    // 테스트 중이므로 임의로 상승(UP) 애니메이션을 가동할 수도 있습니다.
    ArrLed_Update(ARR_DIR_UP);
}
