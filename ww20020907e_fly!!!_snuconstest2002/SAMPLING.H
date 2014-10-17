#ifndef __AM188ES_H
#   include <AM188ES.H>
#endif

#ifndef __SAMPLING_H
#	define __SAMPLING_H

// position 0~255
	#define xL3		43
	#define xL2		71
	#define xL1 	99
	#define xC1		127
	#define xR1		155
	#define xR2		183
	#define xR3		211

	extern void show_sampl_value();

	extern void linearization(unsigned char *tbl, int x1, int y1, int x2, int y2);

	extern void process_sampl_V();
	extern void process_sampl_H();

	extern void ss_sampl();
	extern void ss_sampl_H();
	extern void ss_sampl_V();

	extern unsigned int search_V_step(unsigned char *samp,unsigned char ssv,unsigned int iMAX);

	void sampl_value(unsigned char *sampl_array);

	extern unsigned char threshold_L0;
	extern unsigned char threshold_R0;
	extern unsigned char threshold_L0_A;
	extern unsigned char threshold_R0_A;
	extern unsigned char threshold_L45;
	extern unsigned char threshold_R45;
	extern unsigned char threshold_L45_LOW;
	extern unsigned char threshold_R45_LOW;
	extern unsigned char threshold_L45_D;
	extern unsigned char threshold_R45_D;
	extern unsigned char threshold_L45_DL;
	extern unsigned char threshold_R45_DL;
	extern unsigned char threshold_L45_BR;
	extern unsigned char threshold_R45_BR;
	extern unsigned char threshold_L45_BRL;
	extern unsigned char threshold_R45_BRL;
	extern unsigned char threshold_L90;
	extern unsigned char threshold_R90;
	extern unsigned char threshold_L90_LOW;
	extern unsigned char threshold_R90_LOW;


	#define SAMPL_VSTEP		550 // steps  DO NOT CHANGE!! FIXED!!
	#define step2pos(x)		(unsigned char)((SAMPL_VSTEP - (unsigned int)(x)) * 255 / SAMPL_VSTEP)

	#define yV10 	(0)
	#define yV9		(SAMPL_VSTEP* 1/10 -1)
	#define yV8		(SAMPL_VSTEP* 2/10 -1)
	#define yV7		(SAMPL_VSTEP* 3/10 -1)
	#define yV6		(SAMPL_VSTEP* 4/10 -1)
	#define yV5		(SAMPL_VSTEP* 5/10 -1)
	#define yV4		(SAMPL_VSTEP* 6/10 -1)
	#define yV3		(SAMPL_VSTEP* 7/10 -1)
	#define yV2		(SAMPL_VSTEP* 8/10 -1)
	#define yV1		(SAMPL_VSTEP* 9/10 -1)
	#define yV0		(SAMPL_VSTEP*10/10 -1)

	#define sV0		(0)
	#define sV1		(255 * 1/10)
	#define sV2		(255 * 2/10)
	#define sV3		(255 * 3/10)
	#define sV4		(255 * 4/10)
	#define sV5		(255 * 5/10)
	#define sV6		(255 * 6/10)
	#define sV7		(255 * 7/10)
	#define sV8		(255 * 8/10)
	#define sV9		(255 * 9/10)
	#define sV10	(255 *10/10)

	extern unsigned char sL3[6],sL2[6],sL1[6],sC1[6],sR1[6],sR2[6],sR3[6];

	extern unsigned char sFL0[SAMPL_VSTEP],sFR0[SAMPL_VSTEP];

	extern unsigned char ssv_L0 [256];
	extern unsigned char ssv_R0 [256];
	extern unsigned char ssv_L45[256];
	extern unsigned char ssv_R45[256];
	extern unsigned char ssv_L90[256];
	extern unsigned char ssv_R90[256];

	extern unsigned char pos_L0 [256];
	extern unsigned char pos_R0 [256];
	extern unsigned char pos_L45[256];
	extern unsigned char pos_R45[256];
	extern unsigned char pos_L90[256];
	extern unsigned char pos_R90[256];

#endif