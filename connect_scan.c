#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int id_scan(int sock_desc);

int connect_scan(char *target, int port, int ID_FLAG) {
    int sock_desc;
    if((sock_desc = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        {
            printf("Could not create socket.\n");
            exit(-1);
        }
    struct sockaddr_in server;
    //TODO: A handler for inputing both domain names and ip addresses
    //TODO: Handler for resolving to IPv6.
    server.sin_addr.s_addr = inet_addr(target);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    if(connect(sock_desc, (struct sockaddr *)&server, sizeof(server)) == -1) {
        close(sock_desc);
        return 0;
    }
    printf("%d\t", port);
    if(ID_FLAG == 1)
        id_scan(sock_desc);
    
    close(sock_desc);
    return 1;
}

int id_scan(int sock_desc) {
    char *message;
    message = "GET / HTTP/1.1\r\n\r\n";
    char *received[1024];

    if(send(sock_desc, message, strlen(message),0) == -1) {
        printf("ID failed.");
        return 0;
    }

    if(recv(sock_desc, received, 32, 0) == -1) {
        printf("ID failed.");
        return 0;
    }
    //printf("\t");
    printf("%s\n",received);
    return 1;
}
