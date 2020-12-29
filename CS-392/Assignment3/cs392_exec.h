//"I pledge my honor that I have abided by the Stevens Honor System" - Himanshu Rana - hrana2 

#ifndef CS392_EXEC_H
#define CS392_EXEC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

char** eachWord(char* str);
void execCommand(char* str);


#endif