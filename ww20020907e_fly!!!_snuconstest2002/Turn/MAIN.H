#ifndef __main
#define __main

#define ESC 	1
#define SHIFT	42
#define UP 		72
#define DOWN 	80
#define RIGHT 	77
#define LEFT 	75

#define KEY_1	2
#define KEY_2	3
#define KEY_3	4
#define KEY_4	5
#define KEY_5	6
#define KEY_6	7
#define KEY_7	8
#define KEY_8	9
#define KEY_9	10
#define KEY_0	11
#define KEY__	12
#define KEY___	13


#define KEY_Q	16
#define KEY_W	17
#define KEY_E	18
#define KEY_R	19

#define KEY_U	22
#define KEY_I	23
#define KEY_O	24
#define KEY_P   25

#define KEY_A	30
#define KEY_S	31
#define KEY_D	32
#define KEY_F	33
#define KEY_L	38
#define KEY_Z 	44
#define KEY_X 	45
#define KEY_C 	46
#define KEY_V 	47
#define KEY_M	50
#define KEY_L2	51
#define KEY_R2	52

#define FORWARD 	1
#define BACKWARD   -1

#define ANGLE0_9	0.01570796327 // M_PI*0.9/180

#define WIDTH	64.65		   //mm !!
#define RADIUS  26.403585025622//mm !!

#define STEP_LR 0
#define STEP_L	1
#define STEP_R	2

extern int iSpd ,ioS ,thS;

extern unsigned char key[128];

extern int l_steps;
extern int r_steps;

extern unsigned int l_cnt;
extern unsigned int r_cnt;

extern int spd_ptr_L;
extern int spd_ptr_R;
extern int spd_diff_L;
extern int spd_diff_R;

extern char spd_dptr_L;
extern char spd_dptr_R;


extern void interrupt (*old_interrupt)(...);
extern void interrupt new_key_interrupt(...);

extern void stepping();
extern void init_values();

extern void turn_left(int init_spd_ptr, int io_steps,int th_steps);
extern void turn_right(int init_spd_ptr, int io_steps,int th_steps);

#endif
