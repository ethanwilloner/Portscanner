#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>


/* Function prototypes */
int id_scan(int sock_desc);

int connect_scan(char *target, int port, int ID_FLAG) {

    // Create socket descriptor
    int sock_desc;

    // Set up socket and handle creation error
    if((sock_desc = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        {
            printf("Could not create socket.\n");
            exit(-1);
        }

    // Create socket address struct
    struct sockaddr_in server;

    // TODO: A handler for inputing both domain names and ip addresses
    // TODO: Handler for resolving to IPv6.

    // Sets up the values inside the newly created socket address struct
    server.sin_addr.s_addr = inet_addr(target);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    // Error handling for the connect() operation
    if(connect(sock_desc, (struct sockaddr *)&server, sizeof(server)) == -1) {
        close(sock_desc);
        return 0;
    }

    printf("%d\t", port);

    // Handls the ID_FLAG
    if(ID_FLAG == 1)
        id_scan(sock_desc);    
    close(sock_desc);
    return 1;
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
        printf("ID failed.");
        return 0;
    }

    // Error handling for the recv() function
    if(recv(sock_desc, received, 32, 0) == -1) {
        printf("ID failed.");
        return 0;
    }
    printf("%s\n",received);
    return 1;
}
