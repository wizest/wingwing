#ifndef __AM188ES_H
#   include <AM188ES.H>
#endif

#ifndef __LED_H
#   define __LED_H

/*
 Seven seg

	 2
	___
 0 |_6_| 5
 1 |___| 4
	 3

*/


	#define PIO_LED_1 	(0x00000100l)   //... 0000 0001 0000 0000
	#define PIO_LED_6 	(0x00000200l)   //... 0000 0010 0000 0000
	#define PIO_LED_0 	(0x00800000l)   // port 23 0000 0000 1000 0000 ...
	#define PIO_LED_5 	(0x00000800l)
	#define PIO_LED_2 	(0x00001000l)
	#define PIO_LED_4 	(0x00002000l)
	#define PIO_LED_3 	(0x00004000l)
	#define PIO_LED_ALL ((PIO_LED_0|PIO_LED_1|PIO_LED_2|PIO_LED_3|PIO_LED_4|PIO_LED_5|PIO_LED_6))

	#define EYES_L		(0x80000000l)  // port 31
	#define EYES_R	    (0x00008000l)  // 15

	#define LED_SHOW_H	(PIO_LED_0|PIO_LED_1|PIO_LED_5|PIO_LED_4)
	#define LED_SHOW_V	(PIO_LED_2|PIO_LED_6|PIO_LED_3)


	extern void led_on( long pio_led );
	extern void led_off( long pio_led );
	extern void led_num( char num );
	extern void led_count_down( int countDownNum,int timeForCount);

	extern void led_show();

	extern void eyes_on();
	extern void eyes_off();

	extern void switch_eyes();

#endif
