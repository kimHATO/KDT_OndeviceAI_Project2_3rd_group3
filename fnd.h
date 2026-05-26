#ifndef INC_FND_H_
#define INC_FND_H_

#include "main.h"

/* ===== FND Segment Pin Mapping =====
 *
 * 공통 캐소드(Common Cathode)
 * 3번, 8번 -> GND
 *
 * FND Pin Mapping
 * ----------------
 * a = 10
 * b = 9
 * c = 4
 * d = 2
 * e = 1
 * f = 7
 * g = 6
 */

/* a */
#define FND_A_PORT GPIOA
#define FND_A_PIN  GPIO_PIN_0

/* b */
#define FND_B_PORT GPIOA
#define FND_B_PIN  GPIO_PIN_1

/* c */
#define FND_C_PORT GPIOA
#define FND_C_PIN  GPIO_PIN_4

/* d */
#define FND_D_PORT GPIOB
#define FND_D_PIN  GPIO_PIN_0

/* e */
#define FND_E_PORT GPIOB
#define FND_E_PIN  GPIO_PIN_2

/* f */
#define FND_F_PORT GPIOB
#define FND_F_PIN  GPIO_PIN_3

/* g */
#define FND_G_PORT GPIOB
#define FND_G_PIN  GPIO_PIN_4

void FND_Init(void);
void FND_Clear(void);
void FND_DisplayNumber(uint8_t number);

#endif /* INC_FND_H_ */
