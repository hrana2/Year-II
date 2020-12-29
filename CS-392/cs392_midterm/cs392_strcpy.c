//"I pledge my honor that I have abided by the Stevens Honor System" - Himanshu Rana 
//Himanshu Rana - hrana2 

#include "cs392_midterm.h"


//This function copies one string to another. 
//We loop through the first string until we reach the null byte
//Along the way copying each byte from one string to another and incrementing 
//Finally returning the string once the null byte is reach signifying the end of the string 
char* cs392_strcpy(char* dest, char* src) {
	int index = 0;

	while (src[index] != '\0')
	{
		dest[index] = src[index];
		index++;
	}

	dest[index] = '\0';
	return dest;
}