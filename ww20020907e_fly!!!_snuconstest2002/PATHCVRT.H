#ifndef __PATHCVRT_H
#   define __PATHCVRT_H

	extern unsigned char cvrt_mode;
		#define	CVRT_SCAN_O 	0
		#define CVRT_SCAN_D		1
		#define CVRT_RUSH_D		2

	extern void path_cvrt();

	extern void path_cvrt_scan_O();		// Orthogonal scan
	extern void path_cvrt_scan_D();		// Diagonal scan
	extern void path_cvrt_rush_D();		// Diagonal rush

	extern void path_cvrt_scan_C(int t_fptr,int t_rptr);	// Common scan
	extern void path_cvrt_rush_C(int t_fptr,int t_rptr);	// Common rush

#endif