#ifndef __AM188ES_H
#   include <AM188ES.H>
#endif

#ifndef __KEY_H
#   define __KEY_H

	#define PORT_CANCEL    (word)(0x2000)
	#define PORT_SELECT    (word)(0x0400)

	#define L_KEY 	0
	#define R_KEY 	1

	#define get_key_state()    ( (~inport( PDATA1 ) ) & ( PORT_SELECT | PORT_CANCEL ) )

	extern void 		wait_key();
	extern unsigned int read_key();

#endif
