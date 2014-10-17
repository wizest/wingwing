#include "edge.h"
#include "sensor.h"
#include "sampling.h"
#include "motor.h"

unsigned int level_C_L45,level_P_L45; // Current & Previous level
unsigned int level_C_L90,level_P_L90; // Current & Previous level
unsigned int level_C_R45,level_P_R45; // Current & Previous level
unsigned int level_C_R90,level_P_R90; // Current & Previous level

unsigned int edge_info_L45,edge_info_R45;
unsigned int edge_info_L90,edge_info_R90;

void refresh_level()
{
	scan_level();
	scan_level();
}
void refresh_level_D()
{
	scan_level_D();
	scan_level_D();
}
void refresh_edge()
{
	edge_info_L45 =
	edge_info_R45 =
	edge_info_L90 =
	edge_info_R90 = EDGE_UNKNOWN;
}
void scan_level()
{
	int  cL45,cR45,cL90,cR90;

	cL45 = cR45 = cL90 = cR90 = 0;

	// Count
	for(int i=0 ; i < SS_HISTORY_SIZE ; i++)	{
		// L45
		if ( level_C_L45 == SS_HIGH )	{
			if ( ss_history[SS_L45][i] > threshold_L45_LOW ) cL45++;
		}
		else	{ // SS_LOW
			if ( ss_history[SS_L45][i] > threshold_L45 ) 	 cL45++;
		}
		// R45
		if ( level_C_R45 == SS_HIGH ) 	{
			if ( ss_history[SS_R45][i] > threshold_R45_LOW ) cR45++;
		}
		else	{ // SS_LOW
			if ( ss_history[SS_R45][i] > threshold_R45 ) 	 cR45++;
		}
		// L90
		if ( ss_history[SS_L90][i] > threshold_L90 ) cL90++;
		// R90
		if ( ss_history[SS_R90][i] > threshold_R90 ) cR90++;
	}
	level_P_L45	= level_C_L45;
	level_P_R45 = level_C_R45;
	level_P_L90 = level_C_L90;
	level_P_R90 = level_C_R90;
	if ( cL45 > 3 ) 	level_C_L45 = SS_HIGH;
	else				level_C_L45 = SS_LOW;
	if ( cR45 > 3 ) 	level_C_R45 = SS_HIGH;
	else				level_C_R45 = SS_LOW;
	if ( cL90 > 3 ) 	level_C_L90 = SS_HIGH;
	else				level_C_L90 = SS_LOW;
	if ( cR90 > 3 ) 	level_C_R90 = SS_HIGH;
	else				level_C_R90 = SS_LOW;
}
void scan_level_D()
{
	int  cL45,cR45,cL90,cR90;

	cL45 = cR45 = cL90 = cR90 = 0;

	// Count
	for(int i=0 ; i < SS_HISTORY_SIZE ; i++)	{
		// L45
		if ( level_C_L45 == SS_HIGH )	{
			if ( ss_history[SS_L45][i] > threshold_L45_DL ) cL45++;
		}
		else	{ // SS_LOW
			if ( ss_history[SS_L45][i] > threshold_L45_D ) 	 cL45++;
		}
		// R45
		if ( level_C_R45 == SS_HIGH ) 	{
			if ( ss_history[SS_R45][i] > threshold_R45_DL ) cR45++;
		}
		else	{ // SS_LOW
			if ( ss_history[SS_R45][i] > threshold_R45_D ) 	 cR45++;
		}
		// L90
		if ( ss_history[SS_L90][i] > threshold_L90	 ) cL90++;
		// R90
		if ( ss_history[SS_R90][i] > threshold_R90	 ) cR90++;
	}
	level_P_L45	= level_C_L45;
	level_P_R45 = level_C_R45;
	level_P_L90 = level_C_L90;
	level_P_R90 = level_C_R90;
	if ( cL45 > 3 ) 	level_C_L45 = SS_HIGH;
	else				level_C_L45 = SS_LOW;
	if ( cR45 > 3 ) 	level_C_R45 = SS_HIGH;
	else				level_C_R45 = SS_LOW;
	if ( cL90 > 3 ) 	level_C_L90 = SS_HIGH;
	else				level_C_L90 = SS_LOW;
	if ( cR90 > 3 ) 	level_C_R90 = SS_HIGH;
	else				level_C_R90 = SS_LOW;
}

void scan_edge()
{
	// L45
	if 		(level_P_L45 == SS_HIGH &&
			 level_C_L45 == SS_LOW	)  	edge_info_L45 = EDGE_DN;
	else if (level_P_L45 == SS_LOW &&
			 level_C_L45 == SS_HIGH )   edge_info_L45 = EDGE_UP;
	// R45
	if 		(level_P_R45 == SS_HIGH &&
			 level_C_R45 == SS_LOW	) 	edge_info_R45 = EDGE_DN;
	else if (level_P_R45 == SS_LOW &&
			 level_C_R45 == SS_HIGH )	edge_info_R45 = EDGE_UP;
	// L90
	if 		(level_P_L90 == SS_HIGH &&
			 level_C_L90 == SS_LOW	) 	edge_info_L90 = EDGE_DN;
	else if (level_P_L90 == SS_LOW &&
			 level_C_L90 == SS_HIGH ) 	edge_info_L90 = EDGE_UP;
	// R90
	if 		(level_P_R90 == SS_HIGH &&
			 level_C_R90 == SS_LOW	) 	edge_info_R90 = EDGE_DN;
	else if (level_P_R90 == SS_LOW &&
			 level_C_R90 == SS_HIGH ) 	edge_info_R90 = EDGE_UP;
}
void wait_edge( void (*scan_level_P)(),
				int  (*adj_P)(),
				int  scan_dir,
				unsigned int& edge_L,
				unsigned int& edge_R
			  )
{
	// wait edge
	while( 1 )	{
		scan_level_P();
		scan_edge();
		adj_P();
		switch(scan_dir)	{
			case WAIT_EDGE_L :
				if ( edge_L == EDGE_DN )	{
					edge_L = edge_R = EDGE_UNKNOWN;
					goto END_WAIT_EDGE;
				}
				break;
			case WAIT_EDGE_R :
				if ( edge_R == EDGE_DN )	{
					edge_L = edge_R = EDGE_UNKNOWN;
					goto END_WAIT_EDGE;
				}
				break;
			case WAIT_EDGE_LR :
				if ( edge_L == EDGE_DN ||
					 edge_R == EDGE_DN ) {
					edge_L = edge_R = EDGE_UNKNOWN;
					goto END_WAIT_EDGE;
				}
				break;
		}
		sync_step();
	}
	END_WAIT_EDGE:
}