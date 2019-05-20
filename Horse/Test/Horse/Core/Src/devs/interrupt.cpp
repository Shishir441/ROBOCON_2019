
#include "robo_init.h"

extern leg leg[2];
extern steering steering;

extern bool ROBOT_START_FLAG;
extern bool STEERING_FLAG;
extern bool FRONT_PROXIMITY_FLAG;
extern bool BACK_PROXIMITY_FLAG;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
        switch (GPIO_Pin) {
		case GPIO_PIN_0 : {
			ROBOT_START_FLAG = true;
			printf("\n\n\t\t\t !!start_pressed!!\n\n");
		}break;

                case GPIO_PIN_9 : {
                        leg[0].steps++;
			float leg0_reset_angle = 300*PI/180;
                        leg[0].reset_angle(leg0_reset_angle);
			//leg[0].reset_actual_angle(((leg[0].get_steps()-1)*2*3.14159265)+leg0_reset_angle);
			float temp = fmod(leg[0].get_actual_angle(), 360*PI/180);
			leg[0].reset_actual_angle((int)(temp) + leg0_reset_angle);
			printf("\n\n\t\t\tRobot interrupt0\t %d\n", leg[0].steps);
                } break;

                case GPIO_PIN_11: {
                        leg[1].steps++;
			float leg1_reset_angle = 290*PI/180;
                        leg[1].reset_angle(leg1_reset_angle);
			// leg[1].reset_actual_angle(((leg[1].get_steps()-1)*2*3.14159265)+leg1_reset_angle);
			float temp = fmod(leg[1].get_actual_angle(), 360*PI/180);
			leg[1].reset_actual_angle((int)(temp) + leg1_reset_angle);
			printf("\n\n\t\t\tRobot interrupt1\t %d\n", leg[1].steps);
                } break;

		case GPIO_PIN_15: {
			STEERING_FLAG = true;
			steering.reset_angle(0.7*PI/180);
			 printf("\n\n\t\t\tsteering interrupt \t\n");
                } break;

		case GPIO_PIN_8: {
			FRONT_PROXIMITY_FLAG = true;
		}

		case GPIO_PIN_10: {
			BACK_PROXIMITY_FLAG = true;
		}
        }
}