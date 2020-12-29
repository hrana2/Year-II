//"I pledge my honor that I have abided by the Stevens Honor System" - Himanshu Rana - hrana2 


#include "cs392_log.h"
void loggingCommnads(char* str) {
	//creating a file pointer and using fopen to open the 
	//cs392_shell.log file with type "a" so that you can 
	//write to this file. This will also create the log 
	//file if it is not already created in the working directory. 
    FILE *fp;
    fp = fopen("cs392_shell.log", "a");
    //if the pointer is NULL than an error 
    //message is displayed. 
    if(fp == NULL) {
        perror("Cannot open file.\n");
    } 
    //Prints the command to the log file
    else {
        fprintf(fp, "%s\n", str);
    }
    //Properly closes the file 
    fclose(fp);
}