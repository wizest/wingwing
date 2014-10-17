#ifndef __DRIVE_H
#   define __DRIVE_H

	#define	ONEBLK		(434)
	#define ONEBLK_D	(307)
	#define HALFBLK		(ONEBLK / 2)
	#define HALFBLK_D	(153)
	#define TURNSTP		(246 +4 +1)
	#define tACCLSTP	(72)


	extern	int goal_pos;

	extern void drive();

	extern void drive_one();		// First Drive - rush mode with clear walls
	extern void drive_one_R();		// First Drive - rush mode
	extern void drive_one_S();		// First Drive - scan mode
	extern void drive_two(); 		// Second Drive - rush mode

	// Driving Body
	extern void drive_scan_R();		// Rush mode (diagonal)
	extern void drive_scan_S();		// Scan mode
	extern void drive_rush();

#endif