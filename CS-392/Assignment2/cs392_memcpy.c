//"I pledge my honor that I have abided by the Stevens Honor System" - Himanshu Rana 
//Author: Himanshu Rana - hrana2
#include "cs392_string.h"

//This function resembles that of the built-in funciton memcpy 
//where it copies a certain number of bytes of data from the memory pointed
//to by the src to the memory pointed to by dst
void *cs392_memcpy(void * dst, void * src, unsigned num) {
	int i = 0;

	//I am dereferencing the void pointers and doing a char casting 
	//so that the new variables will be able to handle any variable type 
	//since char is 1 byte
	char *char_dst = (char*)dst; 
	char *char_source = (char*)src; 

	//The while loop will loop through the src copying each byte
	//to the destination and will terminate when num reaches 0 
	while (num != 0)
	{
		char_dst[i] = char_source[i];
		i++;
		num--;
	}

	//Adding the null byte to the end of the destination 
	char_dst[i] = '\0';
	return dst;
}