//"I pledge my honor that I have abided by the Stevens Honor System" - Himanshu Rana 
//Himanshu Rana - hrana2 

#include "cs392_midterm.h"


//This function compares two characters together 
//If s1 is less than s2 than -1 is returned 
//If s1 is equal to  s2 than 0 is returned 
//If s1 is greater than s2 than 1 is returned 
//The strings are compared based on their ASCII values 

int cs392_strcmp(char* s1, char* s2) {

  int index = 0; 

  while ((s1[index] != '\0') && (s2[index] != '\0')) {
    if ((s1[index] - '0') == (s2[index] - '0')) {
      index++;
    }

    else if ((s1[index] - '0') > (s2[index] - '0')) {
      return 1;
    }

    else {
      return -1;
    }
  }

  return 0;
 
}