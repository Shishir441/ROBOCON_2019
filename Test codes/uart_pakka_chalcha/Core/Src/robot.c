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
// Constants that need to be modified according to robot's config


void play(void)
{
	//uint16_t speed=0;
	//int downcount=0;
      uint8_t buffer[2];
	buffer[0] = 'a';
	while (1) 
	{	buffer[0] = 'F';
		/*if (HAL_UART_Receive(&huart3, buffer, 1, 2) == HAL_OK) {
				printf("%c",buffer[0]);
		}
		buffer[0] = 'F';*/
		//send_velocity_to_u3();
		
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
	//calculate_robot_distance();
		//printf("%f \t%f \t%f \t%f \t%f \t%f \t%f \t%f\n", velocity[0], velocity[1], robotx, roboty, Wheel_arr[0].next_velocity, Wheel_arr[1].next_velocity, Wheel_arr[2].next_velocity, Wheel_arr[3].next_velocity);

      }
}

	/*	if (HAL_UART_Receive(&huart1, buffer, 1, 2) == HAL_OK)
		{	
			switch (buffer[0])
			{
				case 'F':
				{
					(pid_dis_1.kpp)+=0.1;
					break;
				}
				case 'B':
				{
					(pid_dis_1.kpp)-=0.1;
					break;
				}
				case 'L':
				{
					(pid_dis_1.kii)-=0.0001;
					break;
				}
				case 'R':
				{
					(pid_dis_1.kii)+=0.0001;
					break;
				}
				case 'G':
				{	
					(pid_dis_1.kdd)-=0.001;
					break;
				}
				case 'I':
				{
					(pid_dis_1.kdd)+=0.001;
					break;
				}
				case 'S':
				{
					break;
				}
				default:
				{
				}
					
			}
			
		}*/

int goto_distance(float dx, float dy, float dth)
{
	
	double distance;
//	double temp_velocity;
	required_dx = dx;
    required_dy = dy;
	required_theta = dth;
	//uint8_t buffer[2];
	//buffer[0] = 'a';
	/*//dx = dx - (previous_robotx-previous_dx);
	//dy = dy - (previous_roboty-previous_dy);
	distance = pow((dx*dx+dy*dy),0.5);
	time = distance/ROBOT_VELOCITY;
	//velocity[2] = 0;
	velocity[2] = -(theta  ) / time;
	temp_velocity = float_abs(velocity[0])	+ float_abs(velocity[1]) + float_abs(velocity[2]);
	velocity[0] = velocity[0] * (ROBOT_VELOCITY / temp_velocity);	// this is to ensure that vx+vy+vw = robot_velocity so that any motor donot exceed it
	velocity[1] = velocity[1] * (ROBOT_VELOCITY / temp_velocity);
*/
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































