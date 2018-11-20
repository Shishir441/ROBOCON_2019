#include "drive.h"

//const float Speed_Multiplier = 1;
//const float time = 1;

const int coupling_matrix[4][3] = {	{    1,    1,    1   },
									{    1,   -1,    1   },
									{   -1,   -1,    1   },
									{   -1,    1,    1   }	  };
float velocity[3];
uint32_t ramp_counter;
extern float req_omega[4];

void calculate_robot_velocity()
{
        for (int i = 0; i < 4; i++)
        {
                Wheel_arr[i].next_velocity = 0;
                for (int j = 0; j < 3; j++)
                {
                        Wheel_arr[i].next_velocity += velocity[j] * coupling_matrix[i][j];
                }

		if(Wheel_arr[i].next_velocity >ROBOT_VELOCITY)
			Wheel_arr[i].next_velocity = ROBOT_VELOCITY;
		if(Wheel_arr[i].next_velocity < -ROBOT_VELOCITY)
			Wheel_arr[i].next_velocity = -	ROBOT_VELOCITY;																																																																	ROBOT_VELOCITY;
		ramp(Wheel_arr[i].id);

        }
}

void ramp(uint8_t wheel_no)
{
	if(Wheel_arr[wheel_no].velocity != Wheel_arr[wheel_no].next_velocity)
	{
		if( (Wheel_arr[wheel_no].velocity + RAMPING_FACTOR) < Wheel_arr[wheel_no].next_velocity)
			Wheel_arr[wheel_no].velocity += RAMPING_FACTOR;
		else if( (Wheel_arr[wheel_no].velocity - RAMPING_FACTOR) > Wheel_arr[wheel_no].next_velocity)
			Wheel_arr[wheel_no].velocity -= RAMPING_FACTOR;
		else
		{
			Wheel_arr[wheel_no].velocity= Wheel_arr[wheel_no].next_velocity;
		}
		req_omega[wheel_no] = (Wheel_arr[wheel_no].velocity*MAX_OMEGA)/MAX_VELOCITY;
	
		//set_Omega(&Wheel_arr[wheel_no], req_omega[wheel_no]);
		set_ocr(&Wheel_arr[wheel_no], Wheel_arr[wheel_no].velocity);
	}	
		//printf("%f\t%f\n",Wheel_arr[wheel_no].next_velocity,Wheel_arr[wheel_no].velocity );
}



