//"I pledge my honor that I have abided by the Stevens Honor System" - Himanshu Rana - hrana2 


#include "cs392_log.h"

void cs392_socket_log(char* IP_add, int port_num) {
    //using fopen with the a attachment so that if the 
    //file does not already exsist, it creates it first 
    //and then lets us write to the file
    FILE *fp = fopen("cs392_socket.log", "a");
    if(fp == NULL) {
        perror("there was an error while creating/loading the file.\n");
        exit(1);
    } 
    else {
        fprintf(fp,"ip address: %s, port number: %d\n", IP_add, port_num);
    }
    //properly closes the file
    fclose(fp);
}