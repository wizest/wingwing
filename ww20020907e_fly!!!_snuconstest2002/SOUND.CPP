#include "SOUND.H"
#include "DELAY.H"

/*
soundlevel Track1[] ={
/////////1
{REST,4,4},

{REST,4,4},

{REST,8,1},
{Re5up,4,1},
{Re5on,8,1},
{Re5up,8,1},
{Re5on,8,1},
{Re5up,8,1},
{Si4on,8,1},

{Sl4up,4,3},
{Re4up,8,1},
{Sl4up,8,1},

{Ra4up,4,3},
{Re4up,8,1},
{Sl4up,8,1},

/////////2
{Si4on,4,4},

{REST,8,1},
{Re5up,4,1},
{Re5on,8,1},
{Re5up,8,1},
{Re5on,8,1},
{Re5up,8,1},
{Si4on,8,1},

{Sl4up,4,3},
{Re4up,8,1},
{Sl4up,8,1},

{Ra4up,8,5},
{Si4on,4,1},
{Ra4up,8,1},

{Sl4up,4,4},

//////////3
{REST,4,1},
{Ra4up,4,1},
{Si4on,4,1},
{Do5up,4,1},

{Re5up,8,5},
{Mi5on,4,1},
{Re5up,8,1},

{Do5up,4,3},
{Re5up,8,1},
{Re5on,8,1},

{Si4on,8,5},
{Do5up,4,1},
{Si4on,8,1},

//////////4
{Ra4up,8,1},
{Re5up,4,1},
{Re5on,8,1},
{Re5up,8,1},
{Re5on,8,1},
{Re5up,8,1},
{Re4on,8,1},

{Sl4up,4,3},
{Re4up,8,1},
{Sl4up,8,1},

{Ra4up,4,3},
{Re4up,8,1},
{Sl4up,8,1},

{Si4on,4,4},

//////////5
{REST,8,1},
{Re5up,4,1},
{Re5on,8,1},
{Re5up,8,1},
{Re5on,8,1},
{Re5up,8,1},
{Si4on,8,1},

{Sl4up,4,3},
{Re4up,8,1},
{Sl4up,8,1},

{Ra4up,8,5},
{Si4on,4,1},
{Ra4up,8,1},

{Sl4up,4,4},

{TRACK_END,0,0}
};

soundlevel Wing_OST[] ={
/////////1
{Sl4on,4,1},

{Do5on,8,3},
{Do5on,16,1},
{Mi4on,4,1},
{Ra4on,4,1},

{Sl4on,4,3},
{Do4on,8,1},
{Re4on,8,1},

{Mi4on,4,1},
{Mi4on,4,1},
{Sl4on,4,1},
{Pa4on,16,3},
{Pa4on,16,1},

{Re4on,4,3},
{Sl4on,4,1},

//

{Do5on,8,3},
{Do5on,8,1},
{Si4on,4,1},
{Re5on,4,1},

{Do5on,4,3},
{Sl4on,8,1},
{Ra4on,8,1},

{Si4on,4,1},
{Si4on,4,1},
{Sl4on,4,1},
{Ra4on,8,1},
{Pa4up,16,1},

{Sl4on,4,3},
{Sl4on,8,1},
{Ra4on,8,1},
{Si4on,8,1},

{Do5on,4,1},
{Do5on,4,1},
{Do5on,4,1},
{Si4on,16,3},
{Do5on,16,1},

{Re5on,4,1},
{Re5on,4,1},
{Re5on,4,1},
{Ra4on,16,3},
{Ra4on,16,1},

{Re5on,4,1},
{Re5on,4,1},
{Re5on,4,1},
{Do5on,16,3},
{Re5on,16,1},

{Mi5on,4,1},
{Mi5on,4,1},
{REST,4,1},
{Do5on,16,3},
{Re5on,16,1},

{Mi5on,4,3},
{Do5on,16,3},
{Re5on,16,1},

{Mi5on,4,1},
{Mi5on,4,1},
{Mi5on,4,1},
{Mi5on,16,3},
{Mi5on,16,1},

{Re5on,2,1},
{Re5on,4,1},
{Mi5on,16,3},
{Re5on,16,1},

{Do5on,4,1},
{Do5on,2,1},
{REST,4,1},

{Mi4on,8,1},
{Pa4on,8,1},
{Sl4on,8,1},
{Sl4on,8,1},
{Sl4on,4,1},
{REST,4,1},

{Mi5on,8,1},
{Mi5on,8,1},
{Re5on,8,1},
{Do5on,8,1},
{Si4on,4,1},
{REST,4,1},

{Do5on,2,1},
{Si4on,4,1},
{Re5on,4,1},

{Ra4on,2,1},
{Sl4on,4,1},
{REST,4,1},

{Do4on,8,1},
{Mi4on,8,1},
{Sl4on,8,1},
{Sl4on,8,1},
{Sl4on,4,1},
{REST,4,1},

{Mi5on,8,1},
{Mi5on,8,1},
{Re5on,8,1},
{Do5on,8,1},
{Si4on,4,1},
{Mi5on,16,3},
{Mi5on,16,1},

{Mi5on,2,1},
{Re5on,4,1},
{Mi5on,4,1},

{Do5on,4,3},
{REST,4,1},

{TRACK_END,0,0}
};
*/



void Sound( word freq, word ms)
{
	long c =290000L;

	word Period;
	word HalfPeriod;
	word count;

	///////////////////////////////
	//inline asm
	asm {
		pusha;

		mov dx, word ptr c+2;
		mov ax, word ptr c;
		div freq;
		mov word ptr Period, ax;

		shr ax, 1;
		mov word ptr HalfPeriod, ax;

		mov ax, ms;
		mul freq;
		mov bx, 1000;
		div bx;
		mov count, ax;

		popa;
	}
	///////////////////////////

	/*
	long Period = 290000/freq;
	long HalfPeriod = Period/2;
	long count=(ms*freq)/1000;
	*/

	long hold;//? why can't word
	while( count--)
	{
		pdata1 &= (~pio_speaker);
		outport( PDATA1,pdata1);
		hold =HalfPeriod;
		while( hold--);

		pdata1 |= (pio_speaker);
		outport( PDATA1,pdata1);
		hold =HalfPeriod;
		while( hold--);
	}
	Sound_Off();
}

void Sound_Off()
{
	pdata1 &= ~(pio_speaker);
	outport( PDATA1,pdata1);
}
void Sound_On()
{
	pdata1 |= pio_speaker;
	outport(PDATA1,pdata1);
}


void Sound_Select()
{
	word i;

	/*
	for( i=2300; i<3000; i+=200) Sound(i,20);
	Delay(60);
	for( i=1300; i<1700; i+=200) Sound(i,30);
	Delay(60);
	for( i=1300; i<1700; i+=200) Sound(i,30);
	*/
	/*
	for( i=2400; i<3200; i+=200) Sound(i,20);
	Delay(60);
	for( i=1300; i<1700; i+=170) Sound(i,20);
	Delay(30);
	for( i=1300; i<1700; i+=170) Sound(i,20);
	*/

	for( i=2400; i<4500; i+=300) Sound(i,20);
	Delay(60);
	for( i=1000; i<1500; i+=150) Sound(i,20);
	Delay(30);
	for( i=1000; i<1500; i+=150) Sound(i,20);

}

void Sound_Start()
{
	word i;

	for( i=3500; i<5000; i+=100) Sound(i,10);
	Delay(400);
	for( i=3500; i<5000; i+=100) Sound(i,10);
	Delay(10);
	for( i=3500; i<5000; i+=100) Sound(i,10);
}

void Sound_Beep()
{
	Sound( 6000,3);
}

/*
void Sound_Test( void)
{
	word SoundTime =100;

	Sound( Do4on, SoundTime);
	Sound( Do4on, SoundTime);
	Sound( Do4up, SoundTime);
	Sound( Re4on, SoundTime);
	Sound( Re4up, SoundTime);
	Sound( Mi4on, SoundTime);
	Sound( Pa4on, SoundTime);
	Sound( Pa4up, SoundTime);
	Sound( Sl4on, SoundTime);
	Sound( Sl4up, SoundTime);
	Sound( Ra4on, SoundTime);
	Sound( Ra4up, SoundTime);
	Sound( Si4on, SoundTime);

	Sound( Do5on, SoundTime);
	Sound( Do5up, SoundTime);
	Sound( Re5on, SoundTime);
	Sound( Re5up, SoundTime);
	Sound( Mi5on, SoundTime);
	Sound( Pa5on, SoundTime);
	Sound( Pa5up, SoundTime);
	Sound( Sl5on, SoundTime);
	Sound( Sl5up, SoundTime);
	Sound( Ra5on, SoundTime);
	Sound( Ra5up, SoundTime);
	Sound( Si5on, SoundTime);
}
*/

/*
void Sound_Track( soundlevel* TrackName )
{
//	long TimeScale =400L;
	long TimeScale =1800L;

	word index =0;
	long SoundTime=0;
	long SoundLevel=0;

	while( (SoundLevel=(TrackName+index)->Frequency) != TRACK_END )
	{
		SoundTime= TimeScale * (TrackName+index)->EachScale / (TrackName+index)->TotalScale;

		if( SoundLevel==REST )
		{
			Sound_Off();
			SoundTime *=10;
			while( SoundTime-- );
		}
		else
		{
			Sound((word)SoundLevel,(word)SoundTime);
		}
		index++;
	}
}



*/