////////////////////////////////////////////////////////////////////////////
// Searching algorithm oriented to diagonal direction for "WingWing"
//
// Author : Kim Sang-hoon
// 			HandS, Korea Univ.
// 			wizest@hanmail.net
// 			http://hands.korea.edu/~wizest
//
// reconstruction of scan_maze()								- 2000.8.28
// unrolling of scan_maze() 									- 2000.9.17
// optimization	of make_path() 									- 2000.9.17
// design sequences to be compared in make_path()
//		 to give current direction priority
//																- 2000.10.7
// cutting paths off not to need for driving in make_path()
//                                  							- 2000.12.3
// scan_maze 2nd unrolling for speed							- 2001.4.5
// change char -> int	for speed								- 2001.4.5
// scan_maze bug fixed											- 2001.4.19
// scan_maze fully puts weight for diagonal oriented searching  - 2001.5.25
// added weight_N												- 2001.9.9
// iSCAN bug fix (inter-run path converting failure)			- 2002.8.28
// word -> byte													- 2002.8.30
// condition optimization  										- 2002.9.1
//
// last updated 2002.9.1
////////////////////////////////////////////////////////////////////////////

#include "algol.h"

unsigned char maze[MAZE_SIZE];
unsigned int maze_weight[MAZE_SIZE];
unsigned char maze_info[MAZE_SIZE];
	// info of valid maze is 1 !!
	// otherwise info     is 0 !!

unsigned char mouse_pos; 	// current position of mouse
unsigned char mouse_dir; 	// current direction of mouse

unsigned char  path_fptr; 					// front pointer of path queue
unsigned char  path_rptr; 					// rear pointer of path queue
unsigned char path[PATH_SIZE];				// queue of paths
unsigned char path_info[PATH_SIZE];			// queue of path's infomations
	// info of valid path is 1 !! it can be converted !!
	// otherwise info     is 0 !!
	// valid path means the path through valid block once drived

char	dxy[4] = {0x01, 0x10,-0x01,-0x10};	// delta position from block to block
//	          N     E     S     W

void init_mouse()
{
	mouse_pos = 0x00;
	mouse_dir = N;
}
void init_maze()
{
/*
	for(int i=0 ; i<MAZE_SIZE ; i++)	{
	}
*/
	unsigned int i;
	i=0xFF;do
	{
		maze_info[i] = 0;
		maze	 [i] = 0;
	}
	while(i--);

/*
	for(i=0 ; i<16 ; i++)		{
		maze[ (i<<4)+0x0F  ] |= NORTH;
		maze[ i + 0xF0	   ] |= EAST;
		maze[ i<<4		   ] |= SOUTH;
		maze[ i		   	   ] |= WEST;
	}
*/
	i=15; do
	{
		maze[ (i<<4)+0x0F  ] |= NORTH;
		maze[ i + 0xF0	   ] |= EAST;
		maze[ i<<4		   ] |= SOUTH;
		maze[ i		   	   ] |= WEST;
	}
	while(i--);

	maze[0x00] |= EAST;
	maze[0x10] |= WEST;

	maze_info[0x00] |= VALID_BLK; // valid
}
void scan_maze( int scan_pos )
{
	// 2000.8.28 reconstruction
	// 2001.4.5	 2nd Optimization
	// 2002.8.30 3nd Optimization (word -> byte)

	// definition and declare
		// position queue
			#define Q_SIZE 		16384//256
			#define up_fptr()	fptr++//fptr = ++fptr & 0xFF//fptr = ++fptr % Q_SIZE
			#define up_rptr()	rptr++//rptr = ++rptr & 0xFF//rptr = ++rptr % Q_SIZE
			unsigned char pos_Q[Q_SIZE];	// position queue
			unsigned int fptr , rptr;		// front & rear pointer of pos_Q
		// direction history
			unsigned char dir_history[MAZE_SIZE]; // index is position
		// weight
			// CAUTION!! : some delta weight values occur dilemma to make paths.
			#define DW_N	8		// delta weight for normal
			#define	DW_F	5 		// delta weight for orthogonal forward
			#define DW_DF	3 		// delta weight for diagonal forward
		// etc
			unsigned char pos,v_pos;		// from pos_Q

	// initiation
	fptr	= rptr	= 0;
	unsigned int i;
	i=0xFF;do
	{
		#define NO_WEIGHT	0xFFFF
		#define NO_HISTORY  0xFF
		maze_weight[i] = NO_WEIGHT;
		dir_history[i] = NO_HISTORY;
	}
	while(i--);

	// put
	if( scan_pos == SCAN_GOAL )		{
		maze_weight[0x77] =
		maze_weight[0x78] =
		maze_weight[0x87] =
		maze_weight[0x88] = 0;

		pos_Q[rptr] = 0x88;		up_rptr();
		pos_Q[rptr] = 0x87;		up_rptr();
		pos_Q[rptr] = 0x78;		up_rptr();
		pos_Q[rptr] = 0x77;		up_rptr();
	}
	else	{
		maze_weight[ scan_pos ] =	0;
		pos_Q[rptr] = scan_pos;	up_rptr();
	}

	// body
	while( 1 )	{

		// get
		if ( fptr == rptr ) 	break;		// empty -> ending condition
		pos  = pos_Q[fptr];		up_fptr();

		if ( pos == mouse_pos ) break; 		// CAUTION!! ; ending condition

		/*// ORIGINAL ////////////////////////////////////////////////////
		for( dir=N ; dir <= W ; dir++ )	{
			// wall exist ?
			if( !( maze[pos] & wall_bit(dir) ) )	{
				v_pos = pos+dxy[dir];
				// processing condition : more previous weight than currently calculated
				if ( maze_weight[ v_pos ] > 	maze_weight[ pos ] + DW_MIN )	{
				//if ( maze_weight[ v_pos ] == NO_WEIGHT )	{
					// process weight
					if ( dir_history[pos] == dir )
						// orthogonal forward ///////////////
						maze_weight [ v_pos ] = maze_weight[ pos ] + DW_F;
					else
						// diagonal forward /////////////////
						// strictly this condition is fail!
						// diagonal forward is exactly that
						// the path before the previous path equals to
						// the current path!
						// but for speed, the condition is loosened
						maze_weight [ v_pos ] = maze_weight[ pos ] + DW_DF;
					// record dir in dir_history for diagonal priority
					dir_history[ v_pos ] = dir;
					// put
					pos_Q[rptr] = v_pos;		up_rptr();
				}
			}
		}
		*/////////////////////////////////////////////////////////////////

		// for speed, unrolling //////////////////////////////////////////
		// 2000.9.17
		// 2001.4.5

		// frequently used values
		unsigned char	c_maze;
		unsigned char  	c_dir_history;
		unsigned char	p_dir_history;
		unsigned int 	weight_F;
		unsigned int 	weight_DF;
		unsigned int	weight_N;

		{
			int i_pos	= pos;

			c_maze			= maze[ i_pos ];
			c_dir_history	= dir_history[ i_pos ];

			weight_N		=
			weight_F		=
			weight_DF		= maze_weight[ i_pos ];

			weight_N		+= DW_N;
			weight_F		+= DW_F;
			weight_DF		+= DW_DF;
		}

		if ( c_dir_history == N ) {
				unsigned char t_pos = pos+dxy[S];
				p_dir_history = dir_history[ t_pos ];

				// N
				if( ( c_maze & NORTH ) == 0 )	{
					v_pos = pos + dxy[ N ];
					int i_pos = v_pos;
					if ( maze_weight[ i_pos ] > weight_F )	{
                    //if ( maze_weight[ i_pos ] == NO_WEIGHT ) {
						maze_weight [ i_pos ] = weight_F;
						dir_history [ i_pos ] = N;
						pos_Q[rptr] = v_pos;		up_rptr();
					}
				}
				// E
				if( ( c_maze & EAST ) == 0 )	{
					v_pos = pos + dxy[ E ];
					int i_pos = v_pos;
					if ( p_dir_history == E )	{
						if ( maze_weight[ i_pos ] > weight_DF )	{
                        //if ( maze_weight[ i_pos ] == NO_WEIGHT ) {
							maze_weight [ i_pos ] = weight_DF;
							dir_history [ i_pos ] = E;
							pos_Q[rptr] = v_pos;		up_rptr();
						}
					}
					else	{
						if ( maze_weight[ i_pos ] > weight_N )	{
						//if ( maze_weight[ i_pos ] == NO_WEIGHT ) {
							maze_weight [ i_pos ] = weight_N;
							dir_history [ i_pos ] = E;
							pos_Q[rptr] = v_pos;		up_rptr();
						}
					}
				}
				// W
				if( ( c_maze & WEST ) == 0 )	{
					v_pos = pos + dxy[ W ];
					int i_pos = v_pos;
					if ( p_dir_history == W )	{
						if ( maze_weight[ i_pos ] > weight_DF )	{
						//if ( maze_weight[ i_pos ] == NO_WEIGHT ) {
							maze_weight [ i_pos ] = weight_DF;
							dir_history [ i_pos ] = W;
							pos_Q[rptr] = v_pos;		up_rptr();
						}
					}
					else	{
						if ( maze_weight[ i_pos ] > weight_N )	{
						//if ( maze_weight[ i_pos ] == NO_WEIGHT ) {
							maze_weight [ i_pos ] = weight_N;
							dir_history [ i_pos ] = W;
							pos_Q[rptr] = v_pos;		up_rptr();
						}
					}
				}
		}
		else if ( c_dir_history == E ) {
				unsigned char t_pos = pos+dxy[W];
				p_dir_history = dir_history[ t_pos ];
				// E
				if( ( c_maze & EAST ) == 0 )	{
					v_pos = pos + dxy[ E ];
					int i_pos = v_pos;
					if ( maze_weight[ i_pos ] > weight_F )	{
					//if ( maze_weight[ i_pos ] == NO_WEIGHT ) {
						maze_weight [ i_pos ] = weight_F;
						dir_history [ i_pos ] = E;
						pos_Q[rptr] = v_pos;		up_rptr();
					}
				}
				// S
				if( ( c_maze & SOUTH ) == 0)	{
					v_pos = pos + dxy[ S ];
					int i_pos = v_pos;
					if ( p_dir_history == S )	{
						if ( maze_weight[ i_pos ] > weight_DF )	{
						//if ( maze_weight[ i_pos ] == NO_WEIGHT ) {
							maze_weight [ i_pos ] = weight_DF;
							dir_history [ i_pos ] = S;
							pos_Q[rptr] = v_pos;		up_rptr();
						}
					}
					else	{
						if ( maze_weight[ i_pos ] > weight_N )	{
						//if ( maze_weight[ i_pos ] == NO_WEIGHT ) {
							maze_weight [ i_pos ] = weight_N;
							dir_history [ i_pos ] = S;
							pos_Q[rptr] = v_pos;		up_rptr();
						}
					}
				}
				// N
				if( ( c_maze & NORTH ) == 0 )	{
					v_pos = pos + dxy[ N ];
					int i_pos = v_pos;
					if ( p_dir_history == N )	{
						if ( maze_weight[ i_pos ] > weight_DF )	{
						//if ( maze_weight[ i_pos ] == NO_WEIGHT ) {
							maze_weight [ i_pos ] = weight_DF;
							dir_history [ i_pos ] = N;
							pos_Q[rptr] = v_pos;		up_rptr();
						}
					}
					else	{
						if ( maze_weight[ i_pos ] > weight_N )	{
						//if ( maze_weight[ i_pos ] == NO_WEIGHT ) {
							maze_weight [ i_pos ] = weight_N;
							dir_history [ i_pos ] = N;
							pos_Q[rptr] = v_pos;		up_rptr();
						}
					}
				}
		}
		else if ( c_dir_history == S ) {
				unsigned char t_pos = pos+dxy[N];
				p_dir_history = dir_history[ t_pos ];
				// S
				if( ( c_maze & SOUTH ) == 0)	{
					v_pos = pos + dxy[ S ];
					int i_pos = v_pos;
					if ( maze_weight[ i_pos ] > weight_F )	{
					//if ( maze_weight[ i_pos ] == NO_WEIGHT ) {
						maze_weight [ i_pos ] = weight_F;
						dir_history [ i_pos ] = S;
						pos_Q[rptr] = v_pos;		up_rptr();
					}
				}
				// W
				if( ( c_maze & WEST ) == 0)	{
					v_pos = pos + dxy[ W ];
					int i_pos = v_pos;
					if ( p_dir_history == W )	{
						if ( maze_weight[ i_pos ] > weight_DF )	{
						//if ( maze_weight[ i_pos ] == NO_WEIGHT ) {
							maze_weight [ i_pos ] = weight_DF;
							dir_history [ i_pos ] = W;
							pos_Q[rptr] = v_pos;		up_rptr();
						}
					}
					else	{
						if ( maze_weight[ i_pos ] > weight_N )	{
						//if ( maze_weight[ i_pos ] == NO_WEIGHT ) {
							maze_weight [ i_pos ] = weight_N;
							dir_history [ i_pos ] = W;
							pos_Q[rptr] = v_pos;		up_rptr();
						}
					}
				}
				// E
				if( ( c_maze & EAST ) == 0)	{
					v_pos = pos + dxy[ E ];
					int i_pos = v_pos;
					if ( p_dir_history == E )	{
						if ( maze_weight[ i_pos ] > weight_DF )	{
						//if ( maze_weight[ i_pos ] == NO_WEIGHT ) {
							maze_weight [ i_pos ] = weight_DF;
							dir_history [ i_pos ] = E;
							pos_Q[rptr] = v_pos;		up_rptr();
						}
					}
					else	{
						if ( maze_weight[ i_pos ] > weight_N )	{
						//if ( maze_weight[ i_pos ] == NO_WEIGHT ) {
							maze_weight [ i_pos ] = weight_N;
							dir_history [ i_pos ] = E;
							pos_Q[rptr] = v_pos;		up_rptr();
						}
					}
				}
		}
		else if ( c_dir_history == W ) {
				unsigned char t_pos = pos+dxy[E];
				p_dir_history = dir_history[ t_pos ];
				// W
				if( ( c_maze & WEST ) == 0)	{
					v_pos = pos + dxy[ W ];
					int i_pos = v_pos;
					if ( maze_weight[ i_pos ] > weight_F )	{
					//if ( maze_weight[ i_pos ] == NO_WEIGHT ) {
						maze_weight [ i_pos ] = weight_F;
						dir_history [ i_pos ] = W;
						pos_Q[rptr] = v_pos;		up_rptr();
					}
				}
				// N
				if( ( c_maze & NORTH ) == 0)	{
					v_pos = pos + dxy[ N ];
					int i_pos = v_pos;
					if ( p_dir_history == N )	{
						if ( maze_weight[ i_pos ] > weight_DF )	{
						//if ( maze_weight[ i_pos ] == NO_WEIGHT ) {
							maze_weight [ i_pos ] = weight_DF;
							dir_history [ i_pos ] = N;
							pos_Q[rptr] = v_pos;		up_rptr();
						}
					}
					else	{
						if ( maze_weight[ i_pos ] > weight_N )	{
						//if ( maze_weight[ i_pos ] == NO_WEIGHT ) {
							maze_weight [ i_pos ] = weight_N;
							dir_history [ i_pos ] = N;
							pos_Q[rptr] = v_pos;		up_rptr();
						}
					}
				}
				// S
				if( ( c_maze & SOUTH ) == 0)	{
					v_pos = pos + dxy[ S ];
					int i_pos = v_pos;
					if ( p_dir_history == S )	{
						if ( maze_weight[ i_pos ] > weight_DF )	{
						//if ( maze_weight[ i_pos ] == NO_WEIGHT ) {
							maze_weight [ i_pos ] = weight_DF;
							dir_history [ i_pos ] = S;
							pos_Q[rptr] = v_pos;		up_rptr();
						}
					}
					else	{
						if ( maze_weight[ i_pos ] > weight_N )	{
						//if ( maze_weight[ i_pos ] == NO_WEIGHT ) {
							maze_weight [ i_pos ] = weight_N;
							dir_history [ i_pos ] = S;
							pos_Q[rptr] = v_pos;		up_rptr();
						}
					}
				}
		}
		else {
				// N
				if( ( c_maze & NORTH ) == 0)	{
					v_pos = pos + dxy[ N ];
					int i_pos = v_pos;
					if ( maze_weight[ i_pos ] > weight_N )	{
					//if ( maze_weight[ i_pos ] == NO_WEIGHT ) {
						maze_weight [ i_pos ] = weight_N;
						dir_history [ i_pos ] = N;
						pos_Q[rptr] = v_pos;		up_rptr();
					}
				}
				// E
				if( ( c_maze & EAST ) == 0)	{
					v_pos = pos + dxy[ E ];
					int i_pos = v_pos;
					if ( maze_weight[ i_pos ] > weight_N )	{
					//if ( maze_weight[ i_pos ] == NO_WEIGHT ) {
						maze_weight [ i_pos ] = weight_N;
						dir_history [ i_pos ] = E;
						pos_Q[rptr] = v_pos;		up_rptr();
					}
				}
				// S
				if( ( c_maze & SOUTH ) == 0)	{
					v_pos = pos + dxy[ S ];
					int i_pos = v_pos;
					if ( maze_weight[ i_pos ] > weight_N )	{
					//if ( maze_weight[ i_pos ] == NO_WEIGHT ) {
						maze_weight [ i_pos ] = weight_N;
						dir_history [ i_pos ] = S;
						pos_Q[rptr] = v_pos;		up_rptr();
					}
				}
				// W
				if( ( c_maze & WEST ) == 0)	{
					v_pos = pos + dxy[ W ];
					int i_pos = v_pos;
					if ( maze_weight[ i_pos ] > weight_N )	{
					//if ( maze_weight[ i_pos ] == NO_WEIGHT ) {
						maze_weight [ i_pos ] = weight_N;
						dir_history [ i_pos ] = W;
						pos_Q[rptr] = v_pos;		up_rptr();
					}
				}
		}
	}
}

void make_path()
{
	// optimization	2000.9.17
	// redesign		2000.10.7
	// 		: sequences to be compared to give current direction priority

	unsigned char c_maze;
	unsigned int  c_weight;
	unsigned int  pos_now,pos_next;	// only INDEX use
	unsigned char dir_now,dir_next;
	unsigned char c_dir;
	unsigned char path_prev;

//	unsigned char sequence[4][4]={{0,1,2,3},{2,3,0,1},{2,3,1,0},{2,1,0,3}};
	// sequences to be compared for the prority of running direction.
	//						   	    F......   R......   B......   L......
	//                        	    F R L B   L F R B   F R L B   R F L B
	// first row is current(running) direction
	// and the other is sequence to be compared

	// reverse alignment for each Direction	 - 2002.9.1
	unsigned char sequence[4][4]={{3,2,1,0},{1,0,3,2},{0,1,3,2},{3,0,1,2}};

	pos_now = mouse_pos;
	dir_now = mouse_dir;
	path_prev = F;

	// clear path buff
	path_fptr = path_rptr = 0;

	while(1) 	{
		// maze_weight[pos_now] == 0 -> ending condition
		if ( (c_weight = maze_weight[pos_now]) == 0 ) break;

		c_maze = maze[pos_now];

		{
			int i_path_prev = path_prev;

/*
			int i = 0;
			while( i < 4 )	{
				// sequence to find the best direction oriented the current direction
				c_dir = (sequence[i_path_prev][i]+dir_now) & 3;
				if( !( c_maze & wall_bit(c_dir) ))	{
					if( maze_weight[pos_now+dxy[c_dir]] < c_weight )	{
						c_weight = maze_weight[ (pos_next=pos_now+dxy[c_dir]) ];
						dir_next = c_dir;
					}
				}
				i++;
			}
*/


			// loop optimization - 2002.9.1
			int i = 3;
			do {
				// sequence to find the best direction oriented the current direction
				c_dir = (sequence[i_path_prev][i]+dir_now) & 3;
				if( ( c_maze & wall_bit(c_dir) ) == 0 )	{
					if( maze_weight[pos_now+dxy[c_dir]] < c_weight )	{
						c_weight = maze_weight[ (pos_next=pos_now+dxy[c_dir]) ];
						dir_next = c_dir;
					}
				}
			} while(i--);
		}

		{
			int i_path_rptr = path_rptr;
			path      [ i_path_rptr ] = path_prev = get_relative_dir(dir_next,dir_now);
			path_info [ i_path_rptr ] = maze_info[ pos_now ] & VALID_BLK;		// 2002.8.28 : iscan bug fix!
		}

		//path_rptr = ++path_rptr % PATH_SIZE;
		path_rptr++; // CAUTION!! it can make bug! 2000.7.3

		dir_now = dir_next;
		pos_now = pos_next;

		//if ( !(maze_info[ pos_now ] & VALID_BLK) ) break; // CAUTION!! 2000.12.3 : ending condition
	}
}

