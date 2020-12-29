//"I pledge my honor that I have abided by the Stevens Honor System" - Himanshu Rana - hrana2 

#include "cs392_signal.h"
#include <stdio.h>



void handler(int sigNum, siginfo_t *siginfo, void* ptr){
    if(sigNum == SIGINT){
        printf ("\nThe signal, ctrl + c, has been received. To exit, type 'exit'.\n");
    }
    if(sigNum == SIGTSTP){
        printf ("\nThe signal, ctrl + z, has been received. To exit, type 'exit'.\n");
    }
}

void sigHandler(){
    struct sigaction sigAct;
    memset(&sigAct, '\0', sizeof(sigAct));

   //setting all the flags and handlers 
    sigAct.sa_sigaction = &handler;
    sigAct.sa_flags = SA_SIGINFO;

    if(sigaction(SIGINT, &sigAct, NULL) < 0){
        perror("There was an error with sigaction");
        }
    if(sigaction(SIGTSTP, &sigAct, NULL) < 0){
        perror("There was an error with sigaction");
        }
}