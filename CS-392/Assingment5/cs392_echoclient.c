//"I pledge my honor that I have abided by the Stevens Honor System" - Himanshu Rana - hrana2 

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

int main(int argc, char** argv) {
    //if the user does not input three arguements then display an 
    //error message. 
    if(argc != 3){
        perror("wrong number of arguments given.\n");
        exit(EXIT_FAILURE);
    }

    int sock_num;
    struct sockaddr_in echoserver;
    //creating a buff_arr of size 0124 
    char buff_arr[1024];

    //This creates the socket. it has to IPv4
    if((sock_num = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == 0) {
        perror("there was an error while creating the socket.\n");
        exit(EXIT_FAILURE);
    }
    memset(&echoserver, 0, sizeof(echoserver));
    echoserver.sin_family = AF_INET;
    //gets the ip address
    echoserver.sin_addr.s_addr = inet_addr(argv[1]); 
    //this is the port
    echoserver.sin_port = htons(atoi(argv[2])); 
    
    //this is where the sockets connect 
    if(connect(sock_num, (struct sockaddr *) &echoserver, sizeof(echoserver)) < 0) {
        perror("there was an error while connecting.\n");
        exit(EXIT_FAILURE);
    } 
    else {
        printf("the connection has been established. the message to the server will be:\n");
        fgets(buff_arr, sizeof(buff_arr), stdin); 
        buff_arr[strlen(buff_arr)-1] = '\0'; 
        printf("sending message: %s\n", buff_arr);

        if(send(sock_num, buff_arr, strlen(buff_arr), 0) == -1){
            perror("there was an error while sending.\n");
            exit(EXIT_FAILURE);
        }
        memset(buff_arr, 0, sizeof(buff_arr)); 
        //this is used to receive the message to from the socket
        //and to handle if something goes wrong
        if(recv(sock_num, buff_arr, 1023, 0) == -1){
            perror("there was an error while recieving.\n");
            exit(EXIT_FAILURE);
        }
        //after the echo it will print out the message the user inputted 
        printf("the message has been recieved: %s\n", buff_arr); 
        fflush(stdout);
        //properly closes the socket
        close(sock_num); 
    }
    return 0; 
}