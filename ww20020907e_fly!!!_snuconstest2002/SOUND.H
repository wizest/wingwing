#ifndef __AM188ES_H
#include <AM188ES.H>
#endif

#ifndef __SOUND_H
#define __SOUND_H

	#define pio_speaker (word)(0x0200)
	#define PIO_SPEAKER pio_speaker


	#define Do4on (261) //Hertz
	#define Do4up (277)
	#define Re4on (293)
	#define Re4up (311)
	#define Mi4on (329)
	#define Pa4on (349)
	#define Pa4up (370)
	#define Sl4on (392)
	#define Sl4up (415)
	#define Ra4on (440)
	#define Ra4up (466)
	#define Si4on (494)

	#define Do5on (523)
	#define Do5up (554)
	#define Re5on (587)
	#define Re5up (622)
	#define Mi5on (659)
	#define Pa5on (698)
	#define Pa5up (740)
	#define Sl5on (783)
	#define Sl5up (830)
	#define Ra5on (880)
	#define Ra5up (923)
	#define Si5on (988)

	#define REST (1)

	#define TRACK_END (0)


	typedef struct {
		word Frequency;
		byte TotalScale;
		byte EachScale;
	} soundlevel;


	extern soundlevel Track1[];
	extern soundlevel Wing_OST[];


	extern void Sound( word freq, word ms);

	extern void Sound_Off();
	extern void Sound_On();
	extern void Sound_Select();
	extern void Sound_Start();
	extern void Sound_Test();
	extern void Sound_Beep();
	extern void Sound_Track( soundlevel* TrackName);

#endif

