#ifndef __AM188ES_H
#   include <AM188ES.H>
#endif

#ifndef __SERIAL_H
#   define __SERIAL_H

	#define init_serial() 			InitSerial()
	#define send_char(Char)     	SendChar(Char)
	#define send_string(String)		SendString(String)
	#define send_byte(ByteValue)	SendByte(ByteValue)
	#define	send_word(WordValue)	SendWord(WordValue)

	extern void InitSerial();
	extern void SendChar( byte Char);
	extern void SendString( char* String);
	extern void SendByte( byte ByteValue);
	extern void SendWord( word WordValue);

#endif
