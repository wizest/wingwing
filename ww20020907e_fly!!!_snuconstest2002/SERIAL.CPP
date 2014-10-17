#include "SERIAL.H"

void InitSerial()
{
	outport(SP1CT,0x0061);
	outport(SP1BAUD,22);
}

void SendChar( byte Char)
{
	while( !(inport(SP1STS)&(0x0004)) );
	outport(SP1TD,Char);
}
void SendString( char* String)
{
	while(*String) SendChar(*String++);
}

void SendByte( byte value)
{
	SendChar(value/100 +'0');  value -=(value/100)*100;
	SendChar(value/10  +'0');  value -=(value/10) *10;
	SendChar(value/1   +'0');
}

void SendWord( word value)
{
	SendChar(value/10000 +'0');  value -=(value/10000)*10000;
	SendChar(value/1000  +'0');  value -=(value/1000) *1000;
	SendChar(value/100   +'0');  value -=(value/100)  *100;
	SendChar(value/10    +'0');  value -=(value/10)   *10;
	SendChar(value/1     +'0');
}



