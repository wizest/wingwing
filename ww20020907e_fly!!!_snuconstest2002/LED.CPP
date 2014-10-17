#include "LED.H"
#include "DELAY.H"
#include "KEY.H"

void led_on( long pio_led )
{
	pdata0 |= (word)(pio_led & 0x0000FFFFl);
	outport( PDATA0, pdata0 );

	pdata1 |= (word)(pio_led >> 16);
	outport( PDATA1, pdata1 );
}

void led_off( long pio_led )
{
	pdata0 &= (word)(~(pio_led & 0x0000FFFFl));
	outport( PDATA0, pdata0 );

	pdata1 &= (word)(~(pio_led >> 16));
	outport( PDATA1, pdata1 );

}

void led_num( char num )
{
	led_off( PIO_LED_0 |PIO_LED_1|PIO_LED_2|PIO_LED_3|PIO_LED_4|PIO_LED_5|PIO_LED_6);
	switch( num )
	{
		case 0 : led_on(PIO_LED_0             | PIO_LED_2 | PIO_LED_3 | PIO_LED_4 | PIO_LED_5 | PIO_LED_1 );break;
		case 1 : led_on(                                                PIO_LED_4 | PIO_LED_5             );break;
		case 2 : led_on(            PIO_LED_2 | PIO_LED_5 | PIO_LED_6             | PIO_LED_1 | PIO_LED_3 );break;
		case 3 : led_on(            PIO_LED_2             | PIO_LED_5 | PIO_LED_4 | PIO_LED_6 | PIO_LED_3 );break;
		case 4 : led_on(PIO_LED_0 | PIO_LED_5 			   		      | PIO_LED_6 | PIO_LED_4             );break;
		case 5 : led_on(PIO_LED_2 | PIO_LED_0             | PIO_LED_6 | PIO_LED_4             | PIO_LED_3 );break;
		case 6 : led_on(PIO_LED_2 | PIO_LED_0 | PIO_LED_6 | PIO_LED_4 | PIO_LED_3             | PIO_LED_1 );break;
		case 7 : led_on(PIO_LED_0                         		      | PIO_LED_2 | PIO_LED_5 | PIO_LED_4 );break;
		case 8 : led_on(PIO_LED_0 | PIO_LED_1 | PIO_LED_2 | PIO_LED_3 | PIO_LED_4 | PIO_LED_5 | PIO_LED_6 );break;
		case 9 : led_on(PIO_LED_0 | PIO_LED_2             | PIO_LED_3 | PIO_LED_4 | PIO_LED_5 | PIO_LED_6 );break;
		case 10: led_on(PIO_LED_0 | PIO_LED_1 | PIO_LED_2 |             PIO_LED_4 | PIO_LED_5 | PIO_LED_6 );break;
		case 11: led_on(PIO_LED_0 | PIO_LED_1 |             PIO_LED_3 | PIO_LED_4 |             PIO_LED_6 );break;
		case 12: led_on(            PIO_LED_1 |             PIO_LED_3 |                         PIO_LED_6 );break;
		case 13: led_on(            PIO_LED_1 |             PIO_LED_3 | PIO_LED_4 | PIO_LED_5 | PIO_LED_6 );break;
		case 14: led_on(PIO_LED_0 | PIO_LED_1 | PIO_LED_2 | PIO_LED_3 |                         PIO_LED_6 );break;
		case 15: led_on(PIO_LED_0 | PIO_LED_1 | PIO_LED_2 |                                     PIO_LED_6 );break;
	}
}

void led_count_down( int countDownNum, int timeForCount )
{
	int timeToDelay = timeForCount / countDownNum;//msec

	switch( countDownNum )
	{
		case 9 : led_num( 9 ); sys_delay( timeToDelay );
		case 8 : led_num( 8 ); sys_delay( timeToDelay );
		case 7 : led_num( 7 ); sys_delay( timeToDelay );
		case 6 : led_num( 6 ); sys_delay( timeToDelay );
		case 5 : led_num( 5 ); sys_delay( timeToDelay );
		case 4 : led_num( 4 ); sys_delay( timeToDelay );
		case 3 : led_num( 3 ); sys_delay( timeToDelay );
		case 2 : led_num( 2 ); sys_delay( timeToDelay );
		case 1 : led_num( 1 ); sys_delay( timeToDelay );
		case 0 : led_num( 0 ); sys_delay( timeToDelay ); break;
	}
}

void led_show()
{
	led_off	(PIO_LED_ALL | EYES_L | EYES_R);

	eyes_on();

	led_on	(                              PIO_LED_3                              );
	sys_delay(30);
	led_on	(          PIO_LED_1|                    PIO_LED_4                    );
	sys_delay(30);
	led_on	(                                                            PIO_LED_6);
	sys_delay(30);
	led_on	(PIO_LED_0|                                        PIO_LED_5          );
	sys_delay(30);
	led_on	(                    PIO_LED_2                                        );
	sys_delay(30);

	led_off (                              PIO_LED_3                              );
	sys_delay(30);
	led_off (          PIO_LED_1|                    PIO_LED_4                    );
	sys_delay(30);
	led_off	(                                                            PIO_LED_6);
	sys_delay(30);
	led_off	(PIO_LED_0|                                        PIO_LED_5          );
	sys_delay(30);
	led_off	(                    PIO_LED_2                                        );
	sys_delay(30);

// inverse
	eyes_off();

	led_on	(                    PIO_LED_2                                        );
	sys_delay(30);
	led_on	(PIO_LED_0|                                        PIO_LED_5          );
	sys_delay(30);
	led_on	(                                                            PIO_LED_6);
	sys_delay(30);
	led_on	(          PIO_LED_1|                    PIO_LED_4                    );
	sys_delay(30);
	led_on	(                              PIO_LED_3                              );
	sys_delay(30);

	led_off	(                    PIO_LED_2                                        );
	sys_delay(30);
	led_off	(PIO_LED_0|                                        PIO_LED_5          );
	sys_delay(30);
	led_off	(                                                            PIO_LED_6);
	sys_delay(30);
	led_off	(          PIO_LED_1|                    PIO_LED_4                    );
	sys_delay(30);
	led_off	(                              PIO_LED_3                              );
	sys_delay(30);

	//eyes_on();	sys_delay(100);	eyes_off();	sys_delay(100);
	//eyes_on();	sys_delay(100);	eyes_off(); sys_delay(100);
}

void eyes_on()
{
	led_on( EYES_L | EYES_R );
}

void eyes_off()
{
	led_off( EYES_L | EYES_R );
}
void switch_eyes()
{
	static unsigned char eyes_state = 0;

	if (!eyes_state)
	{
		eyes_on();
		eyes_state = 1;
	}
	else
	{
		eyes_off();
		eyes_state = 0;
	}
}