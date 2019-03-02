/*
 * leg.c
 *
 * Created : 12/13/2018
 */

#include "leg.h"

/* SET DUTYCYCLE primary function */
void set_DutyCycle_Primary(TIM_HandleTypeDef *htim, uint32_t Channel, uint16_t dutyCycle)
{
        uint16_t mapped_value;
        mapped_value = (10499 * dutyCycle) / 65535;
        __HAL_TIM_SET_COMPARE(htim, Channel, mapped_value);
}

void set_MotorDirection(struct Leg *leg, enum motor_Status d)
{
	if (d == FORWARD)       
	{
		HAL_GPIO_WritePin(leg->Motor.dir1_port, leg->Motor.dir1_pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(leg->Motor.dir2_port, leg->Motor.dir2_pin, GPIO_PIN_RESET);
	}
	else if (d == BACKWARD)
	{
		HAL_GPIO_WritePin(leg->Motor.dir1_port, leg->Motor.dir1_pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(leg->Motor.dir2_port, leg->Motor.dir2_pin, GPIO_PIN_SET);
	}
	else if (d == HALT)
	{
		HAL_GPIO_WritePin(leg->Motor.dir1_port, leg->Motor.dir1_pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(leg->Motor.dir2_port, leg->Motor.dir2_pin, GPIO_PIN_RESET);
	}
	else if(d == BRAKE)
	{
		HAL_GPIO_WritePin(leg->Motor.dir1_port, leg->Motor.dir1_pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(leg->Motor.dir2_port, leg->Motor.dir2_pin, GPIO_PIN_SET);
	}
}


void set_DutyCycle(struct Leg *leg, uint16_t dutyCycle)
{
        set_DutyCycle_Primary(leg->Motor.htim, leg->Motor.channel, dutyCycle);
}

void set_Omega(struct Leg *leg, float omega)
{
        uint16_t new_omega = (65535.0 / MAX_OMEGA) * fabs(omega);
        if (omega > 0) {
                set_MotorDirection(leg, FORWARD);
                set_DutyCycle(leg, new_omega);
        }
        else if (omega < 0) {
                set_MotorDirection(leg, BACKWARD);
                set_DutyCycle(leg, new_omega);
        }
        else {
                set_MotorDirection(leg, BRAKE);
                set_DutyCycle(leg, 0);
        }
}

void set_PneuPosition(struct Leg *leg, enum leg_Status p)
{
	if(p == UP)
	{
		HAL_GPIO_WritePin(leg->pneu_port, leg->pneu_pin,GPIO_PIN_SET);
		leg->Status = UP;
	}
	else if(p == DOWN)
	{
		HAL_GPIO_WritePin(leg->pneu_port,leg->pneu_pin,GPIO_PIN_RESET);
		leg->Status = DOWN;
	}
}

float calculate_omega(struct Leg *leg)
{
	int16_t cps = (leg->Motor.previous_cnt)-(leg->Motor.henc->Instance->CNT);
	leg->Motor.previous_cnt = leg->Motor.henc->Instance->CNT;
	float omega = 1.0471955 * (cps / 10);	//2*3.14159*1000.0/ppr,   ppr = 4000, sample_time = 10
	return omega;
}

float calculate_Angle(struct Leg *leg)
{
	leg->Motor.angle = (leg->Motor.henc->Instance->CNT)*(360/6000); 
	return (leg->Motor.angle);
}

