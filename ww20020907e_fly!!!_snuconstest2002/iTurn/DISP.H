#ifndef __display
#define __display

#define mm2pixel(mm)        double( (BLK_DIST*double((mm))) / double(180.)  )
#define step2pixel(step)	mm2pixel((double( double((step))*ONESTEP)))

#define EDGE_LINE_45 	step2pixel(225)				// red
#define EDGE_LINE_90  	step2pixel(367)				// brown
#define EDGE_LINE_D45	(step2pixel(120)*1.414213) 	// magenta
#define cLINE           step2pixel(380) 			// blue

extern double BLK_DIST;
extern double BLK_X ;
extern double BLK_Y ;
extern double XL ;
extern double XR ;
extern double YL ;
extern double YR ;

extern double ONESTEP; 	//mm
extern double TURNANGLE; //rad
extern double COSTURN;
extern double SINTURN;

extern int L_COLOR;
extern int R_COLOR;
extern int L_DIREC;
extern int R_DIREC;

extern double xl,yl,xl_old,yl_old;
extern double xr,yr,xr_old,yr_old;

extern double bx  , by ; // base x,y

extern void init_scr();
extern void init_scr_size();
extern void enlarge_scr();
extern void delarge_scr();

extern void exchange_color();
extern void reverse_L();
extern void reverse_R();
extern void reverse_LR();

extern void open_screen();
extern void close_screen();

extern void step_left(int f_or_b);
extern void step_right(int f_or_b);

extern void draw_trace();

extern void draw_maze();
extern void show_info();

extern void ks_outtextxy(int x,int y, const char *text);

#endif