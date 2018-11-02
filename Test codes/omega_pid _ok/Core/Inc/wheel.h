/*
 * wheel.h
 *
 * Created : 10/1/2018
 */

#ifndef _WHEEL_H_
#define _WHEEL_H_

#include "stm32f4xx_hal.h"
#include "tim.h"

#include "defines.h"

enum Direction
{
        DIR_AHEAD,
        DIR_BACK,
        DIR_HALT
};

struct Wheel
{
        uint8_t id;
        float radius;
        float velcoity;

        float omega;

        GPIO_TypeDef *in1_port;
        uint16_t in1_pin;
        GPIO_TypeDef *in2_port;
        uint16_t in2_pin;

        TIM_HandleTypeDef *htim;
        uint32_t channel;
};

float float_abs(float x);
void calculate_omega(struct Wheel *w);
void set_Direction(struct Wheel *w, enum Direction d);
void set_DutyCycle_Primary(TIM_HandleTypeDef *htim, uint32_t Channel, uint16_t dutyCycle);
void set_DutyCycle(struct Wheel *w, uint16_t dutyCycle);
void set_Omega(struct Wheel *w, float omega);
uint16_t time_period(uint16_t PWM_frequency);

#endif // _WHEEL_H_
