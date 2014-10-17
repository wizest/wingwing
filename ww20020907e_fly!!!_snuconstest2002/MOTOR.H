#ifndef __AM188ES_H
#   include <AM188ES.H>
#endif

#ifndef __motor_h
#define __motor_h

// ONLY USE LSB 8bit!!!!!!! for custom ASM code
#define  pio_L_A   (0x0010) //   A //0000 0000 0001 0000
#define  pio_L_B   (0x0040) //   B //0000 0000 0100 0000
#define  pio_L_C   (0x0020) //  /A //0000 0000 0010 0000
#define  pio_L_D   (0x0080) //  /B //0000 0000 1000 0000
#define	 pio_L 	   (0x00F0) //	( pio_L_A | pio_L_B | pio_L_C | pio_L_D )
//#define  pio_L_OFF (0xFF0F) //	(~pio_L)

// ONLY USE LSB 8bit!!!!!!! for custom ASM code
#define  pio_R_A   (0x0001)//   A  0000 0000 0000 0001
#define  pio_R_B   (0x0004)//   B  0000 0000 0000 0100
#define  pio_R_C   (0x0002)//  /A  0000 0000 0000 0010
#define  pio_R_D   (0x0008)//  /B  0000 0000 0000 1000
#define	 pio_R 	   (0x000F)//	( pio_R_A | pio_R_B | pio_R_C | pio_R_D )
//#define  pio_R_OFF (0xFFF0)//	(~pio_R)

#define	DISABLE_RUN_SOUND

#define		MOTOR_TIMER_L		T1CMPA
#define		motor_start_L()		Start_Timer1()
#define 	motor_stop_L()  	Stop_Timer1()

#define		MOTOR_TIMER_R		T2CMPA
#define		motor_start_R() 	Start_Timer2()
#define     motor_stop_R()  	Stop_Timer2()

#define		MOTOR_TIMER			T1CMPA
#define		motor_tmr_start()	Start_Timer1()
#define		motor_tmr_stop()	Stop_Timer1()

#define 	MOTOR_SUB_TIMER			T2CMPA
#define		motor_sub_tmr_start()   outport(T2CON,0xC000)	// 1100 0000 0000 0000
#define		motor_sub_tmr_stop()	outport(T2CON,0x4000)	// 0100 0000 0000 0000
#define		get_motor_sub_tmr_count()	inport(T2CNT)

// speed table
extern unsigned int    *speed;
extern unsigned int  	fspeed[];
extern unsigned int  	tspeed[];

extern  volatile int 	spd_ptr_L	,spd_ptr_R;
#define spd_ptr			spd_ptr_L = spd_ptr_R

extern  volatile char 	spd_diff_L	,spd_diff_R;
#define spd_diff	 	spd_diff_L = spd_diff_R

extern  volatile int 	steps_L		,steps_R;
#define steps			steps_L

extern 	volatile char 	sync_signal;
//#define sync_step()		while(sync_signal); sync_signal = 1


extern void init_motor();

extern void torque_on();
extern void torque_off();

extern void set_motor_int();

extern void motor_int_L();
extern void motor_int_R();
extern void motor_int();

extern void set_motor_double_int_mode();
extern void set_motor_single_int_mode();

extern void motor_L();
extern void motor_R();
extern void motor_LR();

extern void reverse_L();
extern void reverse_R();
extern void reverse_LR();

extern void motor_start();
extern void motor_stop();

extern void sync_step();

extern void reset_spd_ptr();
extern void reset_spd_diff();
extern void reset_steps();
extern void equal_spd_ptr();

// set speed table
extern void set_fSPD();
extern void set_tSPD();
#endif