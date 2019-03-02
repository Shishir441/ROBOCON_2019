#include "gait.h"

#define VELOCITY 3

extern struct Leg Leg[4];
extern struct Trap_struct Motion_Profile[4];
extern struct PID PID[4];

// Global flags
uint8_t _CALIBRATE_FLAG = 0;

void goto_Position(struct Leg *leg, float angle, float velocity)
{

}

void rewind_leg(struct Leg *leg)
{
	goto_Position(leg, 0, VELOCITY);
}

void start_Gallop()
{
	set_PneuPosition(&Leg[1], UP);
	/*for(uint8_t i = 0; i<3; i++)
	{
		if(Leg[i].status = UP)
		{
			rewind(&Leg[i]);

		}
		else
		{
			goto_Position&Leg[i], ((Leg.Motor.angle)+60), VELOCITY);
		}		
	}*/	
}

void set_HomePosition()
{
	while(!(Leg[0].home_position || Leg[1].home_position || Leg[2].home_position || Leg[3].home_position))
	{ 
        	HAL_Delay(2);
	}
	_CALIBRATE_FLAG = 1;
	TIM1->CNT = 0;
	TIM2->CNT = 0;
	TIM3->CNT = 0;
	TIM4->CNT = 0;
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN)
{
	if (GPIO_PIN == Leg[0].sw_pin )    // PC13 	for leg0
	{   
	 printf("Home: motor 1 \n");
		if(!_CALIBRATE_FLAG) set_Omega(&Leg[0], 0);
		Leg[0].home_position = 1;		
	}	
	if (GPIO_PIN == Leg[1].sw_pin)     // PE3		for leg1
	{      
	 printf("Home: motor 2 \n");
		if(!_CALIBRATE_FLAG) set_Omega(&Leg[1], 0);
		Leg[1].home_position = 1; 
	}		
	if (GPIO_PIN == Leg[2].sw_pin)     // PE5		for leg2
	{   
	 printf("Home: motor 3 \n");    
		if(!_CALIBRATE_FLAG) set_Omega(&Leg[2], 0);
		Leg[2].home_position = 1;
	}
	if (GPIO_PIN == Leg[3].sw_pin)     // PE1		for leg3
	{   
	 printf("Home: motor 4 \n");    
		if(!_CALIBRATE_FLAG) set_Omega(&Leg[3], 0);
		Leg[3].home_position = 1;
	}            
}
