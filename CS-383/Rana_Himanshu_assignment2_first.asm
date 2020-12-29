;
; Rana_Himanshu_assignment2_first.asm
;
; Created: 11/7/2018 5:53:05 PM
; Author : Himanshu Rana (hrana2) 
;"I pledge my honor that I have abided by the Stevens Honor System" - Himanshu Rana 
; 

; Replace with your application code

.include "m328pdef.inc"

start:
	ldi r16, 0
	ldi r17, low (RAMEND)
	ldi r18, 1
	out spl, r17
	ldi r17, high (RAMEND) 
	out sph, r17
	ldi zl, 0x00
	ldi zh, 0x01

;This pushes 1-100 onto the stack 
Loop: 
	cpi r16, 100
	breq init
	push r18
	inc r16
	inc r18
	rjmp Loop	

init: 
	ldi r16, 0

;compares the register against 1-100 and pops them off the stack 
Popping: 
	cpi r16, 100
	breq end
	pop r19 
	st z+, r19 
	inc r16 
	rjmp Popping

end: 
	rjmp end
