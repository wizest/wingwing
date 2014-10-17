#ifndef __SWING_H
#   define __SWING_H

	#define SWING_iSPD	40
	#define SWING_aSTP	20


	extern void swing(int mm);
	extern void swing_S(int mm);

	extern void swing_left(int iSpd,int ioS,int thS);
	extern void swing_right(int iSpd,int ioS,int thS);

	extern unsigned int  swing_H_tbl[];
	extern unsigned int  swing_V_tbl[];
	extern unsigned int	 swing_S_tbl[];

#endif
