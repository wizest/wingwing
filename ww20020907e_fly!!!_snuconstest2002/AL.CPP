/*///////////////////////////////////////////
	Class version of Algol.H, Algol.CPP
*////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Searching algorithm oriented diagonal direction for MicroMouse "WingWing"
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
// C code -> C++ code using Class
// valuables' and functions' names changed						- 2001.3.29
//
// last updated 2001.3.29
////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "al.h"

CMaze::CMaze()
{
	chDXY[0]	= 0x01;		// N
	chDXY[1]	= 0x10;		// E
	chDXY[2]	= -0x01;	// S
	chDXY[3]	= -0x10;	// W

	InitMaze();
	InitMouse();
}
CMaze::~CMaze()
{
}
void CMaze::InitMouse()
{
	byMousePos = 0x00;
	byMouseDir = N;
}
void CMaze::InitMaze()
{
	for(int i=0 ; i < MAZE_SIZE ; i++)	{
		byMazeInfo	[i] = 0x00;
		byMaze	 	[i] = 0x00;
	}
	for(i=0 ; i<16 ; i++)		{
		byMaze[ (i<<4)+0x0F  ] |= NORTH;
		byMaze[ i + 0xF0	 ] |= EAST;
		byMaze[ i<<4		 ] |= SOUTH;
		byMaze[ i		   	 ] |= WEST;
	}
	byMaze[0x00] |= EAST;
	byMaze[0x10] |= WEST;

	byMazeInfo[0x00] = 1; // valid
}
void CMaze::ScanMaze( int iScanPos )
{
	// definition and declare
	// position queue
		#define Q_SIZE 		256
		#define UpFPtr()	wFPtr = ++wFPtr & 0xFF	//wFPtr = ++wFPtr % Q_SIZE
		#define UpRPtr()	wRPtr = ++wRPtr & 0xFF	//wRPtr = ++wRPtr % Q_SIZE
		BYTE byPosQ[Q_SIZE];	// position queue
		WORD wFPtr, wRPtr;		// front & rear pointer of pos_Q

	// direction history
		BYTE byDirHistory[MAZE_SIZE]; // index is position
	// weight
		// CAUTION!! : some delta weight values occur dilemma to make paths.
		#define	DW_F	2//1//2 		// delta weight for orthogonal forward
		#define DW_DF	1//2//1 		// delta weight for diagonal forward
		#define DW_MIN	DW_DF   		// less value between DW_F and DW_DF
	// etc
		BYTE byPos,byVPos;	 // from pos_Q

	// initiation
	wFPtr	= wRPtr	= 0;
	for (int i=0;i<MAZE_SIZE;i++) 	{
		#define NO_WEIGHT	0xFFFF
		#define NO_HISTORY  0xFF
		wMazeWeight[i] 	= NO_WEIGHT;
		byDirHistory[i] = NO_HISTORY;
	}

	// put
	if( iScanPos == SCAN_GOAL )		{
		wMazeWeight[0x77] =
		wMazeWeight[0x78] =
		wMazeWeight[0x87] =
		wMazeWeight[0x88] = 0;

		byPosQ[wRPtr] = 0x77;		UpRPtr();
		byPosQ[wRPtr] = 0x78;		UpRPtr();
		byPosQ[wRPtr] = 0x87;		UpRPtr();
		byPosQ[wRPtr] = 0x88;		UpRPtr();
	}
	else	{
		wMazeWeight[ iScanPos ] =	0;
		byPosQ[wRPtr] = (BYTE)iScanPos;	UpRPtr();
	}

	// body
	while( 1 )	{
		// get
		if ( wFPtr == wRPtr ) 		break;		// empty -> ending condition
		byPos  = byPosQ[wFPtr];		UpFPtr();

		if ( byPos == byMousePos ) 	break; 	// CAUTION!! ; ending condition

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
		// frequently used values
		register BYTE byCMaze;
		register BYTE byCDirHistory;
		register WORD wWeightTHRS;
				 WORD wWeightF;
				 WORD wWeightDF;

		byCMaze			= byMaze[byPos];
		byCDirHistory	= byDirHistory	[ byPos ];
		wWeightTHRS 	= wMazeWeight	[ byPos ] + DW_MIN;
		wWeightF		= wMazeWeight	[ byPos ] + DW_F;
		wWeightDF		= wMazeWeight	[ byPos ] + DW_DF;

		// N
			if( !( byCMaze & NORTH ) )	{
				byVPos = byPos + chDXY[ N ];
				if ( wMazeWeight[ byVPos ] > wWeightTHRS )	{
					if ( byCDirHistory == N )	wMazeWeight [ byVPos ] = wWeightF;
					else						wMazeWeight [ byVPos ] = wWeightDF;
					byDirHistory[ byVPos ] = N;
					byPosQ[wRPtr] = byVPos;		UpRPtr();
				}
			}
		// E
			if( !( byCMaze & EAST ) )	{
				byVPos = byPos + chDXY[ E ];
				if ( wMazeWeight[ byVPos ] > wWeightTHRS )	{
					if ( byCDirHistory == E )	wMazeWeight [ byVPos ] = wWeightF;
					else						wMazeWeight [ byVPos ] = wWeightDF;
					byDirHistory[ byVPos ] = E;
					byPosQ[wRPtr] = byVPos;		UpRPtr();
				}
			}
		// S
			if( !( byCMaze & SOUTH ) )	{
				byVPos = byPos + chDXY[ S ];
				if ( wMazeWeight[ byVPos ] > wWeightTHRS )	{
					if ( byCDirHistory == S )	wMazeWeight [ byVPos ] = wWeightF;
					else						wMazeWeight [ byVPos ] = wWeightDF;
					byDirHistory[ byVPos ] = S;
					byPosQ[wRPtr] = byVPos;		UpRPtr();
				}
			}
		// W
			if( !( byCMaze & WEST ) )	{
				byVPos = byPos + chDXY[ W ];
				if ( wMazeWeight[ byVPos ] > wWeightTHRS )	{
					if ( byCDirHistory == W )	wMazeWeight [ byVPos ] = wWeightF;
					else						wMazeWeight [ byVPos ] = wWeightDF;
					byDirHistory[ byVPos ] = W;
					byPosQ[wRPtr] = byVPos;		UpRPtr();
				}
			}
	}
}
void CMaze::MakePath()
{
	// optimization	2000.9.17
	// redesign		2000.10.7
	// 		: sequences to be compared to give current direction priority

	register BYTE byCMaze;
	register WORD wCWeight;
			 BYTE byPosNow,byPosNext;
			 BYTE byDirNow,byDirNext;
			 BYTE byCDir;
			 BYTE byPathPrev;
			 BYTE bySequence[4][4]={{0,1,2,3},{2,3,0,1},{2,3,1,0},{2,1,0,3}};
			 // sequences to be compared for the prority of running direction.
			 //				   	     F......   R......   B......   L......
			 //                	     F R L B   L F R B   F R L B   R F L B
			 // first row is current(running) direction
			 // and the other is sequence to be compared

	byPosNow 	= byMousePos;
	byDirNow 	= byMouseDir;
	byPathPrev 	= F;

	// clear path buff
	wPathFPtr = wPathRPtr = 0;

	while(1) 	{
		// wMazeWeight[byPosNow] == 0 -> ending condition
		if ( !(wCWeight = wMazeWeight[byPosNow]) ) break;

		byCMaze = byMaze[byPosNow];

		int i = 0;
		while( i < 4 )	{
			// sequence to find the best direction oriented the current direction
			byCDir = (bySequence[byPathPrev][i]+byDirNow) & 3;
			if( !( byCMaze & WallBit(byCDir) ))	{
				if( wMazeWeight[byPosNow+chDXY[byCDir]] < wCWeight )	{
					wCWeight 	= wMazeWeight[ (byPosNext=byPosNow+chDXY[byCDir]) ];
					byDirNext 	= byCDir;
				}
			}
			i++;
		}

		byPath     [ wPathRPtr ] = byPathPrev = GetRelDir(byDirNext,byDirNow);
		byPathInfo [ wPathRPtr ] = byMazeInfo[ byPosNext ];

		//wPathRPtr = ++wPathRPtr % PATH_SIZE;
		wPathRPtr++; // CAUTION!! it can make bug! 2000.7.3

		byDirNow = byDirNext;
		byPosNow = byPosNext;

		//if ( !byMazeInfo[ byPosNow ] ) break;
		// CAUTION!! 2000.12.3 : ending condition
	}
}

void CMouse::ClearMaze()
{
	for(int i=0;i<256;i++)		{
		byMaze[i]	&=	0x0F;
	}
	for(i=0;i<16;i++)		{
		byMaze[ (i<<4)+0x0F	] |=NORTH;
		byMaze[ 0xF0+i		] |=EAST;
		byMaze[ i<<4		] |=SOUTH;
		byMaze[ i			] |=WEST;
	}
	byMaze[0x00] |= byMaze[0x00] << 4;
	byMaze[0x10] |= WEST;
}

