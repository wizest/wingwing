#include <conio.h>
#include <stdio.h>
#include <dos.h>
#include <stdlib.h>

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


int iSpd = SWING_iSPD,ioS = SWING_aSTP,thS = 10;
// init speed , in/out steps , through steps



void interrupt (*old_interrupt) (...);
void interrupt new_key_interrupt(...)
{
	unsigned char x;

	x = inportb(0x60);

	if ( x < 128 ) 	key[ x       ] = 1;
	else 			key[ x - 128 ] = 0;

	(*old_interrupt)();
}

void init_values()
{
	speed = fspeed;

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

		if (key[KEY_Q]==1)  make_swing_tbl();
		if (key[KEY_W]==1)  delay(50);
		if (key[KEY_E]==1)  delay(100);

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

		if (cnt_loop > 100)
		{
			draw_maze(); // refresh
			cnt_loop = 0;
		}

		init_values();
		if (turn_dir == toLEFT)
		{
			turn_left(iSpd,ioS,thS);
			l_steps = r_steps = 0;
			turn_right(iSpd,ioS,thS);
		}
		else
		{
			turn_right(iSpd,ioS,thS);
			l_steps = r_steps = 0;
			turn_left(iSpd,ioS,thS);
		}

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
	if ( l_cnt > r_cnt )
	{
		l_cnt -= r_cnt;
		r_cnt = speed[ spd_ptr_R += spd_diff_R ];

		step_right(FORWARD);
		draw_trace();

		return;
	}

	if ( l_cnt < r_cnt )
	{
		r_cnt -= l_cnt;
		l_cnt = speed[ spd_ptr_L += spd_diff_L ];

		step_left (FORWARD);
		draw_trace();

		return;
	}

	if ( l_cnt == r_cnt )
	{
		l_cnt = speed[ spd_ptr_L += spd_diff_L ];
		r_cnt = speed[ spd_ptr_R += spd_diff_R ];

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
	spd_diff_L = -1;
	spd_diff_R = 1;
	while( r_steps<io_steps )
		stepping();

	exchange_color();
	spd_diff_L = 0;
	spd_diff_R = 0;
	while( r_steps<io_steps+th_steps )
		stepping();

	exchange_color();
	spd_diff_L = 1;
	spd_diff_R = -1;
	while( r_steps<io_steps+th_steps+io_steps )
		stepping();
}
void turn_right(int init_spd_ptr, int io_steps,int th_steps)
{
	// l_steps standard!

	spd_ptr_L = spd_ptr_R = init_spd_ptr;

	l_cnt 	= speed[spd_ptr_L];
	r_cnt 	= speed[spd_ptr_R];

	exchange_color();
	spd_diff_L = 1;
	spd_diff_R = -1;
	while( l_steps<io_steps )
		stepping();

	exchange_color();
	spd_diff_L = 0;
	spd_diff_R = 0;
	while( l_steps<io_steps+th_steps )
		stepping();

	exchange_color();
	spd_diff_L = -1;
	spd_diff_R = 1;
	while( l_steps<io_steps+th_steps+io_steps )
		stepping();
}

void make_swing_tbl()
{
	int i;

	char text[30];
	sprintf(text,"Generate Swing table...",l_steps);
	ks_outtextxy(30,2,text);

	#define MAX_MM	90
	unsigned int swing_H_tbl[MAX_MM]; /* clear */	for (i=0;i<MAX_MM;i++)	swing_H_tbl[i]=0;
	unsigned int left,mean,right;
	unsigned int iL,iC,iR; // index

	iSpd 	= SWING_iSPD; // fixed
	thS	= 0;	      // valuable
	ioS	= SWING_aSTP; // fixed

	while(1)
	{
			if( ioS > iSpd*2 )	goto END_MAKING;
			if( (xr-XR-bx) > mm2pixel(90-WIDTH/2)) goto END_MAKING;

			init_values();
			l_steps = r_steps = 0;
			turn_right(iSpd,ioS,thS);
			l_steps = r_steps = 0;
			turn_left(iSpd,ioS,thS);

			#define pixel2mm(pix)	double(double(180.)*(double((pix))/BLK_DIST))
			#define pixel2step(pix) double(pixel2mm(pix)/(double)ONESTEP)
				swing_H_tbl[(int)(pixel2mm(xr-bx-XR))]=thS;


			thS++;
	}
	END_MAKING:

	// Horizontal table
		// fill zero value with mean value between left and right values
			i = 0;
			while( i < MAX_MM )
			{
				while( swing_H_tbl[i] == 0 && i < MAX_MM-1) i++;  // find nonzero value's index
				left 	= swing_H_tbl[iL=i]; i++;
				while( swing_H_tbl[i] == 0 && i < MAX_MM-1) i++;  // find nonzero value's index
				right	= swing_H_tbl[iR=i]; i++;
				mean	= ( left + right ) / 2;

				if ( iR - iL > 1 )
					for (iC = iL + 1 ; iC < iR ; )
						swing_H_tbl[iC++] = mean;
				else i--;
			}

	///////////////////////////////////////////
	// Write

	// file open
		FILE *fp;
		if ((fp=fopen("swing.tbl","w"))==NULL)
		{
			printf("FILE open error\n");
			exit(-1);
		}

	// Horizontal table
		fprintf(fp,"\n   unsigned int swing_H_tbl[]= {\n");
		fprintf(fp,"\n");
		fprintf(fp,"          // iSPD  : %d\n",SWING_iSPD);
		fprintf(fp,"          // aSTP  : %d\n",SWING_aSTP);
		fprintf(fp,"          // input : distance from center(mm)\n");
		fprintf(fp,"          // output: ioS (steps)\n");
		fprintf(fp,"\n");

		for(i=0;i<MAX_MM;i++)
		{
			fprintf(fp,"         %d, // %d mm\n",swing_H_tbl[i],i);
		}
		fprintf(fp,"          };\n");


	// file close
		fclose(fp);

	delay(1000);
}
