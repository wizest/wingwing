/*///////////////////////////////////////////
	Class version of Algol.H, Algol.CPP
*////////////////////////////////////////////


typedef unsigned char		BYTE;
typedef unsigned short int  WORD;

// Absolute direction
#define	N	0
#define	E	1
#define	S	2
#define	W	3

// Relative direction
#define	F	0
#define	R	1
#define	B	2
#define	L	3

// Wall Definition
#define	NORTH	0x10	// 0001 0000
#define	EAST	0x20	// 0010 0000
#define	SOUTH	0x40	// 0100 0000
#define	WEST	0x80	// 1000 0000

#define SCAN_GOAL	-1
#define MAZE_SIZE	 256
#define PATH_SIZE	 256

class	CMaze
{
public:
	CMaze();
	~CMaze();

	BYTE byMousePos;	// current position of mouse
	BYTE byMouseDir;    // current direction of mouse

	BYTE byMaze		[MAZE_SIZE];
	WORD wMazeWeight[MAZE_SIZE];
	BYTE byMazeInfo	[MAZE_SIZE];
		// info of VALID maze is 1 !!
		// otherwise info     is 0 !!

	char chDXY		[4];
	// Four Direction : N,E,S,W -> 4
	// Delta position from block to block

	BYTE byPath		[PATH_SIZE];	// Queue of Paths
	BYTE byPathInfo	[PATH_SIZE];	// Queue of PathInfos
		// info of valid path is 1 !! it can be converted !!
		// otherwise info     is 0 !!
		// valid path means the path through valid block once drived


	WORD wPathFPtr;		// Front Pointer
	WORD wPathRPtr;		// Rear Pointer

	BYTE PosX(BYTE byPos)		{return ( ((byPos) >> 4) & 0x000F );}
	BYTE PosY(BYTE byPos)		{return ( (byPos)        & 0x000F );}
	// macro function to calculate each coordination from position value
	// get X parts ; xxxx yyyy in pos
	// get Y parts ; xxxx yyyy in pos

	BYTE WallBit(BYTE byDir)	{return (0x10 << (byDir));}
	// make absolute direction to wall code
	// N: 1<<0, E:1<<1, S:1<<2, W:1<<3
	// N -> NORTH
	// E -> EAST
	// S -> SOUTH
	// W -> WEST

	BYTE GetRelDir(BYTE byNextDir,BYTE byCurDir)	{return ((4+(byNextDir)-(byCurDir)) & 3);}
	// return next relative direction using next and current absolute direction
	// ex) if next direction is E(ast) and current direction is N(orth)
	// 	   this return R(ight)
	BYTE GetAbsDir(BYTE byRelDir, BYTE byMouseDir)	{return (((byRelDir)+(byMouseDir))  & 3);}
	// return next absolute direction

	void InitMaze();
	void InitMouse();

	void ScanMaze(int iScanPos);
	void MakePath();
};

class CMouse : public CMaze
{
public:
	virtual void LoadMaze()	{}
	virtual void SaveMaze()	{}
	virtual void Drive()	{}	// Disply

	void ClearMaze();			// Clear known walls.
};