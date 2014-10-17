#include "init_sys.h"
#include "serial.h"
#include "sensor.h"
#include "motor.h"
#include "adj.h"
#include "led.h"
#include "run.h"

word pdata0 = 0x0000;
word pdata1 = 0x0000;

void init_system()
{
	init_port();
	init_serial();

	init_run();
	init_motor();
	init_adj();

	set_ss_int();

	led_show();

	send_string("\n");
	send_string("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
	send_string("®         WingWing         ¯\n");
	send_string("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
	send_string("> program start..... \n");
}

void init_port()
{
	outport( PIOMODE0, (word)0xFFFF); //1111 1111 1111 1111
	outport( PDIR0,    (word)0x0000); //0000 0000 0000 0000
									  //E777 7P77 MMMM MMMM
	outport( PIOMODE1, (word)0x82FE); //1000 0010 1111 1110
	outport( PDIR1,    (word)0x2400); //0010 0100 0000 0000
									  //E.KR TKB. 7SSS SSSA

									  //7:7segment
									  //P:sensor Power on/off
									  //M:Motor
									  //K:Key
									  //R:RxD
									  //T:TxD
									  //B:Buzzer
									  //E:Eyes
									  //S:Sensor
									  //A:Adc select
									  //.:not_used

	pdata0 = 0x0000;
	pdata1 = 0x0000;
	outport( PDATA0, pdata0);	outport( PDATA1, pdata1);

//	outport( UMCS, (word)0xF0BC ); //1111 0000 1011 1100 64K Default
//	outport( LMCS, (word)0x0FBC ); //0000 1111 1011 1100 64K

	outport( UMCS, (word)0xE0BC ); //1110 0000 1011 1100 128K
	outport( LMCS, (word)0x1FBC ); //0001 1111 1011 1100 128K

//	outport( MPCS, (word)0x8038 ); //1000 0000 0011 1000
	outport( MPCS, (word)0x80BC ); //1000 0000 1011 1100

//	outport( PACS, (word)0x0074 ); //0000 0000 0111 0100 wait 0
	outport( PACS, (word)0x0075 ); //0000 0000 0111 0101 wait 1 <-- Origin
//	outport( PACS, (word)0x0076 ); //0000 0000 0111 0110 wait 2
//	outport( PACS, (word)0x0077 ); //0000 0000 0111 0111 wait 3
//	outport( PACS, (word)0x007C ); //0000 0000 0111 1100 wait 5
}

