#include "motor.h"
#include "adj.h"
#include "sensor.h"
#include "sampling.h"
#include "sound.h"

#include "speed.tbl"

unsigned int *speed;	// speed table pointer

		 char phase_dir_L , phase_dir_R;
		 char phase_ptr_L , phase_ptr_R;

unsigned int spd_cnt_L	,spd_cnt_R;
unsigned int motor_int_interval_cnt;
unsigned int spd_cnt;


volatile int spd_ptr_L	,spd_ptr_R;
volatile char spd_diff_L	,spd_diff_R;

volatile int steps_L, steps_R;

volatile char sync_signal;

unsigned char phase_L[8] ={
					{pio_L_A                        },
					{pio_L_A|pio_L_B                },
					{        pio_L_B                },
					{        pio_L_B|pio_L_C        },
					{                pio_L_C        },
					{                pio_L_C|pio_L_D},
					{                        pio_L_D},
					{pio_L_A|                pio_L_D}
				};
unsigned char phase_R[8] ={
					{pio_R_A                        },
					{pio_R_A|pio_R_B                },
					{        pio_R_B                },
					{        pio_R_B|pio_R_C        },
					{                pio_R_C        },
					{                pio_R_C|pio_R_D},
					{                        pio_R_D},
					{pio_R_A|                pio_R_D}
				};

#define MODE_MOTOR_INT_SINGLE 	0
#define MODE_MOTOR_INT_DOUBLE	1
unsigned char motor_int_mode;
unsigned int motor_cnt_ref;


void init_motor()
{
	set_motor_int();

	phase_dir_L = (-1);
	phase_dir_R = (+1);

	phase_ptr_L = 0;
	phase_ptr_R = 0;

	reset_steps();
	reset_spd_ptr();
	reset_spd_diff();

	init_ss_history();

	set_fSPD();
	motor_stop();
}

void set_motor_int()
{
	outport (TCUCON,0x0000); // Timer interrupt control reg

	outport (T1CNT,0U);
	outport (T1CMPA,0x0000);

	outport (T2CNT,0U);
	outport (T2CMPA,0x0000);

	// single interrupt mode
	motor_stop_L();
	motor_stop_R();
	setvect(INT_TMR1,motor_int);

	// double interrupt mode
	motor_stop_L();
	motor_stop_R();
	setvect(INT_TMR1,motor_int_L);
	setvect(INT_TMR2,motor_int_R);

	asm sti;
}

// single interrupt mode
void motor_int()
{
	// motor interrupt service for sync. - 2002.6.12 / 2002.8.11
	asm pusha;
	asm sti;
	Int_End();

	GO_WING :
	{
		outport(MOTOR_TIMER,0);
//		outport(T1CNT,0);

		motor_tmr_start();	//Start_Timer1()	outport(T1CON,0xE000)
		motor_stop_R();     //Stop_Timer2()     outport(T2CON,0x6000)

		// 1. calculate the next timer count.
		// 2. set the count of timer.
		// 3. speed control & steering.
		// 4. refresh step sensing values.

		if ( spd_cnt_L < spd_cnt_R )
		{
			spd_cnt_R -= spd_cnt_L;

			// left
			pdata0 &= (~pio_L);
			phase_ptr_L = (phase_ptr_L+phase_dir_L) & 7;
			pdata0 |= phase_L[phase_ptr_L];
			outport(PDATA0,pdata0);
			steps_L++;

			// speed control & steering
			spd_ptr_L += spd_diff_L;
			if (spd_ptr_L < 0) 	spd_ptr_L = 0;
			if (adj_switch)	{
				asm mov bx,word ptr spd_ptr_L;
				asm shl bx,1;
				asm mov ax,word ptr fspeed[bx];
				asm mul word ptr adj_mul_L;
				asm shl dx,1;
				asm mov spd_cnt_L,dx;
				// spd_cnt_L = (MSB 16bits of ((spd_tbl[spd_ptr_L+=spd_diff_L] * adj_mul_L)) << 1;
			}	else spd_cnt_L = speed[spd_ptr_L];

			// keep sensor value in ss_history by step unit
			ss_history[SS_L90][ss_his_ptr_L] = ss_value[SS_L90];
			ss_history[SS_L45][ss_his_ptr_L] = ss_value[SS_L45];
			ss_history[SS_L0 ][ss_his_ptr_L] = ss_value[SS_L0 ];
			//ss_his_ptr_L = ++ss_his_ptr_L % SS_HISTORY_SIZE;
			ss_his_ptr_L = (++ss_his_ptr_L) & 7;
		}
		else
		if ( spd_cnt_L > spd_cnt_R )
		{
			spd_cnt_L -= spd_cnt_R;

			// right
			pdata0 &= (~pio_R);
			phase_ptr_R = (phase_ptr_R+phase_dir_R) & 7;
			pdata0 |= phase_R[phase_ptr_R];
			outport(PDATA0,pdata0);
			steps_R++;

			// speed control & steering
			spd_ptr_R += spd_diff_R;
			if (spd_ptr_R < 0) 	spd_ptr_R = 0;
			if (adj_switch)	{
	//			asm mov bx,word ptr spd_ptr_R;
				asm mov bx,word ptr spd_ptr_L;	// refer to the same speed pointer (SYNC Left SpdPtr)
				asm shl bx,1;
				asm mov ax,word ptr fspeed[bx];
				asm mul word ptr adj_mul_R;
				asm shl dx,1;
				asm mov spd_cnt_R,dx;
				// spd_cnt_R = (MSB 16bits of ((spd_tbl[spd_ptr_R+=spd_diff_R] * adj_mul_R)) << 1;
			} else spd_cnt_R = speed[spd_ptr_R];

			// keep sensor value in ss_history by step unit
			ss_history[SS_R0 ][ss_his_ptr_R] = ss_value[SS_R0 ];
			ss_history[SS_R45][ss_his_ptr_R] = ss_value[SS_R45];
			ss_history[SS_R90][ss_his_ptr_R] = ss_value[SS_R90];
			//ss_his_ptr_R = ++ss_his_ptr_R % SS_HISTORY_SIZE;
			ss_his_ptr_R = (++ss_his_ptr_R) & 7;
		}
		else
		if ( spd_cnt_L == spd_cnt_R )
		{
			pdata0 &= ~(pio_L | pio_R);

			// left
			phase_ptr_L = (phase_ptr_L+phase_dir_L) & 7;
			pdata0 |= phase_L[phase_ptr_L];
			steps_L++;
			// right
			phase_ptr_R = (phase_ptr_R+phase_dir_R) & 7;
			pdata0 |= phase_R[phase_ptr_R];
			steps_R++;

			outport(PDATA0,pdata0);


			// speed control & steering
			spd_ptr_L += spd_diff_L;
			spd_ptr_R += spd_diff_R;
			if (spd_ptr_L < 0) 	spd_ptr_L = 0;
			if (spd_ptr_R < 0) 	spd_ptr_R = 0;
			if (adj_switch)	{
				asm mov bx,word ptr spd_ptr_L;
				asm shl bx,1;

				asm mov ax,word ptr fspeed[bx];
				asm mul word ptr adj_mul_L;
				asm shl dx,1;
				asm mov spd_cnt_L,dx;
				// spd_cnt_L = (MSB 16bits of ((spd_tbl[spd_ptr_L+=spd_diff_L] * adj_mul_L)) << 1;

				asm mov ax,word ptr fspeed[bx];
				asm mul word ptr adj_mul_R;
				asm shl dx,1;
				asm mov spd_cnt_R,dx;
				// spd_cnt_R = (MSB 16bits of ((spd_tbl[spd_ptr_R+=spd_diff_R] * adj_mul_R)) << 1;

			}	else	{
				spd_cnt_L = speed[spd_ptr_L];
				spd_cnt_R = speed[spd_ptr_R];
			}

			// keep sensor value in ss_history by step unit
			ss_history[SS_L90][ss_his_ptr_L] = ss_value[SS_L90];
			ss_history[SS_L45][ss_his_ptr_L] = ss_value[SS_L45];
			ss_history[SS_L0 ][ss_his_ptr_L] = ss_value[SS_L0 ];
			//ss_his_ptr_L = ++ss_his_ptr_L % SS_HISTORY_SIZE;
			ss_his_ptr_L = (++ss_his_ptr_L) & 7;

			ss_history[SS_R0 ][ss_his_ptr_R] = ss_value[SS_R0 ];
			ss_history[SS_R45][ss_his_ptr_R] = ss_value[SS_R45];
			ss_history[SS_R90][ss_his_ptr_R] = ss_value[SS_R90];
			//ss_his_ptr_R = ++ss_his_ptr_R % SS_HISTORY_SIZE;
			ss_his_ptr_R = (++ss_his_ptr_R) & 7;
		}
		sync_signal = 0;

		spd_cnt	  = (spd_cnt_L < spd_cnt_R ? spd_cnt_L : spd_cnt_R);

		outport(MOTOR_TIMER,spd_cnt);
//		motor_tmr_start();
	}
	motor_cnt_ref = inport( T1CNT );
	if (motor_cnt_ref >= spd_cnt)
		if (motor_int_mode == MODE_MOTOR_INT_SINGLE)	goto GO_WING;

	asm popa;
	asm iret;
}

// double interrupt mode
void motor_int_L()
{
	asm pusha;
	asm sti;

	Int_End();

	motor_start_L();

	// left
		pdata0 &= (~pio_L);
		phase_ptr_L = (phase_ptr_L+phase_dir_L) & 7;
		pdata0 |= phase_L[phase_ptr_L];
		outport(PDATA0,pdata0);

	// speed control & steering
		spd_ptr_L += spd_diff_L;
		if (spd_ptr_L < 0) 	spd_ptr_L = 0;
		if (adj_switch)	{

			#ifndef DISABLE_RUN_SOUND
			Sound_On();
			#endif

			asm mov bx,word ptr spd_ptr_L;
			asm shl bx,1;
			asm mov ax,word ptr fspeed[bx];
			asm mul word ptr adj_mul_L;
			asm shl dx,1;
			asm mov spd_cnt_L,dx;
			// spd_cnt_L = (MSB 16bits of ((spd_tbl[spd_ptr_L+=spd_diff_L] * adj_mul_L)) << 1;

			#ifndef DISABLE_RUN_SOUND
			Sound_Off();
			#endif

		}	else spd_cnt_L = speed[spd_ptr_L];
		outport(MOTOR_TIMER_L,spd_cnt_L);

	steps_L++;

	// keep sensor value in ss_history by step unit
		ss_history[SS_L90][ss_his_ptr_L] = ss_value[SS_L90];
		ss_history[SS_L45][ss_his_ptr_L] = ss_value[SS_L45];
		ss_history[SS_L0 ][ss_his_ptr_L] = ss_value[SS_L0 ];
		//ss_his_ptr_L = ++ss_his_ptr_L % SS_HISTORY_SIZE;
		ss_his_ptr_L = (++ss_his_ptr_L) & 7;

	sync_signal = 0;

	asm popa;
	asm iret;
}

// double interrupt mode
void motor_int_R()
{
	asm pusha;
	asm sti;

	Int_End();

	motor_start_R();

	// right
		pdata0 &= (~pio_R);
		phase_ptr_R = (phase_ptr_R+phase_dir_R) & 7;
		pdata0 |= phase_R[phase_ptr_R];
		outport(PDATA0,pdata0);

	// speed control & steering
		spd_ptr_R += spd_diff_R;
		if (spd_ptr_R < 0) 	spd_ptr_R = 0;
		if (adj_switch)	{

			#ifndef DISABLE_RUN_SOUND
			Sound_On();
			#endif

//			asm mov bx,word ptr spd_ptr_R;
			asm mov bx,word ptr spd_ptr_L;	// refer to the same speed pointer (SYNC Left SpdPtr)
			asm shl bx,1;
			asm mov ax,word ptr fspeed[bx];
			asm mul word ptr adj_mul_R;
			asm shl dx,1;
			asm mov spd_cnt_R,dx;
			// spd_cnt_R = (MSB 16bits of ((spd_tbl[spd_ptr_R+=spd_diff_R] * adj_mul_R)) << 1;

			#ifndef DISABLE_RUN_SOUND
			Sound_Off();
			#endif

		} else spd_cnt_R = speed[spd_ptr_R];
		outport(MOTOR_TIMER_R,spd_cnt_R);

	steps_R++;

	// keep sensor value in ss_history by step unit
		ss_history[SS_R0 ][ss_his_ptr_R] = ss_value[SS_R0 ];
		ss_history[SS_R45][ss_his_ptr_R] = ss_value[SS_R45];
		ss_history[SS_R90][ss_his_ptr_R] = ss_value[SS_R90];
		//ss_his_ptr_R = ++ss_his_ptr_R % SS_HISTORY_SIZE;
		ss_his_ptr_R = (++ss_his_ptr_R) & 7;

	sync_signal = 0;

	asm popa;
	asm iret;
}

void motor_L()
{
	// left
	pdata0 &= (~pio_L);
	phase_ptr_L = (phase_ptr_L+phase_dir_L) & 7;
	pdata0 |= phase_L[phase_ptr_L];

	outport(PDATA0,pdata0);
}
void motor_R()
{
	// right
	pdata0 &= (~pio_R);
	phase_ptr_R = (phase_ptr_R+phase_dir_R) & 7;
	pdata0 |= phase_R[phase_ptr_R];

	outport(PDATA0,pdata0);
}

void motor_LR()
{
	// left
	pdata0 &= (~pio_L);
	phase_ptr_L = (phase_ptr_L+phase_dir_L) & 7;
	pdata0 |= phase_L[phase_ptr_L];

	// right
	pdata0 &= (~pio_R);
	phase_ptr_R = (phase_ptr_R+phase_dir_R) & 7;
	pdata0 |= phase_R[phase_ptr_R];

	outport(PDATA0,pdata0);
}

void torque_on()
{
	pdata0 &= ~(pio_L | pio_R);

	pdata0 |= ( phase_L[phase_ptr_L ] );
	pdata0 |= ( phase_R[phase_ptr_R ] );
	outport( PDATA0, pdata0 );
}

void torque_off()
{
	pdata0 &= ~(pio_L | pio_R);
	outport( PDATA0, pdata0 );
}
void reverse_L()
{
	phase_dir_L*=(-1);
}
void reverse_R()
{
	phase_dir_R*=(-1);
}
void reverse_LR()
{
	reverse_L();
	reverse_R();
}
void motor_start()
{
	if (motor_int_mode == MODE_MOTOR_INT_DOUBLE)
	{
		motor_start_L();
		motor_start_R();
	}
	else	//motor_int_mode == MODE_MOTOR_INT_SINGLE;
	{
		motor_tmr_start();
		motor_stop_R();
	}
}
void motor_stop()
{
	// single & double interrupt mode
	motor_stop_R();
	motor_stop_L();

	outport(MOTOR_TIMER_L,0x0000);
	outport(MOTOR_TIMER_R,0x0000);

	motor_stop_R();
	motor_stop_L();

	// only single interrupt mode
//	motor_tmr_stop();
//	outport(MOTOR_TIMER,0x0000);
}
void reset_spd_ptr()
{
	spd_ptr_L	= spd_ptr_R	 = 0;
}
void reset_spd_diff()
{
	spd_diff_L 	= spd_diff_R = 0;
}
void reset_steps()
{
	steps_L		= steps_R	 = 0;
	refresh_adj_O(); //!
}
void equal_spd_ptr()
{
	spd_ptr_R	= spd_ptr_L;
}
void sync_step()
{
	while(sync_signal); sync_signal = 1;
}
void set_fSPD()
{
	speed = fspeed;
	set_motor_double_int_mode();
}
void set_tSPD()
{
	speed = tspeed;
	set_motor_single_int_mode();
}
void set_motor_double_int_mode()
{
	// set double interrupt mode
	setvect(INT_TMR1,motor_int_L);
	setvect(INT_TMR2,motor_int_R);
	motor_start_R();	// start INT_TMR2!!!
	motor_int_mode = MODE_MOTOR_INT_DOUBLE;
}
void set_motor_single_int_mode()
{
	// set single interrupt mode
	motor_stop_R();		// stop INT_TMR2!!!!
	setvect(INT_TMR1,motor_int);
	motor_int_mode = MODE_MOTOR_INT_SINGLE;
}
