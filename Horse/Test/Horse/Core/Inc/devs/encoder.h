#ifndef _ENCODER_H_
#define _ENCODER_H_

#include "defines.h"
#include "stm32f4xx_hal.h"
#include "tim.h"
#include "math.h"


struct encoder_config{
	TIM_HandleTypeDef *henc;
	uint16_t ppr;
};

class encoder
{
public:
	encoder(){encoder_ = 0;}
	encoder(encoder_config *encoder){encoder_ = encoder;}
	encoder(encoder &&) = default;
	encoder(const encoder &) = default;
	encoder &operator=(encoder &&) = default;
	encoder &operator=(const encoder &) = default;
	~encoder(){}
        void set_config(encoder_config *encoder) { encoder_ = encoder; }

	float get_omega(void);
	void calculate_omega(void);
	float get_angle(void);
	float get_actual_angle(void);
	void reset_actual_angle(float angle_in_radian);
	void reset_angle(float);
	int32_t get_count();

private:
	encoder_config *encoder_;
	int32_t count_ = 0;
	float omega_ = 0;
	float angle_ = 0;
	float actual_angle_ = 0;
	int32_t actual_count_ = 0;
};


#endif //!_ENCODER_H_
