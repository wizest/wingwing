#include "drive.h"
#include "motor.h"
#include "sensor.h"
#include "algol.h"
#include "pathcvrt.h"
#include "run.h"
#include "adj_pos.h"
#include "key.h"
#include "led.h"
#include "delay.h"
#include "set_run.h"
#include "info.h"

int goal_pos;

void drive()	// automatic mode
{
	//set_run_scan_normal();
	set_run_iscan_normal();		// interSCAN

	//set_run_rush_slow();
	//set_run_rush_normal();
//	set_run_rush_fast();
	set_run_rush_very_fast();

	drive_one();
//	drive_one_R();
//	drive_one_R();

	drive_two();
//	set_run_rush_very_fast();
	drive_two();
	drive_two();	drive_two();
	drive_two();	drive_two();
	drive_two();	drive_two();
	drive_two();	drive_two();
	drive_two();	drive_two();
	drive_two();	drive_two();
}
void drive_one()		// Clear All walls and Explore
{
	torque_on();
	ss_on();
	led_count_down( 5, 300 );

	init_mouse();
	init_maze();

	reset_spd_ptr();	reset_steps();	reset_spd_diff();
	motor_start();

	goal_pos = SCAN_GOAL;	drive_scan_R();
	goal_pos = 0x00;		drive_scan_R();


	motor_stop();		sys_delay(200);		torque_off();
	ss_off();
}
void drive_one_R()		// Explore with known walls.	- rush mode
{
	torque_on();
	ss_on();
	led_count_down( 5, 300 );

	init_mouse();

	reset_spd_ptr();	reset_steps();	reset_spd_diff();
	motor_start();

	goal_pos = SCAN_GOAL; drive_scan_R();
	goal_pos = 0x00;	  drive_scan_R();

	motor_stop();		sys_delay(200);		torque_off();
	ss_off();
}
void drive_one_S()		// Explore with known walls.	- scan mode
{
	torque_on();
	ss_on();
	led_count_down( 5, 300 );

	init_mouse();

	reset_spd_ptr();	reset_steps();	reset_spd_diff();
	motor_start();

	goal_pos = SCAN_GOAL; drive_scan_S();
	goal_pos = 0x00;	  drive_scan_S();

	motor_stop();		sys_delay(200);		torque_off();
	ss_off();
}

void drive_two()		// Drive with RUSH RUNs
{
	torque_on();
	ss_on();
	led_count_down( 5, 300 );

	init_mouse();
	maze_wallup();

	reset_spd_ptr();	reset_steps();	reset_spd_diff();
	motor_start();

	goal_pos = SCAN_GOAL; drive_rush();
	maze_recover();
	goal_pos = 0x00;	  drive_scan_R();

	motor_stop();		sys_delay(200);		torque_off();
	ss_off();

}
void drive_scan_R()
{
	set_run_scan();

	//cvrt_mode = CVRT_SCAN_O;
	cvrt_mode = CVRT_SCAN_D;

	scan_maze(goal_pos);
	make_path();
	path_cvrt();

	get_run();
	// replace
	if ( mouse_pos == 0x00 	) run = run_aSHF;

	while( 1 )	{
		run();
		// run ptn empty! -> ending condition
		if ( !get_run()	) break;
	}

	// process finishing.......
		//maze_backup();
		// 1. Goal
		if (goal_pos == SCAN_GOAL)	run_sFX();
		maze_backup();

		// 2. Start
		if ( mouse_pos == 0x00 )	{
			run_aFHF();
			//adj_pos_V();
			adj_pos_HS();
			motor_stop();	sys_delay(100); motor_start();
			run_aTURN();
			init_mouse();
			torque_off();
			ss_off();
			save_maze();
			ss_on();
			torque_on();
		}
}
void drive_scan_S()
{
	set_run_scan();

	cvrt_mode = CVRT_SCAN_O;
	//cvrt_mode = CVRT_SCAN_D;

	scan_maze(goal_pos);
	make_path();
	path_cvrt();

	get_run();
	// replace
	if ( mouse_pos == 0x00 	) run = run_aSHF;

	while( 1 )	{
		run();
		// run ptn empty! -> ending condition
		if ( !get_run()	) break;
	}

	// process finishing.......
		//maze_backup();
		// 1. Goal
		if (goal_pos == SCAN_GOAL)	run_sFX();
		maze_backup();

		// 2. Start
		if ( mouse_pos == 0x00 )	{
			run_aFHF();
			//adj_pos_V();
			adj_pos_HS();
			motor_stop();	sys_delay(100); motor_start();
			run_aTURN();
			init_mouse();
			torque_off();
			ss_off();
			save_maze();
			ss_on();
			torque_on();
		}
}

void drive_rush()
{
	set_run_rush();

	cvrt_mode = CVRT_RUSH_D;

	scan_maze(goal_pos);
	make_path();
	path_cvrt();

	//run_aSACCL();
	get_run();

	// replace
	if ( mouse_pos == 0x00 	) 	{
		if 		(run == run_rFF)	run = run_aSFF;		// 0
		else if	(run == run_rFR)	run = run_aSFRL;	// 45
		else if (run == run_rFRF)	run = run_aSFRF;	// 90
		else if (run == run_rFRR)	run = run_aSFRRL;	// 135
	}

	while( 1 )	{
		run();
		if ( !get_run()	) break;
		// run ptn empty! -> ending condition
	}

	// process last path
	mouse_dir 	= get_absolute_dir((path[path_rptr-1]), mouse_dir);
	mouse_pos   = mouse_pos + dxy [ mouse_dir ];

	// process finishing.......
		// 1. Goal
		if (goal_pos == SCAN_GOAL)	run_aCHF();
}

