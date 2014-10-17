#include "main.h"
#include "algol.h"
#include "disp.h"
#include "dos.h"


void search();
void knowwall(unsigned char pos);
void clearwall();

void clearwall()
{
	for(int i=0;i<256;i++)
		{
		maze[i]&=0x0f;
		}
	for(i=0;i<16;i++)
		{
		maze[(i<<4)+0x0f]|=NORTH;
		maze[0xf0+i]|=EAST;
		maze[i<<4]|=SOUTH;
		maze[i]|=WEST;
		}
	maze[0x00]|=maze[0x00]<<4;
	maze[0x10]|=WEST;
}


void main(int,char *argv[]	)
{
	int gd=DETECT,gm;
	int ch;

	initgraph(&gd,&gm,"");
	loadmaze(argv[1]);

	clearwall();
	drawmaze();
	drawwall();

	display();


	while(1)
	{
	ch=getch();
	switch(toupper(ch))
		{
		case 'S':
			search();
			break;
		case 27 : goto END;
		}
	}
	END:
	closegraph();
}

void loadmaze(char *filename)
{
	unsigned char t_maze[256];
	FILE *fp;

	if (!(fp=fopen(filename,"rb")))
		{
		printf("not exist %s",filename);
		exit(1);
		}
	fread(t_maze,256,1,fp);
	fclose(fp);

	for ( int i=0; i<256;i++)
		maze[i] = (unsigned int)t_maze[i];
}


void search()
{
	unsigned char dir;
	unsigned char path_now;

	int goal = SCAN_GOAL;
	int togoal = 0;

	mouse_pos = 0x00;
	mouse_dir = N;


	knowwall(mouse_pos);
	knowwall(mouse_pos + dxy[mouse_dir]);

	RESCAN:
	scan_maze(goal);
	make_path();
	showpath();
	getch();

	int 	TimeComplex=0;
	int 	queueMax = 0;
	long  	queueCnt = 0;

	do
	{
		path_now  = path[path_fptr];
		path_fptr = ++path_fptr % PATH_SIZE;

		dir  		= get_absolute_dir( path_now , mouse_dir );  // get asolute direc
		mouse_dir	= dir;
		mouse_pos  += dxy[dir];

		// Read Walls
		if ( !maze_info[mouse_pos] )	{
			knowwall(mouse_pos);

			// Run Algorithm
			if ( maze[mouse_pos] & wall_bit(get_absolute_dir(path[path_fptr],mouse_dir)) )	{
				unsigned int performance = scan_maze(goal);
				make_path();

				showpath();
//				showweight();
//				getch();

				char temp[30];
				sprintf(temp,"Call Times : %3d",++TimeComplex);
				bar(465,300,640,300+10);
				outtextxy(465,300,temp);

				sprintf(temp,"curr Queue : %3u",performance);
				bar(465,310,640,310+10);
				outtextxy(465,310,temp);

				sprintf(temp,"total Queue : %3u",queueCnt+=performance);
				bar(465,320,640,320+10);
				outtextxy(465,320,temp);

				sprintf(temp,"avg Queue : %3u",queueCnt/TimeComplex);
				bar(465,330,640,330+10);
				outtextxy(465,330,temp);

				sprintf(temp,"max Queue : %3u",queueMax = (queueMax < performance ? performance : queueMax));
				bar(465,340,640,340+10);
				outtextxy(465,340,temp);
			}
		}

		drawwall();
		drawmouse();
		//showweight();
		delay(10);
	} while ( path_fptr != path_rptr );

	goal=0x00;

	togoal++;
	if (togoal == 1) {
		getch();
		goto RESCAN;
	}
}

void knowwall(unsigned char pos)
{
	int x,y;

	maze[pos]|=maze[pos]<<4;
	maze_info[pos] = 1;

	x=pos_x(pos);
	y=pos_y(pos);

	if (maze[pos]&NORTH && y<15) maze[pos+dxy[N]]|=SOUTH;
	if (maze[pos]&EAST && x<15) maze[pos+dxy[E]]|=WEST;
	if (maze[pos]&SOUTH && y>0) maze[pos+dxy[S]]|=NORTH;
	if (maze[pos]&WEST && x>0) maze[pos+dxy[W]]|=EAST;
}

