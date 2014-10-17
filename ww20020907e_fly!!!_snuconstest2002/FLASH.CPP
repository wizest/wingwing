#include "flash.h"
#include "serial.h"
#include "delay.h"
#include "led.h"

void SaveProgram()
{
	send_string("\n> Save Program.\n");
	CopyMemoryFLASH((byte far*)SAVE_ADDRESS,(byte far*)LOAD_ADDRESS,DATA_SIZE);
}
void CopyMemory(byte far* Destination,byte far* Source,word Size)
{

	while(Size--)
		*Destination++ = *Source++;
}
void CopyMemoryFLASH(byte far* Destination,byte far* Source,word Size)
{
	led_off(PIO_LED_ALL);
	led_on(PIO_LED_0|PIO_LED_1|PIO_LED_2|PIO_LED_6|PIO_LED_5);

	#define SECTOR_SIZE  (128)

	word SectorNum;
	word s, i;

	byte far*	pSrc;
	byte far*	pDest;

	byte far*	pR5555;
	byte far*	pR2AAA;

	SectorNum = ( Size / SECTOR_SIZE ) + 1;

	pSrc 	= Source;
	pDest	= Destination;

	pR5555	= (byte far*)0xE0005555L;
	pR2AAA	= (byte far*)0xE0002AAAL;

	// unlock
	*pR5555 = (byte)0xAA;
	*pR2AAA = (byte)0x55;
	*pR5555 = (byte)0x80;
	*pR5555 = (byte)0xAA;
	*pR2AAA = (byte)0x55;
	*pR5555 = (byte)0x20;

	SendString("\n> Flash ROM UnLocked. \n");
	SendString("> Writing.\n");
	for( s=0; s<SectorNum; s++)	{
		for( i=0; i<SECTOR_SIZE; i++)
			*pDest++ = *pSrc++;
		//Delay(20);
		Delay(10);
		SendString(".");
	}

	SendString("\n");
	// lock
	*pR5555 = (byte)0xAA;
	*pR2AAA = (byte)0x55;
	*pR5555 = (byte)0xA0;

	pSrc 	= Source;
	pDest	= Destination;
	for( i=0; i<SECTOR_SIZE; i++)
		*pDest++ = *pSrc++;

	SendString("> Locked.\n");
	Delay(500);
	SendString("> Verifying.... : ");

	pSrc 	= Source;
	pDest	= Destination;
	for(i=0;i<Size;i++)	{
		if (*pDest++ != *pSrc++)	{
			SendString("FAILURE\n");
			goto writeEND;
		}
	}
	SendString("SUCCESS\n");
	writeEND:
}
