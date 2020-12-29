;
; Rana_Himanshu_assignment2_second.asm
;
; Created: 11/7/2018 10:10:32 PM
; Author : Himanshu Rana (hrna2)
;"I pledge my honor that I have abided by the Stevens Honor System" - Himanshu Rana 


; Replace with your application code
;this program uses a bubble sort approach by comparing each element with all subsequent elements 
.include "m328pdef.inc"

start: 
	.def compare = r23
	ldi r16, 2
	sts 0x0165, r16 

	ldi r17, 32
	sts 0x0166, r17

	ldi r18, 3
	sts 0x0167, r18 

	ldi r19, 12
	sts 0x0168, r19 

	ldi r20, 8
	sts 0x0169, r20 

	ldi r21, low (RAMEND)
	out spl, r21
	ldi r21, high (RAMEND) 
	out sph, r21

	ldi zl, 0x00
	ldi zh, 0x01

	ldi r22, 0 



Sorting1:
	cpi r22, 5 
	breq StackImplement 
	inc r22
	cp r16, r17
	brlt Sorting2
	mov compare, r16 
	mov r16, r17 
	mov r17, compare
	
Sorting2: 
	cp r17, r18 
	brlt Sorting3
	mov compare, r17 
	mov r17, r18
	mov r18, compare
	
Sorting3: 
	cp r18, r19
	brlt Sorting4
	mov compare, r18
	mov r18, r19 
	mov r19, compare
	
;this step goes back to the first sort to make sure that all the elements are sorted
Sorting4: 
	cp r19, r20 
	brlt Sorting1
	mov compare, r19
	mov r19, r20
	mov r20, compare
	rjmp Sorting1 

StackImplement: 
	push r16 
	push r17 
	push r18 
	push r19 
	push r20
	pop r20 
	pop r19
	pop r18
	pop r17
	pop r16 
	rjmp end
	 
end: 
	rjmp end
	

