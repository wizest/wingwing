;//[]------------------------------------------------------------[]
;//|      C0.ASM -- Start Up Code for Am188es                     |
;//|                                                              |
;//|      -Roh Chang Hyun, HandS Korea Univ.                      |
;//|	  -Kim Sang Hoon,  HandS Korea Univ.					  |
;//|                                                              |
;//[]------------------------------------------------------------[]

		 locals
		 __C0__ = 1

include  rules.asi

;//[]------------------------------------------------------------[]
;//|     define                                                   |
;//[]------------------------------------------------------------[]

RAM_END  equ    0FFFEh
DATA_SEG equ    00000h

; by wizest
STACK_SEG       equ 01000h
STACK_OFFSET	equ 0FFFEh

;//[]------------------------------------------------------------[]
;//|     segment declare                                          |
;//[]------------------------------------------------------------[]

_text    segment byte public 'code'
		 ends

_DATA    segment para public 'data'
		 data@ label byte
				 org 0080h
		 ends

_BSS     segment word public 'bss'
		 bdata@ label byte
		 ends

;//[]------------------------------------------------------------[]
;//|     code                                                     |
;//[]------------------------------------------------------------[]

				assume  cs:_text, ds:dgroup, ss: dgroup

				extrn    _main :dist

_text           segment
startupproc     proc    near

begin:

				;//disable maskable interrupts

				cli

				;//watch_dog_timer_disable

				mov    dx, 0FFE6h
				mov    ax, 03333h
				out    dx, ax
				mov    ax, 0CCCCh
				out    dx, ax
				mov    ax, 00000h
				out    dx, ax

				;//set LMCS
				mov    dx, 0FFA2h
				in     ax, dx     ;activate LMCS

									;0... 1111 ..11 1...
				;mov    ax, 0FBCh  	;0000 1111 1011 1100 / 64K, 0-WAIT
				mov     ax, 01FBCh  ;128k
				out    dx, ax

				;//set UMCS
				mov    dx, 0FFA0h
									;1... 0000 .011 1...
				;mov    ax, 0F0BDh 	;1111 0000 1011 1101 / 64K, 0-WAIT
				mov     ax, 0E0BCh  ;128k
				out    dx, ax


				;//ram data initialize by moving data from rom

				mov    bx, seg data@
				mov    ds, bx

				mov    dx, DATA_SEG
				mov    es, dx

				xor    si, si
				xor    di, di

				mov    cx, offset DGROUP:bdata@

				cld
				rep    movsb

				;//initialize stack pointer

				mov		dx, STACK_SEG
				mov     ss, dx
				mov     sp, STACK_OFFSET

				;//call main()
				mov     dx, DATA_SEG
				mov     ds, dx
				call    _main

				jmp     begin

startupproc		endp
_text           ends

				end

