#include "sensor.h"
#include "serial.h"
#include "delay.h"
#include "key.h"
#include "sampling.h"
#include "motor.h"
#include "led.h"

unsigned char ss_ptr 		= 0;
unsigned char ss_ptr_next[6]= { 1,2,3,4,5,0 };

unsigned char 	ss_get 	[6] = {SS_L45     ,SS_R45     ,SS_L0     ,SS_R0      ,SS_L90     ,SS_R90     }; // get ss_value
unsigned char 	ss_shot	[6] = {SS_R45     ,SS_L0      ,SS_R0     ,SS_L90     ,SS_R90     ,SS_L45     }; // shot pulse
unsigned char   ss_AD_addr[6] = {SS_ADDR_R45,SS_ADDR_L0 ,SS_ADDR_R0,SS_ADDR_L90,SS_ADDR_R90,SS_ADDR_L45}; // address of sensor connected to AD convertor


unsigned char ss_value[6];
unsigned char ss_order[6]=	// only LSB 8bit!!!
{
	SS_PORT_L0,      //0
	SS_PORT_R0,      //1
	SS_PORT_L45,     //2
	SS_PORT_R45,     //3
	SS_PORT_L90,     //4
	SS_PORT_R90      //5
};

// for sensor history in motor.cpp
	unsigned char ss_history[6][SS_HISTORY_SIZE];
			 int ss_his_ptr_L = 0;
			 int ss_his_ptr_R = 0;

/*
void clear_ss_values()
{
	init_ss_history();

	// sensor values
	int i;
	for(i=0;i<6;i++)	{
		ss_value[i] = 0;
	}
}
*/
void init_ss_history()
{
	// clear sensor history.
	for(int i=0;i<6;i++)
		for(int j=0;j<SS_HISTORY_SIZE;j++)
			ss_history[i][j] = 0;
	ss_his_ptr_L = ss_his_ptr_R = 0;
}
void refresh_ss_history()
{
	// refresh all sensor history with newer sensor value.
	for(int i=0;i<6;i++)
		for(int j=0;j<SS_HISTORY_SIZE;j++)
			ss_history[i][j] = ss_value[i];
	ss_his_ptr_L = ss_his_ptr_R = 0;
}
unsigned char cnt_ss_history(unsigned int ss_index,unsigned char threshold)
{
	unsigned char cnt;

	cnt = 0;
	for(int i=0;i<SS_HISTORY_SIZE;i++)
		if ( ss_history[ss_index][i] > threshold ) cnt++;

	return cnt;
}
int intg_ss_history(unsigned int ss_index,unsigned char threshold)
{
	// integration of values in ss_history
	int intg,i;
	intg = 0;
	for (i=0;i<SS_HISTORY_SIZE;i++)
		intg += ((int)ss_history[ss_index][i] - (int)threshold);

	return intg;
}
int diff_ss_history_L(unsigned int ss_index)
{
	// difference of values in ss_history
	unsigned int c_ptr,p_ptr;

	p_ptr = ss_his_ptr_L;
	c_ptr = ( p_ptr + 7 ) & 7;

	return	ss_history[ss_index][p_ptr] - ss_history[ss_index][c_ptr];
}
int diff_ss_history_R(unsigned int ss_index)
{
	// difference of values in ss_history
	unsigned int c_ptr,p_ptr;

	p_ptr = ss_his_ptr_R;
	c_ptr = ( p_ptr + 7 ) & 7;

	return	ss_history[ss_index][p_ptr] - ss_history[ss_index][c_ptr];
}


void ss_on(void)
{
	ss_ptr = 0;

	ss_pulse_fast();

	// enable sensor int
	ss_start();

	// sensor switch on
	pdata0 |= SS_PORT_SW;
	outport(PDATA0,pdata0);

	eyes_on();
}
void ss_off()
{
	// sensor switch off
	pdata0 &= ~SS_PORT_SW;
	outport(PDATA0,pdata0);

	// pulse off
	pdata1 &= (SS_PORT_OFF);
	outport(PDATA1,pdata1);

	// disable sensor interrupt
	ss_stop();

	eyes_off();
}
void set_ss_int()
{
	outport(TCUCON,0x0000);
//	outport(T0CON, 0x0002); // Alternate Compare Bit
	outport(T0CNT, 0x0000);

//	outport(T0CMPA,200u); // Notice! set value under 200
	outport(T0CMPA,onSS_CNT); // Notice! set value under 200

	//outport(T0CMPB,700u); 	// 1200 recommended
	//outport(T0CMPB,1500u); 	// 1200 recommended
	ss_pulse_fast(); 			//outport(T0CMPB,fSS_CNT);
	//ss_pulse_slow();			//outport(T0CMPB,sSS_CNT);

	setvect( INT_TMR0, ss_int );

	ss_off();

	asm sti;
}
void ss_int()
{
	asm pusha;
	//asm cli;

	#define RIU (word)(0x1000)
	if( inport(T0CON) & RIU ) // when using register B
	{
/*
		ss_value[ ss_get[ss_ptr] ] = inportb( ss_AD_addr[ss_ptr] );
		ss_ptr = ss_ptr_next[ss_ptr];
*/
		// ss_ptr
		asm mov	bh,0
		asm mov	bl,byte ptr ss_ptr
		asm mov ah,bl	// ss_ptr backup : bl -> ah

		// get sensor value from ADC
		asm mov dh,0
		asm mov	dl,byte ptr ss_AD_addr[bx]
		asm in al,dx

		// set sensor value to MEMORY
		asm mov	bl,byte ptr ss_get[bx]
		asm mov	byte ptr ss_value[bx],al

		// update ss_ptr
		asm mov bl,ah	// ss_ptr recorver : ah -> bl
		asm mov	al,byte ptr ss_ptr_next[bx]
		asm mov	byte ptr ss_ptr,al

		pdata1 &= ( SS_PORT_OFF );
		outport(PDATA1,pdata1);
	}
	else
	{
//		pdata1 |= ss_order[ ss_shot[ss_ptr] ];

		asm mov	bh,0
		asm mov	bl,byte ptr ss_ptr
		asm mov	bl,byte ptr ss_shot[bx]
		asm mov	bl,byte ptr ss_order[bx]
		asm or	word ptr pdata1,bx

		outport(PDATA1,pdata1);
	}

	Int_End();
	asm popa;
	//asm sti;
	asm iret;
}

void show_ss_threshold()
{
	ss_on();

	while( !( get_key_state()==(PORT_CANCEL) || get_key_state()==(PORT_SELECT) ) )
	{
		if (ss_value[SS_L90] > threshold_L90 ) 	led_on (PIO_LED_4);
		else 									led_off(PIO_LED_4);
		if (ss_value[SS_L45] > threshold_L45 )  led_on (PIO_LED_3);
		else 									led_off(PIO_LED_3);
		if (ss_value[SS_L0] > threshold_L0 )    led_on (PIO_LED_1);
		else 									led_off(PIO_LED_1);
		if (ss_value[SS_R0] > threshold_R0 ) 	led_on (PIO_LED_0);
		else 									led_off(PIO_LED_0);
		if (ss_value[SS_R45] > threshold_R45 ) 	led_on (PIO_LED_2);
		else 									led_off(PIO_LED_2);
		if (ss_value[SS_R90] > threshold_R90 )	led_on (PIO_LED_5);
		else 									led_off(PIO_LED_5);
	}

	ss_off();
}
void show_ss_value()
{
	ss_on();

	send_string("\n\n> showing sensor value ...\n");
	while( !( get_key_state()==(PORT_CANCEL) || get_key_state()==(PORT_SELECT) ) )
	{
	send_string("-") ;send_byte( ss_value[SS_L90] );send_char(' ');
	send_string("\\");send_byte( ss_value[SS_L45] );send_char(' ');
	send_string("|") ;send_byte( ss_value[SS_L0 ] );send_char(' ');
	send_string("|") ;send_byte( ss_value[SS_R0 ] );send_char(' ');
	send_string("/") ;send_byte( ss_value[SS_R45] );send_char(' ');
	send_string("-") ;send_byte( ss_value[SS_R90] );send_char(' ');
	send_string("  ");
	send_string("-") ;send_byte( pos_L90[ss_value[SS_L90]] );send_char(' ');
	send_string("\\");send_byte( pos_L45[ss_value[SS_L45]] );send_char(' ');
	send_string("|") ;send_byte( pos_L0 [ss_value[SS_L0 ]] );send_char(' ');
	send_string("|") ;send_byte( pos_R0 [ss_value[SS_R0 ]] );send_char(' ');
	send_string("/") ;send_byte( pos_R45[ss_value[SS_R45]] );send_char(' ');
	send_string("-") ;send_byte( pos_R90[ss_value[SS_R90]] );send_char(' ');
	/*
	send_string("  ");
	send_string("L/R:");
	send_word(search_V_step(sFL0,ss_value[SS_L0],SAMPL_VSTEP));
	send_char(' ');
	send_word(search_V_step(sFR0,ss_value[SS_R0],SAMPL_VSTEP));
	*/
	send_char('\r');
	send_char('\n');
	sys_delay(5);
	}

	ss_off();
}
