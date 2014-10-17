#include "swing.h"
#include "turn.h"
#include "motor.h"
#include "delay.h"
#include "adj.h"

#include "swing.tbl"
#include "swing_S.tbl"

void swing(int mm) // -90 < mm < 90 , center : 0 mm
{
	int c_mm;
	if ( mm == 0 ) return;
	if ( mm > 0  ) c_mm = mm;
	else 		   c_mm = -mm;

	c_mm /= 2;

	motor_stop();		//sys_delay(50);
	disable_adj();

	reverse_LR();

	reset_spd_diff();
	reset_spd_ptr();
	reset_steps();		motor_start();
	while(steps < 3);

	if ( mm < 0 )	swing_left ( SWING_iSPD , SWING_aSTP, swing_H_tbl[c_mm] );
	else			swing_right( SWING_iSPD , SWING_aSTP, swing_H_tbl[c_mm] );

	reset_spd_diff();
	reset_spd_ptr();
	reset_steps();		motor_start();
	while(steps < 3);

	motor_stop();		//sys_delay(50);

	reset_spd_ptr();
	reverse_LR();

	reset_spd_diff();
	reset_spd_ptr();
	reset_steps();		motor_start();
	while(steps < 3);

	if ( mm < 0 )	swing_left ( SWING_iSPD , SWING_aSTP, swing_H_tbl[c_mm] );
	else			swing_right( SWING_iSPD , SWING_aSTP, swing_H_tbl[c_mm] );

	reset_spd_diff();
	reset_spd_ptr();
	reset_steps();		motor_start();
	while(steps < 3);

	reset_spd_ptr();
	motor_stop();
}


/*
void swing(int mm) // -90 < mm < 90 , center : 0 mm
{
	int c_mm;
	if ( mm == 0 ) return;
	if ( mm > 0  ) c_mm = mm;
	else 		   c_mm = -mm;

	#define SWING_initSpd	50
	#define SWING_thruStp	50

	motor_stop();	sys_delay(50);
	disable_adj();

	reset_spd_ptr();
	reverse_LR();

	motor_start();

	spd_diff 	= 1;
	reset_steps(); 	while(steps < SWING_initSpd);
	spd_diff	= 0;

	if ( mm < 0 )	{
		reset_steps();	turn_left (SWING_initSpd,swing_H_tbl[c_mm],SWING_thruStp,1,1);
		reset_steps();	turn_right(SWING_initSpd,swing_H_tbl[c_mm],SWING_thruStp,1,1);
		//swing_left ( SWING_initSpd , swing_H_tbl[c_mm] , SWING_thruStp );
	}
	else			{
		reset_steps();	turn_right(SWING_initSpd,swing_H_tbl[c_mm],SWING_thruStp,1,1);
		reset_steps();	turn_left (SWING_initSpd,swing_H_tbl[c_mm],SWING_thruStp,1,1);
		//swing_right( SWING_initSpd , swing_H_tbl[c_mm] , SWING_thruStp );
	}

	spd_diff	= -1;
	reset_steps();	while(steps < SWING_initSpd);
	spd_diff	= 0;

	motor_stop();	sys_delay(50);
	reverse_LR();
	reset_spd_ptr();
	reset_steps();
	motor_start();


	//if ( mm > 0 )	{
	//	reset_spd_ptr();	reset_steps();	reverse_L(); 	while( steps < 1 );	reverse_R();
	//}
	//else			{
	//	reset_spd_ptr();	reset_steps();	reverse_R();	while( steps < 1 );	reverse_L();
	//}
	//motor_stop();	sys_delay(50);	motor_start();


	reset_spd_ptr();
	spd_diff	= 1;
	reset_steps();	while(steps < SWING_initSpd);

	spd_diff  	= 0;
	spd_ptr		= SWING_initSpd;
	reset_steps();	while(steps < swing_V_tbl[c_mm]);

	spd_diff	= -1;
	spd_ptr		= SWING_initSpd;
	reset_steps();	while(steps < SWING_initSpd);
	spd_diff	= 0;

	reset_spd_ptr();

	motor_stop();
}
*/

void swing_left(int iSpd,int ioS,int thS)
{
	#define STABLE_STP	0
	reset_spd_ptr();
	reset_steps();
	reset_spd_diff();
	while(steps < STABLE_STP);

	reset_steps();
	spd_diff 	= 1;
	while(steps < iSpd);
	spd_diff	= 0;

	reset_steps();	turn_left (iSpd,ioS,thS,1,1);
	reset_steps();	turn_right(iSpd,ioS,thS,1,1);

	reset_steps();
	spd_diff 	= -1;
	while(steps < iSpd);
	spd_diff	= 0;

	reset_spd_ptr();
	reset_steps();
	reset_spd_diff();
	while(steps < STABLE_STP);

}

void swing_right(int iSpd,int ioS,int thS)
{
	#define STABLE_STP	0

	reset_spd_ptr();
	reset_steps();
	reset_spd_diff();
	while(steps < STABLE_STP);

	reset_steps();
	spd_diff 	= 1;
	while(steps < iSpd);
	spd_diff	= 0;

	reset_steps();	turn_right(iSpd,ioS,thS,1,1);
	reset_steps();	turn_left (iSpd,ioS,thS,1,1);

	reset_steps();
	spd_diff 	= -1;
	while(steps < iSpd);
	spd_diff	= 0;

	reset_spd_ptr();
	reset_steps();
	reset_spd_diff();
	while(steps < STABLE_STP);
}
void swing_S(int mm) // -90 < mm < 90 , center : 0 mm
{
	int swing_steps;
	int c_mm;
	if ( mm == 0 ) return;
	if ( mm > 0  ) c_mm = mm;
	else 		   c_mm = -mm;

	//if ( mm > 0 ) return; // NOTE !!!!!!!!!!!!!!!!!!

	#define mDELAY_S	2
	#define tDELAY_S	70

	motor_stop();	sys_delay(tDELAY_S);
	disable_adj();

	reset_spd_ptr();

	if ( mm < 0 )	{
		reverse_LR();
		for (swing_steps = 0; swing_steps < swing_S_tbl[c_mm]/2 ; swing_steps++)	{
			motor_R();
			sys_delay(mDELAY_S);
		}
		sys_delay(tDELAY_S);
		for (swing_steps = 0; swing_steps < swing_S_tbl[c_mm]/2 ; swing_steps++)	{
			motor_L();
			sys_delay(mDELAY_S);
		}
		sys_delay(tDELAY_S);
		reverse_LR();
		for (swing_steps = 0; swing_steps < swing_S_tbl[c_mm]/2 ; swing_steps++)	{
			motor_R();
			sys_delay(mDELAY_S);
		}
		sys_delay(tDELAY_S);
		for (swing_steps = 0; swing_steps < swing_S_tbl[c_mm]/2 ; swing_steps++)	{
			motor_L();
			sys_delay(mDELAY_S);
		}
		sys_delay(tDELAY_S);
	}
	else			{
		reverse_LR();
		for (swing_steps = 0; swing_steps < swing_S_tbl[c_mm]/2 ; swing_steps++)	{
			motor_L();
			sys_delay(mDELAY_S);
		}
		sys_delay(tDELAY_S);
		for (swing_steps = 0; swing_steps < swing_S_tbl[c_mm]/2 ; swing_steps++)	{
			motor_R();
			sys_delay(mDELAY_S);
		}
		sys_delay(tDELAY_S);
		reverse_LR();
		for (swing_steps = 0; swing_steps < swing_S_tbl[c_mm]/2 ; swing_steps++)	{
			motor_L();
			sys_delay(mDELAY_S);
		}
		sys_delay(tDELAY_S);
		for (swing_steps = 0; swing_steps < swing_S_tbl[c_mm]/2 ; swing_steps++)	{
			motor_R();
			sys_delay(mDELAY_S);
		}
		sys_delay(tDELAY_S);
	}
}
