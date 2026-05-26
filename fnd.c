#include "fnd.h"

/*
 * 공통 캐소드(Common Cathode)
 * HIGH = ON
 * LOW  = OFF
 */
#define SEG_ON   GPIO_PIN_SET
#define SEG_OFF  GPIO_PIN_RESET

static void FND_WriteSegments(uint8_t a,
                              uint8_t b,
                              uint8_t c,
                              uint8_t d,
                              uint8_t e,
                              uint8_t f,
                              uint8_t g)
{
    HAL_GPIO_WritePin(FND_A_PORT, FND_A_PIN, a ? SEG_ON : SEG_OFF);
    HAL_GPIO_WritePin(FND_B_PORT, FND_B_PIN, b ? SEG_ON : SEG_OFF);
    HAL_GPIO_WritePin(FND_C_PORT, FND_C_PIN, c ? SEG_ON : SEG_OFF);
    HAL_GPIO_WritePin(FND_D_PORT, FND_D_PIN, d ? SEG_ON : SEG_OFF);
    HAL_GPIO_WritePin(FND_E_PORT, FND_E_PIN, e ? SEG_ON : SEG_OFF);
    HAL_GPIO_WritePin(FND_F_PORT, FND_F_PIN, f ? SEG_ON : SEG_OFF);
    HAL_GPIO_WritePin(FND_G_PORT, FND_G_PIN, g ? SEG_ON : SEG_OFF);
}

void FND_Init(void)
{
    FND_Clear();
}

void FND_Clear(void)
{
    HAL_GPIO_WritePin(FND_A_PORT, FND_A_PIN, SEG_OFF);
    HAL_GPIO_WritePin(FND_B_PORT, FND_B_PIN, SEG_OFF);
    HAL_GPIO_WritePin(FND_C_PORT, FND_C_PIN, SEG_OFF);
    HAL_GPIO_WritePin(FND_D_PORT, FND_D_PIN, SEG_OFF);
    HAL_GPIO_WritePin(FND_E_PORT, FND_E_PIN, SEG_OFF);
    HAL_GPIO_WritePin(FND_F_PORT, FND_F_PIN, SEG_OFF);
    HAL_GPIO_WritePin(FND_G_PORT, FND_G_PIN, SEG_OFF);
}

void FND_DisplayNumber(uint8_t number)
{
    switch(number)
    {
        case 0:
            FND_WriteSegments(1,1,1,1,1,1,0);
            break;

        case 1:
            FND_WriteSegments(0,1,1,0,0,0,0);
            break;

        case 2:
            FND_WriteSegments(1,1,0,1,1,0,1);
            break;

        case 3:
            FND_WriteSegments(1,1,1,1,0,0,1);
            break;

        case 4:
            FND_WriteSegments(0,1,1,0,0,1,1);
            break;

        case 5:
            FND_WriteSegments(1,0,1,1,0,1,1);
            break;

        case 6:
            FND_WriteSegments(1,0,1,1,1,1,1);
            break;

        case 7:
            FND_WriteSegments(1,1,1,0,0,0,0);
            break;

        case 8:
            FND_WriteSegments(1,1,1,1,1,1,1);
            break;

        case 9:
            FND_WriteSegments(1,1,1,1,0,1,1);
            break;

        default:
            FND_Clear();
            break;
    }
}
