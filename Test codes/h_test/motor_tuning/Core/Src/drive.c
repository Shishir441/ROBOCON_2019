#include "drive.h"

//const float Speed_Multiplier = 1;
//const float time = 1;
const int coupling_matrix[4][3] = {	{    1,    1,    1   },
					{    1,   -1,    1   },
					{   -1,   -1,    1   },
					{   -1,    1,    1   }	  };
float velocity[3];

void robot_direction(enum robot_direction dir)
{
	
	if(dir == FORWARD)
	{
		set_Direction(&Wheel_arr[0], DIR_ANTICLOCKWISE);
		set_Direction(&Wheel_arr[1], DIR_CLOCKWISE);
		set_Direction(&Wheel_arr[2], DIR_CLOCKWISE);
		set_Direction(&Wheel_arr[3], DIR_ANTICLOCKWISE);
	}
	if(dir == BACKWARD)
	{
		set_Direction(&Wheel_arr[0], DIR_CLOCKWISE);
		set_Direction(&Wheel_arr[1], DIR_ANTICLOCKWISE);
		set_Direction(&Wheel_arr[2], DIR_ANTICLOCKWISE);
		set_Direction(&Wheel_arr[3], DIR_CLOCKWISE);
	}
	if(dir == ROTATE)
	{
		set_Direction(&Wheel_arr[0], DIR_ANTICLOCKWISE);
		set_Direction(&Wheel_arr[1], DIR_ANTICLOCKWISE);
		set_Direction(&Wheel_arr[2], DIR_ANTICLOCKWISE);
		set_Direction(&Wheel_arr[3], DIR_ANTICLOCKWISE);
	}
	if(dir == STOP)
	{
		set_Direction(&Wheel_arr[0], DIR_HALT);
		set_Direction(&Wheel_arr[1], DIR_HALT);
		set_Direction(&Wheel_arr[2], DIR_HALT);
		set_Direction(&Wheel_arr[3], DIR_HALT);
	}
	
	
}

void robot_speed(int16_t speed)
{
	for(int i=0; i<4; i++)
	{
	set_DutyCycle(&Wheel_arr[i], speed );
	}
}

void calculate_robot_velocity()
{
        for (int i = 0; i < 4; i++)
        {
                Wheel_arr[i].velocity = 0;
                for (int j = 0; j < 3; j++)
                {
                        Wheel_arr[i].velocity += velocity[j] * coupling_matrix[i][j];
                }
		//ramp(Wheel_arr[i].id);
		set_ocr(&Wheel_arr[i], Wheel_arr[i].velocity);
        }
}

void ramp(int wheel_no)
{
	if( Wheel_arr[wheel_no].velocity < Wheel_arr[wheel_no].next_velocity)
		 Wheel_arr[wheel_no].velocity += 0.02;
	else if(Wheel_arr[wheel_no].velocity > Wheel_arr[wheel_no].next_velocity)
		Wheel_arr[wheel_no].velocity -= 0.035;
	else
	{
	}
		
	set_ocr(&Wheel_arr[wheel_no], Wheel_arr[wheel_no].velocity);	
}


