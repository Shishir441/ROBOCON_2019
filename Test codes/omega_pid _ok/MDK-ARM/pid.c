
/*
 * PID.c
 *
 * Created: 10/4/2018 6:12:32 PM
 * Author : Nirdesh
 */ 
#include "pid.h"
#include "defines.h"

void set_Gains(struct Str_pid* spid, double kp, double ki, double kd)
{
	spid->kp = kp;
	spid->ki = ki;
	spid->kd = kd;
}

void set_OutputLimit(struct Str_pid* spid, float max_output, float min_output)
{
	spid->max_output = max_output;
	spid->max_output  = max_output;
}

float pid_Compute(struct Str_pid* spid,float set_point, float input, uint16_t dt)
{ 

	float alpha = (1 + (spid->ki*dt/spid->kp)/1000);
	
	spid->output = spid->kp*(set_point - alpha*input) + spid->last_output;
	spid->last_output = spid->output;
	
	if(spid->output > (spid->max_output))
	{
		spid->output = (spid->max_output);
	}
	
	if(spid->output < (spid->min_output))
	{
		spid->output = (spid->min_output);
	}
		return (12/MAX_OMEGA)*spid->output;							
}

