/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "stepper.h"
/* USER CODE END Includes */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_TIM11_Init();

  /* USER CODE BEGIN 2 */

  Stepper_Init(&htim11);

  /*
   * 스텝모터 테스트가 필요할 때만 주석 해제
   * 예: 1층에서 2층으로 이동
   */
   Stepper_MoveToFloor(2);

  /* USER CODE END 2 */

  while (1)
  {
      static uint8_t testState = 0;
          static uint32_t waitTick = 0;

          /*
           * 1층 -> 3층 이동
           */
          if (testState == 0)
          {
              Stepper_MoveToFloor(3);
              testState = 1;
          }

          /*
           * 3층 도착 확인
           */
          if (testState == 1 && !Stepper_IsBusy())
          {
              waitTick = HAL_GetTick();
              testState = 2;
          }

          /*
           * 2초 대기 후 1층으로 하강
           */
          if (testState == 2)
          {
              if (HAL_GetTick() - waitTick >= 2000)
              {
                  Stepper_MoveToFloor(1);
                  testState = 3;
              }
          }

          /*
           * 1층 도착 완료
           */
          if (testState == 3 && !Stepper_IsBusy())
          {
              testState = 4;
          }
    /*
     * main.c는 최대한 비워둠
     * 버튼, LED, LCD, 센서 담당 코드가 여기에 추가될 예정
     */

    /* 예시:
     * if (button_1_pressed) Stepper_MoveToFloor(1);
     * if (button_2_pressed) Stepper_MoveToFloor(2);
     * if (button_3_pressed) Stepper_MoveToFloor(3);
     * if (button_4_pressed) Stepper_MoveToFloor(4);
     */
  }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;

  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                              | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
}
#endif
