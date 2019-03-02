/*28-1-2019*/

#include "fsm_tasks.h"
#include "robo_states.h"

#define SINGLE_ANGLE    (40)

extern State gHorse_State;

void homePositionChores(struct fsmStr *fsm)
{
        setHomePosition();
        check_N_Stop();
}

static uint8_t gIs_First = 1;
void phaseOneChores(struct fsmStr *fsm)
{
        uint8_t motor_index = 0;
        float set_point = 0;

        for (uint8_t i = 0; i < 4; i++)
        {
                if (i != motor_index)
                {
                        ffSetAngle(&ff_arr[i], SINGLE_ANGLE);
                        getAngle(&motor_arr[i]);
                        getOmega(&motor_arr[i]);

                        set_point = ffGenerate(&ff_arr[i], motor_arr[i].angle);
                        motor_arr[i].update_omega = PID_Compute(&pid_arr[i],
                                                                set_point,
                                                                motor_arr[i].omega,
                                                                dt_ms);
                }
                else if (i == motor_index)
                {
                        if (gIs_First) {
                                motor_arr[i].update_omega = 0;
                                int_arr[i].intState = STATE_A;
                                gIs_First = 0;
                        }
                        else {
                                motor_arr[i].update_omega = HOME_POSITION_OMEGA;
                        }
                }
        }
}

void phaseTwoChores(struct fsmStr *fsm)
{
        uint8_t motor_index = 1;
        float set_point = 0;

        for (uint8_t i = 0; i < 4; i++)
        {
                if (i != motor_index)
                {
                        ffSetAngle(&ff_arr[i], SINGLE_ANGLE);

                        getAngle(&motor_arr[i]);
                        getOmega(&motor_arr[i]);

                        set_point = ffGenerate(&ff_arr[i], motor_arr[i].angle);
                        motor_arr[i].update_omega = PID_Compute(&pid_arr[i],
                                                                set_point,
                                                                motor_arr[i].omega,
                                                                dt_ms);
                }
                else {
                        motor_arr[i].update_omega = HOME_POSITION_OMEGA;
                }
        }
}

void phaseThreeChores(struct fsmStr *fsm)
{
        uint8_t motor_index = 2;
        float set_point;

        for (uint8_t i = 0; i < 4; i++)
        {
                if (i != motor_index)
                {
                        ffSetAngle(&ff_arr[i], SINGLE_ANGLE);

                        getAngle(&motor_arr[i]);
                        getOmega(&motor_arr[i]);

                        set_point = ffGenerate(&ff_arr[i], motor_arr[i].angle);
                        motor_arr[i].update_omega = PID_Compute(&pid_arr[i],
                                                                set_point,
                                                                motor_arr[i].omega,
                                                                dt_ms);
                }
                else {
                        motor_arr[i].update_omega = HOME_POSITION_OMEGA;
                }
        }
}

void phaseFourChores(struct fsmStr *fsm)
{
        uint8_t motor_index = 3;
        float set_point;

        for (uint8_t i = 0; i < 4; i++)
        {
                if (i != motor_index)
                {

                        ffSetAngle(&ff_arr[i], SINGLE_ANGLE);

                        getAngle(&motor_arr[i]);
                        getOmega(&motor_arr[i]);

                        set_point = ffGenerate(&ff_arr[i], motor_arr[i].angle);
                        motor_arr[i].update_omega = PID_Compute(&pid_arr[i],
                                                                set_point,
                                                                motor_arr[i].omega,
                                                                dt_ms);
                }
                else {
                        motor_arr[i].update_omega = HOME_POSITION_OMEGA;
                }
        }
}

void setHomePosition(void)
{
        setDutyCycle(&balance_motor, 65535);
        setDirection(&balance_motor, DIR_ANTICLOCKWISE);

        for (uint8_t i = 0; i < 4; i++)
        {
                motor_arr[i].update_omega = HOME_POSITION_OMEGA;
        }
}

void check_N_Stop(void)
{
        for (uint8_t i = 0; i < 4; i++)
        {
                if (int_arr[i].fhome_pos)
                {
                        motor_arr[i].update_omega = 0;
                        // resetAngle(&motor_arr[i]);
                        motor_arr[i].encoder->htim->Instance->CNT = 0;
                }
        }
        // if (blnc_int_arr[2].fhome_pos == 1)
        // {
        //         setDutyCycle(&balance_motor, 0);
        // }
}

void updateOmegas(void)
{
        for (uint8_t i = 0; i < 4; i++)
        {
                setOmega(&motor_arr[i], motor_arr[i].update_omega);
        }
}

void resetAngles(void)
{
        for (uint8_t i = 0; i < 4; i++)
        {
                resetAngle(&motor_arr[i]);
        }
}

void resetPID(void)
{
        for (uint8_t i = 0; i < 4; i++)
        {
                PID_resetParams(&pid_arr[i]);
        }
}

void stateReset()
{
        resetPID();
        resetAngles();
        omegaReset();
        resetIntState();
        feedForwardRestart();
}

void omegaReset(void)
{
        for (uint8_t i = 0; i < 4; i++)
        {
                motor_arr[i].update_omega = 0;
        }
}

void feedForwardRestart(void)
{
        for (uint8_t i = 0; i < 4; i++)
        {
                ffRestart(&ff_arr[i]);
        }
}

void resetIntState()
{
        switch(gHorse_State.get_ID())
        {
                case State_ID::HOME:
                        break;


                case State_ID::WS1:
                        int_arr[0].intState = STATE_B;
                        int_arr[1].intState = STATE_A;
                        int_arr[2].intState = STATE_A;
                        int_arr[3].intState = STATE_A;
                        break;

                case State_ID::WS2:
                        int_arr[0].intState = STATE_A;
                        int_arr[1].intState = STATE_B;
                        int_arr[2].intState = STATE_A;
                        int_arr[3].intState = STATE_A;
                        break;

                case State_ID::WS3:
                        int_arr[0].intState = STATE_A;
                        int_arr[1].intState = STATE_A;
                        int_arr[2].intState = STATE_B;
                        int_arr[3].intState = STATE_A;
                        break;

                case State_ID::WS4:
                        int_arr[0].intState = STATE_A;
                        int_arr[1].intState = STATE_A;
                        int_arr[2].intState = STATE_A;
                        int_arr[3].intState = STATE_B;
                        break;
        }
}
