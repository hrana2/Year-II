;
; Rana_Himanshu_assignment1.asm
;
; Created: 10/27/2018 5:53:49 PM
; Author : Himanshu Rana(hrana2)
; "I pledge my honor that I have abided by the Stevens Honor System" - Himanshu Rana



; Replace with your application code



.include "m328pdef.inc"
init: 
;storing all the values
ldi r16, 10
sts 0x0100, r16 

ldi r17, 13
sts 0x0101, r17

ldi r18, 23
sts 0x0102, r18

ldi r19, 26
sts 0x0103, r19

ldi zl, 0x00
ldi zh, 0x01
ldi r19, 0
ldi  r25, 0
	

FindMax: 
	cpi r24, 4
	breq returnMax
	inc r24
	ld r17, z+
	cp r17, r19
	brlt TempMax
	rjmp FindMax

TempMax: 
	mov r17, r19
	rjmp FindMax

returnMax: 
	sts 0x0105, r17

ldi zl, 0x00
ldi r19, 1
ldi r25, 0

FirstEven: 
	cpi r25, 4
	breq none
	ld r16, z
	inc zl
	mov r17, r16
	and r17, r19
	cpi r17, 0
	breq returnEven
	rjmp FirstEven

none: 
	ldi r16, 0
	sts 0x0106, r16 

returnEven: 
	sts 0x0106, r16 

	ldi zl, 0x00
	ldi zh, 0x01
	ldi r18, 0 
	ldi r24, 0

Sum: 
	cpi r24, 4
	breq returnSum
	inc r24
	ld r17, z+ 
	add r18, r17
	rjmp Sum

returnSum: 
	sts 0x0107, r18

;by doing the arithmethic shift right two times on the 
;r18, we get the average
Average: 
	asr r18
	asr r18
	sts 0x0108, r18

ldi zl, 0x00
ldi zh, 0x01
ld r16, z
ldi yl, 0x13
ldi yh, 0x01

Reverse: 
	cpi zl, 0x04
	breq end 
	st y, r16
	inc zl 
	ld r16, z
	dec yl
	rjmp Reverse

end: 
	ret



	