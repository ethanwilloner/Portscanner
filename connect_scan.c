#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>
#include "scanner.h"

/* Function prototypes */
int id_scan(int sock_desc);
//int connect_scan(char *target, int port, bool ID_FLAG) {
void connect_scan(struct host *target) {
    // Create socket descriptor
    int sock_desc;
    // Set up socket and handle creation error
    if((sock_desc = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        {
            //printf("Could not create socket.\n");
            //target->active_threads--;
            return;
        }
    
    // Create socket address struct
    struct sockaddr_in server;

    // Sets up the values inside the newly created socket address struct
    server.sin_addr.s_addr = inet_addr(target->host);
    server.sin_family = AF_INET;
    server.sin_port = htons(target->curr_port);
    // Error handling for the connect() operation
    if(connect(sock_desc, (struct sockaddr *)&server, sizeof(server)) == -1) {
        //printf("Could not connect to host.\n");
        close(sock_desc);
        //target->active_threads--;
        return;
    }
    
    printf("%d\t", target->curr_port);

    // Handles the ID_FLAG
    if(target->ID == true)
        id_scan(sock_desc);
    else
        printf("OPEN\n");    
    close(sock_desc);
    //target->active_threads--;
    return;
}


/* Basic identification scan. Just sends a message and 
   prints some of the reply */
int id_scan(int sock_desc) {

    // The message to send through the connection
    char *message;

    // TODO: Create a way to send different data for better results 
    message = "GET / HTTP/1.1\r\n\r\n";
    char *received[1024];

    // Error handling for the send() function
    if(send(sock_desc, message, strlen(message),0) == -1) {
        printf("ID failed.\n");
        return 0;
    }

    // Error handling for the recv() function
    if(recv(sock_desc, received, 20, 0) == -1) {
        printf("ID failed.\n");
        return 0;
    }
    printf("%s\n",received);
    return 1;
}
