#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <dos.h>
#include <math.h>

#include "main.h"
#include "disp.h"

#include "speed.tbl"

// speed table
unsigned int *speed;

/////////////////////////////////
// for key interrupt
unsigned char key[128];		// for multi key input

int l_steps;
int	r_steps;

unsigned int l_cnt;
unsigned int r_cnt;

int spd_ptr_L;
int spd_ptr_R;
int spd_diff_L;
int spd_diff_R;

char spd_dptr_L = 1;
char spd_dptr_R = 2;


int iSpd = 250,ioS = 10,thS = 10;
// init speed , in/out steps , through steps

void interrupt (*old_interrupt) (...);
void interrupt new_key_interrupt(...)
{
	unsigned char x;

	x = inportb(0x60);

	if ( x < 128 ) 	key[ x       ] = 1;
	else 		key[ x - 128 ] = 0;

	(*old_interrupt)();
}

void init_values()
{
	speed = tspeed;

	l_steps = 0;
	r_steps = 0;

	spd_ptr_L 	= 0;
	spd_ptr_R	= 0;
	spd_diff_L	= 0;
	spd_diff_R	= 0;

	l_cnt = speed[spd_ptr_L];
	r_cnt = speed[spd_ptr_R];

	L_COLOR = LIGHTBLUE;
	R_COLOR = LIGHTRED;
	L_DIREC = FORWARD;
	R_DIREC = FORWARD;

	xl = XL + bx ; yl = YL + by;
	xr = XR + bx ; yr = YR + by;

}

void main()
{
	int turn_dir;
	#define toLEFT  1
	#define toRIGHT 0

	int cnt_loop = 0;

	init_scr();
	init_values();

	// For key interrupt
	old_interrupt = getvect(0x09);
	setvect(0x09, new_key_interrupt );

	open_screen();

	RESTART:

	draw_maze();
	draw_trace();

	while(1)
	{
		show_info();
		draw_trace();

		////////////////////////////////////////
		// key processing
		if (key[ESC]==1) goto PRG_END;

		if ( key[ UP    ] == 1 ) by-=mm2pixel(1);
		if ( key[ DOWN  ] == 1 ) by+=mm2pixel(1);
		if ( key[ LEFT  ] == 1 ) bx-=mm2pixel(1);
		if ( key[ RIGHT ] == 1 ) bx+=mm2pixel(1);

		if (key[KEY_Q]==1)  {XL=xl;XR=xr;YL=yl;YR=yr;goto RESTART;}
		if (key[KEY_W]==1)  delay(50);
		if (key[KEY_E]==1)  delay(100);
		if (key[KEY_R]==1)  {double cX,cY;
							 cX = (XL+XR) /2.; cY= (YL+YR) /2.;
							 XL=cos(M_PI_4)*(XL-cX)-sin(M_PI_4)*(YL-cY)+cX;
							 YL=sin(M_PI_4)*(XL-cX)+cos(M_PI_4)*(YL-cY)+cY;
							 XR=cos(M_PI_4)*(XR-cX)-sin(M_PI_4)*(YR-cY)+cX;
							 YR=sin(M_PI_4)*(XR-cX)+cos(M_PI_4)*(YR-cY)+cY;
							 delay(100);goto RESTART;}

		if (key[KEY_F]==1)  {enlarge_scr(); delay(100);}
		if (key[KEY_V]==1)  {delarge_scr(); delay(100);}

		if (key[KEY_L2]==1)  turn_dir = toLEFT ;
		if (key[KEY_R2]==1)  turn_dir = toRIGHT;

		if (key[KEY_A]==1)  iSpd ++;
		if (key[KEY_Z]==1)  iSpd --;
		if (key[KEY_S]==1)  ioS ++;
		if (key[KEY_X]==1)  ioS --;
		if (key[KEY_D]==1)  thS ++;
		if (key[KEY_C]==1)  thS --;

		if (key[KEY_1]==1) 	spd_dptr_L = 1;
		if (key[KEY_2]==1) 	spd_dptr_L = 2;
		if (key[KEY_3]==1) 	spd_dptr_L = 3;
		if (key[KEY_4]==1) 	spd_dptr_L = 4;
		if (key[KEY_5]==1) 	spd_dptr_L = 5;

		if (key[KEY_6]==1) 	spd_dptr_R = 1;
		if (key[KEY_7]==1) 	spd_dptr_R = 2;
		if (key[KEY_8]==1) 	spd_dptr_R = 3;
		if (key[KEY_9]==1) 	spd_dptr_R = 4;
		if (key[KEY_0]==1) 	spd_dptr_R = 5;

		if (key[KEY__]==1)   spd_dptr_R = 6;
		if (key[KEY___]==1)  spd_dptr_R = 7;

		if (key[KEY_U]==1)	{	spd_dptr_L--; delay(100); }
		if (key[KEY_I]==1)	{	spd_dptr_L++; delay(100); }
		if (key[KEY_O]==1)	{	spd_dptr_R--; delay(100); }
		if (key[KEY_P]==1)	{	spd_dptr_R++; delay(100); }


		if (cnt_loop > 100)
		{
			draw_maze(); // refresh
			cnt_loop = 0;
		}

		init_values();
		if (turn_dir == toLEFT) turn_left(iSpd,ioS,thS);
		else 					turn_right(iSpd,ioS,thS);

		//delay(100);
		pokeb(0,1050,peekb(0,1052)); // clear key buffer

		cnt_loop++;
	}

	PRG_END:
	close_screen();

	// recover key interrupt
	setvect(0x09,old_interrupt);
}
void stepping()
{
	if ( l_cnt > r_cnt )	{
		l_cnt -= r_cnt;
		//r_cnt = speed[ spd_ptr_R += spd_diff_R ];
		spd_ptr_R += spd_diff_R;
		if (spd_ptr_R < 0) spd_ptr_R = 0;
		r_cnt = speed[ spd_ptr_R ];

		step_right(FORWARD);
		draw_trace();
		return;
	}

	if ( l_cnt < r_cnt )	{
		r_cnt -= l_cnt;
		//l_cnt = speed [ spd_ptr_L += spd_diff_L ];
		spd_ptr_L += spd_diff_L;
		if (spd_ptr_L < 0) spd_ptr_L = 0;
		l_cnt = speed [ spd_ptr_L ];

		step_left (FORWARD);
		draw_trace();
		return;
	}

	if ( l_cnt == r_cnt )	{
		//l_cnt = speed [ spd_ptr_L += spd_diff_L ];
		//r_cnt = speed [ spd_ptr_R += spd_diff_R ];

		spd_ptr_L += spd_diff_L;
		if (spd_ptr_L < 0) spd_ptr_L = 0;
		l_cnt = speed [ spd_ptr_L ];

		spd_ptr_R += spd_diff_R;
		if (spd_ptr_R < 0) spd_ptr_R = 0;
		r_cnt = speed[ spd_ptr_R ];


		step_left (FORWARD);
		step_right(FORWARD);
		draw_trace();
		return;
	}
}
void turn_left(int init_spd_ptr, int io_steps,int th_steps)
{
	// r_steps standard!

	spd_ptr_L = spd_ptr_R = init_spd_ptr;

	l_cnt 	= speed[spd_ptr_L];
	r_cnt 	= speed[spd_ptr_R];

	exchange_color();
	spd_diff_L = -spd_dptr_L;
	spd_diff_R = spd_dptr_R;
	while( r_steps<io_steps )
		stepping();

	exchange_color();
	spd_diff_L = 0;
	spd_diff_R = 0;
	while( r_steps<io_steps+th_steps )
		stepping();

	exchange_color();
	spd_diff_L = spd_dptr_L;
	spd_diff_R = -spd_dptr_R;
	while( r_steps<io_steps+th_steps+io_steps )
		stepping();

	line(xl,yl,xr,yr);
}
void turn_right(int init_spd_ptr, int io_steps,int th_steps)
{
	// l_steps standard!

	spd_ptr_L = spd_ptr_R = init_spd_ptr;

	l_cnt 	= speed[spd_ptr_L];
	r_cnt 	= speed[spd_ptr_R];

	exchange_color();
	spd_diff_L = spd_dptr_L;
	spd_diff_R = -spd_dptr_R;
	while( l_steps<io_steps )
		stepping();

	exchange_color();
	spd_diff_L = 0;
	spd_diff_R = 0;
	while( l_steps<io_steps+th_steps )
		stepping();

	exchange_color();
	spd_diff_L = -spd_dptr_L;
	spd_diff_R = spd_dptr_R;
	while( l_steps<io_steps+th_steps+io_steps )
		stepping();

	line(xl,yl,xr,yr);
}
