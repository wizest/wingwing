//////////////////////////////////////////////
// Adjust Running Steps and Biased Direction.
//
//	a. Orthogonal Forward
//		Adjacency Mode
//		Branch Mode
//		Mode by Side Walls
//		Mode by Front Wall
//
//	b. Diagonal Forward
//		Adjacency Mode
//		Normal Mode

#include "adj.h"
#include "sensor.h"
#include "delay.h"
#include "sampling.h"
#include "swing.h"
#include "motor.h"
#include "serial.h"
#include "led.h"
#include "drive.h"

#include "adjmul.tbl"


//#define DEBUG_ADJ
	// show what a kind of ADJ method success via LEDs;
	// F45			-> |L / R|
	// F0			-> | |
	// F0a 			-> ~~~
	// DF0 			-> | |
	// DF0a			-> | |
	// Branch		-> = = / |
	// failure		-> .


unsigned char adj_switch;
unsigned int adj_mul_L		,adj_mul_R;

// Branch adjusting
//unsigned int adj_BrSL,adj_BrSR;	// steps of down-edge

unsigned int adj_BrSLl,adj_BrSRl;	// steps of down-edge refered to steps_L
unsigned int adj_BrSLr,adj_BrSRr;	// steps of down-edge refered to steps_R

unsigned char adj_BrCL,adj_BrPL;	// current,previous level of left
unsigned char adj_BrCR,adj_BrPR;	// current,previous level of right
unsigned char adj_BrLS;				// level status

void init_adj()
{
	enable_adj();
	disable_adj();
}
void refresh_adj_O()
{
	adj_BrCL	=
	adj_BrPL	=
	adj_BrCR	=
	adj_BrPR	= ADJ_LEVEL_UNKNOWN;

//	adj_BrSL	=
//	adj_BrSR	= steps;

	adj_BrSLl	=
	adj_BrSRl	= steps_L;

	adj_BrSLr	=
	adj_BrSRr 	= steps_R;

	adj_BrLS	= ADJ_EDGE_UNKNOWN;
}
void reset_adj_mul()
{
	adj_mul_L  = adj_mul_R = 32768u;
}
void enable_adj()
{
	refresh_adj_O();
	reset_adj_mul();
	equal_spd_ptr();
	adj_switch = ADJ_ON;
}
void disable_adj()
{
	adj_switch = ADJ_OFF;
	equal_spd_ptr();
	reset_adj_mul();
}
/* origin GOOD!!!!!
int adj_O()
{
	#define DISABLE_0a
	//#define DISABLE_45
	//#define DISABLE_BR
	#define DISABLE_0

	unsigned char sL45,sR45,sL0,sR0;
	unsigned char pL45,pR45,pL0,pR0;

	int mul_ptr;

	sL45 = ss_value[SS_L45];
	sR45 = ss_value[SS_R45];
	sL0	 = ss_value[SS_L0];
	sR0	 = ss_value[SS_R0];

	pL45 = pos_L45[sL45];
	pR45 = pos_R45[sR45];
	pL0	 = pos_L0 [sL0 ];
	pR0  = pos_R0 [sR0 ];

	// Branch Adjusting Data /////////////////////////////////////////////

	// Determine Current Level & Previous Level
		//#define BR_BY_90
		#define BR_BY_45

		#ifdef BR_BY_90	/////////////////////////////////////////////
		// Left
		adj_BrPL = adj_BrCL;
		if ( adj_BrCL == ADJ_LEVEL_HIGH )	{
			if ( cnt_ss_history(SS_L90,threshold_L90_LOW) > 3 )	adj_BrCL= ADJ_LEVEL_HIGH;
			else												adj_BrCL= ADJ_LEVEL_LOW;
		}
		else	{
			if ( cnt_ss_history(SS_L90,threshold_L90) > 3 )	adj_BrCL= ADJ_LEVEL_HIGH;
			else											adj_BrCL= ADJ_LEVEL_LOW;
		}
		// Right
		adj_BrPR = adj_BrCR;
		if ( adj_BrCR == ADJ_LEVEL_HIGH )	{
			if ( cnt_ss_history(SS_R90,threshold_R90_LOW) > 3 ) adj_BrCR= ADJ_LEVEL_HIGH;
			else												adj_BrCR= ADJ_LEVEL_LOW;
		}
		else	{
			if ( cnt_ss_history(SS_R90,threshold_R90) > 3 ) adj_BrCR= ADJ_LEVEL_HIGH;
			else										    adj_BrCR= ADJ_LEVEL_LOW;
		}
		#endif	/////////////////////////////////////////////////////

		#ifdef BR_BY_45	/////////////////////////////////////////////
		// Left
		adj_BrPL = adj_BrCL;
		if ( adj_BrCL == ADJ_LEVEL_HIGH )	{
			if ( cnt_ss_history(SS_L45,threshold_L45_BRL) > 3 )	adj_BrCL= ADJ_LEVEL_HIGH;
			else												adj_BrCL= ADJ_LEVEL_LOW;
		}
		else	{
			if ( cnt_ss_history(SS_L45,threshold_L45_BR) > 3 )	adj_BrCL= ADJ_LEVEL_HIGH;
			else											adj_BrCL= ADJ_LEVEL_LOW;
		}
		// Right
		adj_BrPR = adj_BrCR;
		if ( adj_BrCR == ADJ_LEVEL_HIGH )	{
			if ( cnt_ss_history(SS_R45,threshold_R45_BRL) > 3 ) adj_BrCR= ADJ_LEVEL_HIGH;
			else												adj_BrCR= ADJ_LEVEL_LOW;
		}
		else	{
			if ( cnt_ss_history(SS_R45,threshold_R45_BR) > 3 ) adj_BrCR= ADJ_LEVEL_HIGH;
			else										    adj_BrCR= ADJ_LEVEL_LOW;
		}
		#endif	/////////////////////////////////////////////////////

	// Detect Down-edge,Up-edge
		// Left
		if (adj_BrCL == ADJ_LEVEL_LOW && adj_BrPL == ADJ_LEVEL_HIGH) 	{
			adj_BrSL = steps;
			adj_BrLS &= ~ADJ_EDGE_UP_L;
			adj_BrLS |=  ADJ_EDGE_DN_L;
		}
		else if (adj_BrCL == ADJ_LEVEL_HIGH && adj_BrPL == ADJ_LEVEL_LOW) 	{
//			adj_BrSL = steps;
			adj_BrLS &= ~ADJ_EDGE_DN_L;
			adj_BrLS |=  ADJ_EDGE_UP_L;
		}
		else {
//			adj_BrLS &= ~(ADJ_EDGE_DN_L | ADJ_EDGE_UP_L);
		}

		// Right
		if (adj_BrCR == ADJ_LEVEL_LOW && adj_BrPR == ADJ_LEVEL_HIGH) 	{
			adj_BrSR = steps;
			adj_BrLS &= ~ADJ_EDGE_UP_R;
			adj_BrLS |=  ADJ_EDGE_DN_R;
		}
		else if (adj_BrCR == ADJ_LEVEL_HIGH && adj_BrPR == ADJ_LEVEL_LOW) 	{
//			adj_BrSR = steps;
			adj_BrLS &= ~ADJ_EDGE_DN_R;
			adj_BrLS |=  ADJ_EDGE_UP_R;
		}
		else {
//			adj_BrLS &= ~(ADJ_EDGE_DN_R | ADJ_EDGE_UP_R);
		}
	//////////////////////////////////////////////////////////////////////

	// 0a ////////////////////////////////////////////////////////////////
	#ifndef DISABLE_0a

	#define THRS_pL0a		90
	#define THRS_pR0a		90
	#define THRS_dPOS		15//10		// difference of L/R pos for Not adjusting
	#define aLIMIT_0a		30//25//100	// adjusting LIMIT

	if ( pL0 < THRS_pL0a || pR0 < THRS_pR0a )	goto NADJ_0a;

	if ( ( pL0 - pR0 ) <  THRS_dPOS &&
		 ( pL0 - pR0 ) > -THRS_dPOS )			goto EADJ_0a;

	if ( pL0 > pR0 )	{
		mul_ptr = pL0 - pR0 - THRS_dPOS;
		//mul_ptr += mul_ptr;
		mul_ptr <<= 2;	// x4
		if ( mul_ptr >  aLIMIT_0a ) 	mul_ptr =  aLIMIT_0a;

		adj_mul_L = adj_mul_tbl[ 127 + mul_ptr ]; 	// slow
		adj_mul_R = adj_mul_tbl[ 127 - mul_ptr ];	// fast
//		adj_mul_R = adj_mul_tbl[ 127 ];	// fast
//		reset_adj_mul();
	}
	else	{
		mul_ptr = pR0 - pL0 - THRS_dPOS;
		//mul_ptr += mul_ptr;
		mul_ptr <<= 2;	// x4
		if ( mul_ptr >  aLIMIT_0a ) 	mul_ptr =  aLIMIT_0a;

		adj_mul_L = adj_mul_tbl[ 127 - mul_ptr ];	// fast
//		adj_mul_L = adj_mul_tbl[ 127 ];	// fast
		adj_mul_R = adj_mul_tbl[ 127 + mul_ptr ];	// slow
//		reset_adj_mul();
	}
	EADJ_0a:
				#ifdef DEBUG_ADJ
					led_off(PIO_LED_ALL);
					led_on (PIO_LED_0 | PIO_LED_1);
				#endif
				goto EADJ_O;

	NADJ_0a:
	#endif
	//////////////////////////////////////////////////////////////////////

	// Branch ////////////////////////////////////////////////////////////
	#ifndef DISABLE_BR

	#define aLIMIT_BR	    (24)	//(24)	// adjusting limit
	#define THRS_dSTP_MAX	(170)	//(150) 	// MAX thrs of different steps of L,R edge
	#define THRS_dSTP_MIN   (13)	//(15)		// MIN
	#define ADJ_RANGE		(ONEBLK+THRS_dSTP_MAX) 	// watching steps from EdgeDN
	#define ADJ_HOLD		(HALFBLK)	// adjusting steps from EdgeDN
	#define aLIMIT_0b		(5)		//(5) 	// adjusting limit

	#define THRS_AVOID_POS	(70)		// position refered by front sensor value
	#define THRS_AVOID_NPOS (70)		// if front wall exists, disable adjusting.

	// Set Threshold : sensor value threshold
	unsigned char THRS_sL0b,THRS_sR0b;
		THRS_sL0b = ssv_L0[THRS_AVOID_POS];
		THRS_sR0b = ssv_R0[THRS_AVOID_POS];

	if ( (adj_BrLS&ADJ_EDGE_DN) != ADJ_EDGE_DN )	goto NADJ_BR;

	// Not adj condition
	#define THRS_pL0_BR		THRS_AVOID_NPOS //THRS_pL0a
	#define THRS_pR0_BR		THRS_AVOID_NPOS //THRS_pR0a
	if ( pL0 > THRS_pL0_BR && pR0 > THRS_pR0_BR )	{
		reset_adj_mul();
		goto EADJ_BR;
	}

	if ( adj_BrSL > adj_BrSR )	{
		// L biased -> R slow
		if ( steps  - adj_BrSL > ADJ_RANGE ) 			goto NADJ_BR;

		// by FRONT value
		if ( steps  - adj_BrSL > ADJ_HOLD	 )	{
			if ( sL0 > THRS_sL0b ) 	{
				mul_ptr = (sL0 - THRS_sL0b);
				mul_ptr += mul_ptr;	mul_ptr += mul_ptr;// x4;

				if ( mul_ptr >  aLIMIT_0b )		mul_ptr =  aLIMIT_0b;

				//adj_mul_L = adj_mul_tbl[ 127 ];			// fast
				adj_mul_L = adj_mul_tbl[ 127 - mul_ptr ];	// fast
				adj_mul_R = adj_mul_tbl[ 127 + mul_ptr ];	// slow

				#ifdef DEBUG_ADJ
					led_off(PIO_LED_ALL);
					led_on (PIO_LED_6);
				#endif
			}
			else reset_adj_mul();
		}
		// by SIDE value
		else	{
			mul_ptr	  = adj_BrSL - adj_BrSR ;
			if ( (mul_ptr -= THRS_dSTP_MIN)		   < 0 ) 	goto NADJ_BR;
			if ( mul_ptr+THRS_dSTP_MIN > THRS_dSTP_MAX ) 	goto NADJ_BR;

			//mul_ptr	  += mul_ptr;	// x2
			mul_ptr	  = (mul_ptr > aLIMIT_BR) ? aLIMIT_BR : mul_ptr;
			//adj_mul_L = adj_mul_tbl[ 127 ];			// fast
			adj_mul_L = adj_mul_tbl[ 127 - mul_ptr ];	// fast
			adj_mul_R = adj_mul_tbl[ 127 + mul_ptr ];	// slow

			#ifdef DEBUG_ADJ
				led_off(PIO_LED_ALL);
				led_on (LED_SHOW_H);
			#endif
		}
	}
	else	{
		// R biased -> L slow
		if ( steps  - adj_BrSR > ADJ_RANGE ) 			goto NADJ_BR;

		// by FRONT value
		if ( steps  - adj_BrSR > ADJ_HOLD	 )	{

			if ( sR0 > THRS_sR0b ) 	{
				mul_ptr = (sR0 - THRS_sR0b);
				mul_ptr += mul_ptr;	mul_ptr += mul_ptr;// x4;
				if ( mul_ptr >  aLIMIT_0b ) 		mul_ptr =  aLIMIT_0b;

				//adj_mul_R = adj_mul_tbl[ 127 ];				// fast
				adj_mul_R = adj_mul_tbl[ 127 - mul_ptr ];	// fast
				adj_mul_L = adj_mul_tbl[ 127 + mul_ptr ];   // slow

				#ifdef DEBUG_ADJ
					led_off(PIO_LED_ALL);
					led_on (PIO_LED_6);
				#endif
			}
			else reset_adj_mul();
		}
		// by SIDE value
		else	{
			mul_ptr	  = adj_BrSR - adj_BrSL;
			if ( (mul_ptr -= THRS_dSTP_MIN) 	   < 0 )	goto NADJ_BR;
			if ( mul_ptr+THRS_dSTP_MIN > THRS_dSTP_MAX )	goto NADJ_BR;

			//mul_ptr	  += mul_ptr; 	// x2
			mul_ptr	  = (mul_ptr > aLIMIT_BR) ? aLIMIT_BR : mul_ptr;
			adj_mul_L = adj_mul_tbl[ 127 + mul_ptr ];	// slow
			//adj_mul_R = adj_mul_tbl[ 127 ];			// fast
			adj_mul_R = adj_mul_tbl[ 127 - mul_ptr ];	// fast

			#ifdef DEBUG_ADJ
				led_off(PIO_LED_ALL);
				led_on (LED_SHOW_H);
			#endif
		}
	}
	EADJ_BR:	goto EADJ_O;
	NADJ_BR:

	#endif
	//////////////////////////////////////////////////////////////////////

	// 45 ////////////////////////////////////////////////////////////////
	#ifndef DISABLE_45

	#define REF_L	0		// left
	#define REF_R	1		// right
	#define REF_N	2   	// NADJ

	#define aLIMIT_45		(25) // 25 : recommanded

	#define THRS_aPOS       (120)	// NADJ : front pos
	#define THRS_dX			(15) // 15 : recommanded	// NADJ : delta X

	// Set Threshold
	unsigned char THRS_sL45,THRS_sR45;
		THRS_sL45 = threshold_L45;//ssv_L45[xR2];
		THRS_sR45 = threshold_R45;//ssv_R45[xL2];

// CAUTION !!!!
//	if ( (adj_BrLS&ADJ_EDGE_DN) == ADJ_EDGE_DN )	goto NADJ_45;

	if ( pL0 > THRS_aPOS && pR0 > THRS_aPOS ) 		goto NADJ_45;

	unsigned char	ref_dir;

	if ( sL45 > sR45 )			ref_dir = REF_L;
	else						ref_dir = REF_R;

	if 		( ref_dir == REF_L ) {
			if ( THRS_sL45 > sL45 )	{
				if ( THRS_sR45 > sR45 )	ref_dir = REF_N;
				else					ref_dir = REF_R;
			}
	}
	else if ( ref_dir == REF_R ) {
			if ( THRS_sR45 > sR45 )	{
				if ( THRS_sL45 > sL45 )	ref_dir = REF_N;
				else					ref_dir = REF_L;
			}
	}

	if ( ref_dir == REF_N )		goto NADJ_45;

	register int pos45;
	if ( ref_dir == REF_L )		{
		#ifdef DEBUG_ADJ
			led_off(PIO_LED_ALL);
			led_on(PIO_LED_3);
		#endif
		pos45 = pL45;
	}
	else	{ // if ( ref_dir == REF_R )
		#ifdef DEBUG_ADJ
			led_off(PIO_LED_ALL);
			led_on(PIO_LED_2);
		#endif
		pos45 = pR45;
	}

	if ( pos45 > xC1 )	{
		if 		( (pos45 -= THRS_dX) < xC1 )		pos45 = xC1;
		else if ( pos45 > xC1 + aLIMIT_45  )		pos45 = xC1 + aLIMIT_45;

		adj_mul_L = adj_mul_tbl[ pos45 		 ];	// slow
		//adj_mul_R = adj_mul_tbl[ xC1 	];		// fast
		adj_mul_R = adj_mul_tbl[ 255 - pos45 ];	// fast
	}
	else	{
		if 		( (pos45 += THRS_dX) > xC1 )		pos45 = xC1;
		else if ( pos45 < xC1 - aLIMIT_45 ) 		pos45 = xC1 - aLIMIT_45;

		//adj_mul_L = adj_mul_tbl[ xC1	];			// fast
		adj_mul_L = adj_mul_tbl[ pos45	     ];	// fast
		adj_mul_R = adj_mul_tbl[ 255 - pos45 ]; // slow
	}

	EADJ_45:
				goto EADJ_O;
	NADJ_45:

	#endif
	//////////////////////////////////////////////////////////////////////

	// 0 /////////////////////////////////////////////////////////////////
	#ifndef DISABLE_0

	#define THRS_aPOS0      5           // less than THRS_aPOS in ADJ_45
	#define aLIMIT_0		40 			// adjusting limit

	// Set Threshold : sensor value threshold
	unsigned char THRS_sL0,THRS_sR0;
		//THRS_sL0 = threshold_L0_A;//ssv_L0[15];
		//THRS_sR0 = threshold_R0_A;//ssv_R0[15];

		THRS_sL0 = ssv_L0[70];
		THRS_sR0 = ssv_R0[70];

	// not adjust
	if ( pL0 > THRS_aPOS0 && pR0 > THRS_aPOS0 ) 	goto NADJ_0;

	if ( sL0-THRS_sL0 > sR0-THRS_sR0 )	{
		// L reference
		if ( sL0 < THRS_sL0 ) 	goto NADJ_0;

		mul_ptr = (sL0 - THRS_sL0);
		mul_ptr += mul_ptr;		mul_ptr += mul_ptr;
		if ( mul_ptr >  aLIMIT_0 ) 		mul_ptr =  aLIMIT_0;

		adj_mul_L = adj_mul_tbl[ 127 ];
		adj_mul_R = adj_mul_tbl[ 127 + mul_ptr ];	// slow
	}
	else	{
		// R reference
		if ( sR0 < THRS_sR0 ) 	goto NADJ_0;
		mul_ptr = (sR0 - THRS_sR0);
		mul_ptr += mul_ptr;     mul_ptr += mul_ptr;
		if ( mul_ptr >  aLIMIT_0 ) 		mul_ptr =  aLIMIT_0;

		adj_mul_R = adj_mul_tbl[ 127 ];
		adj_mul_L = adj_mul_tbl[ 127 + mul_ptr ];   // slow
	}

	EADJ_0:
				#ifdef DEBUG_ADJ
					led_off(PIO_LED_ALL);
					led_on (PIO_LED_2 | PIO_LED_3 );
				#endif
				goto EADJ_O;
	NADJ_0:

	#endif
	//////////////////////////////////////////////////////////////////////

	NADJ_O:
				#ifdef DEBUG_ADJ
					led_off(PIO_LED_ALL);
				#endif
				reset_adj_mul();    return ADJ_FAILURE;
	EADJ_O:							return ADJ_SUCCESS;
}
*/

int adj_O()
{
	#define DISABLE_0a
	//#define DISABLE_45
	//#define DISABLE_BR
	#define DISABLE_0

	unsigned char sL45,sR45,sL0,sR0;
	unsigned char pL45,pR45,pL0,pR0;

	int mul_ptr;

	sL45 = ss_value[SS_L45];
	sR45 = ss_value[SS_R45];
	sL0	 = ss_value[SS_L0];
	sR0	 = ss_value[SS_R0];

	pL45 = pos_L45[sL45];
	pR45 = pos_R45[sR45];
	pL0	 = pos_L0 [sL0 ];
	pR0  = pos_R0 [sR0 ];

	// Branch Adjusting Data /////////////////////////////////////////////

	// Determine Current Level & Previous Level
		//#define BR_BY_90
		#define BR_BY_45

		#ifdef BR_BY_90	/////////////////////////////////////////////
		// Left
		adj_BrPL = adj_BrCL;
		if ( adj_BrCL == ADJ_LEVEL_HIGH )	{
			if ( cnt_ss_history(SS_L90,threshold_L90_LOW) > 3 )	adj_BrCL= ADJ_LEVEL_HIGH;
			else												adj_BrCL= ADJ_LEVEL_LOW;
		}
		else	{
			if ( cnt_ss_history(SS_L90,threshold_L90) > 3 )	adj_BrCL= ADJ_LEVEL_HIGH;
			else											adj_BrCL= ADJ_LEVEL_LOW;
		}
		// Right
		adj_BrPR = adj_BrCR;
		if ( adj_BrCR == ADJ_LEVEL_HIGH )	{
			if ( cnt_ss_history(SS_R90,threshold_R90_LOW) > 3 ) adj_BrCR= ADJ_LEVEL_HIGH;
			else												adj_BrCR= ADJ_LEVEL_LOW;
		}
		else	{
			if ( cnt_ss_history(SS_R90,threshold_R90) > 3 ) adj_BrCR= ADJ_LEVEL_HIGH;
			else										    adj_BrCR= ADJ_LEVEL_LOW;
		}
		#endif	/////////////////////////////////////////////////////

		#ifdef BR_BY_45	/////////////////////////////////////////////
		// Left
		adj_BrPL = adj_BrCL;
		if ( adj_BrCL == ADJ_LEVEL_HIGH )	{
			if ( cnt_ss_history(SS_L45,threshold_L45_BRL) > 3 )	adj_BrCL= ADJ_LEVEL_HIGH;
			else												adj_BrCL= ADJ_LEVEL_LOW;
		}
		else	{
			if ( cnt_ss_history(SS_L45,threshold_L45_BR) > 3 )	adj_BrCL= ADJ_LEVEL_HIGH;
			else											adj_BrCL= ADJ_LEVEL_LOW;
		}
		// Right
		adj_BrPR = adj_BrCR;
		if ( adj_BrCR == ADJ_LEVEL_HIGH )	{
			if ( cnt_ss_history(SS_R45,threshold_R45_BRL) > 3 ) adj_BrCR= ADJ_LEVEL_HIGH;
			else												adj_BrCR= ADJ_LEVEL_LOW;
		}
		else	{
			if ( cnt_ss_history(SS_R45,threshold_R45_BR) > 3 ) adj_BrCR= ADJ_LEVEL_HIGH;
			else										    adj_BrCR= ADJ_LEVEL_LOW;
		}
		#endif	/////////////////////////////////////////////////////

	// Detect Down-edge,Up-edge
	#define BRANCH_STEP_OFFSET_L 	(0)
	#define BRANCH_STEP_OFFSET_R 	(0)

		// Left
		if (adj_BrCL == ADJ_LEVEL_LOW && adj_BrPL == ADJ_LEVEL_HIGH) 	{
			adj_BrSLl = steps_L	+ BRANCH_STEP_OFFSET_L;
			adj_BrSLr = steps_R + BRANCH_STEP_OFFSET_L;

			adj_BrLS &= ~ADJ_EDGE_UP_L;
			adj_BrLS |=  ADJ_EDGE_DN_L;
		}
		else if (adj_BrCL == ADJ_LEVEL_HIGH && adj_BrPL == ADJ_LEVEL_LOW) 	{
//			adj_BrSLl = steps_L + BRANCH_STEP_OFFSET_L;
//			adj_BrSLr = steps_R + BRANCH_STEP_OFFSET_L;

			adj_BrLS &= ~ADJ_EDGE_DN_L;
			adj_BrLS |=  ADJ_EDGE_UP_L;
		}
		else {
//			adj_BrLS &= ~(ADJ_EDGE_DN_L | ADJ_EDGE_UP_L);
		}

		// Right
		if (adj_BrCR == ADJ_LEVEL_LOW && adj_BrPR == ADJ_LEVEL_HIGH) 	{
			adj_BrSRl = steps_L + BRANCH_STEP_OFFSET_R;
			adj_BrSRr = steps_R + BRANCH_STEP_OFFSET_R;

			adj_BrLS &= ~ADJ_EDGE_UP_R;
			adj_BrLS |=  ADJ_EDGE_DN_R;
		}
		else if (adj_BrCR == ADJ_LEVEL_HIGH && adj_BrPR == ADJ_LEVEL_LOW) 	{
//			adj_BrSRl = steps_L + BRANCH_STEP_OFFSET_R;
//			adj_BrSRr = steps_R + BRANCH_STEP_OFFSET_R;

			adj_BrLS &= ~ADJ_EDGE_DN_R;
			adj_BrLS |=  ADJ_EDGE_UP_R;
		}
		else {
//			adj_BrLS &= ~(ADJ_EDGE_DN_R | ADJ_EDGE_UP_R);
		}
	//////////////////////////////////////////////////////////////////////

	// 0a ////////////////////////////////////////////////////////////////
	#ifndef DISABLE_0a

	#define THRS_pL0a		90
	#define THRS_pR0a		90
	#define THRS_dPOS		15//10		// difference of L/R pos for Not adjusting
	#define aLIMIT_0a		30//25//100	// adjusting LIMIT

	if ( pL0 < THRS_pL0a || pR0 < THRS_pR0a )	goto NADJ_0a;

	if ( ( pL0 - pR0 ) <  THRS_dPOS &&
		 ( pL0 - pR0 ) > -THRS_dPOS )			goto EADJ_0a;

	if ( pL0 > pR0 )	{
		mul_ptr = pL0 - pR0 - THRS_dPOS;
		//mul_ptr += mul_ptr;
		mul_ptr <<= 2;	// x4
		if ( mul_ptr >  aLIMIT_0a ) 	mul_ptr =  aLIMIT_0a;

		adj_mul_L = adj_mul_tbl[ 127 + mul_ptr ]; 	// slow
		adj_mul_R = adj_mul_tbl[ 127 - mul_ptr ];	// fast
//		adj_mul_R = adj_mul_tbl[ 127 ];	// fast
//		reset_adj_mul();
	}
	else	{
		mul_ptr = pR0 - pL0 - THRS_dPOS;
		//mul_ptr += mul_ptr;
		mul_ptr <<= 2;	// x4
		if ( mul_ptr >  aLIMIT_0a ) 	mul_ptr =  aLIMIT_0a;

		adj_mul_L = adj_mul_tbl[ 127 - mul_ptr ];	// fast
//		adj_mul_L = adj_mul_tbl[ 127 ];	// fast
		adj_mul_R = adj_mul_tbl[ 127 + mul_ptr ];	// slow
//		reset_adj_mul();
	}
	EADJ_0a:
				#ifdef DEBUG_ADJ
					led_off(PIO_LED_ALL);
					led_on (PIO_LED_0 | PIO_LED_1);
				#endif
				goto EADJ_O;

	NADJ_0a:
	#endif
	//////////////////////////////////////////////////////////////////////

	// Branch ////////////////////////////////////////////////////////////
	#ifndef DISABLE_BR

	#define aLIMIT_BR	    (24)	//(24)	// adjusting limit
	#define THRS_dSTP_MAX	(170)	//(170) 	// MAX thrs of different steps of L,R edge
	#define THRS_dSTP_MIN   (13)	//(13)		// MIN
	#define ADJ_RANGE		(ONEBLK+THRS_dSTP_MAX) 	// watching steps from EdgeDN
	#define ADJ_HOLD		(HALFBLK)	// adjusting steps from EdgeDN
	#define aLIMIT_0b		(5)		//(5) 	// adjusting limit

	#define THRS_AVOID_POS	(70)		// position refered by front sensor value
	#define THRS_AVOID_NPOS (70)		// if front wall exists, disable adjusting.

	// Set Threshold : sensor value threshold
	unsigned char THRS_sL0b,THRS_sR0b;
		THRS_sL0b = ssv_L0[THRS_AVOID_POS];
		THRS_sR0b = ssv_R0[THRS_AVOID_POS];

	if ( (adj_BrLS&ADJ_EDGE_DN) != ADJ_EDGE_DN )	goto NADJ_BR;

	// Not adj condition
	#define THRS_pL0_BR		THRS_AVOID_NPOS //THRS_pL0a
	#define THRS_pR0_BR		THRS_AVOID_NPOS //THRS_pR0a
	if ( pL0 > THRS_pL0_BR && pR0 > THRS_pR0_BR )	{
		reset_adj_mul();
		goto EADJ_BR;
	}

	char biased_dir;
	if ( steps_L > steps_R )	biased_dir = adj_BrSLl > adj_BrSLl;
	else 						biased_dir = adj_BrSLr > adj_BrSRr;

	if ( biased_dir ) { //( adj_BrSLl > adj_BrSRl )	{
		// L biased -> R slow
		if ( steps_L  - adj_BrSLl > ADJ_RANGE ) 			goto NADJ_BR;

		// by FRONT value
		if ( steps_L  - adj_BrSLl > ADJ_HOLD	 )	{
			if ( sL0 > THRS_sL0b ) 	{
				mul_ptr = (sL0 - THRS_sL0b);
				mul_ptr += mul_ptr;	mul_ptr += mul_ptr;// x4;

				if ( mul_ptr >  aLIMIT_0b )		mul_ptr =  aLIMIT_0b;

				//adj_mul_L = adj_mul_tbl[ 127 ];			// fast
				adj_mul_L = adj_mul_tbl[ 127 - mul_ptr ];	// fast
				adj_mul_R = adj_mul_tbl[ 127 + mul_ptr ];	// slow

				#ifdef DEBUG_ADJ
					led_off(PIO_LED_ALL);
					led_on (PIO_LED_6);
				#endif
			}
			else reset_adj_mul();
		}
		// by SIDE value
		else	{
			mul_ptr	  = adj_BrSLl - adj_BrSRl ;
			if ( (mul_ptr -= THRS_dSTP_MIN)		   < 0 ) 	goto NADJ_BR;
			if ( mul_ptr+THRS_dSTP_MIN > THRS_dSTP_MAX ) 	goto NADJ_BR;

			//mul_ptr	  += mul_ptr;	// x2
			mul_ptr	  = (mul_ptr > aLIMIT_BR) ? aLIMIT_BR : mul_ptr;
			//adj_mul_L = adj_mul_tbl[ 127 ];			// fast
			adj_mul_L = adj_mul_tbl[ 127 - mul_ptr ];	// fast
			adj_mul_R = adj_mul_tbl[ 127 + mul_ptr ];	// slow

			#ifdef DEBUG_ADJ
				led_off(PIO_LED_ALL);
				led_on (LED_SHOW_H);
			#endif
		}
	}
	else	{
		// R biased -> L slow
		if ( steps_R  - adj_BrSRr > ADJ_RANGE ) 			goto NADJ_BR;

		// by FRONT value
		if ( steps_R  - adj_BrSRr > ADJ_HOLD	 )	{

			if ( sR0 > THRS_sR0b ) 	{
				mul_ptr = (sR0 - THRS_sR0b);
				mul_ptr += mul_ptr;	mul_ptr += mul_ptr;// x4;
				if ( mul_ptr >  aLIMIT_0b ) 		mul_ptr =  aLIMIT_0b;

				//adj_mul_R = adj_mul_tbl[ 127 ];				// fast
				adj_mul_R = adj_mul_tbl[ 127 - mul_ptr ];	// fast
				adj_mul_L = adj_mul_tbl[ 127 + mul_ptr ];   // slow

				#ifdef DEBUG_ADJ
					led_off(PIO_LED_ALL);
					led_on (PIO_LED_6);
				#endif
			}
			else reset_adj_mul();
		}
		// by SIDE value
		else	{
			mul_ptr	  = adj_BrSRr - adj_BrSLr;
			if ( (mul_ptr -= THRS_dSTP_MIN) 	   < 0 )	goto NADJ_BR;
			if ( mul_ptr+THRS_dSTP_MIN > THRS_dSTP_MAX )	goto NADJ_BR;

			//mul_ptr	  += mul_ptr; 	// x2
			mul_ptr	  = (mul_ptr > aLIMIT_BR) ? aLIMIT_BR : mul_ptr;
			adj_mul_L = adj_mul_tbl[ 127 + mul_ptr ];	// slow
			//adj_mul_R = adj_mul_tbl[ 127 ];			// fast
			adj_mul_R = adj_mul_tbl[ 127 - mul_ptr ];	// fast

			#ifdef DEBUG_ADJ
				led_off(PIO_LED_ALL);
				led_on (LED_SHOW_H);
			#endif
		}
	}
	EADJ_BR:	goto EADJ_O;
	NADJ_BR:

	#endif
	//////////////////////////////////////////////////////////////////////

	// 45 ////////////////////////////////////////////////////////////////
	#ifndef DISABLE_45

	#define REF_L	0		// left
	#define REF_R	1		// right
	#define REF_N	2   	// NADJ

	#define aLIMIT_45		(25) // 25 : recommanded

	#define THRS_aPOS       (120)	// NADJ : front pos
	#define THRS_dX			(15) // 15 : recommanded	// NADJ : delta X

	// Set Threshold
	unsigned char THRS_sL45,THRS_sR45;
		THRS_sL45 = threshold_L45;//ssv_L45[xR2];
		THRS_sR45 = threshold_R45;//ssv_R45[xL2];

// CAUTION !!!!
//	if ( (adj_BrLS&ADJ_EDGE_DN) == ADJ_EDGE_DN )	goto NADJ_45;

	if ( pL0 > THRS_aPOS && pR0 > THRS_aPOS ) 		goto NADJ_45;

	unsigned char	ref_dir;

	if ( sL45 > sR45 )			ref_dir = REF_L;
	else						ref_dir = REF_R;

	if 		( ref_dir == REF_L ) {
			if ( THRS_sL45 > sL45 )	{
				if ( THRS_sR45 > sR45 )	ref_dir = REF_N;
				else					ref_dir = REF_R;
			}
	}
	else if ( ref_dir == REF_R ) {
			if ( THRS_sR45 > sR45 )	{
				if ( THRS_sL45 > sL45 )	ref_dir = REF_N;
				else					ref_dir = REF_L;
			}
	}

	if ( ref_dir == REF_N )		goto NADJ_45;

	register int pos45;
	if ( ref_dir == REF_L )		{
		#ifdef DEBUG_ADJ
			led_off(PIO_LED_ALL);
			led_on(PIO_LED_3);
		#endif
		pos45 = pL45;
	}
	else	{ // if ( ref_dir == REF_R )
		#ifdef DEBUG_ADJ
			led_off(PIO_LED_ALL);
			led_on(PIO_LED_2);
		#endif
		pos45 = pR45;
	}

	if ( pos45 > xC1 )	{
		if 		( (pos45 -= THRS_dX) < xC1 )		pos45 = xC1;
		else if ( pos45 > xC1 + aLIMIT_45  )		pos45 = xC1 + aLIMIT_45;

		adj_mul_L = adj_mul_tbl[ pos45 		 ];	// slow
		//adj_mul_R = adj_mul_tbl[ xC1 	];		// fast
		adj_mul_R = adj_mul_tbl[ 255 - pos45 ];	// fast
	}
	else	{
		if 		( (pos45 += THRS_dX) > xC1 )		pos45 = xC1;
		else if ( pos45 < xC1 - aLIMIT_45 ) 		pos45 = xC1 - aLIMIT_45;

		//adj_mul_L = adj_mul_tbl[ xC1	];			// fast
		adj_mul_L = adj_mul_tbl[ pos45	     ];	// fast
		adj_mul_R = adj_mul_tbl[ 255 - pos45 ]; // slow
	}

	EADJ_45:
				goto EADJ_O;
	NADJ_45:

	#endif
	//////////////////////////////////////////////////////////////////////

	// 0 /////////////////////////////////////////////////////////////////
	#ifndef DISABLE_0

	#define THRS_aPOS0      5           // less than THRS_aPOS in ADJ_45
	#define aLIMIT_0		40 			// adjusting limit

	// Set Threshold : sensor value threshold
	unsigned char THRS_sL0,THRS_sR0;
		//THRS_sL0 = threshold_L0_A;//ssv_L0[15];
		//THRS_sR0 = threshold_R0_A;//ssv_R0[15];

		THRS_sL0 = ssv_L0[70];
		THRS_sR0 = ssv_R0[70];

	// not adjust
	if ( pL0 > THRS_aPOS0 && pR0 > THRS_aPOS0 ) 	goto NADJ_0;

	if ( sL0-THRS_sL0 > sR0-THRS_sR0 )	{
		// L reference
		if ( sL0 < THRS_sL0 ) 	goto NADJ_0;

		mul_ptr = (sL0 - THRS_sL0);
		mul_ptr += mul_ptr;		mul_ptr += mul_ptr;
		if ( mul_ptr >  aLIMIT_0 ) 		mul_ptr =  aLIMIT_0;

		adj_mul_L = adj_mul_tbl[ 127 ];
		adj_mul_R = adj_mul_tbl[ 127 + mul_ptr ];	// slow
	}
	else	{
		// R reference
		if ( sR0 < THRS_sR0 ) 	goto NADJ_0;
		mul_ptr = (sR0 - THRS_sR0);
		mul_ptr += mul_ptr;     mul_ptr += mul_ptr;
		if ( mul_ptr >  aLIMIT_0 ) 		mul_ptr =  aLIMIT_0;

		adj_mul_R = adj_mul_tbl[ 127 ];
		adj_mul_L = adj_mul_tbl[ 127 + mul_ptr ];   // slow
	}

	EADJ_0:
				#ifdef DEBUG_ADJ
					led_off(PIO_LED_ALL);
					led_on (PIO_LED_2 | PIO_LED_3 );
				#endif
				goto EADJ_O;
	NADJ_0:

	#endif
	//////////////////////////////////////////////////////////////////////

	NADJ_O:
				#ifdef DEBUG_ADJ
					led_off(PIO_LED_ALL);
				#endif
				reset_adj_mul();    return ADJ_FAILURE;
	EADJ_O:							return ADJ_SUCCESS;
}

int adj_D()	// Diagonal
{
	/* call directily by run //

	*//////////////////////////
	return 0;
}

int adj_DF0()
{
	#define aLIMIT_DF0		125
	#define pTHRS_DF0 		1

	// Set Threshold
	unsigned char THRS_sDL0,THRS_sDR0;
		THRS_sDL0 = threshold_L0_A;
		THRS_sDR0 = threshold_R0_A;

	unsigned char sL,sR,pL,pR;
	int mul_ptr;

	sL = ss_value[SS_L0];
	sR = ss_value[SS_R0];
	pL = pos_L0[sL];
	pR = pos_R0[sR];

	// not adjust
	if ( pL > pTHRS_DF0 && pR > pTHRS_DF0 ) goto NADJ_DF0;

	if ( sL-THRS_sDL0 > sR-THRS_sDR0 )	{
		// L reference
		if ( sL < THRS_sDL0 ) 	goto NADJ_DF0;

		mul_ptr = sL - THRS_sDL0;
		mul_ptr <<= 2;	// x4
//		mul_ptr = (mul_ptr << 2) + mul_ptr;	// x5

		if ( mul_ptr >  aLIMIT_DF0 ) 	mul_ptr =  aLIMIT_DF0;

		adj_mul_L = adj_mul_tbl[ 127 - mul_ptr ];	// fast
		adj_mul_R = adj_mul_tbl[ 127 + mul_ptr ];	// slow

		goto END_ADJ_DF0;
	}
	else	{
		// R reference
		if ( sR < THRS_sDR0	) 	goto NADJ_DF0;

		mul_ptr = sR - THRS_sDR0;
		mul_ptr <<= 2;	// x4
//		mul_ptr = (mul_ptr << 2) + mul_ptr;	// x5

		if ( mul_ptr >  aLIMIT_DF0 ) 	mul_ptr =  aLIMIT_DF0;

		adj_mul_R = adj_mul_tbl[ 127 - mul_ptr ];	// fast
		adj_mul_L = adj_mul_tbl[ 127 + mul_ptr ];	// slow

		goto END_ADJ_DF0;
	}
	NADJ_DF0:
		#ifdef DEBUG_ADJ
			led_off(PIO_LED_ALL);
		#endif
		reset_adj_mul();
		return ADJ_FAILURE;
	END_ADJ_DF0:
		#ifdef	DEBUG_ADJ
			led_off(PIO_LED_ALL);
			led_on(PIO_LED_2|PIO_LED_3);
		#endif
		return ADJ_SUCCESS;
}
int adj_DF0a()		// adjacency
{
//	return adj_DF0();
	#define aLIMIT_DF0a		84
	#define pTHRS_DF0a 		1

	// Set Threshold
	unsigned char THRS_sDL0,THRS_sDR0;
		THRS_sDL0 = threshold_L0_A;
		THRS_sDR0 = threshold_R0_A;

	unsigned char sL,sR,pL,pR;
	int mul_ptr;

	sL = ss_value[SS_L0];
	sR = ss_value[SS_R0];
	pL = pos_L0[sL];
	pR = pos_R0[sR];

	// not adjust
	if ( pL > pTHRS_DF0a && pR > pTHRS_DF0a ) goto NADJ_DF0;

	if ( sL-THRS_sDL0 > sR-THRS_sDR0 )	{
		// L reference
		if ( sL < THRS_sDL0 ) 	goto NADJ_DF0;

		mul_ptr = sL - THRS_sDL0;
		mul_ptr <<= 2;	// x4
//		mul_ptr = (mul_ptr << 2) + mul_ptr;	// x5

		if ( mul_ptr >  aLIMIT_DF0a ) 	mul_ptr =  aLIMIT_DF0a;

		adj_mul_L = adj_mul_tbl[ 127 - mul_ptr ];	// fast
		adj_mul_R = adj_mul_tbl[ 127 + mul_ptr ];	// slow

		goto END_ADJ_DF0;
	}
	else	{
		// R reference
		if ( sR < THRS_sDR0	) 	goto NADJ_DF0;

		mul_ptr = sR - THRS_sDR0;
		mul_ptr <<= 2;	// x4
//		mul_ptr = (mul_ptr << 2) + mul_ptr;	// x5

		if ( mul_ptr >  aLIMIT_DF0a ) 	mul_ptr =  aLIMIT_DF0a;

		adj_mul_R = adj_mul_tbl[ 127 - mul_ptr ];	// fast
		adj_mul_L = adj_mul_tbl[ 127 + mul_ptr ];	// slow

		goto END_ADJ_DF0;
	}
	NADJ_DF0:
		#ifdef DEBUG_ADJ
			led_off(PIO_LED_ALL);
		#endif
		reset_adj_mul();
		return ADJ_FAILURE;
	END_ADJ_DF0:
		#ifdef	DEBUG_ADJ
			led_off(PIO_LED_ALL);
			led_on(PIO_LED_2|PIO_LED_3);
		#endif
		return ADJ_SUCCESS;
}
