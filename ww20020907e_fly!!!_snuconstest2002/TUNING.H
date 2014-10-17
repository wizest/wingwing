#ifndef __TUNING_H
#define __TUNING_H

	// Scan RUNs
	#define	tune_scan_set()	   set_run_scan_normal()

	// Inter RUNs
	#define tune_iscan_set()   set_run_iscan_normal()

	// Rush RUNs
	//#define tune_rush_set()	   set_run_rush_slow()
	//#define tune_rush_set()	   set_run_rush_normal()
	//#define tune_rush_set()	   set_run_rush_fast()
	#define tune_rush_set()	   set_run_rush_very_fast()

	extern void tune();
	extern void tune_rush();
	extern void 	tune_rush_O();	// Orthogonal
	extern void 	tune_rush_D();	// Diagonal
	extern void 	tune_rush_S();	// Start
	extern void 	tune_rush_C();	// Continuously Tune
	extern void 	tune_rush_Oc();	// Continuously Tune / Orthogonal
	extern void 	tune_rush_Dc();	// Continuously Tune / Diagonal
	extern void 	tune_rush_body(char D_O,char tDIR,void (*run_type)());
	extern void 	tune_rush_body_C(void (*run_type)());
	extern void tune_scan();
	extern void tune_inter_SR();	// Scan -> Rush
	extern void tune_inter_RS();	// Rush -> Scan
	extern void tune_turn_180();
	extern void tune_edge();
	extern void tune_oneblk();
	extern void tune_conti_turn();

#endif
