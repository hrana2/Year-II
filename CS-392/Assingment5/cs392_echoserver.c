//"I pledge my honor that I have abided by the Stevens Honor System" - Himanshu Rana - hrana2 


#define MAXPENDING 5 

#include "cs392_log.h"

int main(int argc, char** argv) {
    //the user has to input two arguements and if they 
    //dont then an error message is displayed.
    if(argc != 2) {
        perror("wrong number of arguments given.\n");
        exit(EXIT_FAILURE);
    }

    int server_sock, client_sock;
    char buff_arr[1024];  
    struct sockaddr_in echoserver, echoclient;
    int client_len = sizeof(struct sockaddr_in);

    //this creates the socket. it has to be IPv4 
    if((server_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1){
        perror("there was an error while creating the socket\n");
        exit(EXIT_FAILURE);
    }
    memset(&echoserver, 0, sizeof(echoserver));
    echoserver.sin_family = AF_INET;
    echoserver.sin_addr.s_addr = htonl(INADDR_ANY);
    //this gets the serverport 
    echoserver.sin_port = htons(atoi(argv[1])); 

    //by using the bind function we are binding the socket to the port 
    if(bind(server_sock, (struct sockaddr*) &echoserver, sizeof(echoserver)) < 0){
        perror("Bind failure. Exiting...\n");
        exit(EXIT_FAILURE);
    }
    //this limits the amount of clients that can connect to the server to 5 
    if (listen(server_sock, MAXPENDING) != 0) { 
        perror("an error occrred, sorry.\n");
        exit(EXIT_FAILURE);
    } 
    else {
        printf("listening for message\n");
    }
    client_len = sizeof(struct sockaddr_in);
    while(1) {
        if((client_sock = accept(server_sock, (struct sockaddr *) &echoclient, &client_len)) == -1) {
            perror("there was an error while accepting\n");
            exit(EXIT_FAILURE);
        } 
        else { 
            //computing IP address to binary 
            printf("the client is connected. IP address: %s, port number: %d\n", inet_ntoa(echoclient.sin_addr), ntohs(echoclient.sin_port));
            fflush(stdout);
            //this logs the ip address and port number
            cs392_socket_log(inet_ntoa(echoclient.sin_addr), ntohs(echoclient.sin_port));  
            memset(buff_arr, 0, sizeof(buff_arr));
            //this is used to receive the message to from the socket
            //and to handle if something goes wrong
            if(recv(client_sock, buff_arr, 1023, 0) == -1){
                perror("there was an error while recieving.\n");
                exit(EXIT_FAILURE);
            }
            //this is where the message is sent back to the client 
            if(send(client_sock, buff_arr, strlen(buff_arr), 0) == -1){
                perror("there was an error while sending.\n");
                exit(EXIT_FAILURE);
            }
            printf("sent message: %s\n", buff_arr); 
            //properly closes the socket after one message has been recieved
            close(client_sock);  
        }
    }
    return 0;
}
