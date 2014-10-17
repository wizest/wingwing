#include "turn.h"
#include "motor.h"

void turn_left(int init_spd_ptr, int io_steps,int th_steps,int spd_dptr_L,int spd_dptr_R)
{
	// reference by steps_R !
	int goal_steps;

	spd_ptr = init_spd_ptr;
	reset_steps();

	spd_diff_L = -spd_dptr_L;
	spd_diff_R =  spd_dptr_R;
	goal_steps = io_steps;
	while( steps_R < goal_steps );

	spd_diff_L  = spd_diff_R = 0;
	goal_steps += th_steps;
	while( steps_R < goal_steps );

	spd_diff_L =  spd_dptr_L;
	spd_diff_R = -spd_dptr_R;
	goal_steps += io_steps;
	while( steps_R < goal_steps );

	reset_spd_diff();
	spd_ptr = init_spd_ptr;
}
void turn_right(int init_spd_ptr, int io_steps,int th_steps,int spd_dptr_L,int spd_dptr_R)
{
	// reference by steps_L !
	int goal_steps;

	spd_ptr = init_spd_ptr;
	reset_steps();

	spd_diff_L =  spd_dptr_L;
	spd_diff_R = -spd_dptr_R;
	goal_steps = io_steps;
	while( steps_L < goal_steps );

	spd_diff_L = spd_diff_R = 0;
	goal_steps += th_steps;
	while( steps_L < goal_steps );

	spd_diff_L = -spd_dptr_L;
	spd_diff_R =  spd_dptr_R;
	goal_steps += io_steps;
	while( steps_L < goal_steps );

	reset_spd_diff();
	spd_ptr = init_spd_ptr;
}

