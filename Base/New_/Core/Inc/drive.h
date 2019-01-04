#ifndef _DRIVE_H_
#define _DRIVE_H_

#include "wheel.h"
#include "robo_init.h"

void calculate_robot_velocity(void);
void ramp(uint8_t wheel_no);

#endif //_DRIVE_H_
