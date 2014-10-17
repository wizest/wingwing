#include "sampling.h"
#include "motor.h"
#include "delay.h"
#include "turn.h"
#include "led.h"
#include "key.h"
#include "sensor.h"
#include "serial.h"
#include "swing.h"
#include "adj_pos.h"
#include "drive.h"
#include "adj.h"
#include "sound.h"
#include "info.h"

// sampled sensor value
	// for H sampl
		unsigned char sL3[6],sL2[6],sL1[6],sC1[6],sR1[6],sR2[6],sR3[6];
	// for V sampl
		unsigned char sFL0[SAMPL_VSTEP],sFR0[SAMPL_VSTEP];

// threshold of wall existance
	unsigned char threshold_L0;
	unsigned char threshold_R0;
	unsigned char threshold_L0_A;	// for Adj
	unsigned char threshold_R0_A;	// for Adj

	unsigned char threshold_L45;
	unsigned char threshold_R45;
	unsigned char threshold_L45_LOW;
	unsigned char threshold_R45_LOW;
	unsigned char threshold_L45_D;
	unsigned char threshold_R45_D;
	unsigned char threshold_L45_DL;
	unsigned char threshold_R45_DL;
	unsigned char threshold_L45_BR;
	unsigned char threshold_R45_BR;
	unsigned char threshold_L45_BRL;
	unsigned char threshold_R45_BRL;

	unsigned char threshold_L90;
	unsigned char threshold_R90;
	unsigned char threshold_L90_LOW;
	unsigned char threshold_R90_LOW;

// sensor value by position
	unsigned char ssv_L0 [256];
	unsigned char ssv_R0 [256];
	unsigned char ssv_L45[256];
	unsigned char ssv_R45[256];
	unsigned char ssv_L90[256];
	unsigned char ssv_R90[256];

// position by sensor value
	unsigned char pos_L0 [256];
	unsigned char pos_R0 [256];
	unsigned char pos_L45[256];
	unsigned char pos_R45[256];
	unsigned char pos_L90[256];
	unsigned char pos_R90[256];


void show_tbl(unsigned char *tbl)
{
	for (int i=0; i<256;i++)
	{
		send_byte(tbl[i]);
		send_char(' ');
	}
	send_char('\n');
}
void process_sampl_V()
{
	int i;

	// make tbl (input : position / output : sensor value)
		// L0
		for(i = 0 ; i < 256 ; i++)	ssv_L0[i] = 0; // clear
		linearization(ssv_L0,  sV0, 0 		 , sV0 	,sFL0[yV0] );
		linearization(ssv_L0 , sV0, sFL0[yV0], sV1	,sFL0[yV1] );
		linearization(ssv_L0 , sV1, sFL0[yV1], sV2	,sFL0[yV2] );
		linearization(ssv_L0 , sV2, sFL0[yV2], sV3	,sFL0[yV3] );
		linearization(ssv_L0 , sV3, sFL0[yV3], sV4	,sFL0[yV4] );
		linearization(ssv_L0 , sV4, sFL0[yV4], sV5	,sFL0[yV5] );
		linearization(ssv_L0 , sV5, sFL0[yV5], sV6	,sFL0[yV6] );
		linearization(ssv_L0 , sV6, sFL0[yV6], sV7	,sFL0[yV7] );
		linearization(ssv_L0 , sV7, sFL0[yV7], sV8	,sFL0[yV8] );
		linearization(ssv_L0 , sV8, sFL0[yV8], sV9	,sFL0[yV9] );
		linearization(ssv_L0 , sV9, sFL0[yV9], sV10	,sFL0[yV10] );
		linearization(ssv_L0 , sV10,sFL0[yV10],sV10	,255 );

		// R0
		for(i = 0 ; i < 256 ; i++)	ssv_R0[i] = 0; // clear
		linearization(ssv_R0, sV0	, 0    		, sV0 	, sFR0[yV0] );
		linearization(ssv_R0, sV0	, sFR0[yV0]	, sV1	, sFR0[yV1] );
		linearization(ssv_R0, sV1	, sFR0[yV1]	, sV2	, sFR0[yV2] );
		linearization(ssv_R0, sV2	, sFR0[yV2]	, sV3	, sFR0[yV3] );
		linearization(ssv_R0, sV3	, sFR0[yV3]	, sV4	, sFR0[yV4] );
		linearization(ssv_R0, sV4	, sFR0[yV4]	, sV5	, sFR0[yV5] );
		linearization(ssv_R0, sV5	, sFR0[yV5]	, sV6	, sFR0[yV6] );
		linearization(ssv_R0, sV6	, sFR0[yV6]	, sV7	, sFR0[yV7] );
		linearization(ssv_R0, sV7	, sFR0[yV7]	, sV8	, sFR0[yV8] );
		linearization(ssv_R0, sV8	, sFR0[yV8]	, sV9	, sFR0[yV9] );
		linearization(ssv_R0, sV9	, sFR0[yV9]	, sV10	, sFR0[yV10]);
		linearization(ssv_R0, sV10	, sFR0[yV10], sV10	, 255 );

	// make tbl (input : sensor value / output : position)
		// L0
		for(i = 0 ; i < 256 ; i++)	pos_L0[i] = 0; // clear
		linearization(pos_L0, 0  		 , sV0  ,sFL0[yV0]  , sV0  );
		linearization(pos_L0, sFL0[yV0]  , sV0  ,sFL0[yV1]  , sV1  );
		linearization(pos_L0, sFL0[yV1]  , sV1  ,sFL0[yV2]  , sV2  );
		linearization(pos_L0, sFL0[yV2]  , sV2  ,sFL0[yV3]  , sV3  );
		linearization(pos_L0, sFL0[yV3]  , sV3  ,sFL0[yV4]  , sV4  );
		linearization(pos_L0, sFL0[yV4]  , sV4  ,sFL0[yV5]  , sV5  );
		linearization(pos_L0, sFL0[yV5]  , sV5  ,sFL0[yV6]  , sV6  );
		linearization(pos_L0, sFL0[yV6]  , sV6  ,sFL0[yV7]  , sV7  );
		linearization(pos_L0, sFL0[yV7]  , sV7  ,sFL0[yV8]  , sV8  );
		linearization(pos_L0, sFL0[yV8]  , sV8  ,sFL0[yV9]  , sV9  );
		linearization(pos_L0, sFL0[yV9]  , sV9  ,sFL0[yV10] , sV10 );
		linearization(pos_L0, sFL0[yV10] , sV10 ,255	    , sV10 );

		// R0
		for(i = 0 ; i < 256 ; i++)	pos_R0[i] = 0; // clear
		linearization(pos_R0, 0  		 , sV0  ,sFR0[yV0]  , sV0  );
		linearization(pos_R0, sFR0[yV0]  , sV0  ,sFR0[yV1]  , sV1  );
		linearization(pos_R0, sFR0[yV1]  , sV1  ,sFR0[yV2]  , sV2  );
		linearization(pos_R0, sFR0[yV2]  , sV2  ,sFR0[yV3]  , sV3  );
		linearization(pos_R0, sFR0[yV3]  , sV3  ,sFR0[yV4]  , sV4  );
		linearization(pos_R0, sFR0[yV4]  , sV4  ,sFR0[yV5]  , sV5  );
		linearization(pos_R0, sFR0[yV5]  , sV5  ,sFR0[yV6]  , sV6  );
		linearization(pos_R0, sFR0[yV6]  , sV6  ,sFR0[yV7]  , sV7  );
		linearization(pos_R0, sFR0[yV7]  , sV7  ,sFR0[yV8]  , sV8  );
		linearization(pos_R0, sFR0[yV8]  , sV8  ,sFR0[yV9]  , sV9  );
		linearization(pos_R0, sFR0[yV9]  , sV9  ,sFR0[yV10] , sV10 );
		linearization(pos_R0, sFR0[yV10] , sV10 ,255	    , sV10 );

	// set threshold ///////////////
		threshold_L0  = (unsigned char)((int)sFL0[540]); // 540
		threshold_R0  = (unsigned char)((int)sFR0[540]); // 540

		threshold_L0_A = (int)threshold_L0 * 1 / 3;
		threshold_R0_A = (int)threshold_R0 * 1 / 3;
}
void process_sampl_H()
{
	int i;

	// make tbl (input : position / output : sensor value)
		// L45
		for(i = 0 ; i < 256 ; i++)	ssv_L45[i] = 0; // clear
		linearization(ssv_L45, 0,((sL1[SS_L45]>sC1[SS_L45])?255:0), xL3, sL3[SS_L45]);	// LeftWall~L3
		linearization(ssv_L45, xL3, sL3[SS_L45], xL2, sL2[SS_L45]);	// L3~L2
		linearization(ssv_L45, xL2, sL2[SS_L45], xL1, sL1[SS_L45]);	// L2~L1
		linearization(ssv_L45, xL1, sL1[SS_L45], xC1, sC1[SS_L45]);	// L1~C1
		linearization(ssv_L45, xC1, sC1[SS_L45], xR1, sR1[SS_L45]);	// C1~R1
		linearization(ssv_L45, xR1, sR1[SS_L45], xR2, sR2[SS_L45]);	// R1~R2
		linearization(ssv_L45, xR2, sR2[SS_L45], xR3, sR3[SS_L45]);	// R2~R3
		linearization(ssv_L45, xR3, sR3[SS_L45], 255,((sC1[SS_L45]<sR1[SS_L45])?255:0) ); // R3~RightWall
		// R45
		for(i = 0 ; i < 256 ; i++)	ssv_R45[i] = 0; // clear
		linearization(ssv_R45, 0,((sL1[SS_R45]>sC1[SS_R45])?255:0), xL3, sL3[SS_R45]);	// LeftWall~L3
		linearization(ssv_R45, xL3, sL3[SS_R45], xL2, sL2[SS_R45]);	// L3~L2
		linearization(ssv_R45, xL2, sL2[SS_R45], xL1, sL1[SS_R45]);	// L2~L1
		linearization(ssv_R45, xL1, sL1[SS_R45], xC1, sC1[SS_R45]);	// L1~C1
		linearization(ssv_R45, xC1, sC1[SS_R45], xR1, sR1[SS_R45]);	// C1~R1
		linearization(ssv_R45, xR1, sR1[SS_R45], xR2, sR2[SS_R45]);	// R1~R2
		linearization(ssv_R45, xR2, sR2[SS_R45], xR3, sR3[SS_R45]);	// R2~R3
		linearization(ssv_R45, xR3, sR3[SS_R45], 255,((sC1[SS_R45]<sR1[SS_R45])?255:0) ); // R3~RightWall
		// L90
		for(i = 0 ; i < 256 ; i++)	ssv_L90[i] = 0; // clear
		linearization(ssv_L90, 0,((sL1[SS_L90]>sC1[SS_L90])?255:0), xL3, sL3[SS_L90]);	// LeftWall~L3
		linearization(ssv_L90, xL3, sL3[SS_L90], xL2, sL2[SS_L90]);	// L3~L2
		linearization(ssv_L90, xL2, sL2[SS_L90], xL1, sL1[SS_L90]);	// L2~L1
		linearization(ssv_L90, xL1, sL1[SS_L90], xC1, sC1[SS_L90]);	// L1~C1
		linearization(ssv_L90, xC1, sC1[SS_L90], xR1, sR1[SS_L90]);	// C1~R1
		linearization(ssv_L90, xR1, sR1[SS_L90], xR2, sR2[SS_L90]);	// R1~R2
		linearization(ssv_L90, xR2, sR2[SS_L90], xR3, sR3[SS_L90]);	// R2~R3
		linearization(ssv_L90, xR3, sR3[SS_L90], 255,((sC1[SS_L90]<sR1[SS_L90])?255:0) ); // R3~RightWall
		// R90
		for(i = 0 ; i < 256 ; i++)	ssv_R90[i] = 0; // clear
		linearization(ssv_R90, 0,((sL1[SS_R90]>sC1[SS_R90])?255:0), xL3, sL3[SS_R90]);	// LeftWall~L3
		linearization(ssv_R90, xL3, sL3[SS_R90], xL2, sL2[SS_R90]);	// L3~L2
		linearization(ssv_R90, xL2, sL2[SS_R90], xL1, sL1[SS_R90]);	// L2~L1
		linearization(ssv_R90, xL1, sL1[SS_R90], xC1, sC1[SS_R90]);	// L1~C1
		linearization(ssv_R90, xC1, sC1[SS_R90], xR1, sR1[SS_R90]);	// C1~R1
		linearization(ssv_R90, xR1, sR1[SS_R90], xR2, sR2[SS_R90]);	// R1~R2
		linearization(ssv_R90, xR2, sR2[SS_R90], xR3, sR3[SS_R90]);	// R2~R3
		linearization(ssv_R90, xR3, sR3[SS_R90], 255,((sC1[SS_R90]<sR1[SS_R90])?255:0) ); // R3~RightWall

	// make tbl (input : sensor value / output : position)
		// L45
		for(i = 0 ; i < 256 ; i++)	pos_L45[i] = 0; // clear
		linearization(pos_L45,sL3[SS_L45],xL3, ((sL1[SS_L45]>sC1[SS_L45])?255:0),0);	// LeftWall~L3
		linearization(pos_L45, sL2[SS_L45], xL2, sL3[SS_L45], xL3);	// L3~L2
		linearization(pos_L45, sL1[SS_L45], xL1, sL2[SS_L45], xL2);	// L2~L1
		linearization(pos_L45, sC1[SS_L45], xC1, sL1[SS_L45], xL1);	// L1~C1
		linearization(pos_L45, sR1[SS_L45], xR1, sC1[SS_L45], xC1);	// C1~R1
		linearization(pos_L45, sR2[SS_L45], xR2, sR1[SS_L45], xR1);	// R1~R2
		linearization(pos_L45, sR3[SS_L45], xR3, sR2[SS_L45], xR2);	// R2~R3
		linearization(pos_L45, ((sC1[SS_L45]<sR1[SS_L45])?255:0),255, sR3[SS_L45], xR3); // R3~RightWall
		// R45
		for(i = 0 ; i < 256 ; i++)	pos_R45[i] = 0; // clear
		linearization(pos_R45, ((sL1[SS_R45]>sC1[SS_R45])?255:0),0,sL3[SS_R45],xL3);	// LeftWall~L3
		linearization(pos_R45, sL3[SS_R45], xL3, sL2[SS_R45], xL2);	// L3~L2
		linearization(pos_R45, sL2[SS_R45], xL2, sL1[SS_R45], xL1);	// L2~L1
		linearization(pos_R45, sL1[SS_R45], xL1, sC1[SS_R45], xC1);	// L1~C1
		linearization(pos_R45, sC1[SS_R45], xC1, sR1[SS_R45], xR1);	// C1~R1
		linearization(pos_R45, sR1[SS_R45], xR1, sR2[SS_R45], xR2);	// R1~R2
		linearization(pos_R45, sR2[SS_R45], xR2, sR3[SS_R45], xR3);	// R2~R3
		linearization(pos_R45, sR3[SS_R45], xR3, ((sC1[SS_R45]<sR1[SS_R45])?255:0),255); // R3~RightWall
		// L90
		for(i = 0 ; i < 256 ; i++)	pos_L90[i] = 0; // clear
		linearization(pos_L90,sL3[SS_L90],xL3, ((sL1[SS_L90]>sC1[SS_L90])?255:0),0);	// LeftWall~L3
		linearization(pos_L90, sL2[SS_L90], xL2, sL3[SS_L90], xL3);	// L3~L2
		linearization(pos_L90, sL1[SS_L90], xL1, sL2[SS_L90], xL2);	// L2~L1
		linearization(pos_L90, sC1[SS_L90], xC1, sL1[SS_L90], xL1);	// L1~C1
		linearization(pos_L90, sR1[SS_L90], xR1, sC1[SS_L90], xC1);	// C1~R1
		linearization(pos_L90, sR2[SS_L90], xR2, sR1[SS_L90], xR1);	// R1~R2
		linearization(pos_L90, sR3[SS_L90], xR3, sR2[SS_L90], xR2);	// R2~R3
		linearization(pos_L90, ((sC1[SS_L90]<sR1[SS_L90])?255:0),255, sR3[SS_L90], xR3); // R3~RightWall
		// R90
		for(i = 0 ; i < 256 ; i++)	pos_R90[i] = 0; // clear
		linearization(pos_R90, ((sL1[SS_R90]>sC1[SS_R90])?255:0),0,sL3[SS_R90],xL3);	// LeftWall~L3
		linearization(pos_R90, sL3[SS_R90], xL3, sL2[SS_R90], xL2);	// L3~L2
		linearization(pos_R90, sL2[SS_R90], xL2, sL1[SS_R90], xL1);	// L2~L1
		linearization(pos_R90, sL1[SS_R90], xL1, sC1[SS_R90], xC1);	// L1~C1
		linearization(pos_R90, sC1[SS_R90], xC1, sR1[SS_R90], xR1);	// C1~R1
		linearization(pos_R90, sR1[SS_R90], xR1, sR2[SS_R90], xR2);	// R1~R2
		linearization(pos_R90, sR2[SS_R90], xR2, sR3[SS_R90], xR3);	// R2~R3
		linearization(pos_R90, sR3[SS_R90], xR3, ((sC1[SS_R90]<sR1[SS_R90])?255:0),255); // R3~RightWall

	// set threshold ///////////////

		threshold_L45 	= (unsigned char)((int)sR3[SS_L45]	* 2 / 3); // 2/3
		threshold_R45 	= (unsigned char)((int)sL3[SS_R45]  * 2 / 3); // 2/3
		threshold_L45_LOW=(unsigned char)((int)sR3[SS_L45]	* 1 / 2); // 1/2
		threshold_R45_LOW=(unsigned char)((int)sL3[SS_R45]  * 1 / 2); // 1/2
/*
		threshold_L45_D	= (unsigned char)((int)sR1[SS_L45]  * 2 / 3); // 2/3
		threshold_R45_D	= (unsigned char)((int)sL1[SS_R45]  * 2 / 3); // 2/3
		threshold_L45_DL= (unsigned char)((int)sR1[SS_L45]  * 1 / 2); // 1/2
		threshold_R45_DL= (unsigned char)((int)sL1[SS_R45]  * 1 / 2); // 1/2
*/
		threshold_L45_D	= (unsigned char)((int)sC1[SS_L45]  * 2 / 3); // 2/3
		threshold_R45_D	= (unsigned char)((int)sC1[SS_R45]  * 2 / 3); // 2/3
		threshold_L45_DL= (unsigned char)((int)sC1[SS_L45]  * 1 / 2); // 1/2
		threshold_R45_DL= (unsigned char)((int)sC1[SS_R45]  * 1 / 2); // 1/2


		threshold_L45_BR= (unsigned char)((int)sR3[SS_L45]	* 2 / 3); // 1/2
		threshold_R45_BR= (unsigned char)((int)sL3[SS_R45]  * 2 / 3); // 1/2
		threshold_L45_BRL=(unsigned char)((int)sR3[SS_L45]	* 1 / 2); // 1/3
		threshold_R45_BRL=(unsigned char)((int)sL3[SS_R45]  * 1 / 2); // 1/3

		threshold_L90 	= (unsigned char)((int)sR3[SS_L90]	* 2 / 3); // 2/3
		threshold_R90 	= (unsigned char)((int)sL3[SS_R90]  * 2 / 3); // 2/3
		threshold_L90_LOW=(unsigned char)((int)sR3[SS_L90]	* 1 / 3); // 1/2
		threshold_R90_LOW=(unsigned char)((int)sL3[SS_R90]  * 1 / 3); // 1/2
}

void sampl_value(unsigned char *sampl_array)
{
	int i;

	for ( i=0; i < 6; i++ ) // SS_L0 SS_R0 SS_L45 SS_R45 SS_L90 SS_R90
		sampl_array[i] = ss_value[i];
}

void show_sampl_value()
{
	int i;

	send_string("\n");
	send_string("         SS_L0   SS_R0  SS_L45  SS_R45  SS_L90  SS_R90 \n");
	send_string("-------------------------------------------------------\n");
	send_string(" sL3      ");
		for(i=0;i<6;i++)	{send_byte(sL3[i]);send_string("     ");} send_string("\n");
	send_string(" sL2	  ");
		for(i=0;i<6;i++)	{send_byte(sL2[i]);send_string("     ");} send_string("\n");
	send_string(" sL1	  ");
		for(i=0;i<6;i++)	{send_byte(sL1[i]);send_string("     ");} send_string("\n");
	send_string(" sC1	  ");
		for(i=0;i<6;i++)	{send_byte(sC1[i]);send_string("     ");} send_string("\n");
	send_string(" sR1	  ");
		for(i=0;i<6;i++)	{send_byte(sR1[i]);send_string("     ");} send_string("\n");
	send_string(" sR2	  ");
		for(i=0;i<6;i++)	{send_byte(sR2[i]);send_string("     ");} send_string("\n");
	send_string(" sR3	  ");
		for(i=0;i<6;i++)	{send_byte(sR3[i]);send_string("     ");} send_string("\n");
	send_string(" L0 : ");send_byte(threshold_L0);
	send_string(" 		R0 : ");send_byte(threshold_R0);send_char('\n');
	send_string(" L0_A : ");send_byte(threshold_L0_A);
	send_string(" 		R0_A : ");send_byte(threshold_R0_A);send_char('\n');
	send_string(" L45: ");send_byte(threshold_L45);
	send_string(" 		R45: ");send_byte(threshold_R45);send_char('\n');
	send_string(" L45_L: ");send_byte(threshold_L45_LOW);
	send_string(" 		R45_L: ");send_byte(threshold_R45_LOW);send_char('\n');
	send_string(" L45_D: ");send_byte(threshold_L45_D);
	send_string(" 		R45_D: ");send_byte(threshold_R45_D);send_char('\n');
	send_string(" L45_DL: ");send_byte(threshold_L45_DL);
	send_string(" 		R45_DL: ");send_byte(threshold_R45_DL);send_char('\n');
	send_string(" L45_BR: ");send_byte(threshold_L45_BR);
	send_string(" 		R45_BR: ");send_byte(threshold_R45_BR);send_char('\n');
	send_string(" L45_BRL: ");send_byte(threshold_L45_BRL);
	send_string(" 		R45_BRL: ");send_byte(threshold_R45_BRL);send_char('\n');
	send_string(" L90: ");send_byte(threshold_L90);
	send_string(" 		R90: ");send_byte(threshold_R90);send_char('\n');
	send_string(" L90_L: ");send_byte(threshold_L90_LOW);
	send_string(" 		R90_L: ");send_byte(threshold_R90_LOW);send_char('\n');

	/*
	send_string("\n> hit me to view vertical sampling values\n");
	wait_key();
	for(i=0;i<SAMPL_VSTEP;i++)
	{
		send_string("L / ");send_word(i);send_string(" : ");send_byte(sFL0[i]);
		send_string("    ");
		send_string("R / ");send_word(i);send_string(" : ");send_byte(sFR0[i]);
		send_string("\n");
		sys_delay(1);
	}

	send_string("\n> hit me to view pos by ssv\n");
	wait_key();
	send_string("> pos_L0 :  ");show_tbl(pos_L0);
	wait_key();
	send_string("> pos_R0 :  ");show_tbl(pos_R0);
	wait_key();
	send_string("> pos_L45 : ");show_tbl(pos_L45);
	wait_key();
	send_string("> pos_R45 : ");show_tbl(pos_R45);
	wait_key();
	send_string("> pos_L90 : ");show_tbl(pos_L90);
	wait_key();
	send_string("> pos_R90 : ");show_tbl(pos_R90);

	send_string("\n> hit me to view ssv by pos\n");
	wait_key();
	send_string("> ssv_L0 :  ");show_tbl(ssv_L0);
	wait_key();
	send_string("> ssv_R0 :  ");show_tbl(ssv_R0);
	wait_key();
	send_string("> ssv_L45 : ");show_tbl(ssv_L45);
	wait_key();
	send_string("> ssv_R45 : ");show_tbl(ssv_R45);
	wait_key();
	send_string("> ssv_L90 : ");show_tbl(ssv_L90);
	wait_key();
	send_string("> ssv_R90 : ");show_tbl(ssv_R90);
	*/
}

void ss_sampl()
{
	while( 1 )	{
		// Sampling	Vertical		//////////////////////////////////////
		led_off(PIO_LED_ALL);
		led_on (PIO_LED_0|PIO_LED_1|PIO_LED_5|PIO_LED_4);
		if ( L_KEY == read_key() )	{
			Sound_Select();
			ss_sampl_V(); process_sampl_V();
			save_sampl_value();
		}	else Sound_Beep();
		// Sampling	Horizonal		//////////////////////////////////////
		led_off(PIO_LED_ALL);
		led_on (PIO_LED_2|PIO_LED_6|PIO_LED_3);
		if ( L_KEY == read_key() )	{
			Sound_Select();
			ss_sampl_H(); process_sampl_V();
			save_sampl_value();
		}	else Sound_Beep();

	}
	END_SEL:
}
void ss_sampl_V()
{
	led_off(PIO_LED_ALL);
	led_on (PIO_LED_0 | PIO_LED_1 | PIO_LED_5 | PIO_LED_4);

	wait_key();		torque_on();	wait_key();
	led_count_down( 5, 1000 );

	disable_adj();

	spd_ptr	 = 0;
	spd_diff = 0;
	reverse_LR();

	ss_on();	sys_delay(300);

	unsigned int ref_L;
	unsigned int ref_R;

	ref_L = ss_value[SS_L0];
	ref_R = ss_value[SS_R0];

	int i=0;

	reset_spd_ptr();
	spd_diff = 1;
	motor_start();

	while(i < SAMPL_VSTEP)
	{
		#define SAM_SPD		20 //25
		if ( spd_ptr_L >= SAM_SPD ) 	{
			spd_diff = 0;
			equal_spd_ptr();
		}

		reset_steps();
		while( steps == 0 );

		ref_L = ss_value[SS_L0];
		ref_R = ss_value[SS_R0];

		sFL0[i] = (unsigned char)ref_L;
		sFR0[i] = (unsigned char)ref_R;
		i++;
	}
	ss_off();

	spd_diff = -1;
	while (spd_ptr_L > 0);
	reset_spd_ptr();

	motor_stop();
	sys_delay(200);

	reverse_LR();

	torque_off();
}

unsigned int search_V_step(unsigned char *samp,unsigned char ssv,unsigned int iMAX)
{
	unsigned int i;

	i=0;
	while( i < iMAX )
	{
		if(samp[i] <= ssv) break;
		i++;
	}

	return i;
}

void ss_sampl_H()
{
	// Choose sampling method.
		//#define SAMP_METHOD_SWING
		#define SAMP_METHOD_SWING_S

	// SWING mm
	#if defined(SAMP_METHOD_SWING)

		#define toR2	24+1	//20
		#define toR3	12+2	//10
		#define toR1	23		//15
		#define toL1	23-2	//20
		#define toL3	23		//20
		#define toL2	12+3	//15
		#define toC1	24+3	//20

	#elif defined(SAMP_METHOD_SWING_S)

		#define toR2	40
		#define toR3	20
		#define toR1	40
		#define toL1	40
		#define toL3	40
		#define toL2	20
		#define toC1	40

	#else
	#error Choose Sampling Method
	#endif

	led_off(PIO_LED_ALL);
	led_on (PIO_LED_2 | PIO_LED_6 | PIO_LED_3);
//	sys_delay(1000);

	ss_on();
	// show LEDs to find the center of block
	int ss_diff;
	while( !( get_key_state()==(PORT_CANCEL) || get_key_state()==(PORT_SELECT) ) )
	{
		ss_diff = ((int)ss_value[SS_L45]) - ((int)ss_value[SS_R45]);

		led_off(PIO_LED_ALL);
		if 		( ss_diff > 10) 	led_on(PIO_LED_3);
		else if	( ss_diff > 5)		led_on(PIO_LED_4 | PIO_LED_1);
		else if ( ss_diff < -10)    led_on(PIO_LED_2);
		else if ( ss_diff < -5 ) 	led_on(PIO_LED_5 | PIO_LED_0);
		else						led_on(PIO_LED_6);
	}

//	wait_key();

	torque_on();
	wait_key();

//	ss_on();
	led_count_down( 5, 1000 );

	// debug
	//#define DEBUG_SAMPL

	disable_adj();
	reset_spd_ptr();

	// C1
	led_off( PIO_LED_0 |PIO_LED_1|PIO_LED_2|PIO_LED_3|PIO_LED_4|PIO_LED_5|PIO_LED_6);
	led_on ( PIO_LED_6 );
	sys_delay(100);	sampl_value( sC1 );
	motor_start();

	#ifdef	DEBUG_SAMPL
	motor_stop();	wait_key();	motor_start();
	#endif

	// R2
	led_off( PIO_LED_0|PIO_LED_1|PIO_LED_2|PIO_LED_3|PIO_LED_4|PIO_LED_5|PIO_LED_6);
	led_on ( PIO_LED_0|PIO_LED_5|PIO_LED_2 );

	#if defined(SAMP_METHOD_SWING)
	  swing(toR2);
	#elif defined(SAMP_METHOD_SWING_S)
	  swing_S(toR2);
	#else
	#error Choose Sampling Method
	#endif
	sampl_value( sR2 );

	#ifdef	DEBUG_SAMPL
	motor_stop();	wait_key();	motor_start();
	#endif

	// R3
	led_off( PIO_LED_0|PIO_LED_1|PIO_LED_2|PIO_LED_3|PIO_LED_4|PIO_LED_5|PIO_LED_6);
	led_on ( PIO_LED_2 );

	#if defined(SAMP_METHOD_SWING)
	  swing(toR3);
	#elif defined(SAMP_METHOD_SWING_S)
	  swing_S(toR3);
	#else
	#error Choose Sampling Method
	#endif
	sampl_value( sR3 );

	#ifdef	DEBUG_SAMPL
	motor_stop();	wait_key();	motor_start();
	#endif

	// R1
	led_off( PIO_LED_0 |PIO_LED_1|PIO_LED_2|PIO_LED_3|PIO_LED_4|PIO_LED_5|PIO_LED_6);
	led_on ( PIO_LED_0 | PIO_LED_5);

	#if defined(SAMP_METHOD_SWING)
	  swing(-toR1);
	#elif defined(SAMP_METHOD_SWING_S)
	  swing_S(-toR1);
	#else
	#error Choose Sampling Method
	#endif
	sampl_value( sR1 );

	#ifdef	DEBUG_SAMPL
	motor_stop();	wait_key();	motor_start();
	#endif

	// L1
	led_off( PIO_LED_0 |PIO_LED_1|PIO_LED_2|PIO_LED_3|PIO_LED_4|PIO_LED_5|PIO_LED_6);
	led_on ( PIO_LED_1 | PIO_LED_4);

	#if defined(SAMP_METHOD_SWING)
	  swing(-toL1);
	#elif defined(SAMP_METHOD_SWING_S)
	  swing_S(-toL1);
	#else
	#error Choose Sampling Method
	#endif
	sampl_value( sL1 );

	#ifdef	DEBUG_SAMPL
	motor_stop();	wait_key();	motor_start();
	#endif

	// L3
	led_off( PIO_LED_0 |PIO_LED_1|PIO_LED_2|PIO_LED_3|PIO_LED_4|PIO_LED_5|PIO_LED_6);
	led_on ( PIO_LED_3);

	#if defined(SAMP_METHOD_SWING)
	  swing(-toL3);
	#elif defined(SAMP_METHOD_SWING_S)
	  swing_S(-toL3);
	#else
	#error Choose Sampling Method
	#endif
	sampl_value( sL3 );

	#ifdef	DEBUG_SAMPL
	motor_stop();	wait_key();	motor_start();
	#endif

	// L2
	led_off( PIO_LED_0 |PIO_LED_1|PIO_LED_2|PIO_LED_3|PIO_LED_4|PIO_LED_5|PIO_LED_6);
	led_on ( PIO_LED_1|PIO_LED_3|PIO_LED_4 );

	#if defined(SAMP_METHOD_SWING)
	  swing(toL2);
	#elif defined(SAMP_METHOD_SWING_S)
	  swing_S(toL2);
	#else
	#error Choose Sampling Method
	#endif
	sampl_value( sL2 );

	#ifdef	DEBUG_SAMPL
	motor_stop();	wait_key();	motor_start();
	#endif

	// C1
	led_off( PIO_LED_0 |PIO_LED_1|PIO_LED_2|PIO_LED_3|PIO_LED_4|PIO_LED_5|PIO_LED_6);
	led_on ( PIO_LED_6 );

	#if defined(SAMP_METHOD_SWING)
	  swing(toC1);
	#elif defined(SAMP_METHOD_SWING_S)
	  swing_S(toC1);
	#else
	#error Choose Sampling Method
	#endif

	#ifdef	DEBUG_SAMPL
	motor_stop();	wait_key();	motor_start();
	#endif

	motor_stop();
	ss_off();

	torque_off();
}

void linearization(unsigned char *tbl, int x1, int y1, int x2, int y2)
{
	int x, y;

	tbl[x1] = (unsigned char)y1;
	tbl[x2] = (unsigned char)y2;

	if ( x1 == x2 )		{
		tbl[ x1 ] = (unsigned char)y1;
		return;
	}
	if ( x1 < x2 )		{
		for (x = x1+1 ; x < x2 ; x++ )		{
			y = ( y2 - y1 ) * ( x - x1 ) / ( x2 - x1 ) + y1;
			tbl[ x ] = (unsigned char)y;
		}
	}
	if ( x1 > x2 )		{
		for (x = x2+1 ; x < x1 ; x++ )		{
			y = ( y2 - y1 ) * ( x - x1 ) / ( x2 - x1 ) + y1;
			tbl[ x ] = (unsigned char)y;
		}
	}
}

