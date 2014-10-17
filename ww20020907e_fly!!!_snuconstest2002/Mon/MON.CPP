#include <AM188ES.H>

#define SUCCESS (1)
#define FAILURE (0)

#define LOAD_ADDRESS (0x04000000L)
#define SAVE_ADDRESS (0xE4000000L)
#define DATA_SIZE	 (0xBFF0)

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

#define PORT_R_KEY    (word)(0x2000)
#define PORT_L_KEY    (word)(0x0400)
#define L_KEY 	0
#define R_KEY 	1
#define GetKeyState()   ( (~inport(PDATA1)) & (PORT_L_KEY|PORT_R_KEY) )


word pdata0, pdata1;

void Delay(word ms);
void LedShow();		// download
void LedShowEntry();	// program starting wait
void LedOn(long pio_led);
void LedOff(long pio_led);
word ReadKey();
void InitPort();
void InitSerial();
void SendChar( byte Char);
void SendString( char* String);
byte ReceiveChar();
byte ReceiveByte();
byte DownLoad( long LoadStartAddress);
void RAMmemcpy(long Destination,long Source,word Size);
void ROMmemcpy(long Destination,long Source,word Size);

void main()
{
	InitPort();
	InitSerial();

	LedShow();

	/////////////////////////////////////////
	//test connect
	SendString("\nÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ");
	SendString("\n®      WingWing Loader      ¯");
	SendString("\nÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ");
	SendString("\n> connected.\n\n");

	/////////////////////////////////////////
	//serial down loading

	if( GetKeyState() )	{
		SendString("> Waiting for DOWNLOAD.\n");
		LedOn( PIO_LED_0 | PIO_LED_1 | PIO_LED_3 );

		if( DownLoad(LOAD_ADDRESS)==SUCCESS ) NULL;
		else 								  goto END;

		/*
		SendString("\n> LKey:Write&Start / RKey:Start\n");
		if ( L_KEY == ReadKey()	)	{

			ROMmemcpy(SAVE_ADDRESS,LOAD_ADDRESS,DATA_SIZE);
			SendString("> Program Written into Flash Memory...\n");
		}
		else	NULL;
		*/
	}
	else RAMmemcpy(LOAD_ADDRESS,SAVE_ADDRESS,DATA_SIZE);

	/////////////////////////////////////////
	//application main run
	//SendString("> Waiting for program start...\n");
	//while (!GetKeyState())		LedShowEntry();
	SendString("> Program start\n");
	( *(void far(*)(void))LOAD_ADDRESS )();

END:
}

void InitPort()
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
									  //E:Eye
									  //S:Sensor
									  //A:Adc select
									  //.:not_used

	pdata0 =0x0000;				pdata1 =0x0000;
	outport( PDATA0, pdata0);	outport( PDATA1, pdata1);

//	outport( UMCS, (word)0xF0BC ); //1111 0000 1011 1100 64K Default
//	outport( LMCS, (word)0x0FBC ); //0000 1111 1011 1100 64K

	outport( UMCS, (word)0xE0BC ); //1110 0000 1011 1100 128K
	outport( LMCS, (word)0x1FBC ); //0001 1111 1011 1100 128K

//	outport( MPCS, (word)0x8038 ); //1000 0000 1011 1000
//	outport( PACS, (word)0x007C ); //0000 0000 0111 1100 - wait 5
}

void InitSerial()
{
	outport( SP1CT,0x0061 );
	outport( SP1BAUD,  22 ); //40 MHz, 115200 baud
}

void SendChar( byte Char)
{
	while( !(inport(SP1STS)&(0x0004)) );
	outport(SP1TD,Char);
}

void SendString( char* String)
{
	while( *String) SendChar( *String++);
}

byte ReceiveChar()
{
	while( !(inport(SP1STS)&(0x0080)) ); //wait
	return inport(SP1RD);
}

byte ReceiveByte()
{
	byte HighNibble =ReceiveChar();
	byte LowNibble  =ReceiveChar();

	if( HighNibble<'A' ) HighNibble =HighNibble -'0';
	else HighNibble =HighNibble -'A' +10;

	if( LowNibble<'A' ) LowNibble =LowNibble -'0';
	else LowNibble =LowNibble -'A'+10;

	return (byte)((HighNibble<<4)+LowNibble);
}

byte DownLoad( long LoadStartAddress )
{
	byte DataCount;
	word OffsetAddress;
	byte RecordType =0;
	byte TotalSum =0;

	byte far* WriteAddress;

	while( RecordType!=1 )
	{
		//wait start of record
		while(ReceiveChar()!=':');

		TotalSum +=DataCount                  =ReceiveByte();//read repeat count from record
		TotalSum +=((byte*)&OffsetAddress)[1] =ReceiveByte();//read address
		TotalSum +=((byte*)&OffsetAddress)[0] =ReceiveByte();
		TotalSum +=RecordType                 =ReceiveByte();//

		//if data, write code in specific memory
		if(RecordType==0)
		{
			WriteAddress =(byte far*)(LoadStartAddress+OffsetAddress);
			while( DataCount--) TotalSum +=(*WriteAddress++ =ReceiveByte());
		}
		else
		{
			while( DataCount--) TotalSum+= ReceiveByte();
		}

		//read check sum itself
		TotalSum +=ReceiveByte();

		//summation check
		if(TotalSum!=0)
		{
			Delay(10);
			SendString("\n> CHECK SUM ERROR!");
			goto OUTBYERROR;
		}
		else
		{
			TotalSum =0;//reset total sun
		}
	}
	Delay(10);
	SendString("\n> Load complete...\n");
	return (byte)SUCCESS;

	OUTBYERROR:
	return (byte)FAILURE;
}
word ReadKey()
{
	unsigned int key_state;
	unsigned int prev_key_clear = 0;

	while( 1 )
	{
		key_state = GetKeyState();

		if( !key_state ) prev_key_clear = 1;

		if( prev_key_clear == 1 )
		{
			if( key_state & PORT_L_KEY )
			{
				Delay(200);
				return L_KEY;
			}
			else
			if( key_state & PORT_R_KEY )
			{
				Delay(200);
				return R_KEY;
			}
		}
	}
}

void Delay( word ms)
{
	 int adjust;

	 while ( ms--)
	 {
		 adjust =1132;
		 while( adjust--);
	 }
}

void LedOn( long pio_led )
{
	pdata0 |= (word)(pio_led & 0x0000ffffL);
	outport( PDATA0, pdata0 );

	pdata1 |= (word)(pio_led >> 16);
	outport( PDATA1, pdata1 );
}

void LedOff( long pio_led )
{
	pdata0 &= (word)(~(pio_led & 0x0000ffffL));
	outport( PDATA0, pdata0 );

	pdata1 &= (word)(~(pio_led >> 16));
	outport( PDATA1, pdata1 );

}
void LedShow()
{
	for (int i=0 ; i< 2; i++)	{
		LedOn  ( EYES_L | EYES_R ); LedOn  ( PIO_LED_ALL );		Delay(100);
		LedOff ( EYES_L | EYES_R ); LedOff ( PIO_LED_ALL );		Delay(100);
		LedOn  ( EYES_L | EYES_R ); LedOn  ( PIO_LED_ALL );		Delay(100);
		LedOff ( EYES_L | EYES_R ); LedOff ( PIO_LED_ALL );		Delay(100);
	}
}
void LedShowEntry()
{
	#define led_on 		LedOn
	#define led_off 	LedOff
	#define sys_delay	Delay
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

}
void ROMmemcpy(long Destination,long Source,word Size)
{
	#define SECTOR_SIZE  (128)

	word SectorNum;
	word s, i;

	byte far*	pSrc;
	byte far*	pDest;

	byte far*	pR5555;
	byte far*	pR2AAA;

	SectorNum = ( Size / SECTOR_SIZE ) + 1;

	pSrc 	= (byte far*)Source;
	pDest	= (byte far*)Destination;

	pR5555	= (byte far*)0xE0005555L;
	pR2AAA	= (byte far*)0xE0002AAAL;

	SendString("> Writing...\n");

	// unlock
	*pR5555 = (byte)0xAA;
	*pR2AAA = (byte)0x55;
	*pR5555 = (byte)0x80;
	*pR5555 = (byte)0xAA;
	*pR2AAA = (byte)0x55;
	*pR5555 = (byte)0x20;

	SendString("> UnLocked ... \n");

	for( s=0; s<SectorNum; s++)	{
		for( i=0; i<SECTOR_SIZE; i++)
			*pDest++ = *pSrc++;
		Delay(20);
		SendString(".");
	}

	SendString("> Data Transmitted ...\n");
	// lock
	*pR5555 = (byte)0xAA;
	*pR2AAA = (byte)0x55;
	*pR5555 = (byte)0xA0;
	for( i=0; i<SECTOR_SIZE; i++)
		*pDest++ = *pSrc++;

	SendString("> Locked ...\n");

	Delay(50);
}
void RAMmemcpy(long Destination,long Source,word Size)
{
	byte far* pSrc;
	byte far* pDest;
	pSrc 	= (byte far*)Source;
	pDest   = (byte far*)Destination;

	while(Size--)
		*pDest++=*pSrc++;

	Delay(50);
}
