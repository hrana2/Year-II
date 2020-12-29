//"I pledge my honor that I have abided by the Stevens Honor System" - Himanshu Rana 
//Himanshu Rana - hrana2 

#include "cs392_midterm.h"

//This function appends the src string to the dest string 
//It also overwrites the terminating null byte and appends 
//a null byte after terminating. 
char *cs392_strncat(char *dest, char *src, unsigned n) {
	int index = 0; 
	while(dest[index] != '\0') {
		index++; 
	}
	for(int i = 0; i < n; i++) {
		dest[index] = src[i]; 
		index++; 
	}
	dest[index] = '\0'; 

	return dest; 
}