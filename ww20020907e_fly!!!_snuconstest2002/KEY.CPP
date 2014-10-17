#include "KEY.H"
#include "DELAY.H"

void wait_key()
{
	unsigned int key_state;
	unsigned int prev_key_clear = 0;

	while( 1 )
	{
		key_state = get_key_state();

		if( !key_state ) prev_key_clear = 1;

		if( prev_key_clear == 1 )
			if( ( key_state & (PORT_SELECT|PORT_CANCEL)) )	break;
	}
	sys_delay(150);
}

unsigned int read_key()
{
	unsigned int key_state;
	unsigned int prev_key_clear = 0;

	while( 1 )
	{
		key_state = get_key_state();

		if( !key_state ) prev_key_clear = 1;

		if( prev_key_clear == 1 )
		{
			if( key_state & PORT_SELECT )
			{
				sys_delay(200);
				return L_KEY;
			}
			else
			if( key_state & PORT_CANCEL )
			{
				sys_delay(200);
				return R_KEY;
			}
		}
	}
}


