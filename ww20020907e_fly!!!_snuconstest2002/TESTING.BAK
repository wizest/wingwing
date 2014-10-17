#include "testing.h"
#include "motor.h"
#include "key.h"
#include "led.h"
#include "sensor.h"
#include "drive.h"
#include "adj.h"
#include "swing.h"
#include "run.h"
#include "delay.h"
#include "algol.h"
#include "edge.h"
#include "sound.h"
#include "sampling.h"
#include "adj_pos.h"
#include "turn.h"
#include "set_run.h"
#include "algol.h"


///////////////////////////////////////////////////////////////////////////
// Test Module															 //
///////////////////////////////////////////////////////////////////////////
void testing()
{
/*
	int item = 0;
	while(1)
	{
		led_num( item );
		if ( R_KEY == read_key() )
		{
			item++;
			Sound_Beep();
		}
		else
		{
			Sound_Select();
			// blink LED //////////////////////////
			led_off( PIO_LED_ALL );	sys_delay(100);
			led_num( item );		sys_delay(100);
			led_off( PIO_LED_ALL );	sys_delay(100);
			led_num( item );		sys_delay(100);
			///////////////////////////////////////
			switch(item)
			{
				case 0 : motor_test();				 break;
				case 1 : swing_test();				 break;
				case 2 : run_test();  				 break;
				case 3 : edge_dn_90_test();			 break;
				case 4 : edge_dn_45_test();			 break;
				case 5 : watch_test();     			 break;
				case 6 : adj_pos();        			 break;
				case 7 : show_ss_threshold();		 break;
				case 8 : adj_F_45_test();		 break;
				case 9 : adj_DF_0_test(); 		 break;
			}
			led_show();
			item = 0;
			goto END;
		}
		item = ( item > 9 ) ? 0 : item;
	}
	END:
*/
}
void watch_test()
{
/*
	torque_on();
	wait_key();
	led_count_down( 9, 1000 );

	ss_on();
	sys_delay(150);

	reset_spd_ptr();
	reset_steps();

	spd_ptr = 30;
	spd_diff = 0;

	motor_start();

	#define pSTOP	FWCSTEP + HALFBLK - 62
	while( sFL0[pSTOP] > ss_value[SS_L0] || sFR0[pSTOP] > ss_value[SS_R0] );

	motor_stop();
	ss_off();

	wait_key();
	torque_off();
*/
}
void turn_test()
{
/*
	torque_on();
	wait_key();
	led_count_down( 9, 1000);

	reverse_LR();
	reset_spd_ptr();

	motor_start();

	#define	iSpd	200

	reset_steps();
	while(steps < iSpd);

	motor_stop();
	sys_delay(100);
	reverse_LR();

	motor_start();
	reset_steps();

	reset_steps(); spd_diff = +1;
	while(steps < iSpd);

	spd_diff = 0;

	turn_right(200,117,247,2,2);
	turn_right(200,117,247,2,2);
	turn_right(200,117,247,2,2);
	turn_right(200,117,247,2,2);

	motor_stop();
*/
}
void motor_test()
{
	/*
	//led_show();

	torque_on();
	ss_on();

	wait_key();
	led_count_down( 9, 1000 );

	enable_adj();

	motor_start();
	reset_spd_ptr();

	#define aSTP	200
	#define uSTP	ONEBLK*10

	// ENACCL
	spd_diff = 1; 	reset_steps();
	while(steps < aSTP)			adj_O();
	// UNIF
	spd_diff = 0;	reset_steps();
	while(steps < uSTP) 		adj_O();
	//while(1)		adj_O();

	// DEACCL
	spd_diff = -1;	reset_steps();
	while(steps < aSTP)			adj_O();

	motor_stop();
	ss_off();
	sys_delay(1000);
	torque_off();

	ss_off();
	*/

}

void adj_O_test()
{
	#define aSTP		2300//940//(ONEBLK * 3)
	#define uSTP		0//(ONEBLK*4)//(ONEBLK * 4)
	#define NADJ_STP	10

	torque_on();
	wait_key();

	ss_pulse_fast();
	ss_on();


	int i=0;
	while(i++<10)	{

		led_count_down( 5, 500 );


		reset_steps();
		reset_spd_ptr();
		spd_diff = 1;

		motor_start();

		while(steps < NADJ_STP);
		enable_adj();
		while(steps < aSTP)	{
				adj_O();
				sync_step();
		}

		spd_diff = 0;	reset_steps();
		while(steps < uSTP)	{
			adj_O();
			sync_step();
		}
		spd_diff = -1;	reset_steps();
		while(steps < aSTP-NADJ_STP)	{
			adj_O();
			sync_step();
		}
		disable_adj();
		while(steps < aSTP)	;

		motor_stop();
		sys_delay(1000);

		torque_off();
		wait_key();
		torque_on();

//		run_aTURN();

	}

	torque_off();
	ss_off();
}
void adj_DF_0_test()
{
/*
	torque_on();
	wait_key();
	led_count_down( 9, 1000 );

	ss_on();	sys_delay(200);
	enable_adj();

	refresh_ss_history();
	motor_start();
	reset_steps();
	reset_spd_ptr();
	spd_diff = 1;
	while(steps < ONEBLK * 2)	{
		adj_DF_0();
	}
	spd_diff=0;
	reset_steps();
	while(steps < ONEBLK * 7)
//	while(get_key_state()==0)
	{
		adj_DF_0();
	}
	spd_diff = -1;
	reset_steps();
	while(steps < ONEBLK * 2)	{
		adj_DF_0();
	}
	motor_stop();
	torque_off();

	ss_off();
*/
}
void swing_test()
{
/*
	torque_on();
	wait_key();
	led_count_down( 9, 1000 );

	for(int i=50;i>0;i-=10)		{
		swing(i);
		swing(-i);
	}

	torque_off();
*/
}
void edge_dn_45_test()
{
/*
	torque_on();
	wait_key();
	led_count_down( 9, 1000 );

	//ss_start();
	ss_on();

	reset_spd_ptr();
	reset_spd_diff();
	reset_steps();

	motor_start();

	spd_diff = 1;
	while(steps<70)
	{
		adj_F_45();
	}
	spd_diff = 0;

	refresh_level(); refresh_edge();
	while( 1 )	{
		if (edge_info_L45 == EDGE_DN ||
			edge_info_R45 == EDGE_DN ) break;
		scan_level(); scan_edge();
		adj_F_45();
	}

	motor_stop();

	ss_off();
	//ss_stop();

	wait_key();
	torque_off();
*/
}
void edge_dn_90_test()
{
   /*
	torque_on();
	wait_key();
	led_count_down( 9, 1000 );

	ss_on();

	reset_spd_ptr();
	reset_spd_diff();
	reset_steps();
	enable_adj();

	motor_start();

	spd_diff = 1;
	while(steps < 20)	adj_O();
	spd_diff = 0;
	equal_spd_ptr();

	refresh_level();
	refresh_edge();
	while( 1 )	{
		if ( edge_info_L90 == EDGE_DN ||
			 edge_info_R90 == EDGE_DN ) break;
		scan_level_D(); scan_edge();
		adj_O();
	}
	reset_steps();
	while(steps < ONEBLK - EDGESTEP_90 )	adj_O();

	motor_stop();
	ss_off();

	wait_key();
	torque_off();
	*/
}

