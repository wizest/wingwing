#include "DELAY.H"

void sys_delay( unsigned int ms )
{
	 int adjust;

	 while( ms-- )
	 {
		 adjust = 1132;
		 while( adjust-- );
	 }
}

void sys_short_delay( unsigned int time )
{
	int adjust;

	while( time-- )
	{
		adjust = 28;
		while( adjust-- );
	}
}
