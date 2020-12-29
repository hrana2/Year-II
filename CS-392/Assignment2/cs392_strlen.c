//"I pledge my honor that I have abided by the Stevens Honor System" - Himanshu Rana 
//Author: Himanshu Rana - hrana2

#include "cs392_string.h"

//This function resembles the library built-in function of strlen where
//it returns the length of a string 
unsigned cs392_strlen(char *str) {
	int length = 0;
	int i = 0;

	//The while loop will keep track of the length of the given string 
	//and will terminate when the string has reached the null byte 
	while (str[i] != '\0')
	{
		length++;
		i++;
	}
	return length;
	
	return 0; 
}