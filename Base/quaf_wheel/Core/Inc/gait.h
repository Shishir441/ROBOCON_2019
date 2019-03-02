#ifndef _GAIT_H_
#define _GAIT_H_

/*
	NOW	: Motion profile
	DO	: Pos PID
			eliminate angle variable
			enum for all flags
			Change the relatvie angle to absolute angle
*/

#include "stm32f4xx_hal.h"
#include "stdlib.h"
#include "leg.h"

void set_HomePosition(void);
void goto_Position(struct Leg *leg, float angle, float velocity);
void rewind_leg(struct Leg *leg);
void start_Gallop(void);



#endif /*_GAIT_H_*/
