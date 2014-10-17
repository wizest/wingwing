#ifndef __ADJ_POS_H
#   define __ADJ_POS_H



	extern void adj_pos();

	extern void adj_pos_V();
	extern void adj_pos_H();
	extern void adj_pos_HS();

//	#define STOP_METHOD_FRONTWALL
	#define STOP_METHOD_SIDEWALL
	extern void adj_pos_stop();		// run_sBX(), run_aFHF()

#endif
