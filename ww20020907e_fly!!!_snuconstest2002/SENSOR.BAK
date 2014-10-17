#ifndef __AM188ES_H
#   include <AM188ES.H>
#endif

#ifndef __SENSOR_H
#	define __SENSOR_H

	#define ss_start()  Start_Timer0()
	#define ss_stop()   Stop_Timer0()

	// ONLY USE LSB 8bit!!!! (for costom ASM code)
	#define SS_PORT_R90	0x0002   // port 17  : 0000 0000 0000 0010
	#define SS_PORT_R45	0x0040   //      22  : 0000 0000 0100 0000
	#define SS_PORT_L0	0x0010   //      20  : 0000 0000 0001 0000
	#define SS_PORT_L45	0x0004   //      18  : 0000 0000 0000 0100
	#define SS_PORT_L90	0x0008   //      19  : 0000 0000 0000 1000
	#define SS_PORT_R0	0x0020   //      21  : 0000 0000 0010 0000

	#define SS_PORT_ALL 0x007E   //            0000 0000 0111 1110
	#define SS_PORT_OFF 0xFF81   //            1111 1111 1000 0001
	#define SS_PORT_SW  0x0400   // port 10    0000 0100 0000 0000

	#define SS_ADDR_R45		5
	#define SS_ADDR_L90		0
	#define SS_ADDR_L0		3
	#define SS_ADDR_R90		4
	#define SS_ADDR_R0		2
	#define SS_ADDR_L45 	1

	#define SS_L0 		0
	#define SS_R0		1
	#define SS_L45		2
	#define SS_R45		3
	#define SS_L90		4
	#define SS_R90 		5

	#define onSS_CNT	200			// sensor on counts
	#define fSS_CNT	    1200//1200//700	// 700	// sensor non-pulsing counts - fast
	#define sSS_CNT     2400//1700//1700//1700	// sensor non-pulsing counts - slow
	#define ss_pulse_fast()		outport(T0CMPB,fSS_CNT)
	#define ss_pulse_slow()		outport(T0CMPB,sSS_CNT)

	extern void ss_on();
	extern void ss_off();
	extern void set_ss_int();
		   void ss_int();

	extern void show_ss_value();
	extern void show_ss_threshold();

	extern unsigned char ss_value[6];

	// for sensor history
	#define SS_HISTORY_SIZE		8 // Do not change!
	extern unsigned char ss_history[6][SS_HISTORY_SIZE];
	extern          int ss_his_ptr_L;
	extern          int ss_his_ptr_R;

//	extern void 			clear_ss_values()
	extern void 			init_ss_history();
	extern void 			refresh_ss_history();

	extern unsigned char 	cnt_ss_history   (unsigned int ss_index,unsigned char threshold);
	extern 			int		intg_ss_history  (unsigned int ss_index,unsigned char threshold);
	extern 			int 	diff_ss_history_L(unsigned int ss_index);
	extern 			int 	diff_ss_history_R(unsigned int ss_index);


#endif
