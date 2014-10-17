#ifndef __AM188ES_H
#   include <AM188ES.H>
#endif

#ifndef __DELAY_H
#   define __DELAY_H

	extern void sys_delay		( unsigned int ms );
	extern void sys_short_delay	( unsigned int time );

	#define Delay sys_delay

#endif
