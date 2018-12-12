#include "encoder.h"


struct encoder e[4];
float robotx = -450, roboty = 500;
//float robotx = 0, roboty = 0;
float actual_robotx = 0, actual_roboty = 0;
float theta =0;
float distance[2][3];		//set1, set2 (distancex, distancey, yaw)
extern int counts[4];
void init_encoder()
{
	for(int i=0; i<4; i++)
	{
		e[i].id = i;
	}
}

void calculate_encoder_distance(struct encoder *e)
{
	//Assuming that encoder count increases in anticlockwise direction
	if(e->id==0)
	{
		e->distance = -(e->count)*(CIRCUMFERENCE_OF_WHEEL/PPR);
	}
	else if(e->id==1)
	{
		e->distance = -(e->count)*(CIRCUMFERENCE_OF_WHEEL/PPR);
	}
	else if(e->id==2)
	{
		e->distance = (e->count)*(CIRCUMFERENCE_OF_WHEEL/PPR);	
	}
	else if(e->id==3)
	{
		e->distance = (e->count)*(CIRCUMFERENCE_OF_WHEEL/PPR);
	}
	else{}
}

void reset_robot_distance()
{
	actual_robotx = robotx;
	actual_roboty = roboty;
}

void calculate_robot_distance()
{
	static float d13 = 0, d24 = 0;
	int temp_count[4]; 
	for(int i=0;i<4;i++)
	{
		calculate_encoder_distance(&e[i]);
	}
	d13 = (e[0].distance + e[2].distance)/2;
	d24 = (e[1].distance + e[3].distance)/2;
	temp_count[0] = e[0].count;
	temp_count[1] = e[1].count;
	temp_count[2] = e[2].count;
	temp_count[3] = e[3].count;
	robotx += (-d24) * cos(theta + PI/4) - d13 * sin(theta + PI/4);	//this is to be modified according to robot motor direction
	roboty += (-d13) * cos(theta + PI/4) + d24 * sin(theta+PI/4);
	theta += (((e[2].distance - e[0].distance + e[3].distance - e[1].distance)/WIDTH)/2);//*(180/3.14159265359) //here the theta is in radian
	e[0].count -= temp_count[0];
	e[1].count -= temp_count[1];
	e[2].count -= temp_count[2];
	e[3].count -= temp_count[3];

}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
        switch (GPIO_Pin) {
                case GPIO_PIN_1 : {             // PA1
                        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0))
                        {
                                ++e[0].count;
				++counts[0];
                        }
                        else
                        {
                                --e[0].count;
				--counts[0];
                        }
                } break;

                case GPIO_PIN_7 : {             // PA7
                        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6))
                        {
                                ++e[1].count;
				++counts[1];
                        }
                        else
                        {
                                --e[1].count;
				--counts[1];
                        }
                } break;

                case GPIO_PIN_11 : {            // PE11
                        if (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_9))
                        {
                                ++e[2].count;
				++counts[2];
                        }
                        else 
                        {
                                --e[2].count;
				--counts[2];
                        }
                } break;

                case GPIO_PIN_13 : {            // PD13
                        if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_12))
                        {
                                ++e[3].count; 
				++counts[3];
                        }
                        else
                        {
                                --e[3].count;
				--counts[3];
                        }
                } break;

                default : {

                }
        }
}

