/*Author: Himanshu Rana - hrana2*/
/*"I pledge my honor that I have abided by the Stevens Honor System" - Himanshu Rana*/

#include <stdio.h>
#include <stdlib.h>

/*This function implements a version of the library function cat
by using malloc, fread, and fwrite functions.*/
void cat(FILE *fp) {
	int max_len = 1024;
	char *buffer = malloc(max_len*sizeof(char)); 
	if(!buffer) {
		perror("There is a malloc error.");
		exit(1);

	}
	//Used fwrite in order to handle .pcap files 
	while(fread(buffer, 1, max_len, fp)) {
		fwrite(buffer, 1, max_len, stdout);
	}
}


/*The main function handles error checking and proper closure of files.*/
int main(int argc, char** argv[]) {
	//Makes sure that there are only 2 arguements in the command line. 
	if(argc != 2) {
		perror("Usage: %s [input file]");
		exit(1); 
	}

	//Creates a file pointer to use when opening the file 
	FILE *fp; 
	char file[50]; 
	char *x; 
	fp = fopen(argv[1], "r"); 

	// printf("%s\n", argv[1]);

	//Gives an error if the pointer in null 
	if(fp == NULL) {
		perror("Error: This file can not be accessed."); 
		exit(1);
	}

	//Calls the cat function and properly closes all files that 
	//have been opened and cleans up. 
	cat(fp); 
	fclose(fp); 
	return 0; 

}
