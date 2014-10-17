//[]------------------------------------------------[]
//|             <AM188ES HEADER FILE>                |
//|                                                  |
//|         Roh Chang Hyun, HandS Korea Univ.        |
//[]------------------------------------------------[]


#ifndef __AM188ES_H
#    define __AM188ES_H

#    ifndef __SMALL__
#    error	Invalid memory model!!	Set memory model to <Small>.
#    endif

#    ifndef __cplusplus
#    error  Compile by C++!!  Set file extension to CPP.
#    endif

//[]------------------------------------------[]
//|  system function                           |
//[]------------------------------------------[]

#    if __STDC__
#      define _Cdecl
#    else
#      define _Cdecl  cdecl
#    endif

#    define NULL  (0)

extern "C" {
	unsigned char _Cdecl  __inportb__ ( unsigned __portid );
	unsigned      _Cdecl  __inportw__ ( unsigned __portid );
	unsigned char _Cdecl  __outportb__( unsigned __portid, unsigned char __value );
	unsigned      _Cdecl  __outportw__( unsigned __portid, unsigned __value );
}

#define inportb(__portid)           __inportb__(__portid)
#define outportb(__portid, __value) ((void) __outportb__(__portid, __value))
#define inport(__portid)            __inportw__(__portid)
#define outport(__portid, __value)  ((void) __outportw__(__portid, __value))

#define getvect(No) ( (void interrupt(*)(void))*(long far*)((No)*4) )
#define setvect(No,Service) ( *(long far*)((No)*4) = (long)(void far(*)(void))(Service) )
//                            ~~~~~~~~~~~~ ~~~~~~~~         ~~~~~~~~~~~~~~~~~~~


#define Push_All()     asm pusha
#define Pop_All()      asm popa

#define Int_Enable()   asm sti
#define Int_Disable()  asm cli
#define Int_Return()   asm iret
#define Int_End()      outport( EOI, 0x8000)



#define Start_Timer0() outport(T0CON,0xE003) // 1110 0000 0000 0011
//#define Start_Timer0() outport(T0CON,0xE000)  //1110 0000 0000 0000

#define Start_Timer1() outport(T1CON,0xE000)
#define Start_Timer2() outport(T2CON,0xE000)

#define Stop_Timer0()  outport(T0CON,0x6003) // 0110 0000 0000 0011
//#define Stop_Timer0()  outport(T0CON,0x6000) // 0110 0000 0000 0000

#define Stop_Timer1()  outport(T1CON,0x6000)
#define Stop_Timer2()  outport(T2CON,0x6000)

//[]--------------------------------------------------[]
//|   AM188ES's Peripheral Control Block Register MAP  |
//[]--------------------------------------------------[]

////////////////////////////////////////////////////
//processor control register
#define AUXCON   (0xFFF2)

////////////////////////////////////////////////////
//serial port 0 register
#define SP0CON    (0xFF44)// <-interrupt register
#define SP0CT     (0xFF80)
#define SP0STS    (0xFF82)
#define SP0TD     (0xFF84)
#define SP0RD     (0xFF86)
#define SP0BAUD   (0xFF88)

////////////////////////////////////////////////////
//serial port 1 register
#define SP1CON    (0xFF42)//
#define SP1CT     (0xFF10)
#define SP1STS    (0xFF12)
#define SP1TD     (0xFF14)
#define SP1RD     (0xFF16)
#define SP1BAUD   (0xFF18)

////////////////////////////////////////////////////
//PIO register
#define PIOMODE0 (0xFF70)
#define PDIR0    (0xFF72)
#define PDATA0   (0xFF74)

#define PIOMODE1 (0xFF76)
#define PDIR1    (0xFF78)
#define PDATA1   (0xFF7A)

///////////////////////////////////////////////////
//timer
#define TCUCON   (0xFF32)// <-interrupt register

#define T0CNT    (0xFF50)
#define T0CMPA   (0xFF52)
#define T0CMPB   (0xFF54)
#define T0CON    (0xFF56)

#define T1CNT    (0xFF58)
#define T1CMPA   (0xFF5A)
#define T1CMPB   (0xFF5C)
#define T1CON    (0xFF5E)

#define T2CNT    (0xFF60)
#define T2CMPA   (0xFF62)
#define T2CON    (0xFF66)

///////////////////////////////////////////////////
//interrupt
#define EOI      (0xFF22)
#define IMASK    (0xFF28)

///////////////////////////////////////////////////
//chip select register
#define MPCS     (0xFFA8)
#define MMCS     (0xFFA6)
#define PACS     (0xFFA4)
#define LMCS     (0xFFA2)
#define UMCS     (0xFFA0)

//[]---------------------------[]
//| AM188ES's Interrupt Types  |
//[]---------------------------[]

#define INT_TMR0 (0x0008)
#define INT_TMR1 (0x0012)
#define INT_TMR2 (0x0013)

#define ASPI     (0x0014)

//[]--------------------------[]
//| type define                |
//[]--------------------------[]

typedef unsigned char byte;
typedef unsigned int  word;

//[]--------------------------[]
//| Grobal Variable define    |
//[]--------------------------[]

extern word pdata0, pdata1;

#endif

