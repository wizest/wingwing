// Adjust Position when stops.


#include "adj_pos.h"
#include "sensor.h"
#include "delay.h"
#include "sampling.h"
#include "swing.h"
#include "motor.h"
#include "drive.h"
#include "adj.h"

void adj_pos()
{
	//adj_pos_V();
	adj_pos_H();
	//adj_pos_HS();
}

void adj_pos_V()
{
	/*
	#define xNADJV	100 // Do not adjust position value
	#define fpADJSL	235	// front position of adjusting startline
	#define rpADJSL	230 // rear
	#define mDELAY 	10	// motor stepping delay

	motor_stop();
	reset_steps();  	reset_spd_ptr();

	// NOT ADJUST
	if (pos_L0[ss_value[SS_L0]] < xNADJV ||
		pos_R0[ss_value[SS_R0]] < xNADJV) 		return;

	sys_delay(50);

	// FRONT
	while(pos_L0[ss_value[SS_L0]] > fpADJSL &&
		  pos_R0[ss_value[SS_R0]] > fpADJSL  ) {
		reverse_LR();	motor_LR();		reverse_LR();
		sys_delay(mDELAY);
	}
	while(pos_L0[ss_value[SS_L0]] < rpADJSL &&
		  pos_R0[ss_value[SS_R0]] < rpADJSL  ) {
		motor_LR();
		sys_delay(mDELAY);
	}
	*/
	/*
	// TURN
	if (pos_L0[ss_value[SS_L0]] > pos_R0[ss_value[SS_R0]])	{
		while(pos_L0[ss_value[SS_L0]] > pos_R0[ss_value[SS_R0]] )		{
			reverse_L();	motor_LR();		reverse_L();
			sys_delay(mDELAY*2);
		}
	}
	else	{
		while(pos_L0[ss_value[SS_L0]] < pos_R0[ss_value[SS_R0]] )		{
			reverse_R();	motor_LR();		reverse_R();
			sys_delay(mDELAY*2);
		}
	}
	*/

}
void adj_pos_H()
{
	#define xNADJH  (25)	// (20)	// not adjusting delta x

	char by_LR;
	#define BY_L	0
	#define BY_R	1

	motor_stop();
	reset_spd_ptr();

	unsigned int comp_L = 0;
	unsigned int comp_R = 0;

	#define nSAMPL	(5)		//(7)
	for (unsigned char i=0;i< nSAMPL ;i++) {
		comp_L += ss_value[SS_L90];
		comp_R += ss_value[SS_R90];
		sys_delay(5);
	}
	comp_L /= nSAMPL;	comp_R /= nSAMPL;

	if( ssv_L90[xR3] > comp_L &&
		ssv_R90[xL3] > comp_R ) 	return;

	if( comp_L > comp_R )	{
		if( ssv_R90[xL3] > comp_R	)			by_LR = BY_L;
		else 									by_LR = BY_R;
	}
	else	{
		if( ssv_L90[xR3] > comp_L	)			by_LR = BY_R;
		else 									by_LR = BY_L;
	}

	switch( by_LR )
	{
		case BY_L: // adj by L value
			if (ssv_L90[xC1 - xNADJH] > comp_L &&
				ssv_L90[xC1 + xNADJH] < comp_L ) return;
			swing( (int)( (int)(pos_L90[comp_L] - xC1) * 50 / 127 * -1));
			break;
		case BY_R: // adj by R value
			if (ssv_R90[xC1 + xNADJH] > comp_R &&
				ssv_R90[xC1 - xNADJH] < comp_R ) return;
			swing( (int)( (int)(pos_R90[comp_R] - xC1) * 50 / 127 * -1));
			break;
	}
}
void adj_pos_HS()   // startline
{
	#define xNADJHS  2 // not adjusting delta x

	char by_LR;
	#define BY_L	0
	#define BY_R	1

	motor_stop();
	reset_spd_ptr();

	unsigned int comp_L = 0;
	unsigned int comp_R = 0;

	#define nSAMPL	(5)	//(7)
	for (unsigned char i=0;i< nSAMPL ;i++) {
		comp_L += ss_value[SS_L90];
		comp_R += ss_value[SS_R90];
		sys_delay(7);
	}
	comp_L /= nSAMPL;	comp_R /= nSAMPL;

	if( ssv_L90[xR3] > comp_L &&
		ssv_R90[xL3] > comp_R ) 	return;

	if( comp_L > comp_R )	{
		if( ssv_R90[xL3] > comp_R	)			by_LR = BY_L;
		else 									by_LR = BY_R;
	}
	else	{
		if( ssv_L90[xR3] > comp_L	)			by_LR = BY_R;
		else 									by_LR = BY_L;
	}

	switch( by_LR )
	{
		case BY_L: // adj by L value
			if (ssv_L90[xC1 - xNADJHS] > comp_L &&
				ssv_L90[xC1 + xNADJHS] < comp_L ) return;
			swing_S( (int)(pos_L90[comp_L] - xC1) * (-1) );
			break;
		case BY_R: // adj by R value
			if (ssv_R90[xC1 + xNADJHS] > comp_R &&
				ssv_R90[xC1 - xNADJHS] < comp_R ) return;
			swing_S( (int)(pos_R90[comp_R] - xC1) * (-1) );
			break;
	}
}


#ifdef STOP_METHOD_FRONTWALL
void adj_pos_stop()
{
	equal_spd_ptr();
	spd_diff = -1;

	char stop_mL,stop_mR;
	stop_mL = stop_mR = 0;

	reset_steps();

	disable_adj();
	while(1)    {
		if ( spd_ptr_L < 5 ) {
			spd_diff = 0;
			equal_spd_ptr();
		}
		#define stopPOS     (175)
		#define remainSTP   (108)

//		#define stopPOS     (205)
//		#define remainSTP   (50	+5)

//		#define stopPOS		(190)
//		#define remainSTP	(87)

//		#define thrsDSTP	(10)	//20
		#define thrsDSTP	(0)	//20
		#define thrsSTP		(ONEBLK)

		if ( stop_mL == 0 )
			if ( pos_L0[ss_value[SS_L0]] >= stopPOS ||
				 cnt_ss_history( SS_L0,ssv_L0[stopPOS] ) > 3 )		{
				stop_mL = 1; spd_ptr = 0; disable_adj();  motor_stop_L();
				steps_R = 0;
			}
		if ( stop_mR == 0 )
			if ( pos_R0[ss_value[SS_R0]] >= stopPOS ||
				 cnt_ss_history( SS_R0,ssv_R0[stopPOS] ) > 3 )		{
				stop_mR = 1; spd_ptr = 0; disable_adj();  motor_stop_R();
				steps_L = 0;
			}

		// ending condition
		if ( stop_mL==0 && stop_mR==0 )	{
			if ( steps > thrsSTP ) goto END_WATCH;
		}
		else	{
			if ( stop_mL )
				if ( steps_R > thrsDSTP ) {
					//motor_R();
					goto END_WATCH;
				}
			if ( stop_mR )
				if ( steps_L > thrsDSTP ) {
					//motor_L();
					goto END_WATCH;
				}
			if ( stop_mL && stop_mR )   goto END_WATCH;
		}

		sync_step();
	}
	END_WATCH:

	reset_spd_ptr();
	reset_steps();
	spd_diff = 1;
	motor_start();
	#define REMAIN_SPD_PTR	10
	while(steps < remainSTP )    {
		if (spd_ptr_L > REMAIN_SPD_PTR) 	{
			spd_diff = 0;
			equal_spd_ptr();
		}
		if (steps > remainSTP - REMAIN_SPD_PTR )	{
			spd_diff = -1;
			equal_spd_ptr();
		}
		sync_step();
	}
	motor_stop();
}
#endif

#ifdef STOP_METHOD_SIDEWALL
void adj_pos_stop()
{
	#define STOP_POS	170
	#define STOP_STP	120

	// STOP POSITION
	enable_adj();
	while(1)	{
		if ( pos_L0[ss_value[SS_L0]] > STOP_POS ||
			 pos_R0[ss_value[SS_R0]] > STOP_POS )	break;

		adj_O();
		sync_step();
	}

	STOPPING:
	reset_steps();
	equal_spd_ptr();
	spd_diff = -1;

	disable_adj();
	while( steps < STOP_STP )    {
		sync_step();
	}
	motor_stop();

	reset_spd_diff();
	reset_spd_ptr();
	reset_steps();
}
#endif