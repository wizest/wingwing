//////////////////////////////////////////////////////////////////////////
// Path converter for SCAN and RUSH.
//
// Built path_cvrt_scan_D() for iSCAN. 						- 2001.4.30
// path_cvrt_scan_D() bug fixed.							- 2001.5.2
// The selection to use Twist Turn.							- 2001.5.3
// NEW path_cvrt_scan_D() !!								- 2001.9.12
// optimization												- 2002.8.30

#include "pathcvrt.h"
#include "algol.h"
#include "run.h"
#include "info.h"

unsigned char cvrt_mode;

void path_cvrt()
{
/*
	switch(cvrt_mode)	{
		case CVRT_SCAN_O : path_cvrt_scan_O(); 	break;
		case CVRT_SCAN_D : path_cvrt_scan_D();	break;
		case CVRT_RUSH_D : path_cvrt_rush_D();	break;
	}
*/
	// faster for BYTE
	if 		( cvrt_mode == CVRT_SCAN_O ) 	path_cvrt_scan_O();
	else if ( cvrt_mode == CVRT_SCAN_D )	path_cvrt_scan_D();
	else if ( cvrt_mode == CVRT_RUSH_D ) 	path_cvrt_rush_D();
}
void path_cvrt_scan_O()
{
	clr_run();

	path_cvrt_scan_C(path_fptr,path_rptr);
}
void path_cvrt_rush_D()
{
	clr_run();

	// Add last blk : F
	path     [ path_rptr ] = F;
	path_info[ path_rptr ] = 1;
	path_rptr++;

	path_cvrt_rush_C(path_fptr,path_rptr);
}
void path_cvrt_scan_D()
{
	// New Path Converter.
	// 2001.9.12

	int 			t_fptr, t_rptr;
	unsigned char	known_info;
	unsigned char	t_info;

	clr_run();

	// PreProcess.

	// 0. Only convert more paths than 3 DIRs.
	if (path_rptr < 4) 	{
		path_cvrt_scan_O();
		return;
	}

	// 1.First,Second Blocks for proper RUSH-in.
	path_info[0] = 0;
	path_info[1] = 0;

	// 2.Backward scan for SCAN RUNs to read walls.
	for(t_rptr=path_rptr,known_info=0; 1 < t_rptr ;)	{
		--t_rptr;
		if ( path_info[t_rptr] )	known_info++;
		else						known_info = 0;
		if ( known_info <  3 )		path_info[t_rptr] = 0;
	}

	// 3.Backward scan for proper RUSH-out.
	for(t_rptr=path_rptr,known_info=0; 1 < t_rptr ;)	{
		--t_rptr;
		if ( path_info[t_rptr] )	known_info++;
		else						known_info = 0;

		if ( known_info == 1 )	{
			unsigned char c_path = path[t_rptr];
			if 		( c_path == F ) {
					// CAUTION!!
					// Rush Forward -> Scan Forward
					//if(path[t_rptr-1] == F)	{
						path_info[t_rptr] = 0;
						known_info = 0;
					//}
			}
			else if ( c_path == R ) {
					if(path[t_rptr-1] != L) {
						path_info[t_rptr] = 0;
						known_info = 0;
					}
			}
			else if ( c_path == L ) {
					if(path[t_rptr-1] != R)	{
						path_info[t_rptr] = 0;
						known_info = 0;
					}
			}
			else
			{
					path_info[t_rptr] = 0;
					known_info = 0;
			}
		}
	}

	// 4.Forward scan for proper RUSH-in.
	for(t_fptr=0,t_rptr=path_rptr-1,known_info=0;t_fptr<t_rptr;)		{
		if ( path_info[t_fptr] )	known_info++;
		else						known_info = 0;

		if ( known_info == 1 )	{
			unsigned char c_path = path[t_fptr];
			if 		( c_path == F ) {
					// CAUTION!!
					// Rush Forward -> Scan Forward
					//if(path[t_fptr+1] == F) {
						path_info[t_fptr] = 0;
						known_info = 0;
					//}
			}
			else if ( c_path == R ) {
					if(path[t_fptr+1] != L) {
						path_info[t_fptr] = 0;
						known_info = 0;
					}
			}
			else if ( c_path == L ) {
					if(path[t_fptr+1] != R)	{
						path_info[t_fptr] = 0;
						known_info = 0;
					}
			}
			else {
					path_info[t_fptr] = 0;
					known_info = 0;
			}
		}
		++t_fptr;
	}

	// 5. One Block Rush Filter.
	for(t_fptr=1,t_rptr=path_rptr-1,known_info=0;t_fptr<t_rptr;)		{
		if ( path_info[t_fptr] )	known_info++;
		else						known_info = 0;

		if ( known_info == 1 )	{
			if ( path_info[t_fptr-1] == 0 &&
				 path_info[t_fptr+1] == 0 )		path_info[t_fptr] = 0;
		}
		++t_fptr;
	}

	// Body
	#define ANALYSIS_sMODE		0		// SCAN  RUNs
	#define ANALYSIS_rMODE      1		// RUSH  RUNs
	#define ANALYSIS_iMODE_SR   2   	// INTER RUNs	scan -> rush
	#define ANALYSIS_iMODE_RS   3   	// INTER RUNs	rush -> scan
	int analysis_mode = ANALYSIS_sMODE;	// default
	while (path_fptr < path_rptr)	{
		// Find # of paths that have identical path_infos.
		t_fptr = t_rptr = path_fptr;
		t_info = path_info[t_fptr];

		{
			int i_path_rptr = path_rptr;
			while(t_rptr < i_path_rptr &&
				  path_info[t_rptr] == t_info)	t_rptr++;
		}

		if 		( analysis_mode == ANALYSIS_sMODE ) {
				if (t_rptr < path_rptr) 	t_rptr--;
				path_cvrt_scan_C(t_fptr,t_rptr);
				analysis_mode = ANALYSIS_iMODE_SR;
		}
		else if ( analysis_mode == ANALYSIS_rMODE ) {
				path_cvrt_rush_C(t_fptr,t_rptr);
				t_rptr--;
				analysis_mode = ANALYSIS_iMODE_RS;
		}
		else if ( analysis_mode == ANALYSIS_iMODE_SR ) {
				switch(path[t_fptr])	{
					case F:
						switch(path[t_fptr+1])	{
							case F: put_run( run_irFF );	break;
							case L: put_run( run_irFL );	break;
							case R: put_run( run_irFR );	break;
						}
						break;
					case L:
						switch(path[t_fptr+1])	{
							case F: put_run( run_irLF );	break;
							case L: put_run( run_irLL );	break;
							case R: put_run( run_irLR );	break;
						}
						break;
					case R:
						switch(path[t_fptr+1])	{
							case F: put_run( run_irRF );	break;
							case L: put_run( run_irRL );	break;
							case R: put_run( run_irRR );	break;
						}
						break;
				}
				analysis_mode = ANALYSIS_rMODE;
		}
		else if ( analysis_mode == ANALYSIS_iMODE_RS ) {
				switch(path[t_fptr])	{
					case F:
						switch(path[t_fptr+1])	{
							case F: put_run( run_isFF );	break;
							case L: put_run( run_isFL );	break;
							case R: put_run( run_isFR );	break;
						}
						break;
					case L:
						switch(path[t_fptr+1])	{
							case F: put_run( run_isLF );	break;
							case L: put_run( run_isLL );	break;
							case R: put_run( run_isLR );	break;
						}
						break;
					case R:
						switch(path[t_fptr+1])	{
							case F: put_run( run_isRF );	break;
							case L: put_run( run_isRL );	break;
							case R: put_run( run_isRR );	break;
						}
						break;
				}
				t_rptr++;
				analysis_mode = ANALYSIS_sMODE;
		}
		path_fptr = t_rptr;
	}
}

void path_cvrt_scan_C(int t_fptr,int t_rptr)
{
	while( t_fptr < t_rptr )		{
		unsigned char c_path = path[t_fptr];

		if 		( c_path == F )	put_run( run_sFX );
		else if ( c_path == R ) put_run( run_sRX );
		else if ( c_path == B ) put_run( run_sBX );
		else if ( c_path == L ) put_run( run_sLX );

		t_fptr++;
	}
}
void path_cvrt_rush_C(int t_fptr,int t_rptr)
{
	while( 1 )
	{
		if ( t_fptr >= t_rptr ) goto CVRT_RUSH_END;

		unsigned char c_path = path[t_fptr];
		if ( c_path == F ) {
			t_fptr++; // 1
			if ( t_fptr >= t_rptr ) goto CVRT_RUSH_END;

			c_path = path[t_fptr];
			if 		( c_path == F ) {
				put_run(run_rFF);
			}
			else if ( c_path == L ) {
				t_fptr++; // 2
				if ( t_fptr >= t_rptr ) goto CVRT_RUSH_END;

				c_path = path[t_fptr];
				if 		( c_path == F ) {
					put_run(run_rFLF);
				}
				else if	( c_path == L ) {
					t_fptr++; //3
					if ( t_fptr >= t_rptr ) goto CVRT_RUSH_END;

					c_path = path[t_fptr];
					if ( c_path == F ) {
						put_run(run_rFLLF);
					}
					else {
						put_run(run_rFLL);  t_fptr--;
					}
				}
				else {
					put_run(run_rFL);	t_fptr--;
				}
			}
			else if ( c_path == R ) {
				t_fptr++; // 2
				if ( t_fptr >= t_rptr ) goto CVRT_RUSH_END;

				c_path = path[t_fptr];
				if 		( c_path == F ) {
					put_run(run_rFRF);
				}
				else if ( c_path == R ) {
					t_fptr++; // 3
					if ( t_fptr >= t_rptr ) goto CVRT_RUSH_END;

					c_path = path[t_fptr];
					if ( c_path == F ) {
						put_run(run_rFRRF);
					}
					else {
						put_run(run_rFRR);  t_fptr--;
					}
				}
				else {
					put_run(run_rFR); t_fptr--;
				}
			}
		}
		else if ( c_path == L )	{
			t_fptr++; // 1
			if ( t_fptr >= t_rptr ) goto CVRT_RUSH_END;

			c_path = path[t_fptr];
			if 		( c_path == F ) {
				put_run(run_rLF);
			}
			else if ( c_path == L ) {
				t_fptr++; // 2
				if ( t_fptr >= t_rptr ) goto CVRT_RUSH_END;

				c_path = path[t_fptr];
				if ( c_path == F ) {
					put_run(run_rLLF);
				}
				else {
					put_run(run_rLL);  t_fptr--;
				}
			}
			else {
				put_run(run_rLR);
			}
		}
		else if ( c_path == R ) {
			t_fptr++; // 1
			if ( t_fptr >= t_rptr ) goto CVRT_RUSH_END;

			c_path = path[t_fptr];
			if 		( c_path == F ) {
				put_run(run_rRF);
			}
			else if ( c_path == R ) {
				t_fptr++; // 2
				if ( t_fptr >= t_rptr ) goto CVRT_RUSH_END;

				c_path = path[t_fptr];
				if ( c_path == F ) {
					put_run(run_rRRF);
				}
				else {
					put_run(run_rRR); t_fptr--;
				}
			}
			else {
				put_run(run_rRL);
			}
		}
		else goto CVRT_RUSH_END;
	}
	CVRT_RUSH_END:
}
