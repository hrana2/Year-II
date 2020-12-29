//"I pledge my honor that I have abided by the Stevens Honor System" - Himanshu Rana - hrana2 

#include <stdlib.h>
#include "cs392_exec.h"
#include "cs392_log.h"
#include "cs392_signal.h"


int main(){

    char buffer[256];
    int value;
   
    //while loop that will loop forever. 
    while(1) {
    	//calls sigHandler function and prints the standard 
    	//message to indicate that the user is in the shell.
    	//fflsuh is used because it forces a write of all 
    	//the user space buffered data. this will also 
    	//write to a new line. 
        sigHandler();
        printf("cs392_shell $: ");
        fflush(stdout);
        
     	//The read function will read upto the count byte 
     	//and store it into the buffer.
        if((value = read(0, buffer, 255)) < 0) {
        	//errno is a number set by the system that 
        	//corresponds to a type of error so that 
        	//we can know/find out what kind of error occured. 
            if(errno == EINTR){     
                continue;
            }
            //if the error does not equal eintr then we print 
            //an error message
            else {
                perror("There is an error while reading.\n");
                exit(1);
            }
        }
        
        buffer[value - 1] = '\0';
  
  		//calling the logging function to log to the text file 
  		//getting all the execution command that will be typed 
  		//in the command line.
        loggingCommnads(buffer);
        execCommand(buffer);
    }
    return 0;
}