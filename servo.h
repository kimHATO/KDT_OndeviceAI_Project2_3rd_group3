/*
 * servo.h
 *
 *  Created on: 2026. 5. 26.
 *      Author: user10
 */

#ifndef APPLICATION_USER_SERVO_H_
#define APPLICATION_USER_SERVO_H_

#include "main.h"
#include "gpio.h"
#include "tim.h"

#include <stdbool.h>

#define	SERVO_PORT				GPIOB
#define	SERVO_PIN				GPIO_PIN_5


enum {
	DOOR_CLOSED,
	DOOR_CLOSING,
	DOOR_OPENING,
	DOOR_OPENED
};


uint8_t ServoState = DOOR_CLOSED;
uint8_t ServoCurrentAngle = 0;

void Init_Servo();
bool IsServoBusy();
void OpenDoor();
void CloseDoor();







#define SERVO_PORT

#endif /* APPLICATION_USER_SERVO_H_ */
