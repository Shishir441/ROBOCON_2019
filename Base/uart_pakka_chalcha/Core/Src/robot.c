/*
 * robot.c
 *
 * Created : 10/1/2018
 */

#include "robot.h"
#include "pid.h"
#include  "usart.h"


extern struct encoder e[4];
extern float robotx, roboty, theta;
extern float actual_robotx, actual_roboty;
float required_dx, required_dy,required_theta;
float previous_robotx = 0, previous_roboty = 0;
float previous_dx, previous_dy;
double previous_distance = 0;
extern float velocity[3];
float time;
extern float distance_pid[3];
extern uint32_t ramp_counter;
extern float del_distance_pid[3];
extern struct Str_pid_distance pid_dis_1;
extern struct Str_pid_distance pid_dis_2;
extern struct Str_pid_distance pid_dis_3;
float data_from_navigator[3];
uint32_t receive_data_time, send_data_time;
// Constants that need to be modified according to robot's config


void play(void)
{
    uint8_t buffer[2];
	buffer[0] = 'a';
	while (1) 
	{	buffer[0] = 'F';
		if (HAL_UART_Receive(&huart2, buffer, 1, 2) == HAL_OK) 
		{
				//printf("%c",buffer[0]);
		}
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
				velocity[2] = -ROBOT_VELOCITY;
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
		if((HAL_GetTick()-send_data_time) >= 40)
		{
			send_velocity_to_u3();
			send_data_time = HAL_GetTick();
		}
		calculate_robot_distance();
      }
}


int goto_distance(float dx, float dy, float dth)
{
	
	double distance;
//	double temp_velocity;
	required_dx = dx;
    required_dy = dy;
	required_theta = dth;
	distance = pow((dx*dx + dy*dy + ((dth*WIDTH)/2)*((dth*WIDTH)/2)),0.5);
	time = distance/ROBOT_VELOCITY;
	calculate_robot_distance();	
	while((float_abs(del_distance_pid[0])>10) || (float_abs(del_distance_pid[1])>10) ||  (float_abs(distance_pid[0])>50) || (float_abs(distance_pid[1])>50))
	//while (float_abs(pow((pow((previous_robotx-robotx),2)+pow((previous_roboty-roboty),2)) , 0.5) - distance)> 10)
	{
		pid_distance();
		//calculate_velocity_with_pid();
		calculate_robot_velocity();
		calculate_robot_distance();
		if((HAL_GetTick()-receive_data_time) >= 20)
		{
			get_Navigator(data_from_navigator);
			receive_data_time = HAL_GetTick();
		}
		if((HAL_GetTick()-send_data_time) >= 40)
		{
			send_velocity_to_u3();
			send_data_time = HAL_GetTick();
		}
			//printf("%f \t%f \t%f \t%f \t%f \t%f \t%f \t%f \t%f \t%f\n",distance, velocity[0], velocity[1], velocity[2], actual_roboty, theta, Wheel_arr[0].velocity, Wheel_arr[1].velocity, Wheel_arr[2].velocity, Wheel_arr[3].velocity );			 
		//HAL_Delay(10);
		
	}
	
	printf("Finished \n");
	//HAL_Delay(1000);
	reset_robot_distance();
	previous_dx = dx;
	previous_dy = dy;
	previous_robotx = robotx;
	previous_roboty = roboty;
	printf("Finished \n");
	robotx = 0;
	roboty = 0;
	//HAL_Delay(1000);
	return 1;
}


int goto_absolute_distance(float dx, float dy)
{
	float time;
	double distance;
	double temp_velocity;
	double temp_distance = 0;
	dx -= previous_robotx;
	dy -= previous_roboty;
	distance = pow((dx*dx+dy*dy),0.5);
	time = distance/ROBOT_VELOCITY;			
	velocity[0] = dx / time;
	velocity[1] = dy / time;
	velocity[2] = 0;
	temp_velocity = float_abs(velocity[0]) + float_abs(velocity[1]);
	velocity[0] = velocity[0] * (ROBOT_VELOCITY / temp_velocity);	// this is to ensure that vx+vy = robot_velocity so that any motor donot exceed it
	velocity[1] = velocity[1] * (ROBOT_VELOCITY / temp_velocity);
	//reset_robot_distance();	 
	while( temp_distance < distance)
	{	
		temp_distance = pow((pow((previous_robotx-robotx),2)+pow((previous_roboty-roboty),2)) , 0.5);
		//calculate_velocity_with_pid();
		calculate_robot_distance();
		printf("%f \t%f \t%f \t%f \t%f \t%f \t%f \t%f \t%f\n",distance, velocity[0], velocity[1], robotx, roboty, dx, dy, previous_robotx, previous_roboty);			
	}
	printf("Finished \n");
	 velocity[0]=0;
	velocity[1]=0;
	velocity[2]=0;
	calculate_robot_velocity();
	previous_distance = distance;
	previous_robotx = robotx;
	previous_roboty = roboty;	
	printf("Finished \n");
	return 1;
}































