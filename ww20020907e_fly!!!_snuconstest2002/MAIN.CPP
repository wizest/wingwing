////////////////////////////////////////////////////////////////////////////
//				   _      ___          _      ___                         //
//				  | | /| / (_)__  ___ | | /| / (_)__  ___ _               //
//				  | |/ |/ / / _ \/ _ `/ |/ |/ / / _ \/ _ `/               //
//	 	          |__/|__/_/_//_/\_, /|__/|__/_/_//_/\_, /                //
//	              		        /___/               /___/                 //
//                                                                        //
// - - - - - - - - - - - - - -[ WingWing ]- - - - - - - - - - - - - - - - //
//																		  //
//	 Author : Kim Sang-hoon                                               //
//			  1999-2002													  //
//                                                                        //
// 			wizest@hanmail.net                                            //
//			http://wingwing.pe.kr										  //
//	      	http://hands.korea.ac.kr/~wizest                              //
//                                                                        //
// 			HandS Institute. (http://hands.korea.ac.kr)                   //
// 			School of Electrical Engineering.                             //
// 			Korea University.                                             //
//          			                                                  //
////////////////////////////////////////////////////////////////////////////


#include "init_sys.h"
#include "led.h"
#include "key.h"
#include "sound.h"
#include "delay.h"
#include "sampling.h"
#include "drive.h"
#include "sensor.h"
#include "testing.h"
#include "adj_pos.h"
#include "info.h"
#include "set_run.h"
#include "flash.h"
#include "tuning.h"
#include "serial.h"


void menu();

void main()
{
	init_system();
	load_sampl_value();
	maze_recover();

//	Sound_Start();

	menu();
}

void menu()
{
	while( 1 )	{
		// Sampling				- S	//////////////////////////////////////
		led_off(PIO_LED_ALL);
		led_on (PIO_LED_2|PIO_LED_6|PIO_LED_3);
		if ( L_KEY == read_key() )	{
			Sound_Select();
			ss_sampl();
			led_show();
		}	else Sound_Beep();

		// Auto Driving			- A //////////////////////////////////////
		led_on(PIO_LED_ALL);
		led_off(PIO_LED_3);
		if ( L_KEY == read_key() )	{
			Sound_Select();
			drive();
			led_show();
		}	else Sound_Beep();

		// Scan Maze (Rush mode)- 1 //////////////////////////////////////
		led_num(1);
		if ( L_KEY == read_key() )	{
			Sound_Select();
			set_run_iscan_normal();
			set_run_rush_very_fast();
			drive_one_R();	// Rush mode
			drive_two();		drive_two();
			drive_two();		drive_two();
			drive_two();		drive_two();
			led_show();
		}	else Sound_Beep();
		// Scan Maze (Scan mode)- 2 //////////////////////////////////////
		led_num(2);
		if ( L_KEY == read_key() )	{
			Sound_Select();
			set_run_iscan_normal();
			set_run_rush_very_fast();
			drive_one_S();	// Scan mode
			drive_two();		drive_two();
			drive_two();		drive_two();
			drive_two();		drive_two();
			led_show();
		}	else Sound_Beep();

		// Second Driving (iSCAN) - 3 /////////////////////////////////////
		// Slow
		led_num(3);
		if ( L_KEY == read_key() )	{
			Sound_Select();
			set_run_rush_slow();
			drive_two();
//			set_run_rush_very_fast();
			drive_two();		drive_two();
			drive_two();		drive_two();
			drive_two();		drive_two();
			led_show();
		}	else Sound_Beep();
		// Second Driving    	- 4 //////////////////////////////////////
		// Normal
		led_num(4);
		if ( L_KEY == read_key() )	{
			Sound_Select();
			set_run_rush_normal();
			drive_two();
//			set_run_rush_very_fast();
			drive_two();		drive_two();
			drive_two();		drive_two();
			drive_two();		drive_two();
			led_show();
		}	else Sound_Beep();
		// Second Driving 2    	- 5 //////////////////////////////////////
		// Fast
		led_num(5);
		if ( L_KEY == read_key() )	{
			Sound_Select();
			set_run_rush_fast();
			drive_two();
//			set_run_rush_very_fast();
			drive_two();		drive_two();
			drive_two();		drive_two();
			drive_two();		drive_two();
			led_show();
		}	else Sound_Beep();
		// Second Driving 3    	- 6 //////////////////////////////////////
		// Very Fast
		led_num(6);
		if ( L_KEY == read_key() )	{
			Sound_Select();
			set_run_rush_very_fast();
			drive_two();
			drive_two();		drive_two();
			drive_two();		drive_two();
			drive_two();		drive_two();
			led_show();
		}	else Sound_Beep();
		// Load Maze			- M //////////////////////////////////////
		led_off(PIO_LED_ALL);
		led_on (PIO_LED_2|PIO_LED_6|PIO_LED_0|PIO_LED_1|PIO_LED_3);
		if ( L_KEY == read_key() )	{
			Sound_Select();
			load_maze();
			led_show();
		}	else Sound_Beep();


		// Save Program			- P //////////////////////////////////////
		led_off(PIO_LED_ALL);
		led_on (PIO_LED_2|PIO_LED_0|PIO_LED_6|PIO_LED_1|PIO_LED_5);
		if ( L_KEY == read_key() )	{
			Sound_Select();
			SaveProgram();
			led_show();
		}	else Sound_Beep();
		// Tuning				- t //////////////////////////////////////
		led_off(PIO_LED_ALL);
		led_on (PIO_LED_0|PIO_LED_6|PIO_LED_1|PIO_LED_3);
		if ( L_KEY == read_key() )	{
			Sound_Select();
			tune();
			led_show();
		}	else Sound_Beep();

		// Show Infomation		- i //////////////////////////////////////
		led_off(PIO_LED_ALL);
		led_on (PIO_LED_1|PIO_LED_2|PIO_LED_3|PIO_LED_6|PIO_LED_4);
		if ( L_KEY == read_key() )	{
			Sound_Select();
			show_info();
			led_show();
		}	else Sound_Beep();
		// Led Show				- L /////////////////////////////////////
		led_off(PIO_LED_ALL);
		led_on (PIO_LED_0|PIO_LED_1|PIO_LED_3);
		if ( L_KEY == read_key() )	{
			Sound_Select();
			while(!get_key_state())		led_show();
		}	else Sound_Beep();

		// Forward Test - 8 //////////////////////////////////////////////
		led_num(8);
		if ( L_KEY == read_key() )	{
			Sound_Select();
			adj_O_test();
//			Sound_Test();
//			Sound_Track(Track1);
			led_show();
		}	else Sound_Beep();


/*
		// Temp - 9
		led_num(9);
		if ( L_KEY == read_key() )	{
			Sound_Select();
//			adj_O_test();
//			Sound_Test();
			Sound_Track(Wing_OST);
			led_show();
		}	else Sound_Beep();
*/

	}
}
