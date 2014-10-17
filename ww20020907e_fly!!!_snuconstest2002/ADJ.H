#ifndef __ADJ_H
#   define __ADJ_H

	#define ADJ_ON	1
	#define	ADJ_OFF	0
	extern unsigned char 	adj_switch;
	extern unsigned int 	adj_mul_L		,adj_mul_R;

	// adj_Xs return these
	#define ADJ_FAILURE		0
	#define ADJ_SUCCESS		1

	// Branch adjusting
	#define ADJ_LEVEL_LOW		0
	#define	ADJ_LEVEL_HIGH		1
	#define ADJ_LEVEL_UNKNOWN	2

	#define ADJ_EDGE_UNKNOWN	0	// 0000
	#define ADJ_EDGE_DN_R		1	// 0001
	#define ADJ_EDGE_DN_L		2	// 0010
	#define ADJ_EDGE_DN			3	// 0011
	#define ADJ_EDGE_UP_R		4	// 0100
	#define ADJ_EDGE_UP_L		8	// 1000
	#define ADJ_EDGE_UP		   12	// 1100

	extern void refresh_adj_O();	// for Branch
	extern void reset_adj_mul();
	extern void enable_adj();
	extern void disable_adj();
	extern void init_adj();

	extern int adj_O();	// Orthogonal
	extern int adj_D();	// Diagonal
	extern int adj_DF0();
	extern int adj_DF0a(); // adjacency if front wall exists !!

#endif
