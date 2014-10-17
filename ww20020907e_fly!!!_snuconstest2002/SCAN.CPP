#include "algol.h"
#include "sensor.h"
#include "sampling.h"
#include "run.h"
#include "adj.h"
#include "pathcvrt.h"
#include "drive.h"
#include "scan.h"
#include "motor.h"
#include "led.h"


void chk_walls(unsigned int c_pos, unsigned char m_dir)
{
	unsigned int i;
	unsigned char cnt_L0,cnt_R0,cnt_L45,cnt_R45;

	// Initiate.
	cnt_L0 = cnt_R0 = cnt_L45 = cnt_R45 = 0;

	// Count.
	for(i=0;i<SS_HISTORY_SIZE;i++)	{
		if (ss_history[SS_L45][i] > threshold_L45 ) cnt_L45++;
		if (ss_history[SS_R45][i] > threshold_R45 ) cnt_R45++;
		if (ss_history[SS_L0 ][i] > threshold_L0  ) cnt_L0++;
		if (ss_history[SS_R0 ][i] > threshold_R0  ) cnt_R0++;
	}

	// Decide the existance of walls.
	if ( cnt_L45 > 2 ) 				 maze[c_pos] |= wall_bit(get_absolute_dir(L,m_dir));
	if ( cnt_R45 > 2 )  			 maze[c_pos] |= wall_bit(get_absolute_dir(R,m_dir));
	//if ( cnt_L0  > 2 && cnt_R0 > 2 ) maze[c_pos] |= wall_bit(get_absolute_dir(F,m_dir));
	if ( cnt_L0  > 1 && cnt_R0 > 1 ) maze[c_pos] |= wall_bit(get_absolute_dir(F,m_dir));

	// Process walls of blocks around.
	unsigned char x,y;
	x = pos_x( c_pos ); y = pos_y( c_pos );
	if ( (maze[c_pos] & NORTH) && y < 15 )  maze[ c_pos + dxy[N] ] |= SOUTH;
	if ( (maze[c_pos] & EAST ) && x < 15 )  maze[ c_pos + dxy[E] ] |= WEST;
	if ( (maze[c_pos] & SOUTH) && y >  0 )  maze[ c_pos + dxy[S] ] |= NORTH;
	if ( (maze[c_pos] & WEST ) && x >  0 )  maze[ c_pos + dxy[W] ] |= EAST;

	// Check the block read.
	maze_info[ c_pos ] |= VALID_BLK;
}
void run_algol()
{
	// ALGOL /////////////////////////////////////////////////////////
	if ((maze_info[mouse_pos] & VALID_BLK) == 0)  {
		chk_walls(mouse_pos,mouse_dir);
		ss_pulse_slow();

		#ifdef DEBUG_ALGOL
			unsigned int	steps_checker = steps_L;
		#endif

		unsigned int v_dir;
		if ( run_fptr < run_rptr )	{
			if 		( run_queue[ run_fptr ] == run_sFX )	v_dir = get_absolute_dir(F,mouse_dir);
			else if ( run_queue[ run_fptr ] == run_sRX )	v_dir = get_absolute_dir(R,mouse_dir);
			else if ( run_queue[ run_fptr ] == run_sLX )	v_dir = get_absolute_dir(L,mouse_dir);
			else goto RUN_ALGOL;

			// Conditional running algorithm
			if ( (maze[mouse_pos] & wall_bit(v_dir)) == 0 )	{
				eyes_on();
				goto END_ALGOL;
			}
		}

		RUN_ALGOL:
		//ss_pulse_slow();
		eyes_off();

		disable_adj();
		scan_maze(goal_pos);
		make_path();
		path_cvrt();
		refresh_ss_history();
		enable_adj();

		//ss_pulse_fast();
		END_ALGOL:
		ss_pulse_fast();

		#ifdef 	DEBUG_ALGOL
			led_num((steps_L - steps_checker)/10);
			//led_num((steps_L - steps_checker));
		#endif
	}
	else eyes_on();
	//////////////////////////////////////////////////////////////////
}

