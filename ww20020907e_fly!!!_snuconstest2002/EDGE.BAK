#ifndef		__EDGE_H
	#define	__EDGE_H

#define EDGESTEP_90			EDGESTEP_90_FAST
#define EDGESTEP_90_SLOW    300						// steps
//#define EDGESTEP_90_FAST	(EDGESTEP_90_SLOW+54)	// steps
#define EDGESTEP_90_FAST	(EDGESTEP_90_SLOW+57)	// steps
	// this value needs to adjust according to speed!!

#define EDGE_UNKNOWN	0
#define EDGE_DN			1
#define EDGE_UP			2

#define WAIT_EDGE_L		0
#define WAIT_EDGE_R		1
#define WAIT_EDGE_LR	2

#define SS_LOW		0
#define SS_HIGH		1


extern unsigned int level_C_L45,level_P_L45; // Current & Previous level
extern unsigned int level_C_L90,level_P_L90; // Current & Previous level
extern unsigned int level_C_R45,level_P_R45; // Current & Previous level
extern unsigned int level_C_R90,level_P_R90; // Current & Previous level

extern unsigned int edge_info_L45,edge_info_R45;
extern unsigned int edge_info_L90,edge_info_R90;

extern void refresh_level();
extern void refresh_level_D();	// for diagonal
extern void refresh_edge();
extern void scan_level();
extern void scan_level_D();		// for diagonal
extern void scan_edge();

extern void wait_edge(  void (*scan_level_P)(),
						int  (*adj_P)(),
						int  scan_dir,
						unsigned int& edge_L,
						unsigned int& edge_R
					 );
#endif
