/*
 * processor.h
 *
 * Created : 1/9/2019
 *  Author : n-is
 *   email : 073bex422.nischal@pcampus.edu.np
 */

#ifndef _PROCESSOR_H_
#define _PROCESSOR_H_

#include "state_sensor.h"
#include "robo_states.h"

class Processor
{
public:
        Processor(Processor &&) = default;
        Processor(const Processor &) = default;
        Processor &operator=(Processor &&) = default;
        Processor &operator=(const Processor &) = default;
        ~Processor() { }

        static Processor& get_Instance(State_Sensor *sen);
        
        int init(uint32_t dt_millis);
        Vec3<float> process(Vec3<float> state, State_Vars *robot_state_vars_, uint32_t dt_millis);

private:
        Robo_States *curr_state_;
        State_Sensor *sensor_;
        bool is_first_;
        Vec3<float> first_state_;
        
        Processor() { is_first_ = true; }

        void update_State();
};

#endif // !_PROCESSOR_H_
