//"I pledge my honor that I have abided by the Stevens Honor System" - Himanshu Rana - hrana2 

#ifndef CS392_SIGNAL_H
#define CS392_SIGNAL_H

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

void handler(int sigNum, siginfo_t* siginfo, void* ptr);
void sigHandler();

#endif