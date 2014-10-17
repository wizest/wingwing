#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <dos.h>
#include <string.h>

#include "main.h"
#include "disp.h"

double ONESTEP   = RADIUS*ANGLE0_9; 	//mm
double TURNANGLE = ONESTEP/WIDTH; //rad
double COSTURN   = cos(TURNANGLE);
double SINTURN   = sin(TURNANGLE);

int L_COLOR = LIGHTBLUE;
int R_COLOR = LIGHTRED;
int L_DIREC = FORWARD;
int R_DIREC = FORWARD;

double xl = XL, yl = YL, xl_old, yl_old;
double xr = XR, yr = YR, xr_old, yr_old;

double bx = 0 , by = 0; // base x,y

double BLK_DIST ; // pixel
double BLK_X	;   // pixel
double BLK_Y	;   // pixel
double XL ;
double XR ;
double YL ;
double YR ;


void init_scr()
{
	 BLK_DIST   = 300;//440;//230;//440; // pixel
	 init_scr_size();
}
void init_scr_size()
{
	 BLK_X		= 5;   // pixel
	 BLK_Y	    = 5;   // pixel
	 XL =(double)BLK_DIST/2.+BLK_X-mm2pixel(WIDTH/2.);
	 XR =XL+mm2pixel(WIDTH);
	 YL =BLK_Y+BLK_DIST * 1;
	 YR =YL;
}
void enlarge_scr()
{
	BLK_DIST *= 1.1;
	init_scr_size();
}
void delarge_scr()
{
	BLK_DIST *= 0.9;
	init_scr_size();
}

void exchange_color()
{
	int temp_color; temp_color=L_COLOR;	L_COLOR=R_COLOR; R_COLOR=temp_color;
}
void reverse_L()
{
	L_DIREC *= -1;
}
void reverse_R()
{
	R_DIREC *= -1;
}
void reverse_LR()
{
	reverse_L();
	reverse_R();
}



void open_screen()
{
	int gdriver = DETECT, gmode, errorcode;

	initgraph(&gdriver, &gmode, "");
	errorcode = graphresult();

	if (errorcode != grOk)  /* an error occurred */
	{
		   printf("Graphics error: %s\n", grapherrormsg(errorcode));
		   printf("Press any key to halt:");
		   getch();
		   exit(1);             /* return with error code */
	}

	/* clean up */
}
void close_screen()
{
	closegraph();
}

void step_left(int f_or_b)
{
	xl_old=xl;
	yl_old=yl;

	xl=xr+	     (xl_old-xr)*COSTURN-f_or_b*(yl_old-yr)*SINTURN;
	yl=yr+f_or_b*(xl_old-xr)*SINTURN+	    (yl_old-yr)*COSTURN;

	l_steps++;
}
void step_right(int f_or_b)
{
	xr_old=xr;
	yr_old=yr;

	xr=xl+		 (xr_old-xl)*COSTURN+f_or_b*(yr_old-yl)*SINTURN;
	yr=yl-f_or_b*(xr_old-xl)*SINTURN+	    (yr_old-yl)*COSTURN;

	r_steps++;
}

void draw_trace()
{
	putpixel(xl,yl,L_COLOR);
	putpixel(xr,yr,R_COLOR);

	putpixel((xl+xr)/2,(yl+yr)/2,LIGHTGREEN);
}


void draw_maze()
{
	int blk_x=BLK_X;
	int blk_y=BLK_Y;

//	setfillstyle(SOLID_FILL,BLACK);
//	bar(0,0,639,479);

	cleardevice();

	for (int i=0;i<5;i++)
		{
			 for(int j=0;j<5;j++)
			 {
				 //block
				 setcolor(GREEN);
				 rectangle(blk_x,blk_y,blk_x+BLK_DIST,blk_y+BLK_DIST);

				 //Compare Guide Line
				 setcolor(DARKGRAY);
				 setlinestyle(SOLID_LINE,0,NORM_WIDTH);
				 //setlinestyle(DOTTED_LINE,0,NORM_WIDTH);
				 for(double x=blk_x;x<=blk_x+BLK_DIST;x+=mm2pixel(10)) line(x,blk_y+mm2pixel(6),x,blk_y+BLK_DIST-mm2pixel(6));
				 for(double y=blk_y;y<=blk_y+BLK_DIST;y+=mm2pixel(10)) line(blk_x+mm2pixel(6),y,blk_x+BLK_DIST-mm2pixel(6),y);

				 //Pole
				 setcolor(LIGHTRED);
				 setlinestyle(SOLID_LINE,0,NORM_WIDTH);
				 rectangle(blk_x -mm2pixel(6),blk_y   -mm2pixel(6),blk_x +mm2pixel(6),blk_y  +mm2pixel(6) );
				 rectangle(blk_x+BLK_DIST -mm2pixel(6),blk_y   -mm2pixel(6),blk_x+BLK_DIST +mm2pixel(6),blk_y  +mm2pixel(6) );
				 rectangle(blk_x -mm2pixel(6),blk_y+BLK_DIST   -mm2pixel(6),blk_x +mm2pixel(6),blk_y+BLK_DIST  +mm2pixel(6) );
				 rectangle(blk_x+BLK_DIST -mm2pixel(6),blk_y+BLK_DIST   -mm2pixel(6),blk_x+BLK_DIST +mm2pixel(6),blk_y+BLK_DIST  +mm2pixel(6) );

				 //Diagonal
				 setcolor(CYAN);
				 setlinestyle(DOTTED_LINE,0,NORM_WIDTH);
				 line(blk_x+BLK_DIST/2,blk_y,blk_x+BLK_DIST,blk_y+BLK_DIST/2);
				 line(blk_x+BLK_DIST/2,blk_y,blk_x,blk_y+BLK_DIST/2);
				 line(blk_x+BLK_DIST/2,blk_y+BLK_DIST,blk_x+BLK_DIST,blk_y+BLK_DIST/2);
				 line(blk_x+BLK_DIST/2,blk_y+BLK_DIST,blk_x,blk_y+BLK_DIST/2);

				 line(blk_x,blk_y,blk_x+BLK_DIST,blk_y+BLK_DIST);
				 line(blk_x+BLK_DIST,blk_y,blk_x,blk_y+BLK_DIST);

				 // cLINE
				 setcolor(BLUE);
				 setlinestyle(DOTTED_LINE,0,NORM_WIDTH);
				 rectangle(blk_x+cLINE,blk_y+cLINE,blk_x+BLK_DIST-cLINE,blk_y+BLK_DIST-cLINE);

				 // edge line 90
				 setcolor(BROWN);
				 setlinestyle(SOLID_LINE,0,NORM_WIDTH);
				 rectangle(blk_x+EDGE_LINE_90,blk_y+EDGE_LINE_90,blk_x+BLK_DIST-EDGE_LINE_90,blk_y+BLK_DIST-EDGE_LINE_90);

				 // edge line 45
				 setcolor(RED);
				 setlinestyle(SOLID_LINE,0,NORM_WIDTH);
				 rectangle(blk_x+EDGE_LINE_45,blk_y+EDGE_LINE_45,blk_x+BLK_DIST-EDGE_LINE_45,blk_y+BLK_DIST-EDGE_LINE_45);

				 // edge line D45
				 setcolor(MAGENTA);
				 setlinestyle(DOTTED_LINE,0,NORM_WIDTH);
				 line(blk_x+EDGE_LINE_D45,blk_y,blk_x+BLK_DIST,blk_y+BLK_DIST-EDGE_LINE_D45);
				 line(blk_x+BLK_DIST-EDGE_LINE_D45,blk_y,blk_x+BLK_DIST,blk_y+EDGE_LINE_D45);
				 line(blk_x+EDGE_LINE_D45,blk_y+BLK_DIST,blk_x+BLK_DIST,blk_y+EDGE_LINE_D45);
				 line(blk_x+BLK_DIST-EDGE_LINE_D45,blk_y+BLK_DIST,blk_x+BLK_DIST,blk_y+BLK_DIST-EDGE_LINE_D45);
				 line(blk_x+EDGE_LINE_D45,blk_y,blk_x,blk_y+EDGE_LINE_D45);
				 line(blk_x+BLK_DIST-EDGE_LINE_D45,blk_y,blk_x,blk_y+BLK_DIST-EDGE_LINE_D45);
				 line(blk_x,blk_y+EDGE_LINE_D45,blk_x+BLK_DIST-EDGE_LINE_D45,blk_y+BLK_DIST);
				 line(blk_x,blk_y+BLK_DIST-EDGE_LINE_D45,blk_x+EDGE_LINE_D45,blk_y+BLK_DIST);

				 blk_x+=BLK_DIST;
			 }
			 blk_x=BLK_X;
			 blk_y+=BLK_DIST;
		}

		setcolor(WHITE);
		setlinestyle(SOLID_LINE,0,NORM_WIDTH);


}

void show_info()
{
		char text[30];
		// Show the count of the steps
		sprintf(text,"L:%d",l_steps);
		ks_outtextxy(520,2,text);
		sprintf(text,"R:%d",r_steps);
		ks_outtextxy(520+8*7,2,text);

		sprintf(text,"SL:%d",spd_ptr_L);
		ks_outtextxy(520,12,text);
		sprintf(text,"SR:%d",spd_ptr_R);
		ks_outtextxy(520,22,text);

		sprintf(text,"iS:%d",iSpd);
		ks_outtextxy(520,32,text);

		sprintf(text,"io:%d",ioS);
		ks_outtextxy(520,42,text);

		sprintf(text,"th:%d",thS);
		ks_outtextxy(520,52,text);

		sprintf(text,"io2:%d",ioS2);
		ks_outtextxy(520,112,text);

		sprintf(text,"th2:%d",thS2);
		ks_outtextxy(520,122,text);

		sprintf(text,"dPL:%d",spd_dptr_L);
		ks_outtextxy(520,62,text);
		sprintf(text,"dPR:%d",spd_dptr_R);
		ks_outtextxy(520,72,text);
		if ( ioS*spd_dptr_L > iSpd && l_steps< r_steps )	{
			sprintf(text,"L Jitter");
			ks_outtextxy(520,82,text);
		}
		else	{
			sprintf(text,"         ");
			ks_outtextxy(520,82,text);
		}
		if ( ioS*spd_dptr_R > iSpd && l_steps>r_steps )	{
			sprintf(text,"R Jitter");
			ks_outtextxy(520,92,text);
		}
		else	{
			sprintf(text,"         ");
			ks_outtextxy(520,92,text);
		}
}


void ks_outtextxy(int x,int y, const char *text)
{

	setfillstyle(SOLID_FILL,BLACK);
	bar(x,y,x+8*(strlen(text)+1),y+8);

	outtextxy(x,y,text);
}
