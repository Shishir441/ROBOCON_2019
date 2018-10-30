/*
 * robot.c
 *
 * Created : 10/1/2018
 */

#include "robot.h"

extern struct encoder e[4];
extern float robotx, roboty;
extern float velocity[3];
extern uint32_t ramp_counter;
// Constants that need to be modified according to robot's config



void play(void)
{
	//uint16_t speed=0;
	//int downcount=0;
        uint8_t buffer[1];
        while (1) 
	{
		
                if (HAL_UART_Receive(&huart1, buffer, 1, 2) == HAL_OK)
		printf("%c",buffer[0]);
		/*if(speed<58000)
			speed += 500;
		//robot_speed(speed);
		if(buffer[0]!='S')
			downcount=20;*/
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
				
				/*if(downcount>0)
				{
					speed -=2000;
					downcount--;
					break;
				}*/
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
	//HAL_Delay(300);
	float time;
//	ramp_counter = HAL_GetTick();


	double distance;
	double temp_velocity;
	distance = pow((dx*dx+dy*dy),0.5);
	time = distance/ROBOT_VELOCITY;			
	velocity[0] = dx / time;
	velocity[1] = dy / time;
	velocity[2] = 0;
	temp_velocity = float_abs(velocity[0] + velocity[1]);
	velocity[0] = velocity[0] * (ROBOT_VELOCITY / temp_velocity);	// this is to ensure that vx+vy = robot_velocity so that any motor donot exceed it
	velocity[1] = velocity[1] * (ROBOT_VELOCITY / temp_velocity);
	
	reset_robot_distance();
		
	while(((pow((robotx*robotx + roboty*roboty),0.5))<distance))
	{	
		
		calculate_robot_velocity();
		calculate_robot_distance();
		printf("%f \t%f \t%f \t%f \t%f \t%f \t%f\n",distance, velocity[0], velocity[1], robotx, roboty,Wheel_arr[0].next_velocity, Wheel_arr[1].next_velocity);
		//printf("%d \t%d \t%d \t%d \t%f \t%f\n", e[0].count, e[1].count, e[2].count, e[3].count, robotx, roboty);
		//if(((float_abs(robotx)-float_abs(dx))>=0)&&((float_abs(roboty)-float_abs(dy))>=0))
			
	}
	velocity[0]=0;
	velocity[1]=0;
	velocity[2]=0;
	calculate_robot_velocity();
	printf("Finished \n");
	printf("Finished \n");
	//HAL_Delay(1000);
	return 1;
}
