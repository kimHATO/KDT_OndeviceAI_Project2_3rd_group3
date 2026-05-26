#include "servo.h"


void Init_Servo()
{
	TIM3->CCR1 = 100; 				// centeral servo first
	HAL_Delay(100);
	TIM3->CCR1 = 50;					// door close pos
}

bool IsServoBusy()
{
	if ()
}

void OpenDoor()
{

}

void CloseDoor()
{

}
