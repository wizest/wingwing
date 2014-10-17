#include "info.h"
#include "algol.h"
#include "serial.h"
#include "flash.h"
#include "sampling.h"
#include "led.h"
#include "key.h"
#include "sound.h"
#include "sensor.h"
#include "pathcvrt.h"

#define MAZE_BACKUP_ADDR	   0xE0000000l
#define MAZE_INFO_BACKUP_ADDR  0xE0A00000l

// Horizontal
#define SAMPL_BACKUP_ADDR_H    0xE1000000l
#define SAMPL_BACKUP_SIZE_H	   (sizeof(sL3)+sizeof(sL2)+sizeof(sL1)+sizeof(sC1)+sizeof(sR1)+sizeof(sR2)+sizeof(sR3))
#define SAMPL_BASE_ADDR_H	   sL3		// CAUTION!!!!!!!!!

// Vertical
#define SAMPL_BACKUP_ADDR_V    0xE2000000l		// Vertical		sFL0
#define SAMPL_BACKUP_SIZE_V	   (sizeof(sFL0)+sizeof(sFR0))
#define SAMPL_BASE_ADDR_V	   sFL0		// CAUTION!!!!!!!!!

void update_pos(unsigned char rel_dir)
{
	 mouse_dir   = get_absolute_dir(rel_dir , mouse_dir);
	 mouse_pos  += dxy [ mouse_dir ];
}
void maze_backup()
{
	for(int i=0;i<256;i++)	{
		maze[i] &= 0xF0;//0xFFF0;
		maze[i] |= (maze[i] >> 4) & 0x0F;//0x000F;

		//CAUTION!!
//		maze_info[i] &= 0x0F;//0xFF0F;
//		maze_info[i] |= (maze_info[i] << 4) & 0xF0;//0x00F0;
		maze_info[i] &= ~(VALID_BLK << 1);
		maze_info[i] |= (maze_info[i] << 1) & (VALID_BLK << 1);
	}
}
void maze_recover()
{
	for(int i=0;i<256;i++)	{
		maze[i] &= 0x0F;//0xFF0F;
		maze[i] |= (maze[i] << 4) & 0xF0;//0x00F0;

		//CAUTION!!
//		maze_info[i] &= 0xF0;//0xFFF0;
//		maze_info[i] |= (maze_info[i] >> 4) & 0x0F;//0x000F;
		maze_info[i] &= ~VALID_BLK;
		maze_info[i] |= (maze_info[i] >> 1) & (VALID_BLK);
	}
}
void save_maze()
{
	CopyMemoryFLASH((byte far*)MAZE_BACKUP_ADDR,(unsigned char*)maze,sizeof(maze));
	send_string("\n> Save maze.\n");
	CopyMemoryFLASH((byte far*)MAZE_INFO_BACKUP_ADDR,(unsigned char*)maze_info,sizeof(maze_info));
	send_string("\n> Save maze_info.\n");
}
void load_maze()
{
	init_maze();

	CopyMemory((unsigned char*)maze,(byte far*)MAZE_BACKUP_ADDR,sizeof(maze));
	send_string("\n> Load maze.\n");
	CopyMemory((unsigned char*)maze_info,(byte far*)MAZE_INFO_BACKUP_ADDR,sizeof(maze_info));
	send_string("\n> Load maze_info.\n");

	maze_backup();

	init_mouse();
}
void save_sampl_value()
{
	// Horizontal
	CopyMemoryFLASH((byte far*)SAMPL_BACKUP_ADDR_H,
					(byte far*)SAMPL_BASE_ADDR_H,
					SAMPL_BACKUP_SIZE_H);
	// Vertical
	CopyMemoryFLASH((byte far*)SAMPL_BACKUP_ADDR_V,
					(byte far*)SAMPL_BASE_ADDR_V,
					SAMPL_BACKUP_SIZE_V);

	send_string("\n> Save values sampled.\n");
}
void load_sampl_value()
{
	// Horizontal
	CopyMemory     ((byte far*)SAMPL_BASE_ADDR_H,
					(byte far*)SAMPL_BACKUP_ADDR_H,
					SAMPL_BACKUP_SIZE_H);
	// Vertical
	CopyMemory     ((byte far*)SAMPL_BASE_ADDR_V,
					(byte far*)SAMPL_BACKUP_ADDR_V,
					SAMPL_BACKUP_SIZE_V);

	process_sampl_V();
	process_sampl_H();

	send_string("\n> Load values sampled.\n");
}

void maze_wallup()
{
	int i;

	// Wall up unknown blocks
	for(i=0;i<256;i++)
		if ((maze_info[i] & VALID_BLK) == 0)	{
			maze[i] |= 0x00F0;

			int x,y;
			x=pos_x(i);	y=pos_y(i);

			if (maze[i]&NORTH && y<15) maze[i+dxy[N]] |= SOUTH;
			if (maze[i]&EAST  && x<15) maze[i+dxy[E]] |= WEST;
			if (maze[i]&SOUTH && y>0 ) maze[i+dxy[S]] |= NORTH;
			if (maze[i]&WEST  && x>0 ) maze[i+dxy[W]] |= EAST;
		}

	// Goal
	maze[0x77] &= ~EAST; maze[0x77] &= ~NORTH;
	maze[0x87] &= ~WEST; maze[0x87] &= ~NORTH;
	maze[0x78] &= ~EAST; maze[0x78] &= ~SOUTH;
	maze[0x88] &= ~WEST; maze[0x88] &= ~SOUTH;
}
void show_info()
{
	while( 1 )	{
		// Show Sensor Value	- 0 //////////////////////////////////////
		led_num(0);
		if ( L_KEY == read_key() )	{
			Sound_Select();
			show_ss_value();
		}	else Sound_Beep();
		// Show Sampl Value		- 1 //////////////////////////////////////
		led_num(1);
		if ( L_KEY == read_key() )	{
			Sound_Select();
			show_sampl_value();
		}	else Sound_Beep();
		// Show Maze			- 2 //////////////////////////////////////
		led_num(2);
		if ( L_KEY == read_key() )	{
			Sound_Select();
			show_maze();
		}	else Sound_Beep();
		// Show Path 			- 3 //////////////////////////////////////
		led_num(3);
		if ( L_KEY == read_key() )	{
			Sound_Select();
//			init_mouse();
//			scan_maze(SCAN_GOAL);
//			make_path();
			show_path();
		}	else Sound_Beep();
		// Show Weight 			- 4 //////////////////////////////////////
		led_num(4);
		if ( L_KEY == read_key() )	{
			Sound_Select();
			init_mouse();
			scan_maze(SCAN_GOAL);
			show_weight();
		}	else Sound_Beep();

	}
}

void show_mouse()
{
	send_string("\n> Mouse Pos,Dir.\n");
	send_string("  pos:X:");	send_byte( pos_x(mouse_pos));
	send_string(" , Y:");		send_byte( pos_y(mouse_pos));
}

void _show_path()
{
	unsigned int cc_fptr ;
	unsigned int cc_rptr ;

	cc_fptr = 0;//path_fptr;
	cc_rptr = path_rptr;

	if (cc_rptr > 256) cc_rptr = 256;

	send_string("> Paths.");
	switch(cvrt_mode)
	{
		case CVRT_SCAN_O : send_string("(mode:CVRT_SCAN_O)\n");break;
		case CVRT_SCAN_D : send_string("(mode:CVRT_SCAN_D)\n");break;
		case CVRT_RUSH_D : send_string("(mode:CVRT_RUSH_D)\n");break;
	}

	while ( cc_fptr < cc_rptr )
	{
		switch( path[cc_fptr] )
		{
			case F : send_char('F');	 break;
			case R : send_char('R');	 break;
			case B : send_char('B');	 break;
			case L : send_char('L');	 break;
		}
		if (path_info[cc_fptr]) 	send_char('1');
		else						send_char('0');
		cc_fptr++;
	}
	send_char('\n');
}

void show_path()
{
	// Current path
	send_string("> Current path\n");
	_show_path();

	// debug path
	send_string("> Debug path : StartLine\n");

	init_mouse();
	scan_maze(SCAN_GOAL);

	make_path();
	cvrt_mode = CVRT_SCAN_O;
	path_cvrt();
	_show_path();

	make_path();
	cvrt_mode = CVRT_SCAN_D;
	path_cvrt();
	_show_path();

	make_path();
	cvrt_mode = CVRT_RUSH_D;
	path_cvrt();
	_show_path();
}

void show_maze()
{
	send_string("\n> Maze.\n");
	send_string(" - - - - - - - - - - - - - - - -\n");

	for(int i=15;i>=0;i--)
	{
		for(int j=0;j<16;j++)
		{
			if( maze[ ( j << 4 ) + i ] & WEST  ) send_char('|');
				else send_char(' ');
			if( j==pos_x(mouse_pos) && i==pos_y(mouse_pos) )	send_char('*');
			else {
				if( maze[ ( j << 4 ) + i ] & SOUTH ) send_char('_');
				else send_char(' ');
			}
		}
		send_string("|   ");

		for(j=0;j<16;j++)
		{
			send_char(' ');
			if( maze_info[ ( j << 4 ) + i ] & VALID_BLK ) send_char('1');
			else send_char('0');
		}
		send_string("\n");

	}
	send_string("> Pos:(");
	send_byte(pos_x(mouse_pos));
	send_char(',');
	send_byte(pos_y(mouse_pos));
	send_string(") / Dir:");
	switch(mouse_dir)
	{
		case N : send_char('N'); break;
		case E : send_char('E'); break;
		case S : send_char('S'); break;
		case W : send_char('W'); break;
	}
	send_string("\n");
}
void show_weight()
{
	send_string("\n> Weight.\n");

	for(int i=15;i>=0;i--)	{
		for(int j=0;j<16;j++)	{
			send_byte((unsigned char)maze_weight[(j<<4) +i]);
			send_char(' ');
		}
		send_string("\n");
	}
}

