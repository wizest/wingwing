#include "tuning.h"
#include "set_run.h"
#include "led.h"
#include "key.h"
#include "sound.h"
#include "delay.h"
#include "algol.h"
#include "run.h"
#include "motor.h"
#include "sensor.h"
#include "adj.h"
#include "edge.h"
#include "drive.h"
#include "pathcvrt.h"

void tune()
{
	while( 1 )	{
		// rush		- r
		led_off(PIO_LED_ALL);
		led_on (PIO_LED_1|PIO_LED_6);
		if ( L_KEY == read_key() )	{
			Sound_Select();
			tune_rush();
		}	else Sound_Beep();
		// scan		- S
		led_off(PIO_LED_ALL);
		led_on (PIO_LED_2|PIO_LED_0|PIO_LED_6|PIO_LED_4|PIO_LED_3);
		if ( L_KEY == read_key() )	{
			Sound_Select();
			tune_scan();
		}	else Sound_Beep();
		// turn 180	- UpsideDown U
		led_off(PIO_LED_ALL);
		led_on (PIO_LED_1|PIO_LED_0|PIO_LED_2|PIO_LED_5|PIO_LED_4);
		if ( L_KEY == read_key() )	{
			Sound_Select();
			tune_turn_180();
		}	else Sound_Beep();
		// edge			- =
		led_off(PIO_LED_ALL);
		led_on (PIO_LED_0|PIO_LED_1|PIO_LED_5|PIO_LED_4);
		if ( L_KEY == read_key() )	{
			Sound_Select();
			tune_edge();
		}	else Sound_Beep();
		// one blk		- b
		led_off(PIO_LED_ALL);
		led_on (PIO_LED_0|PIO_LED_1|PIO_LED_6|PIO_LED_4|PIO_LED_3);
		if ( L_KEY == read_key() )	{
			Sound_Select();
			tune_oneblk();
		}	else Sound_Beep();

	}
}
void tune_rush()
{
	tune_rush_set();

	while( 1 )	{
		// Orthogonal		- o
		led_off(PIO_LED_ALL);
		led_on (PIO_LED_1|PIO_LED_4|PIO_LED_6|PIO_LED_3);
		if ( L_KEY == read_key() )	{
			Sound_Select();
			tune_rush_O();
		}	else Sound_Beep();
		// Diagonal			- d
		led_off(PIO_LED_ALL);
		led_on (PIO_LED_1|PIO_LED_3|PIO_LED_4|PIO_LED_6|PIO_LED_5);
		if ( L_KEY == read_key() )	{
			Sound_Select();
			tune_rush_D();
		}	else Sound_Beep();
		// Start		    - S
		led_off(PIO_LED_ALL);
		led_on (PIO_LED_2|PIO_LED_0|PIO_LED_4|PIO_LED_6|PIO_LED_3);
		if ( L_KEY == read_key() )	{
			Sound_Select();
			tune_rush_S();
		}	else Sound_Beep();
		// Continuously Tuning	- C
		led_off(PIO_LED_ALL);
		led_on (PIO_LED_6|PIO_LED_1|PIO_LED_3);
		if ( L_KEY == read_key() )	{
			Sound_Select();
			tune_rush_C();
		}	else Sound_Beep();
	}
}
void tune_rush_O()	// orthogonal RUSH
{
	#define ORTHOGONAL  0
	#define DIAGONAL	1

	int item = 0;
	while( 1 )	{
		led_num( item );
		if ( R_KEY == read_key() )	{
			item++;
			Sound_Beep();
		}
		else	{
			Sound_Select();
			switch(item)	{
				case 0 :led_num(0); tune_rush_body(ORTHOGONAL,L,run_rFL);	break;
				case 1 :led_num(1); tune_rush_body(ORTHOGONAL,R,run_rFR);	break;
				case 2 :led_num(2);	tune_rush_body(ORTHOGONAL,L,run_rFLF);	break;
				case 3 :led_num(3); tune_rush_body(ORTHOGONAL,R,run_rFRF);	break;
				case 4 :led_num(4);	tune_rush_body(ORTHOGONAL,L,run_rFLL);	break;
				case 5 :led_num(5); tune_rush_body(ORTHOGONAL,R,run_rFRR);	break;
				case 6 :led_num(6); tune_rush_body(ORTHOGONAL,L,run_rFLLF);	break;
				case 7 :led_num(7); tune_rush_body(ORTHOGONAL,R,run_rFRRF);	break;
			}
			item = 0;
		}
		item = ( item > 7 ) ? 0 : item;
	}
}
void tune_rush_D()	// diagonal RUSH
{
	#define ORTHOGONAL  0
	#define DIAGONAL	1

	int item = 0;
	while( 1 )	{
		led_num( item );
		if ( R_KEY == read_key() )	{
			item++;
			Sound_Beep();
		}
		else	{
			Sound_Select();
			switch(item)	{
				case 0 :led_num(0); tune_rush_body(DIAGONAL,L,run_rLF);	break;
				case 1 :led_num(1); tune_rush_body(DIAGONAL,R,run_rRF);	break;
				case 2 :led_num(2);	tune_rush_body(DIAGONAL,L,run_rLLF);break;
				case 3 :led_num(3); tune_rush_body(DIAGONAL,R,run_rRRF);break;
				case 4 :led_num(4);	tune_rush_body(DIAGONAL,L,run_rLL);	break;
				case 5 :led_num(5); tune_rush_body(DIAGONAL,R,run_rRR);	break;
			}
			item = 0;
		}
		item = ( item > 5 ) ? 0 : item;
	}
}
void tune_rush_C()
{
	tune_rush_set();

	while( 1 )	{
		// Orthogonal		- o
		led_off(PIO_LED_ALL);
		led_on (PIO_LED_1|PIO_LED_4|PIO_LED_6|PIO_LED_3);
		if ( L_KEY == read_key() )	{
			Sound_Select();
			tune_rush_Oc();
		}	else Sound_Beep();
		// Diagonal			- d
		led_off(PIO_LED_ALL);
		led_on (PIO_LED_1|PIO_LED_3|PIO_LED_4|PIO_LED_6|PIO_LED_5);
		if ( L_KEY == read_key() )	{
			Sound_Select();
			tune_rush_Dc();
		}	else Sound_Beep();
	}
}
void tune_rush_Oc()	// Continuously Tune , Orthogonal
{
	#define ORTHOGONAL  0
	#define DIAGONAL	1

	int item = 0;
	while( 1 )	{
		led_num( item );
		if ( R_KEY == read_key() )	{
			item++;
			Sound_Beep();
		}
		else	{
			Sound_Select();
			switch(item)	{
				case 0 :led_num(0); tune_rush_body_C(run_rFL);	 break;
				case 1 :led_num(1); tune_rush_body_C(run_rFR);	 break;
				case 2 :led_num(2);	tune_rush_body_C(run_rFLF);  break;
				case 3 :led_num(3); tune_rush_body_C(run_rFRF);  break;
				case 4 :led_num(4);	tune_rush_body_C(run_rFLL);  break;
				case 5 :led_num(5); tune_rush_body_C(run_rFRR);  break;
				case 6 :led_num(6); tune_rush_body_C(run_rFLLF); break;
				case 7 :led_num(7); tune_rush_body_C(run_rFRRF); break;
			}
			item = 0;
		}
		item = ( item > 7 ) ? 0 : item;
	}
}
void tune_rush_Dc()	// Continuously Tune , Diagonal
{
	#define ORTHOGONAL  0
	#define DIAGONAL	1

	int item = 0;
	while( 1 )	{
		led_num( item );
		if ( R_KEY == read_key() )	{
			item++;
			Sound_Beep();
		}
		else	{
			Sound_Select();
			switch(item)	{
				case 0 :led_num(0); tune_rush_body_C(run_rLF);	break;
				case 1 :led_num(1); tune_rush_body_C(run_rRF);	break;
				case 2 :led_num(2);	tune_rush_body_C(run_rLLF);	break;
				case 3 :led_num(3); tune_rush_body_C(run_rRRF);	break;
				case 4 :led_num(4);	tune_rush_body_C(run_rLL);	break;
				case 5 :led_num(5); tune_rush_body_C(run_rRR);	break;
			}
			item = 0;
		}
		item = ( item > 5 ) ? 0 : item;
	}
}
void tune_rush_S()	// starting RUSH
{
	int item = 0;
	while( 1 )	{
		led_num( item );
		if ( R_KEY == read_key() )	{
			item++;
			Sound_Beep();
		}
		else	{
			Sound_Select();
			torque_on();
			ss_on();
			led_count_down( 5, 500 );

			init_mouse();
			tune_rush_set();

			switch(item)	{
				case 0 : run_aSFF();	break;
				case 1 : run_aSFRL();   break;
				case 2 : run_aSFRF();   break;
				case 3 : run_aSFRRL();  break;
			}
			item = 0;
			equal_spd_ptr(); spd_diff = -1; while(spd_ptr_L > 0 ) equal_spd_ptr();
			motor_stop();	torque_off();
			ss_off();
		}
		item = ( item > 3 ) ? 0 : item;
	}
}
void tune_rush_body(char D_O,char tDIR,void (*run_type)())
{
	if ( D_O == 0 )		{ // orthogonal
		led_off(PIO_LED_ALL);
		led_on (PIO_LED_1|PIO_LED_3|PIO_LED_4|PIO_LED_6);
	}
	else	{	// diagonal
		led_off(PIO_LED_ALL);
		led_on (PIO_LED_1|PIO_LED_3|PIO_LED_4|PIO_LED_6|PIO_LED_5);
	}
	wait_key();
	torque_on();
	ss_on();
	led_count_down( 5, 500 );

	clr_run();
	disable_adj();

	if ( D_O == 0 ) 	{
		refresh_level();
		refresh_edge();
		put_run( run_rFF );	// orthogonal
		spd_diff = 1;
	}
	else	{				// diagonal
		refresh_level_D();
		refresh_edge();
		if ( tDIR == L ) 	put_run( run_rRL );
		else				put_run( run_rLR );
		spd_diff = 1;
	}
	put_run( run_type );

	init_maze();
	mouse_pos = 0x77;

	spd_ptr  = 0;

	reset_steps();

//	enable_adj();
	disable_adj();

	motor_start();

	while( spd_ptr_L <= INFO_iSPD_RUSH )	{
		if (D_O == 0 ) 	{
			adj_O();
		}
		else 			{
			adj_DF0();
		}
		equal_spd_ptr();
	}
	reset_adj_mul();
	spd_diff = 0;
	spd_ptr = INFO_iSPD_RUSH;
	disable_adj();

	int i = 2;
	while(i--)	{
		get_run();
		(run)();
	}
	disable_adj();
	ss_off();

	reset_steps();
	spd_ptr = INFO_iSPD_RUSH;
	spd_diff = 0;

	reset_steps();
	spd_ptr = INFO_iSPD_RUSH;
	while(steps < ONEBLK)
		if ( ONEBLK - steps  < INFO_iSPD_RUSH + 10 ) spd_diff = -1;

	motor_stop();
	sys_delay(500);
	torque_off();
}
void tune_rush_body_C(void (*run_type)())
{
	wait_key();
	torque_on();
	ss_on();
	led_count_down( 5, 500 );

	clr_run();

	put_run( run_type );
	put_run( run_type );
	put_run( run_type );
	put_run( run_type );

	init_maze();
	mouse_pos = 0x77;

	spd_diff = 0;
	spd_ptr  = 0;

	reset_steps();
	disable_adj();
	motor_start();

//	while( steps <= 50 )	equal_spd_ptr();

	reset_steps();
	spd_diff = 1;
	while( spd_ptr_L <= INFO_iSPD_RUSH )	equal_spd_ptr();

	spd_diff = 0;
	spd_ptr  = INFO_iSPD_RUSH;

	reset_steps();
	while( steps <= 100 );


	//int i = (4);
	int i = (1);

	while(i--)	{
		refresh_level();
		refresh_edge();
		level_P_L45	= level_C_L45 = level_P_R45 = level_C_R45 = SS_HIGH;
		get_run();
		(run)();
	}
	disable_adj();
	ss_off();

	reset_steps();
	reset_spd_diff();
	spd_ptr = INFO_iSPD_RUSH;

	while(steps < ONEBLK)	{
		if ( ONEBLK - steps < INFO_iSPD_RUSH + 10 )		{
			spd_diff = -1;
		}
		sync_step();
	}


//	reset_steps();
//	spd_ptr = INFO_iSPD_RUSH;
//	spd_diff = -1;

//	while(steps<INFO_iSPD_RUSH) equal_spd_ptr();
//	spd_diff = 0;
//	spd_ptr	 = 0;
//	while(steps<ONEBLK) equal_spd_ptr();

	motor_stop();
	sys_delay(500);
	torque_off();
}
void tune_scan()
{
	int nREPEAT;

	#define NOWAIT_EDGE     0
	#define WAIT_EDGE		1

	unsigned char wait_flag = NOWAIT_EDGE;

	tune_scan_set();

	RESTART_TUNING_SCAN:
	clr_run();
	while( 1 )	{
		// L
		led_off(PIO_LED_ALL);
		led_on (PIO_LED_3);
		if ( L_KEY == read_key() )	{
			Sound_Select();
			nREPEAT = 4;
			put_run( run_sLX );
			wait_flag = NOWAIT_EDGE;
			goto START_TUNING_SCAN;
		}	else Sound_Beep();
		// R
		led_off(PIO_LED_ALL);
		led_on (PIO_LED_2);
		if ( L_KEY == read_key() )	{
			Sound_Select();
			nREPEAT = 4;
			put_run( run_sRX );
			wait_flag = NOWAIT_EDGE;
			goto START_TUNING_SCAN;
		}	else Sound_Beep();
		// B
		led_off(PIO_LED_ALL);
		led_on (PIO_LED_4|PIO_LED_5);
		if ( L_KEY == read_key() )	{
			Sound_Select();
			nREPEAT = 4;
			put_run( run_sBX );
			wait_flag = NOWAIT_EDGE;
			goto START_TUNING_SCAN;
		}	else Sound_Beep();
		// L	OneShot
		led_off(PIO_LED_ALL);
		led_on (PIO_LED_3|PIO_LED_1|PIO_LED_4);
		if ( L_KEY == read_key() )	{
			Sound_Select();
			nREPEAT = 1;
			put_run( run_sLX );
			wait_flag = WAIT_EDGE;
			goto START_TUNING_SCAN;
		}	else Sound_Beep();
		// R    OneShot
		led_off(PIO_LED_ALL);
		led_on (PIO_LED_2|PIO_LED_0|PIO_LED_5);
		if ( L_KEY == read_key() )	{
			Sound_Select();
			nREPEAT = 1;
			put_run( run_sRX );
			wait_flag = WAIT_EDGE;
			goto START_TUNING_SCAN;
		}	else Sound_Beep();
		// inter RUNs : Scan -> Rush	- S
		led_num(5);
		if ( L_KEY == read_key() )	{
			Sound_Select();
			tune_inter_SR();
		}	else Sound_Beep();
		// inter RUNs : Rush -> Scan	- r
		led_off(PIO_LED_ALL);
		led_on (PIO_LED_1|PIO_LED_6);
		if ( L_KEY == read_key() )	{
			Sound_Select();
			tune_inter_RS();
		}	else Sound_Beep();

		// continuous smooth turn to detect forward steps - c
		led_off(PIO_LED_ALL);
		led_on (PIO_LED_6|PIO_LED_1|PIO_LED_3);
		if ( L_KEY == read_key() )	{
			Sound_Select();
			tune_conti_turn();
		}	else Sound_Beep();

	}

	START_TUNING_SCAN:

	wait_key();
	torque_on();
	ss_on();
	led_count_down( 5, 500 );

	init_maze();			init_mouse();
	goal_pos = SCAN_GOAL;	mouse_pos = 0x77;
	cvrt_mode = CVRT_SCAN_O;

	spd_ptr  = 0;
	spd_diff = 1;
	reset_steps();

//	enable_adj();
	disable_adj();

	motor_start();
	spd_diff = 1;
	while(steps<INFO_iSPD_SCAN) equal_spd_ptr();
	spd_diff = 0;

	spd_ptr = INFO_iSPD_SCAN;

	refresh_level();
	refresh_edge();

	if (wait_flag == WAIT_EDGE)
		// wait edge
		wait_edge(  scan_level,
					adj_O,
					WAIT_EDGE_LR,
					edge_info_L90,
					edge_info_R90
				  );

	disable_adj();

	// remain step
	reset_steps();
	while( steps < ONEBLK - EDGESTEP_90) ;

	get_run();
	while(nREPEAT--)	{
		(run)();
	}
	disable_adj();
	reset_steps();
	reset_spd_diff();
	equal_spd_ptr();
	while(steps<ONEBLK);

	reset_steps();
	spd_diff = -1;
	while(steps<INFO_iSPD_SCAN) equal_spd_ptr();
	spd_diff = 0;

	ss_off();

	motor_stop();
	sys_delay(1000);
	torque_off();
	goto RESTART_TUNING_SCAN;
}
void tune_inter_SR()	// Scan -> Rush
{
	tune_iscan_set();

	int item = 0;
	while( 1 )	{
		led_num( item );
		if ( R_KEY == read_key() )	{
			item++;
			Sound_Beep();
		}
		else	{
			Sound_Select();
			ss_on();
			torque_on();
			wait_key();
			led_count_down( 5, 500 );

			init_maze();
			init_mouse();
			cvrt_mode = CVRT_SCAN_O;
			scan_maze(SCAN_GOAL);
			make_path();
			path_cvrt();

			motor_start();
			run_aSHF();

			#ifndef DISABLE_OVERSTP
			INFO_overSTP = 0;
			#endif

			switch(item)	{
				// L45
				case 0 :led_num(0); run_irFL();	break;
				// R45
				case 1 :led_num(1); run_irFR(); break;
				// L90
				case 2 :led_num(2);	run_irLF();	break;
				// R90
				case 3 :led_num(3); run_irRF();	break;
				// L135
				case 4 :led_num(4);	run_irLL();	break;
				// R135
				case 5 :led_num(5); run_irRR();	break;
				// L45 twist
				case 6 :led_num(6); run_irLR(); break;
				// R45 twist
				case 7 :led_num(7); run_irRL(); break;
				// F
				case 8 :led_num(8); run_irFF();	break;
			}
			item = 0;
			disable_adj();
			ss_off();
			reset_steps();
			while(steps < HALFBLK);

			reset_steps();
			spd_diff = -1;
			spd_ptr  = INFO_iSPD_SCAN;
			while(steps < INFO_iSPD_SCAN) equal_spd_ptr();
			reset_spd_diff();
			reset_spd_ptr();
			motor_stop();
			sys_delay(1000);
			torque_off();
		}
		item = ( item > 8 ) ? 0 : item;
	}
}
void tune_inter_RS()	// Rush -> Scan
{
	tune_iscan_set();

	#define ORTHOGONAL  0
	#define DIAGONAL	1

	init_maze();			init_mouse();
	goal_pos 	= SCAN_GOAL;	mouse_pos = 0x77;
	cvrt_mode 	= CVRT_SCAN_O;


	int item = 0;
	while( 1 )	{
		led_num( item );
		if ( R_KEY == read_key() )	{
			item++;
			Sound_Beep();
		}
		else	{
			Sound_Select();

			switch(item)	{
				// L45
				case 0 :led_num(0); tune_rush_body(DIAGONAL,L,run_isLF);break;
				// R45
				case 1 :led_num(1); tune_rush_body(DIAGONAL,R,run_isRF);break;
				// L90
				case 2 :led_num(2);	tune_rush_body(ORTHOGONAL,L,run_isFL);break;
				// R90
				case 3 :led_num(3); tune_rush_body(ORTHOGONAL,R,run_isFR);break;
				// L135
				case 4 :led_num(4);	tune_rush_body(DIAGONAL,L,run_isLL);break;
				// R135
				case 5 :led_num(5); tune_rush_body(DIAGONAL,R,run_isRR);break;
				// L45 twist
				case 6 :led_num(6); tune_rush_body(DIAGONAL,L,run_isLR);break;
				// R45 twist
				case 7 :led_num(7); tune_rush_body(DIAGONAL,R,run_isRL);break;
				// F
				case 8 :led_num(8); tune_rush_body(ORTHOGONAL,L,run_isFF);break;
			}
			item = 0;
		}
		item = ( item > 8 ) ? 0 : item;
	}
}
void tune_turn_180()
{
	 torque_on();

	 wait_key();
	 led_count_down( 5, 500 );

	 run_aTURN();run_aTURN();
	 run_aTURN();run_aTURN();

	 torque_off();
}
void tune_edge()
{
	torque_on();
	wait_key();
	ss_on();
	led_count_down( 5, 500 );

	refresh_ss_history();
	refresh_level();
	refresh_edge();

	reset_steps();
	reset_spd_diff();
	reset_spd_ptr();
//	enable_adj();
	disable_adj();

	motor_start();

	led_off(PIO_LED_ALL);
	equal_spd_ptr();
	// wait edge
	while (1) 	{
		if ( edge_info_L90 == EDGE_DN || edge_info_R90 == EDGE_DN ) {
			edge_info_L90 = edge_info_R90 = EDGE_UNKNOWN;
			led_off(PIO_LED_ALL);led_on(LED_SHOW_H);
			goto REMAIN_STEP;
		}
		scan_level();
		scan_edge();
		//adj_O();
		sync_step();
	}
	REMAIN_STEP:

	reset_steps();
	spd_diff = 0;
	equal_spd_ptr();
	while (steps < ONEBLK - EDGESTEP_90) 	{
		//adj_O();
		sync_step();
	}

	motor_stop();
	ss_off();
	wait_key();
	torque_off();
}
void tune_oneblk()
{
	// running for 10 block

	#define aSTP		HALFBLK
	#define uSTP		(ONEBLK * 9)
	#define NADJ_STP	50

	torque_on();
	wait_key();

	ss_pulse_fast();
	ss_on();

	led_count_down( 3, 300 );

	reset_steps();
	reset_spd_ptr();
	spd_diff = 1;

	motor_start();

	while(steps < NADJ_STP) equal_spd_ptr();
	enable_adj();
	while(steps < aSTP)	{
			adj_O();
			equal_spd_ptr();
			sync_step();
	}

	spd_diff = 0;	reset_steps();
	while(steps < uSTP)	{
		adj_O();
		equal_spd_ptr();
		sync_step();
	}
	spd_diff = -1;	reset_steps();
	while(steps < aSTP-NADJ_STP)	{
		adj_O();
		equal_spd_ptr();
		sync_step();
	}
	disable_adj();
	while(steps < aSTP)	equal_spd_ptr();
	spd_diff = 0;
	spd_ptr	 = 0;
	motor_stop();
	ss_off();

	wait_key();

	torque_off();
}
void tune_conti_turn()
{
	// continuous smooth turn.

	torque_on();
	wait_key();
	led_count_down( 3, 300 );

	set_run_iscan_normal();

	init_mouse();
	goal_pos 	= SCAN_GOAL;
	cvrt_mode 	= CVRT_SCAN_O;

	init_maze();

	disable_adj();
	reset_steps();
	reset_spd_ptr();

	spd_diff = 1;
	motor_start();
	while(steps < INFO_iSPD_SCAN) equal_spd_ptr();

	spd_diff 	= 0;
	spd_ptr		= INFO_iSPD_SCAN;
	while(steps < HALFBLK);

	#ifndef DISABLE_OVERSTP
	INFO_overSTP = 0;
	#endif

	init_maze();	run_sRX();
					run_sLX();

	init_maze();	run_sRX();
					run_sLX();

//	init_maze();	run_sRX();
//					run_sLX();

	init_maze();	run_sRX();

	disable_adj();

	reset_steps();
	spd_diff = -1;
	while(steps < INFO_iSPD_SCAN) equal_spd_ptr();

	spd_diff = 0;
	spd_ptr  = 0;
	while(steps < HALFBLK);

	motor_stop();
	sys_delay(500);
	torque_off();
}

