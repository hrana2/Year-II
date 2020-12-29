#include "avr/io.h"
#include <avr/portpins.h>

//Himanshu Rana - hrana2
//I pledge my honor that I have abided by the Stevens Honor System
.text
.global setup
.global loop

.global Time150
.global Time300
.global Time400
.global again

setup:
  ldi r16, 0b00100000
  sts DDRB, r16

loop:
//this part is where "S" begins 
  ldi r17, 0b00100000
  sts PORTB, r17
  call Time150
  ldi r17, 0b00000000
  sts PORTB, r17
  call Time150
  
  ldi r17, 0b00100000
  sts PORTB, r17
  call Time150
  ldi r17, 0b00000000
  sts PORTB, r17
  call Time150
  
  ldi r17, 0b00100000
  sts PORTB, r17
  call Time150
  ldi r17, 0b00000000
  sts PORTB, r17
  
  call Time300
  
  ldi r17, 0b00100000
  sts PORTB, r17
  call Time400
  ldi r17, 0b00000000
  sts PORTB, r17
  call Time400
  
  ldi r17, 0b00100000
  sts PORTB, r17
  call Time400
  ldi r17, 0b00000000
  sts PORTB, r17
  call Time400
  
  ldi r17, 0b00100000
  sts PORTB, r17
  call Time400
  
//"O" begins here 
  ldi r17, 0b00000000
  sts PORTB, r17
  
  call Time300
  
  ldi r17, 0b11111111
  sts PORTB, r17
  call Time150
  ldi r17, 0b00000000
  sts PORTB, r17
  call Time150
  
  ldi r17, 0b00100000
  sts PORTB, r17
  call Time150
  ldi r17, 0b00000000
  sts PORTB, r17
  call Time150
  
  ldi r17, 0b00100000
  sts PORTB, r17
  call Time150
  ldi r17, 0b00000000
  sts PORTB, r17
  call Time300
  
  jmp loop

Time300:
    ldi  r18, 25
    ldi  r19, 90
    ldi  r20, 178
L1: 
    dec  r20
    brne L1
    dec  r19
    brne L1
    dec  r18
    brne L1
    ret

Time150:
    ldi  r18, 13
    ldi  r19, 45
    ldi  r20, 216
    
L2: 
    dec  r20
    brne L2
    dec  r19
    brne L2
    dec  r18
    brne L2
    ret
       
Time400:
    ldi  r18, 33
    ldi  r19, 120
    ldi  r20, 153
    
L3: 
    dec  r20
    brne L3
    dec  r19
    brne L3
    dec  r18
    brne L3
    ret
