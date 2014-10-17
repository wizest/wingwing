#ifndef __ALGOL_H
#   define __ALGOL_H


// absolute direction
#define	N	0
#define	E	1
#define	S	2
#define	W	3

// relative direction
#define	F	0
#define	R	1
#define	B	2
#define	L	3

// wall definition
#define	NORTH	0x0010	// 0001 0000
#define	EAST	0x0020	// 0010 0000
#define	SOUTH	0x0040	// 0100 0000
#define	WEST	0x0080	// 1000 0000

#define VALID_BLK	0x0001

// macro function to calculate each coordination from position value
#define	pos_x(pos)	( ((pos) >> 4) & 0x000F )	// get X parts ; xxxx yyyy in pos
#define pos_y(pos)	( (pos)        & 0x000F )	// get Y parts ; xxxx yyyy in pos

#define get_relative_dir(next_dir,current_dir) ((4+(next_dir)-(current_dir)) & 3)
//#define get_relative_direc(next_dir,current_dir) ((4+(next_dir)-(current_dir))%4)
	// return next relative direction using next and current absolute direction
	// ex) if next direction is E(ast) and current direction is N(orth)
	// this return R(ight)

#define get_absolute_dir(relative_direc,mouse_direc) (((relative_direc)+(mouse_direc)) & 3)
//#define get_absolute_direc(relative_direc,mouse_direc) (((relative_direc)+(mouse_direc))%4)

#define	wall_bit(direc)  (0x10 << (direc))
	// make absolute direction to wall code
	// N: 1<<0, E:1<<1, S:1<<2, W:1<<3
	// N -> NORTH
	// E -> EAST
	// S -> SOUTH
	// W -> WEST

// etc
#define SCAN_GOAL	-1

extern 			void init_maze();
extern 			void init_mouse();

extern 			unsigned int scan_maze(int scan_pos);
extern 			void make_path();

#define MAZE_SIZE	 256
extern unsigned char maze[MAZE_SIZE];
extern unsigned char maze_info[MAZE_SIZE];
extern unsigned int  maze_weight[MAZE_SIZE];

extern 			char dxy[4];

extern unsigned char mouse_pos;
extern unsigned char mouse_dir;

#define PATH_SIZE	 (256)
extern unsigned char path_fptr;
extern unsigned char path_rptr;
extern unsigned char path[PATH_SIZE];
extern unsigned char path_info[PATH_SIZE];

#endif