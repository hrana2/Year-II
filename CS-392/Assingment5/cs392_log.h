//"I pledge my honor that I have abided by the Stevens Honor System" - Himanshu Rana - hrana2 

#ifndef CS392_LOG_H
#define CS392_LOG_H


#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <string.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <sys/wait.h>
#include <arpa/inet.h>


void cs392_socket_log(char* IP_add, int port_num);


#endif 