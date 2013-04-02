#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>

#define THREADS_DEFAULT 20
#define PORTS_DEFAULT 10000

void usage();
void error(char *msg);
int connect_scan(char *target, int port, int i);

int main(int argc, char **argv) {
    if(argc < 3) usage();
    char *target = argv[1];
    int port_start = atoi(argv[2]);
    int port_end = atoi(argv[3]);

    printf("PORT\tSERVICE\n");
    for(int port = port_start; port <= port_end; port++)
        connect_scan(target, port, 1);

    //printf("\n");
    return 1;
}

void usage(){
    printf("Usage: ./portscan IPADDRESS INITIALPORT FINALPORT\n");
    exit(0);
}

void error(char *msg){
	perror(msg);
	exit(0);
}
