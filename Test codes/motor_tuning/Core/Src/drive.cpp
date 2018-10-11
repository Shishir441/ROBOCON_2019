 /*
 * robot.c
 *
 * Created : 10/1/2018
 */

#include "drive.h"


// Latest delta_x and delta_y as received

static float final_delta_x, final_delta_y;
static float curr_delta_x, curr_delta_y;\

static uint8_t isBraking;

static float try_Reach_Value(float curr_value, float final_value, float response)
{

        if (float_abs(curr_value - final_value) > response) {
                if (curr_value < final_value) {
                        curr_value += response;
                }
                else if (curr_value > final_value) {
                        curr_value = final_value;
                }
        }
        else {
                curr_value = final_value;
        }
        return curr_value;
}


static void get_UARTData()
{
        uint8_t buffer[9];
        for(uint8_t i = 0; i < 9; ++i) {
                if (HAL_UART_Receive(&huart1, buffer, 1, 2) == HAL_OK) {
                        if (buffer[0] == 's') {         // Start Byte Received
                                if (HAL_UART_Receive(&huart1, buffer, 9, 10) == HAL_OK) {
                                        final_delta_x = ((buffer[7] - 1) / 50.0) - 1;
                                        final_delta_y = ((buffer[8] - 1) / 50.0) - 1;
                                        if (buffer[3]) {
                                                final_delta_x = 0;
						final_delta_y = 0;
                                                isBraking = 1;
                                        }
                                        else {
                                                isBraking = 0;
                                        }
                                }
                                else {
                                        printf("Only Start Byte was Received\n");
                                }
                        }
                        break;
                }
        }
}

/*void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim)
{
}*/

void calculate_robot_velocity(float dx, float dy)
{
        float x,y;
        x = dx * Speed_Multiplier;
        y = dy * Speed_Multiplier;
        float velocity[3] = {x / time, y / time, 0};

        for (int i = 0; i < 4; i++)
        {
                motor[i].velcoity = 0;
                for (int j = 0; j < 3; j++)
                {
                        motor[i].velcoity += velocity[j] * Coupling_Matrix[i][j];
                }
                motor[i].calculate_omega();
        }
}

void run_CurrentConfig(void)
{
        for (uint8_t i = 0; i < 4; ++i) {
                motor[i].set_Omega(motor[i].omega);
        }
}

void play(void)
{
        uint32_t tick_start = HAL_GetTick();
        
        while (1) {

                if (HAL_GetTick() < tick_start) {
                        if ((HAL_GetTick() + (65535 - tick_start)) > 100L) {
                                tick_start = HAL_GetTick();
                                get_UARTData();
                        }
                }
                else {
                        if (HAL_GetTick() - tick_start > 100L) {
                                tick_start = HAL_GetTick();
                                get_UARTData();
                        }
                }

                if (!isBraking) {
                        curr_delta_x = try_Reach_Value(curr_delta_x, final_delta_x, HUMAN_RESPONSE);

                        curr_delta_y = try_Reach_Value(curr_delta_y, final_delta_y, HUMAN_RESPONSE);
                }
                else {
                        curr_delta_x = 0;
                        curr_delta_y = 0;
                }
                
                
                calculate_robot_velocity(curr_delta_x, curr_delta_y);
                run_CurrentConfig();

                HAL_Delay(5);
        }
}
