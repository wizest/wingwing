#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <graphics.h>

#include "algol.h"
#include "disp.h"

#define NORTH_R	0x01
#define EAST_R	0x02
#define SOUTH_R	0x04
#define WEST_R	0x08

void drawmouse()
{
	int x,y,xx,yy;
	char temp[]="**";
	x=pos_x(mouse_pos);
	y=pos_y(mouse_pos);

	xx=x*28+2;
	yy=28*(15-y)+2;

//	showweight(); getch();

	setcolor(WHITE);
	outtextxy(xx+2,yy+10,temp);

}

void drawwall()
{
	int x,y,xx,yy;


	setcolor(LIGHTCYAN);

	for (int i=0;i<256;i++)
		{
		x=i>>4;
		y=i&0x0f;

		xx=x*28+2;
		yy=28*(15-y)+2;

		if (maze[i] & NORTH) line(xx,yy,xx+26,yy);
		if (maze[i] & EAST ) line(xx+26,yy,xx+26,yy+26);
		if (maze[i] & SOUTH) line(xx,yy+26,xx+26,yy+26);
		if (maze[i] & WEST ) line(xx,yy,xx,yy+26);

		}

}

void display()
{
	setcolor(WHITE);
	outtextxy(465,425,"HandS '99");
	setcolor(LIGHTBLUE);
	line(465,435,630,435);
	setcolor(LIGHTRED);
	outtextxy(465+30,438,"       Korea Univ");

	setcolor(WHITE);
//	outtextxy(465,15,"C.Clear walls");
//	outtextxy(465,30,"W.Clear weight");
//	outtextxy(465,45,"B.Block open walls");
//	outtextxy(465,60,"L.Load maze");
	outtextxy(465,90,"S.Run mouse");
//	outtextxy(465,120,"1/2/3/P");

	setcolor(LIGHTGRAY);
	rectangle(0,465,639,479);

	setfillstyle(SOLID_FILL,DARKGRAY);
	bar(1,466,638,478);

	setcolor(LIGHTGREEN);
	outtextxy(450,469,"               WingWing");
	setcolor(LIGHTMAGENTA);
	outtextxy(10,469,"wizest@hanmail.net");


}
void drawmaze()
{
	int x,y,xx,yy;

	setfillstyle(SOLID_FILL,BLACK);
	bar(0,0,450,450);

	setcolor (YELLOW);

	for (int i=0;i<256;i++)
		{
		x=i>>4;
		y=i&0x0f;

		xx=x*28+2;
		yy=28*(15-y)+2;

		if (maze[i] & NORTH_R) line(xx,yy,xx+26,yy);
		if (maze[i] & EAST_R ) line(xx+26,yy,xx+26,yy+26);
		if (maze[i] & SOUTH_R) line(xx,yy+26,xx+26,yy+26);
		if (maze[i] & WEST_R ) line(xx,yy,xx,yy+26);

		putpixel(xx-1,yy-1,LIGHTGREEN);
		putpixel(xx-1+28,yy-1+28,LIGHTGREEN);
		}


	setcolor(LIGHTCYAN);
	rectangle(0,0,28*16+2,28*16+2);

}
void showweight()
{
		char temp[3];
		int x,y,xx,yy;

		setcolor (DARKGRAY);
		setfillstyle(SOLID_FILL,BLACK);

		for (int i=0;i<256;i++)
		{

		x=i>>4;
		y=i&0x0f;

		xx=x*28+2;
		yy=28*(15-y)+2;

		if (maze_weight[i] != 0xFFFF)
			sprintf(temp,"%3u",maze_weight[i]);
		else
			sprintf(temp,"  ");

		bar(xx+2,yy+10,xx+25,yy+20);
		outtextxy(xx+2,yy+10,temp);

		if (kbhit()) {if (' '==getch()) getch();}
		}


}


void showpath()
{
	int x,y,xx,yy;
//	unsigned char pos;
	unsigned char direc=mouse_dir;
   unsigned char path_now;
   unsigned int path_fptr_cmp;

	setfillstyle(SOLID_FILL,BLACK);


	for (int i=0;i<256;i++)
		{

		x=i>>4;
		y=i&0x0f;

		xx=x*28+2;
		yy=28*(15-y)+2;

		bar(xx+2,yy+10,xx+25,yy+20);
		outtextxy(xx+2,yy+10,"   ");

		}

	x=mouse_pos>>4;
	y=mouse_pos&0x0f;
//	pos=mouse_pos;

	//for(int index=0;index<mouse_path_index;index++)
   path_fptr_cmp=path_fptr;
   while ( path_fptr_cmp != path_rptr )
	{
      path_now = path[path_fptr_cmp];
      if (path_info[path_fptr_cmp] == 0)		setcolor(MAGENTA);
		else												setcolor(GREEN);

      path_fptr_cmp = ++path_fptr_cmp % PATH_SIZE;


		switch(path_now)
		{
			case F:
				xx=x*28+2;
				yy=28*(15-y)+2;

				bar(xx+2,yy+10,xx+25,yy+20);
				outtextxy(xx+2,yy+10," F");

				break;
			case R:
				xx=x*28+2;
				yy=28*(15-y)+2;

				bar(xx+2,yy+10,xx+25,yy+20);
				outtextxy(xx+2,yy+10," R");

				break;
			case B:
				xx=x*28+2;
				yy=28*(15-y)+2;

				bar(xx+2,yy+10,xx+25,yy+20);
				outtextxy(xx+2,yy+10," B");

				break;
			case L:
				xx=x*28+2;
				yy=28*(15-y)+2;

				bar(xx+2,yy+10,xx+25,yy+20);
				outtextxy(xx+2,yy+10," L");

				break;
		} // end of switch

		direc=(direc+path_now)%4;

		switch(direc)
		{
			case N: y++;break;
			case E: x++;break;
			case S: y--;break;
			case W: x--;break;
		}
//		pos=(x<<4) | (y&0x000f);


	} // end of for

	if (kbhit()) {if (' '==getch()) getch();}
}
