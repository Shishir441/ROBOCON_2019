/*
 * robot.c
 *
 * Created : 10/1/2018
 */

#include "robot.h"
#include "pid.h"


extern struct encoder e[4];
extern float robotx, roboty;
extern float velocity[3];
extern uint32_t ramp_counter;
// Constants that need to be modified according to robot's config


void play(void)
{
	//uint16_t speed=0;
	//int downcount=0;
        uint8_t buffer[2];
	buffer[0] = 'a';
        while (1) 
	{
		
                if (HAL_UART_Receive(&huart1, buffer, 1, 2) == HAL_OK)
		printf("%c",buffer[0]);
		
		/*if(HAL_OK==HAL_UART_Transmit(&huart1,buffer,1,0xFFFF))
			printf("OK");
		else
			printf("NOT");*/
		//HAL_UART_Transmit(&huart1,buffer,1,0xFFFF)
		//printf("%c",(HAL_UART_Transmit(&huart1,buffer,1,0xFFFF)));
		//HAL_Delay(500);
		//HAL_UART_Transmit(&huart1,(uint8_t *)&buffer,2,2);
		//HAL_UART_Transmit(&huart1,(uint8_t *)&buffer,1,2);
		
		switch (buffer[0])
		{
			case 'F':
			{
				velocity[0] = 0;
				velocity[1] = ROBOT_VELOCITY;
				velocity[2] = 0;
				break;
			}
			case 'B':
			{
				velocity[0] = 0;
				velocity[1] = -ROBOT_VELOCITY;
				velocity[2] = 0;
				break;
			}
			case 'L':
			{
				velocity[0] = -ROBOT_VELOCITY;
				velocity[1] = 0;
				velocity[2] = 0;
				break;
			}
			case 'R':
			{
				velocity[0] = ROBOT_VELOCITY;
				velocity[1] = 0;
				velocity[2] = 0;
				break;
			}
			case 'G':
			{	
				velocity[0] = -ROBOT_VELOCITY/2;
				velocity[1] = ROBOT_VELOCITY/2;
				velocity[2] = 0;
				break;
			}
			case 'I':
			{
				velocity[0] = ROBOT_VELOCITY/2;
				velocity[1] = ROBOT_VELOCITY/2;
				velocity[2] = 0;
				break;
			}
			case 'H':
			{
				velocity[0] = 0;
				velocity[1] = 0;
				velocity[2] = ROBOT_VELOCITY;
				break;
			}
			case 'J':
			{
				velocity[0] = 0;
				velocity[1] = 0;
				velocity[2] = ROBOT_VELOCITY;
				break;
			}
			case 'S':
			{
				
				velocity[0] = 0;
				velocity[1] = 0;
				velocity[2] = 0;;
				break;

			}
			default:
			{
			}
				
		}
		
                calculate_robot_velocity();
                //run_CurrentConfig();
        }
}

int goto_distance(float dx, float dy)
{
	
	float time;
	double distance;
	
	double temp_velocity;
	distance = pow((dx*dx+dy*dy),0.5);
	time = distance/ROBOT_VELOCITY;			
	velocity[0] = dx / time;
	velocity[1] = dy / time;
	velocity[2] = 0;
	temp_velocity = float_abs(velocity[0])	+ float_abs(velocity[1]);
	velocity[0] = velocity[0] * (ROBOT_VELOCITY / temp_velocity);	// this is to ensure that vx+vy = robot_velocity so that any motor donot exceed it
	velocity[1] = velocity[1] * (ROBOT_VELOCITY / temp_velocity);
	
	reset_robot_distance();
		
	while(((pow((robotx*robotx + roboty*roboty),0.5)) <= distance))
	{	
		calculate_velocity_with_pid();
		//calculate_robot_velocity();
		calculate_robot_distance();
		printf("%f \t%f \t%f \t%f \t%f \t%f \t%f \t%f \t%f\n",distance, velocity[0], velocity[1], robotx, roboty, Wheel_arr[0].next_velocity, Wheel_arr[1].next_velocity, Wheel_arr[2].next_velocity, Wheel_arr[3].next_velocity);			
	}
	printf("Finished \n");
	//HAL_Delay(1000);
	reset_robot_distance();
	printf("Finished \n");
	//HAL_Delay(1000);
	return 1;
}

































