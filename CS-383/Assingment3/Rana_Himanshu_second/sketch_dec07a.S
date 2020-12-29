#define __SFR_OFFSET 0x0
#include "avr/io.h"
#include <avr/portpins.h>

//Himanshu Rana - hrana2
//I pledge my honor that I have abided by the Stevens Honor System 

.text
.global loop
.global setup
.global Time30

setup:
  ser r16
  out DDRB, r16

loop:
  ldi r17, 0b00000011
  out PORTB, r17
  call Time30
  
  ldi r17, 0b00001100
  out PORTB, r17
  call Time30
  jmp loop
  
Time30:
  ldi  r18, 2
  ldi  r19, 132
  ldi  r20, 11
  ldi  r21, 6
  
L1: 
  dec  r21
  brne L1
  dec  r20
  brne L1
  dec  r19
  brne L1
  dec  r18
  brne L1
  
ret
